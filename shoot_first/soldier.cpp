#include "soldier.hpp"

#include "game_textures.hpp"

Soldier::Soldier(Game* game, unsigned short category, ControlKeys controls) : Fighter(game, category){
	this->mgun = nullptr;
	this->control_keys = controls;
	this->my = GameTextures::soldier;
}

void Soldier::load(){
	if (mgun == nullptr){
		mgun = new MachineGun(this);
	}
	else{
		mgun->freeBullets();
	}

	/*set default bullets*/
	SimpleBullet* sb = new SimpleBullet(this);
	mgun->charge(sb);
	delete sb;

	my = GameTextures::soldier;
	direction = DOWN;
	state = STOPPED;
	area.setWidth(3.0f);
	area.setHeight(3.0f);
	speed = c_speed = 1.0f;
	setDefense(1.0f);
	setLife(1.0f);
	points = 0;

	if (body == nullptr)
		this->createBody(SizeF(area.getWidth(), area.getHeight()), b2BodyType::b2_dynamicBody, category, getEnemyCategory() | BULLET | TANK | TIMED_BOOST_ITEM | SCENARIO, false);
}

void Soldier::calculate(){
	/*calculate bullets*/
	mgun->calculate();

	/*calculate effects*/
	for (unsigned int i = 0; i < effects.size(); i++){
		Effect* e = effects[i];
		e->calculate();

		if (e->getTState() == TIMER_STATE::ENDED){
			effects.erase(effects.begin() + i);
			delete e;
		}
	}

	calculateFaceDirection();

	if (state != DEAD){
		/*update position*/
		area.setX(body->GetPosition().x - area.getWidth() / 2);
		area.setY(body->GetPosition().y - area.getHeight() / 2);
	}
}

void Soldier::render(Painter* painter){
	mgun->render(painter);

	if (state != DEAD){
		painter->drawTexture(GameTextures::life_bar, AreaF(area.getX(), area.getY() + area.getHeight() + 0.5f, area.getWidth() * clife, 1.0f));

		if (clife < 1.0f){
			painter->drawTexture(GameTextures::black_bar, AreaF(area.getX() + area.getWidth() * clife, area.getY() + area.getHeight() + 0.5f, area.getWidth() - area.getWidth() * clife, 1.0f));
		}

		switch (face_direction){
		case UP:
			painter->drawTexture(my, area, 0.0f);
			break;
		case DOWN:
			painter->drawTexture(my, area, 180.0f);
			break;
		case LEFT:
			painter->drawTexture(my, area, 90.0f);
			break;
		case RIGHT:
			painter->drawTexture(my, area, 270.0f);
			break;
		}
	}
	else{
		painter->drawTexture(GameTextures::black_bar, area);
	}
}

void Soldier::unload(){
	destroyBody();

	for (Effect* e : effects){
		delete e;
	}
	
	effects.clear();
}

void Soldier::calculateFaceDirection(){
	float dx, dy, x, y, r, b;

	if (enemy->getState() != DEAD){
		x = enemy->getPosition().getX();
		y = enemy->getPosition().getY();
		r = enemy->getArea().getRight();
		b = enemy->getArea().getBottom();
	}
	else{
		x = ((Soldier*)enemy)->getTank()->getPosition().getX();
		y = ((Soldier*)enemy)->getTank()->getPosition().getY();
		r = ((Soldier*)enemy)->getTank()->getArea().getRight();
		b = ((Soldier*)enemy)->getTank()->getArea().getBottom();
	}

	dx = area.getX() - x;
	dy = area.getY() - y;

	if ((dx >= 0 && dy >= 0)){
		if (r < area.getX() && b < area.getY()){
			if (direction == RIGHT || direction == LEFT){
				face_direction = DOWN;
			}
			else{
				face_direction = LEFT;
			}
		}
		else if(r > area.getX()){
			face_direction = DOWN;
		}
		else/*b > area.getBottom()*/{
			face_direction = LEFT;
		}
	}
	else if ((dx < 0 && dy >= 0)){
		if (x > area.getRight() && b < area.getY()){
			if (direction == RIGHT || direction == LEFT){
				face_direction = DOWN;
			}
			else{
				face_direction = RIGHT;
			}
		}
		else if (x < area.getRight()){
			face_direction = DOWN;
		}
		else/*b > area.getBottom()*/{
			face_direction = RIGHT;
		}
	}
	else if (dx < 0 && dy <= 0){
		if (x > area.getRight() && y > area.getBottom()){
			if (direction == RIGHT || direction == LEFT){
				face_direction = UP;
			}
			else{
				face_direction = RIGHT;
			}
		}
		else if (x < area.getRight()){
			face_direction = UP;
		}
		else/*y < area.getBottom()*/{
			face_direction = RIGHT;
		}
	}
	else if (dx >= 0 && dy <= 0){
		if (r < area.getX() && y > area.getBottom()){
			if (direction == RIGHT || direction == LEFT){
				face_direction = UP;
			}
			else{
				face_direction = LEFT;
			}
		}
		else if (r > area.getX()){
			face_direction = UP;
		}
		else/*y < area.getBottom()*/{
			face_direction = LEFT;
		}
	}
}

void Soldier::keyDown(SDL_KeyboardEvent* event){
	SDL_Keycode key = event->keysym.sym;

	if (state == DEAD)
		return;

	if (key == control_keys.up){
		direction = UP;
		state = WALKING;
		body->SetLinearVelocity(b2Vec2(0.0f, 30.0f * c_speed));
	}
	else if (key == control_keys.down){
		direction = DOWN;
		state = WALKING;
		body->SetLinearVelocity(b2Vec2(0.0, -30.0f * c_speed));
	}
	else if (key == control_keys.left){
		direction = LEFT;
		state = WALKING;
		body->SetLinearVelocity(b2Vec2(-30.0f * c_speed, 0.0f));
	}
	else if (key == control_keys.right){
		direction = RIGHT;
		state = WALKING;
		body->SetLinearVelocity(b2Vec2(30.0f * c_speed, 0.0f));
	}
	else if (key == control_keys.shoot){
		mgun->startShooting();
	}
}

void Soldier::keyUp(SDL_KeyboardEvent* event){
	SDL_Keycode key = event->keysym.sym;

		if (state == DEAD)
			return;

	if (key == control_keys.up){
		if (state == WALKING && direction == UP){
			state = STOPPED;
			body->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
		}
	}
	else if (key == control_keys.down){
		if (state == WALKING && direction == DOWN){
			state = STOPPED;
			body->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
		}
	}
	else if (key == control_keys.left){
		if (state == WALKING && direction == LEFT){
			state = STOPPED;
			body->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
		}
	}
	else if (key == control_keys.right){
		if (state == WALKING && direction == RIGHT){
			state = STOPPED;
			body->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
		}
	}
	else if (key == control_keys.shoot){
		mgun->stopShooting();
	}
}