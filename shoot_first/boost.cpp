#include "boost.hpp"

#include "random.hpp"

void Boost::load(){
	switch (btype){
	case BOOST_TYPE::SPEED:
		speed();
		ttl = 10000;
		break;
	case BOOST_TYPE::DEFENSE:
		defense();
		ttl = 15000;
		break;
	case BOOST_TYPE::LIFE:
		life();
		ttl = 0;
		break;
	}
}

void Boost::onEnd(){
	switch (btype){
	case BOOST_TYPE::SPEED:
		target->addSpeed(-added);
	break;
	case BOOST_TYPE::DEFENSE:
		target->addDefense(-added);
		break;
	}
}

void Boost::speed(){
	if (target->getCurrentSpeed() < 2.0f){
		added = target->getSpeed() * 0.5f;
		target->addSpeed(added);
	}
}

void Boost::defense(){
	if (target->getCurrentDefense() > target->getDefense())
		return;

	added = target->getCurrentDefense() * 0.3f;
	target->addDefense(added);
}

void Boost::life(){
	float life = target->getLife();
	float nlife = life * 0.2f;
	if (target->getCurrentLife() + nlife > life)
		target->addLife(life - target->getLife());
	else
		target->addLife(nlife);
}

void TimedBoostItem::load(){
	/*generate random position*/

	this->createBody(SizeF(TIMED_BOOST_SIZE, TIMED_BOOST_SIZE), b2_dynamicBody, TIMED_BOOST_ITEM, TANK |FIGHTER1 | FIGHTER2, true);

	setPosition(
		PointF(
		Random::genInteger(game->camera.getLeft() + TIMED_BOOST_SIZE / 2.0f, game->camera.getRight() - TIMED_BOOST_SIZE / 2.0f),
		Random::genInteger(game->camera.getBottom() + TIMED_BOOST_SIZE / 2.0f, game->camera.getTop() - TIMED_BOOST_SIZE / 2.0f)));

	unsigned int t = Random::genUInteger(1, 3);

	/*!!PROBLEM!!*/
	if (t == 1){
		boost = new Boost(game->p1, Boost::BOOST_TYPE::SPEED);
		my = GameTextures::speed_boost;
	}
	else if (t == 2){
		boost = new Boost(game->p1, Boost::BOOST_TYPE::DEFENSE);
		my = GameTextures::defense_boost;
	}
	else if (t == 3){
		boost = new Boost(game->p1, Boost::BOOST_TYPE::LIFE);
		my = GameTextures::life_boost;
	}

	ttl = 10000;

	area = AreaF(body->GetPosition().x - TIMED_BOOST_SIZE / 2, body->GetPosition().y - TIMED_BOOST_SIZE / 2, TIMED_BOOST_SIZE, TIMED_BOOST_SIZE);
}

void TimedBoostItem::step(){
	area.setX(body->GetPosition().x - TIMED_BOOST_SIZE / 2);
	area.setY (body->GetPosition().y - TIMED_BOOST_SIZE / 2);
}

void TimedBoostItem::render(Painter* painter){
	painter->drawTexture(my, area);
}

void TimedBoostItem::onCollide(GameData* g){
	/*avoid two players from getting the same object*/
	if (this->t_state != ENDED)
	if (g != nullptr && (g->bits ==  FIGHTER1 || g->bits == FIGHTER2)){
		boost->setTarget((Soldier*)g->thing);
		((Soldier*)g->thing)->addEffect(boost);
		boost->start();
		end();
	}
}
