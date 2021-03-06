#ifndef __DECK_H__
#define __DECK_H__

enum cardName { 
	KNIGHT,		SQUIRE,	LONGBOWMAN,	SPEARMAN,			SORCERER_APPRENTICE,	MILITIAN,		GOBLIN,			PYROMANCERR,	DIREWOLF,	ALPHAWOLF,	WOLF, 
	WOLF_RIDER,	VIKING,	THIEF,		TREBUCHET,			SORCERER,				MAGE,			WIZARD,		SUMMONER,		PHALAX,		MERCENARY,	TACTICIAN, 
	FIRST_AID,	PLAGUE,	FIREBALL,	COMMAND_PROMOTE,	COMMAND_SHIELD,			COMMAND_SWORD,	COMMAND_VOLLEY, RATS,			BLESSING,	CHOSEN_ONE,	EARTHQUAKE,
	NOCARD, 
	//now, after NOCARD, we put all the disabled cards
	// NOCARD must ALWAYS be the last card. ALWAYS! Check image-name is named accordingly to NOCARD value
	MEDIC, PRIEST };

#endif