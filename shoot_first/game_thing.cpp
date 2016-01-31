#include "game_thing.hpp"

#include "game.hpp"

GameThing::GameThing(Game* game){
	this->my = nullptr;
	this->area = AreaF(0.0f, 0.0f, 0.0f, 0.0f);
	this->game = game;
	body = nullptr;
}

Camera2D GameThing::getCamera()const{ return game->getCamera(); }

void GameThing::createBody(const SizeF& size, b2BodyType btype, unsigned short bits, unsigned short colliders, bool is_sensor){
	this->data.bits = bits;
	this->data.thing = this;

	b2BodyDef bdef;
	bdef.type = btype;
	bdef.userData = &this->data;
	this->body = this->game->getWorld()->CreateBody(&bdef);

	b2PolygonShape bshape;
	bshape.SetAsBox(size.getWidth() / 2, size.getHeight() / 2);

	b2FixtureDef fdef;
	fdef.isSensor = is_sensor;
	fdef.friction = 0.0f;
	fdef.shape = &bshape;
	fdef.filter.categoryBits = bits;
	fdef.filter.maskBits = colliders;
	this->body->CreateFixture(&fdef);
}

void GameThing::destroyBody(){
	if (body != nullptr){
		game->getWorld()->DestroyBody(body);
		body = nullptr;
	}
}