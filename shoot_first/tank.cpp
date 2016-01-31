#include "tank.hpp"
#include "game_textures.hpp"

Tank::Tank(Game* game, Fighter* defensor) : Fighter(game, defensor->getCategory()){
	this->defensor = defensor;
	mgun = nullptr;
	my = GameTextures::tank;
}

void Tank::load(){
	if (mgun == nullptr)
		mgun = new MachineGun(defensor);

	clife = life = 1.0f;
	cdefense = defense = 40.0f;
	setTankState(INVULNERABLE);
	setState(STOPPED);

	area.setWidth(19.75f);
	area.setHeight(9.25f);

	if (body == nullptr)
		this->createBody(SizeF(area.getWidth(), area.getHeight()), b2_kinematicBody, TANK, TIMED_BOOST_ITEM |FIGHTER1 | FIGHTER2 | BULLET | TANK, false);
}

void Tank::calculate(){
	area.setX(body->GetPosition().x - area.getWidth() / 2);
	area.setY(body->GetPosition().y - area.getHeight() / 2);
}

void Tank::render(Painter* painter){
	/*paint life bar*/
	painter->drawTexture((tstate == VULNERABLE ? GameTextures::life_bar : GameTextures::gray_bar), AreaF(area.getX(), area.getY() + area.getHeight() + 0.5f, area.getWidth() * clife, 1.0f));

	if (clife < 1.0f){
		painter->drawTexture(GameTextures::black_bar, AreaF(area.getX() + area.getWidth() * clife, area.getY() + area.getHeight() + 0.5f, area.getWidth() - area.getWidth() * clife, 1.0f));
	}

	painter->drawTexture(my, area);
}

void Tank::erase(){
	delete mgun;
}

void Tank::setTankState(TANK_STATE state){
	this->tstate = state;
}