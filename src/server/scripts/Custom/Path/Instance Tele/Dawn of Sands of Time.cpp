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

class Dawn_sand : public CreatureScript
{
public:
	Dawn_sand()
		: CreatureScript("Dawn_sand") 
	{
	}
	
	struct Dawn_sandAI : public ScriptedAI
	{
		Dawn_sandAI(Creature *c) : ScriptedAI(c){}
		
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
		return new Dawn_sandAI(pCreature);
    }

	void CreatureWhisperBasedOnBool(const char *text, Creature *pCreature, Player *pPlayer, bool value)
	{
		if (value)
			pCreature->MonsterWhisper(text, pPlayer->GetGUID());
	}

	void MainMenu(Player *pPlayer, Creature *pCreature)
	{

		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|TInterface/icons/Achievement_BG_DefendXtowers_AV:35|t Kael'thas Sunstrider ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|TInterface/icons/Achievement_BG_DefendXtowers_AV:35|t Grobbulus ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|TInterface/icons/Achievement_BG_DefendXtowers_AV:35|t Forgemaster ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|TInterface/icons/Achievement_BG_DefendXtowers_AV:35|t Devourer of Souls ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);


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
			case GOSSIP_ACTION_INFO_DEF + 1: 
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(550, 638.2289f, -0.7779f, 47.5418f, 6.2721f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 2: 
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(533, 3212.1162f, -3189.5527f, 295.12039f, 5.4591f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 3: 
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(658, 694.7522f, -111.6783f, 514.7655f, 4.7007f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 4: 
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(632, 5482.2685f, 2500.5654f, 706.8743f, 5.5896f);

				break;
			/*case GOSSIP_ACTION_INFO_DEF + 3:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(530, 9487.69f, -7279.2f, 14.2866f, 6.16478f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 4:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, 1584.07f, 241.987f, -52.1534f, 0.049647f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 6:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, -8833.38f, 628.628f, 94.0066f, 1.06535f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 18:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, -4918.88f, -940.406f, 501.564f, 5.42347f);

				break;
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

void AddSc_ScriptDawn_sand()
{
	new Dawn_sand();
}