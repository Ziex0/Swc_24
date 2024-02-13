/*
<--------------------------------------------------------------------------->
 - Developer(s): Zie
 - Complete: 100%
 - ScriptName: 'tele ICC' 
 - Comment: N/A
<--------------------------------------------------------------------------->
*/ 
#include "ScriptPCH.h"
#include "Language.h"

class quest_freya : public CreatureScript
{
public:
	quest_freya()
		: CreatureScript("quest_freya") 
	{
	}
	
	struct quest_freyaAI : public ScriptedAI
	{
		quest_freyaAI(Creature *c) : ScriptedAI(c){}
		
		void Reset()
		{
			me->RestoreFaction();
		}

		void EnterEvadeMode()
        {
            me->GetMotionMaster()->Clear();
            ScriptedAI::EnterEvadeMode();
        }
				void ReceiveEmote(Player *pPlayer, uint32 uiTextEmote)
		{
			if (pPlayer->IsInCombat())
				{ pPlayer->GetSession()->SendAreaTriggerMessage("|cffff0000You are in combat!|r"); } 
				return;
		}
	};

	CreatureAI* GetAI(Creature* pCreature) const
    {
		return new quest_freyaAI(pCreature);
    }

	void CreatureWhisperBasedOnBool(const char *text, Creature *pCreature, Player *pPlayer, bool value)
	{
		if (value)
			pCreature->MonsterWhisper(text, pPlayer->GetGUID());
	}

	void MainMenu(Player *pPlayer, Creature *pCreature)
	{
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|TInterface/ICONS/inv_sigil_freya:30|t The first step! ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|TInterface/ICONS/Achievement_boss_grandmagustelestra:30|t Getting to know Freya ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|TInterface/ICONS/Inv_misc_runedorb_01:30|t The Glimmering Pillar ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|TInterface/ICONS/Achievement_zone_azuremystisle_01:30|t The Makers Perch ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|TInterface/ICONS/Achievement_zone_grizzlyhills_03:30|t Makers Overlook ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|TInterface/ICONS/Achievement_dungeon_utgardekeep_10man:30|t The Shapers Terrace ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
		//pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|TInterface/ICONS/Spell_shaman_lavaflow:30|t Suffering MIdgett 240 - 255 ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
		//pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|TInterface/ICONS/Inv_misc_coin_09:30|t The Destiny of Primordial Pain. ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
		pPlayer->SEND_GOSSIP_MENU(907, pCreature->GetGUID());
	}

	bool OnGossipHello(Player* pPlayer, Creature* pCreature)
    {
		MainMenu(pPlayer, pCreature);
		return true;
    }

	bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 /*uiSender*/, uint32 uiAction)
    {
		
		pPlayer->PlayerTalkClass->ClearMenus();

		switch (uiAction)
		{
			case GOSSIP_ACTION_INFO_DEF + 1: //level 1
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(571, 5494.2680f, 4731.5639f, -194.6069f, 1.8825f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 2: //level 2
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(571, 5867.6938f, 4112.6914f, -85.0739f, 0.3980f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 3: //lvel 3
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(571, 6231.3017f, 4753.9174f, 225.2605f, 2.7799f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 4: // lvl 4
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(571, 6169.1015f, 5707.2724f, 5.9006f, 0.7366f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 5: // lvl 5
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(571, 5740.9853f, 3136.4111f, 294.5661f, 4.8316f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 6: // lvl 6
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(1, -6191.3969f, -1264.2722f, -159.5468f, 1.1595f);

		 		break;
	       case GOSSIP_ACTION_INFO_DEF + 7: // 8000x
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, 3062.9011f, -3073.8112f, 126.0011f, 2.9769f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 8:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, 3422.1235f, -3379.6655f, 142.6201f, 6.2677f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 19:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(530, -3965.7f, -11653.6f, -138.844f, 0.852154f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 20:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(1, 9949.56f, 2284.21f, 1341.4f, 1.59587f);
			
			pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());
		}

        return true;
	}
};

void AddSc_Scriptquest_freya()
{
	new quest_freya();
}