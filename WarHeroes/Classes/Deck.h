/*					VERY IMPORTANT NOTE
**
** This file should be the same in both projects, client and
** server, otherwise there will be errors around the card types
** Therefore I reccomand NOT to modify this file in the client's
** files but in the server's, and then copy it there!
**													PhD
*/

#ifndef __DECK_H__
#define __DECK_H__

enum cardName { KNIGHT, SQUIRE, LONGBOWMAN, SPEARMAN, SORCERER_APPRENTICE, MILITIAN, GOBLIN, PYROMANCERR, DIREWOLF, ALPHAWOLF, WOLF, WOLF_RIDER, VIKING, THIEF, TREBUCHET, 
	SORCERER, MAGE, WIZZARD, SUMMONER, PHALAX, MERCENARY, TACTICIAN, FIRST_AID, PLAGUE, FIREBALL, COMMAND_PROMOTE, COMMAND_SHIELD, COMMAND_SWORD, COMMAND_VOLLEY, RATS, 
	BLESSING, CHOSEN_ONE, EARTHQUAKE, NOCARD, 
	//now, after NOCARD, we put all the disabled cards
	MEDIC, PRIEST };

#endif