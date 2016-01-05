#include "Deck.h"
#include "Card.h"
#include <sstream>
USING_NS_CC;

using namespace cocos2d::ui;

Card* Card::create(cardName cardID)
{

	std::stringstream ss;
	ss << "Card" << cardID << ".png";
	std::string str = ss.str();
	
	Card* pSprite = new Card();


	if (pSprite->initWithSpriteFrameName(str))
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
	switch (ID)
	{
	case KNIGHT:
		manaCost = 0;
		goldCost = 5;
		attack = 5;
		health = 5;
		ability = "Lads"; // Lads
	    break;
	case SQUIRE:
		manaCost = 0;
		goldCost = 2;
		attack = 2;
		health = 2;
		ability = "Lads"; //Lads
		break;
	case LONGBOWMAN:
		manaCost = 0;
		goldCost = 5;
		attack = 4;
		health = 3;
		ability = "No_retal";
		break;
	case SPEARMAN:
		manaCost = 0;
		goldCost = 3;
		attack = 2;
		health = 3;
		ability = "Anti_Cavalry|Defender";
		break;
	case SORCERER_APPRENTICE:
		manaCost = 2;
		goldCost = 1;
		attack = 4;
		health = 3;
		ability = "";
		break;
	case MILITIAN:
		manaCost = 0;
		goldCost = 2;
		attack = 2;
		health = 2;
		ability = "Defender";
		break;
	case GOBLIN:
		manaCost = 0;
		goldCost = 2;
		attack = 2;
		health = 2;
		ability = "";
		break;
	case PYROMANCERR:
		manaCost = 0;
		goldCost = 5;
		attack = 5;
		health = 3;
		ability = "";
		break;
	case DIREWOLF:
		manaCost = 0;
		goldCost = 4;
		attack = 5;
		health = 2;
		ability = "";
		break;
	case ALPHAWOLF:
		manaCost = 0;
		goldCost = 6;
		attack = 5;
		health = 5;
		ability = "Leader";
		break;
	case WOLF:
		manaCost = 0;
		goldCost = 2;
		attack = 3;
		health = 2;
		ability = "";
		break;
	case WOLF_RIDER:
		manaCost = 0;
		goldCost = 5;
		attack = 5;
		health = 5;
		ability = "";
		break;
	case VIKING:
		manaCost = 0;
		goldCost = 6;
		attack = 6;
		health = 5;
		ability = "";
		break;
	case THIEF:
		manaCost = 0;
		goldCost = 2;
		attack = 3;
		health = 2;
		ability = "";
		break;
	case TREBUCHET:
		manaCost = 0;
		goldCost = 7;
		attack = 10;
		health = 3;
		ability = "CAN'T_ATTACK_CREATURE";
		break;
	case SORCERER:
		manaCost = 3;
		goldCost = 2;
		attack = 5;
		health = 4;
		ability = "";
		break;
	case MAGE:
		manaCost = 3;
		goldCost = 1;
		attack = 5;
		health = 3;
		ability = "";
		break;
	case WIZZARD:
		manaCost = 4;
		goldCost = 1;
		attack = 6;
		health = 3;
		ability = "";
		break;
	case MEDIC:
		manaCost = 0;
		goldCost = 0;
		attack = 0;
		health = 0;
		ability = "";
		break;
	case PRIEST:
		manaCost = 0;
		goldCost = 0;
		attack = 0;
		health = 0;
		ability = "";
		break;
	case SUMMONER:
		manaCost = 3;
		goldCost = 2;
		attack = 5;
		health = 3;
		ability = "";
		break;
	case PHALAX:
		manaCost = 0;
		goldCost = 4;
		attack = 3;
		health = 5;
		ability = "Defender";
		break;
	case MERCENARY:
		manaCost = 0;
		goldCost = 4;
		attack = 3;
		health = 7;
		ability = "Defender|DecreaseIncome";
		break;
	case TACTICIAN:
		manaCost = 0;
		goldCost = 4;
		attack = 4;
		health = 3;
		ability = "Defender";
		break;
	case FIRST_AID:
		manaCost = 3;
		goldCost = 0;
		attack = -2;
		health = 0;
		ability = "";
		break;
	case PLAGUE:			//change
		manaCost = 3;
		goldCost = 0;
		attack = 0;
		health = 0;
		ability = "";
		break;
	case FIREBALL:
		manaCost = 4;
		goldCost = 0;
		attack = 5;
		health = 0;
		ability = "";
		break;
	case COMMAND_PROMOTE:
		manaCost = 4;
		goldCost = 0;
		attack = 0;
		health = 0;
		ability = "Promote";
		break;
	case COMMAND_SHIELD:			//maybe change
		manaCost = 4;
		goldCost = 0;
		attack = 0;
		health = 0;
		ability = "Armor";
		break;
	case COMMAND_SWORD:
		manaCost = 4;
		goldCost = 0;
		attack = 0;
		health = 0;
		ability = "Attack";
		break;
	case COMMAND_VOLLEY:
		manaCost = 3;
		goldCost = 0;
		attack = 1;
		health = 0;
		ability = "ALL";
		break;
	case RATS:				//change
		manaCost = 0;
		goldCost = 0;
		attack = 0;
		health = 0;
		ability = "";
		break;
	case BLESSING:
		manaCost = 2;
		goldCost = 0;
		attack = -1;
		health = 0;
		ability = "Attack";
		break;
	case CHOSEN_ONE:			
		manaCost = 6;
		goldCost = 0;
		attack = 0;
		health = 0;
		ability = "IMUNE|UNSTOPPABLE";
		break;
	case EARTHQUAKE:		
		manaCost = 3;
		goldCost = 0;
		attack = 2;
		health = 0;
		ability = ""; //resources
		break;
	default:
		break;
	}


	
		
	
	// de facut switch cu case pt fiecare carte
	
}
