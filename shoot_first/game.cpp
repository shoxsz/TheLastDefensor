#include "game.hpp"

#include "random.hpp"
#include "game_textures.hpp"
#include "boost.hpp"

void Game::pre(){
	camera.set(50, 50);
	painter.setCamera(camera);

	glClearColor(0.50, 0.50, 0.50, 1.0f);

	Random::genSeed();
	
	/*create the world with no gravity*/
	world = new b2World(b2Vec2(0.0f, 0.0f));
	world->SetContactListener(this);
	world->SetContactFilter(this);

	/*Create world bounds*/
	b2Vec2 vertices[] = { b2Vec2(camera.getLeft(), camera.getTop()), b2Vec2(camera.getRight(), camera.getTop()),
						  b2Vec2(camera.getRight(), camera.getBottom()), b2Vec2(camera.getLeft(), camera.getBottom())};

	b2BodyDef bdef;
	bdef.type = b2_staticBody;
	world_bounds = world->CreateBody(&bdef);

	b2ChainShape cshape;
	cshape.CreateLoop(vertices, 4);

	b2FixtureDef fdef;
	fdef.shape = &cshape;
	fdef.friction = 0.0f;
	fdef.filter.categoryBits = SCENARIO;

	world_bounds->CreateFixture(&fdef);

	/*textures*/
	GameTextures::textureAtlas = loadTexture("images\\images.png");
	GameTextures::life_bar = new TextureRegion(GameTextures::textureAtlas, 0, 224, 1, 5);
	GameTextures::black_bar = new TextureRegion(GameTextures::textureAtlas, 1, 224, 1, 5);
	GameTextures::gray_bar = new TextureRegion(GameTextures::textureAtlas, 2, 224, 1, 5);
	GameTextures::simple_bullet = new TextureRegion(GameTextures::textureAtlas, 64, 192, 32, 32);
	GameTextures::speed_boost = new TextureRegion(GameTextures::textureAtlas, 96, 196, 32, 32);
	GameTextures::defense_boost = new TextureRegion(GameTextures::textureAtlas, 0, 192, 32, 32);
	GameTextures::life_boost = new TextureRegion(GameTextures::textureAtlas, 32, 192, 32, 32);
	GameTextures::soldier = new TextureRegion(GameTextures::textureAtlas, 0, 0, 128, 128);
	GameTextures::tank = new TextureRegion(GameTextures::textureAtlas, 0, 128, 128, 64);

	/*players*/
	p1 = new Soldier(this, FIGHTER1, {SDLK_UP,
							 SDLK_DOWN,
							 SDLK_LEFT,
							 SDLK_RIGHT,
							 SDLK_m,
							 SDLK_m
					});

	p2 = new Soldier(this, FIGHTER2, {SDLK_w,
							 SDLK_s,
							 SDLK_a,
							 SDLK_d,
							 SDLK_q,
							 SDLK_e
					});

	p1->setEnemy(p2);
	p2->setEnemy(p1);

	tank1 = new Tank(this, p1);
	tank1->setEnemy(p2);

	tank2 = new Tank(this, p2);
	tank2->setEnemy(p1);

	p1->setTank(tank1);
	p2->setTank(tank2);

	start();
}

#include <iostream>

