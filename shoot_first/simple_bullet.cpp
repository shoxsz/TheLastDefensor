#include "simple_bullet.hpp"

#include "fighter.hpp"
#include "tank.hpp"

void SimpleBullet::load(){
	PointF bpos;
	AreaF area = shooter->getArea();

	state = STATE::WALKING;
	
	this->createBody(SizeF(1.0f, 1.0f), b2_dynamicBody, BULLET, shooter->getEnemyCategory() | TANK | SCENARIO, false);

	switch (shooter->getFaceDirection()){
	case UP:
		angle = 90.0f;
		bpos = PointF(area.getX() + area.getWidth() / 2, area.getY() + area.getHeight() + 0.5f);
		body->SetLinearVelocity(b2Vec2(0.0f, 50.0f));
		break;
	case DOWN:
		angle = 270.0f;
		bpos = PointF(area.getX() + area.getWidth() / 2, area.getY() - 0.5f);
		body->SetLinearVelocity(b2Vec2(0.0f, -50.0f));
		break;
	case LEFT:
		angle = 180.0f;
		bpos = PointF(area.getX() - 0.5f, area.getY() + area.getHeight() / 2);
		body->SetLinearVelocity(b2Vec2(-50.0f, 0.0f));
		break;
	case RIGHT:
		angle = 0.0f;
		bpos = PointF(area.getX() + area.getWidth() + 0.5f, area.getY() + area.getHeight() / 2);
		body->SetLinearVelocity(b2Vec2(50.0f, 0.0f));
		break;
	}

	setPosition(bpos);
	this->area = AreaF(bpos.getX() - 0.5f, bpos.getY() - 0.5f, 1.0f, 1.0f);
}

void SimpleBullet::calculate(){
	area.setX(body->GetPosition().x - 0.5f);
	area.setY(body->GetPosition().y - 0.5f);
}

void SimpleBullet::render(Painter* painter){
	painter->drawTexture(my, area, angle);
}

void SimpleBullet::onCollide(GameData* g){
	if (g != nullptr){
		if (g->bits == shooter->getEnemyCategory()){
			if (g->thing != this->shooter){
				((Fighter*)g->thing)->setDamage(this->damage);
			}
		}
		else if (g->bits == TANK){
			if (((Tank*)g->thing)->getDefensor() != shooter && ((Tank*)g->thing)->getTankState() == TANK_STATE::VULNERABLE){
				((Tank*)g->thing)->setDamage(damage);
			}
		}
	}

	state = DEAD;
}