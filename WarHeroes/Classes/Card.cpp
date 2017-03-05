#include "Card.h"

#include "Deck.h"
#include <sstream>

USING_NS_CC;

using namespace cocos2d::ui;

Card* Card::create(cardName cardID)
{

	std::stringstream ss;
	ss << "Card_S_" << cardID << ".png";
	
	std::string str = ss.str();
	
	Card* pSprite = new Card();


	if (pSprite->initWithFile(str.c_str()))
	{
		pSprite->ID = cardID;
		pSprite->cardInit();
		pSprite->autorelease();

		return pSprite;
	}

	CC_SAFE_DELETE(pSprite);
	return NULL;
}
void Card::cardInit()
{
	active = 1;
	switch (ID)
	{
	case KNIGHT:
		manaCost = 0;
		goldCost = 5;
		attack = 5;
		health = 5;
		//ability = "Lads"; // Lads
		type = CLASS_CAVALERY;
	    break;
	case SQUIRE:
		manaCost = 0;
		goldCost = 2;
		attack = 2;
		health = 2;
		type = CLASS_INFANTRY;
		//ability = "Lads"; //Lads
		break;
	case LONGBOWMAN:
		manaCost = 0;
		goldCost = 4;
		attack = 3;
		health = 4;
		//ability = "No_retal";
		type = CLASS_ARCHER;
		break;
	case SPEARMAN:
		manaCost = 0;
		goldCost = 3;
		attack = 2;
		health = 3;
		//ability = "Anti_Cavalry|Defender";
		type = CLASS_INFANTRY;
		break;
	case SORCERER_APPRENTICE:
		manaCost = 2;
		goldCost = 1;
		attack = 4;
		health = 3;
		type = CLASS_CASTER;
		break;
	case MILITIAN:
		manaCost = 0;
		goldCost = 2;
		attack = 2;
		health = 2;
		//ability = "Defender";
		type = CLASS_INFANTRY;
		break;
	case GOBLIN:
		manaCost = 0;
		goldCost = 2;
		attack = 2;
		health = 2;
		type = CLASS_INFANTRY;
		break;
	case PYROMANCERR:
		manaCost = 0;
		goldCost = 5;
		attack = 5;
		health = 3;
		type = CLASS_INFANTRY;
		break;
	case DIREWOLF:
		manaCost = 0;
		goldCost = 4;
		attack = 5;
		health = 2;
		type = CLASS_CAVALERY;
		break;
	case ALPHAWOLF:
		manaCost = 0;
		goldCost = 6;
		attack = 5;
		health = 5;
		//ability = "Leader";
		type = CLASS_CAVALERY;
		break;
	case WOLF:
		manaCost = 0;
		goldCost = 2;
		attack = 3;
		health = 2;
		type = CLASS_CAVALERY;
		break;
	case WOLF_RIDER:
		manaCost = 0;
		goldCost = 5;
		attack = 5;
		health = 5;
		type = CLASS_CAVALERY;
		break;
	case VIKING:
		manaCost = 0;
		goldCost = 6;
		attack = 6;
		health = 5;
		type = CLASS_INFANTRY;
		break;
	case THIEF:
		manaCost = 0;
		goldCost = 2;
		attack = 3;
		health = 2;
		type = CLASS_INFANTRY;
		break;
	case TREBUCHET:
		manaCost = 0;
		goldCost = 7;
		attack = 10;
		health = 3;
		//ability = "CAN'T_ATTACK_CREATURE";
		type = CLASS_SIEGE;
		break;
	case SORCERER:
		manaCost = 3;
		goldCost = 2;
		attack = 5;
		health = 4;
		type = CLASS_CASTER;
		break;
	case MAGE:
		manaCost = 3;
		goldCost = 1;
		attack = 5;
		health = 3;
		type = CLASS_CASTER;
		break;
	case WIZARD:
		manaCost = 4;
		goldCost = 1;
		attack = 6;
		health = 3;
		type = CLASS_CASTER;
		break;
	case MEDIC:
		manaCost = 0;
		goldCost = 0;
		attack = 0;
		health = 0;
		type = CLASS_SUPPORT;
		break;
	case PRIEST:
		manaCost = 0;
		goldCost = 0;
		attack = 0;
		health = 0;
		type = CLASS_CASTER;
		break;
	case SUMMONER:
		manaCost = 3;
		goldCost = 2;
		attack = 5;
		health = 3;
		type = CLASS_CASTER;
		break;
	case PHALAX:
		manaCost = 0;
		goldCost = 4;
		attack = 3;
		health = 5;
		//ability = "Defender";
		type = CLASS_INFANTRY;
		break;
	case MERCENARY:
		manaCost = 0;
		goldCost = 4;
		attack = 3;
		health = 7;
		//ability = "Defender|DecreaseIncome";
		type = CLASS_INFANTRY;
		break;
	case TACTICIAN:
		manaCost = 0;
		goldCost = 4;
		attack = 3;
		health = 6;
		//ability = "Defender";
		type = CLASS_SUPPORT;
		break;
	case FIRST_AID:
		manaCost = 3;
		goldCost = 0;
		attack = 0;
		health = 2;
		type = CLASS_SPELL;
		break;
	case PLAGUE:			//change
		manaCost = 3;
		goldCost = 0;
		attack = 0;
		health = 0;
		break;
	case FIREBALL:
		manaCost = 4;
		goldCost = 0;
		attack = 5;
		health = 0;
		type = CLASS_SPELL;
		break;
	case COMMAND_PROMOTE:
		manaCost = 4;
		goldCost = 0;
		attack = 0;
		health = 0;
		//ability = "Promote";
		type = CLASS_SPELL;
		break;
	case COMMAND_SHIELD:			//maybe change
		manaCost = 4;
		goldCost = 0;
		attack = 0;
		health = 0;
		//ability = "Armor";
		type = CLASS_SPELL;
		break;
	case COMMAND_SWORD:
		manaCost = 4;
		goldCost = 0;
		attack = 0;
		health = 0;
		//ability = "Attack";
		type = CLASS_SPELL;
		break;
	case COMMAND_VOLLEY:
		manaCost = 3;
		goldCost = 0;
		attack = 1;
		health = 0;
		//ability = "ATTACK ALL";
		type = CLASS_SPELL;
		break;
	case RATS:				//change
		manaCost = 0;
		goldCost = 0;
		attack = 0;
		health = 0;
		break;
	case BLESSING:
		manaCost = 2;
		goldCost = 0;
		attack = -1;
		health = 0;
		//ability = "Attack++";
		type = CLASS_SPELL;
		break;
	case CHOSEN_ONE:			
		manaCost = 6;
		goldCost = 0;
		attack = 0;
		health = 0;
		//ability = "IMUNE|UNSTOPPABLE";
		type = CLASS_SPELL;
		break;
	case EARTHQUAKE:		
		manaCost = 3;
		goldCost = 0;
		attack = 2;
		health = 0;
		//ability = ""; //resources
		type = CLASS_SPELL;
		break;
	default:
		active = 0;
		break;
	}

	cardLayout = Layer::create();
	addChild(cardLayout, 0, 10);
	//cardLayout->setVisible(false);

	if (active && type != CLASS_SPELL)
	{
		char txt[4];
		sprintf(txt, "%d", health);
		hpLabel = Label::createWithSystemFont(txt, "Kristen ITC", 24);
		hpLabel->setPosition(Vec2(getContentSize().width * 0.78, getContentSize().height *0.07)); // should be 0.07
		//hpLabel->setVisible(false);
		cardLayout->addChild(hpLabel);

		sprintf(txt, "%d", attack);
		atkLabel = Label::createWithSystemFont(txt, "Kristen ITC", 24);
		atkLabel->setPosition(Vec2(getContentSize().width * 0.2, getContentSize().height *0.09)); // should be 0.09
		atkLabel->setTextColor(Color4B(81, 9, 45, 255));
		//atkLabel->setVisible(false);
		cardLayout->addChild(atkLabel);
	}
	if (type == CLASS_SPELL)
	{
		if (health > 0)
		{
			char txt[4];
			sprintf(txt, "+%d", health);
			hpLabel = Label::createWithSystemFont(txt, "Kristen ITC", 24);
			hpLabel->setPosition(Vec2(getContentSize().width * 0.78, getContentSize().height *0.07)); // should be 0.07
			addChild(hpLabel);
		}
	}
	
		
	
	// de facut switch cu case pt fiecare carte
	//Edit phd 23/11/2016 ^^ WAS I CRAZY OR WHAT:D we need 1 file/each :)))
	// 21/02/2017 ^^ Should, (not need). Let's hope we find a better ideea
	// 27/02/2017 Stick to Switch, as on Client we only need atk and hp.
	
}

