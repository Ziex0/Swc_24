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

class custom_porterz : public CreatureScript
{
public:
	custom_porterz()
		: CreatureScript("custom_porterz") 
	{
	}
	
	struct custom_porterzAI : public ScriptedAI
	{
		custom_porterzAI(Creature *c) : ScriptedAI(c){}
		
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
		return new custom_porterzAI(pCreature);
    }

	void CreatureWhisperBasedOnBool(const char *text, Creature *pCreature, Player *pPlayer, bool value)
	{
		if (value)
			pCreature->MonsterWhisper(text, pPlayer->GetGUID());
	}

	void MainMenu(Player *pPlayer, Creature *pCreature)
	{
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|TInterface/ICONS/Achievement_zone_icecrown_12:30|t The Purgatory 1 - 70 ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|TInterface/ICONS/Achievement_zone_icecrown_12:30|t Seeker of Ambition 70 - 85 ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|TInterface/ICONS/Achievement_zone_icecrown_12:30|t Seeker of Diversity 85 - 100 ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|TInterface/ICONS/Achievement_zone_icecrown_12:30|t Seeker of Hope 100 - 140 ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|TInterface/ICONS/Spell_shaman_lavaflow:30|t Suffering Void 140 - 200 ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|TInterface/ICONS/Spell_shaman_lavaflow:30|t Suffering Marker 200 - 240 ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|TInterface/ICONS/Spell_shaman_lavaflow:30|t Suffering Midgett 240 - 255 ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|TInterface/ICONS/Inv_misc_coin_09:30|t The Destiny of Primordial Pain. ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
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
			case GOSSIP_ACTION_INFO_DEF + 1: //The Purgatory
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, -1226.3797f, 410.0861f, 3.4660f, 1.9663f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 2: //1000x
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, -1375.1357f, 648.2921f, 51.6770f, 4.5220f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 3: //4000x
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, -1408.9381f, 579.8723f, 70.7610f, 5.9271f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 4: // 5000x
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, -1379.4130f, 521.9547f, 82.5371f, 2.16225f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 5: // 6000x
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, 3306.5678f, -3379.2629f, 144.8170f, 0.0117f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 6: // 7000x
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, 3126.9057f, -3377.2871f, 141.0176f, 1.8412f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 7: // 8000x
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, 3062.9011f, -3073.8112f, 126.0011f, 2.9769f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 8:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, 3422.1235f, -3379.6655f, 142.6201f, 6.2677f);

				/*break;
			case GOSSIP_ACTION_INFO_DEF + 19:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(530, -3965.7f, -11653.6f, -138.844f, 0.852154f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 20:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(1, 9949.56f, 2284.21f, 1341.4f, 1.59587f);*/
			
			pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());
		}

        return true;
	}
};

void AddSc_Scriptcustom_porterz()
{
	new custom_porterz();
}