void Game::process(SDL_Event* event){
	switch (event->type){
	case SDL_QUIT:
		running = false;
		break;
	case SDL_WINDOWEVENT:
		if (event->window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
			glViewport(0, 0, event->window.data1, event->window.data2);
		break;
	case SDL_KEYDOWN:
		p1->keyDown(&event->key);
		p2->keyDown(&event->key);
		break;
	case SDL_KEYUP:
		p1->keyUp(&event->key);
		p2->keyUp(&event->key);
		break;
	}
}

void Game::logics(){
	if (boost_t.compare(to_next_boost)){
		TimedBoostItem* t = new TimedBoostItem(this);

		t->start();
		boosts.push_back(t);
		to_next_boost = Random::genUInteger(5000, 20000);
	}

	for (unsigned int i = 0; i < boosts.size(); i++){
		TimedBoostItem* t = boosts[i];

		t->calculate();

		if (t->getTState() == ENDED){
			boosts.erase(boosts.begin() + i);
			i--;
			delete t;
		}
	}

	tank1->calculate();
	tank2->calculate();

	p1->calculate();
	if (p1t.isRunning()){
		if (p1t.compare(5000)){
			preparePlayer(p1);
			tank1->setTankState(INVULNERABLE);
		}
	}else if (p1->getState() == DEAD){
		setToSleep(p1);
		tank1->setTankState(VULNERABLE);
	}

	p2->calculate();
	if (p2t.isRunning()){
		if (p2t.compare(5000)){
			preparePlayer(p2);
			tank2->setTankState(INVULNERABLE);
		}
	}else if (p2->getState() == DEAD){
		setToSleep(p2);
		tank2->setTankState(VULNERABLE);
	}

	if (tank1->getState() == DEAD && tank2->getState() == DEAD){
		SDL_ShowSimpleMessageBox(SDL_MessageBoxFlags::SDL_MESSAGEBOX_INFORMATION, "Fim!", "Empate!", NULL);
		start();
	}
	else if(tank1->getState() == DEAD){
		SDL_ShowSimpleMessageBox(SDL_MessageBoxFlags::SDL_MESSAGEBOX_INFORMATION, "Fim!", "Player 2 destruiu o tank!", NULL);
		start();
	}else if (tank2->getState() == DEAD){
		SDL_ShowSimpleMessageBox(SDL_MessageBoxFlags::SDL_MESSAGEBOX_INFORMATION, "Fim!", "Player 1 destruiu o tank!", NULL);
		start();
	}


	world->Step(1.0f / 40.0f, 1, 1);
}

void Game::render(){
	/*draw background*/

	painter.begin(GameTextures::textureAtlas);

	for (TimedBoostItem* t : boosts){
		t->render(&painter);
	}

	p1->render(&painter);
	p2->render(&painter);
	tank1->render(&painter);
	tank2->render(&painter);
	painter.end();
	/*draw HUD*/
}

void Game::pos(){
	delete tank1;
	delete tank2;
	delete p1;
	delete p2;

	delete GameTextures::simple_bullet;
	delete GameTextures::speed_boost;
	delete GameTextures::defense_boost;
	delete GameTextures::life_boost;
	delete GameTextures::soldier;
	delete GameTextures::tank;
}

bool Game::active(){
	return running;
}

Camera2D Game::getCamera()const{
	return camera;
}

void Game::start(){
	preparePlayer(p1);
	preparePlayer(p2);

	tank1->load();
	tank1->setPosition(PointF(10.0f, 17.0f));

	tank2->load();
	tank2->setPosition(PointF(-10.0f, -17.0f));

	running = true;

	to_next_boost = Random::genUInteger(5000, 20000);

	world->ClearForces();

	boost_t.start();
}

void Game::preparePlayer(Soldier* soldier){
	soldier->unload();
	soldier->load();
	if (soldier->getCategory() == FIGHTER2){
		p2t.stop();
	}
	else{
		p1t.stop();
	}

	soldier->setPosition(
		PointF(
		Random::genInteger(camera.getLeft() + soldier->getArea().getWidth() / 2.0f, camera.getRight() - soldier->getArea().getWidth() / 2.0f),
		Random::genInteger(-17 + soldier->getArea().getHeight() / 2.0f, 17 + soldier->getArea().getHeight() / 2.0f)));
}

void Game::setToSleep(Soldier* soldier){
	soldier->unload();
	soldier->getMachineGun()->stopShooting();
	if (soldier->getCategory() == FIGHTER2){
		p2t.start();
	}
	else{
		p1t.start();
	}
}


void Game::BeginContact(b2Contact* contact){
	b2Body* a = contact->GetFixtureA()->GetBody();
	b2Body* b = contact->GetFixtureB()->GetBody();
	GameData* gdata_a = (GameData*)a->GetUserData();
	GameData* gdata_b = (GameData*)b->GetUserData();

	if (gdata_a != nullptr)
		gdata_a->thing->onCollide(gdata_b);
	
	if (gdata_b != nullptr)
		gdata_b->thing->onCollide(gdata_a);
}

void Game::EndContact(b2Contact* contact){

}

bool Game::ShouldCollide(b2Fixture* fixtureA, b2Fixture* fixtureB){
	b2Body* a = fixtureA->GetBody();
	b2Body* b = fixtureB->GetBody();
	GameData* gdata_a = (GameData*)a->GetUserData();
	GameData* gdata_b = (GameData*)b->GetUserData();

	if (gdata_b != nullptr && gdata_a != nullptr){
		if (gdata_a->bits == BULLET){
			/*avoid bullet collision with its shooter and TIMED_BOOST_ITEM(bit masks is not working :s)*/
			if (gdata_b->thing == ((Bullet*)gdata_a->thing)->getShooter() || gdata_b->bits == TIMED_BOOST_ITEM){
				return false;
			}
		}
		else if (gdata_b->bits == BULLET){
			if (gdata_a->thing == ((Bullet*)gdata_b->thing)->getShooter() || gdata_a->bits == TIMED_BOOST_ITEM){
				return false;
			}
		}
	}

	return true;
}