bool Card::isMouseOver(Vec2 p)
{
	cocos2d::Rect rect = this->getBoundingBox();

	if (rect.containsPoint(p))
	{
		return true;
	}

	return false;
}

void Card::enterScroll()
{
	Vector<SpriteFrame*> animFrames;
	Vector<FiniteTimeAction*> actions;
	SpriteFrame* frame;

	char str[50] = { 0 };

	sprintf(str, "Card%d.png", NOCARD);
	frame = SpriteFrame::create(str, Rect(Vec2(0, 0), getContentSize()));
	animFrames.pushBack(frame);

	for (int i = 3; i > 0; --i)
	{
		sprintf(str, "CardClose%02d.png", i);
		frame = SpriteFrame::create(str, Rect(Vec2(0, 0), getContentSize()));
		animFrames.pushBack(frame);
	}

	sprintf(str, "Card_S_%d.png", ID);
	frame = SpriteFrame::create(str, Rect(Vec2(0, 0), getContentSize()));
	animFrames.pushBack(frame);

	Animation * animation = Animation::createWithSpriteFrames(animFrames, 0.07);
	Animate * animate = Animate::create(animation);
	FadeIn * fadeIn = FadeIn::create(0.3);
	CallFunc* showLayout = CallFunc::create([=]() {
		this->getChildByTag(10)->setVisible(true);
	});
	actions.pushBack(fadeIn);
	actions.pushBack(animate);
	actions.pushBack(showLayout);
	cocos2d::Action* openScroll = Sequence::create(actions);
	runAction(openScroll);
}

