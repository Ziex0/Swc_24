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

class twis_void : public CreatureScript
{
public:
	twis_void()
		: CreatureScript("twis_void") 
	{
	}
	
	struct twis_voidAI : public ScriptedAI
	{
		twis_voidAI(Creature *c) : ScriptedAI(c){}
		
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
		return new twis_voidAI(pCreature);
    }

	void CreatureWhisperBasedOnBool(const char *text, Creature *pCreature, Player *pPlayer, bool value)
	{
		if (value)
			ChatHandler(pPlayer->GetSession()).PSendSysMessage(text, pPlayer->GetGUID());
	}

	void MainMenu(Player *pPlayer, Creature *pCreature)
	{
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|TInterface/ICONS/Thrown_1H_Harpoon_D_01Blue:35|t Steelbreaker ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|TInterface/ICONS/Thrown_1H_Harpoon_D_01Blue:35|t Kologarn ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|TInterface/ICONS/Thrown_1H_Harpoon_D_01Blue:35|t Freya ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|TInterface/ICONS/Thrown_1H_Harpoon_D_01Blue:35|t General Vezax ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
		

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
			case GOSSIP_ACTION_INFO_DEF + 1: //Levi
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(603, 1703.4593f, 134.5658f, 428.0989f, 4.7140f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 2: //Kologarn
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(603, 1498.0699f, -24.3113f, 422.0029f, 6.2691f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 3: //Freya
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(603, 2108.3039f, -24.7539f, 421.8127f, 0.0098f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 4: // General Vezax
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(603, 1821.9119f, 203.9488f, 359.2489f, 4.9476f);

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

void AddSc_Scripttwis_void()
{
	new twis_void();
}