void Card::exitScroll()
{
	Vector<SpriteFrame*> animFrames;
	Vector<FiniteTimeAction*> actions;

	char str[50] = { 0 };

	sprintf(str, "Card_S_%d.png", ID);
	SpriteFrame* frame = SpriteFrame::create(str, Rect(Vec2(0, 0), getContentSize()));
	animFrames.pushBack(frame);

	for (int i = 0; i < 4; ++i)
	{
		sprintf(str, "CardClose%02d.png", i);
		frame = SpriteFrame::create(str, Rect(Vec2(0, 0), getContentSize()));
		animFrames.pushBack(frame);
	}
	sprintf(str, "Card%d.png", NOCARD);
	frame = SpriteFrame::create(str, Rect(Vec2(0, 0), getContentSize()));
	animFrames.pushBack(frame);

	CallFunc* hideLayout = CallFunc::create([=]() {
		this->getChildByTag(10)->setVisible(false);
	});
	Animation * animation = Animation::createWithSpriteFrames(animFrames, 0.07);
	Animate * animate = Animate::create(animation);
	FadeOut * fadeOut = FadeOut::create(0.3);
	actions.pushBack(hideLayout);
	actions.pushBack(animate);
	actions.pushBack(fadeOut);
	cocos2d::Action* closeScroll = Sequence::create(actions);
	runAction(closeScroll);
}

void Card::moveScroll(cocos2d::Vec2 pos)
{
	Vector<SpriteFrame*> animFrames;
	Vector<FiniteTimeAction*> actions;

	char str[50] = { 0 };

	sprintf(str, "Card_S_%d.png", ID);
	SpriteFrame* frame = SpriteFrame::create(str, Rect(Vec2(0, 0), getContentSize()));
	animFrames.pushBack(frame);

	for (int i = 0; i < 4; ++i)
	{
		sprintf(str, "CardClose%02d.png", i);
		frame = SpriteFrame::create(str, Rect(Vec2(0, 0), getContentSize()));
		animFrames.pushBack(frame);
	}
	sprintf(str, "Card%d.png", NOCARD);
	frame = SpriteFrame::create(str, Rect(Vec2(0, 0), getContentSize()));
	animFrames.pushBack(frame);

	Animation * animation = Animation::createWithSpriteFrames(animFrames, 0.07);
	CallFunc* hideLayout = CallFunc::create([=]() {
		this->getChildByTag(10)->setVisible(false);
	});
	Animate * animate = Animate::create(animation);
	Animate * revAnimate = animate->reverse();
	FadeOut * fadeOut = FadeOut::create(0.3);
	MoveTo * move = MoveTo::create(0, pos);
	FadeIn * fadeIn = FadeIn::create(0.3);
	CallFunc* showLayout = CallFunc::create([=]() {
		this->getChildByTag(10)->setVisible(true);
	});
	actions.pushBack(hideLayout);
	actions.pushBack(animate);
	actions.pushBack(fadeOut);
	actions.pushBack(move);
	actions.pushBack(fadeIn);
	actions.pushBack(revAnimate);
	actions.pushBack(showLayout);
	cocos2d::Action* closeScroll = Sequence::create(actions);
	runAction(closeScroll);
}

cardName Card::getCardID()
{
	return ID;
}

int Card::getSlot()
{
	return slot;
}

void Card::setSlot(int newSlot)
{
	slot = newSlot;
}

cardRole Card::getRole()
{
	return role;
}

void Card::setRole(cardRole newRole)
{
	role = newRole;
}

classType Card::getType()
{
	return type;
}
