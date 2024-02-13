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

class leg_venge : public CreatureScript
{
public:
	leg_venge()
		: CreatureScript("leg_venge") 
	{
	}
	
	struct leg_vengeAI : public ScriptedAI
	{
		leg_vengeAI(Creature *c) : ScriptedAI(c){}
		
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
		return new leg_vengeAI(pCreature);
    }

	void CreatureWhisperBasedOnBool(const char *text, Creature *pCreature, Player *pPlayer, bool value)
	{
		if (value)
			pCreature->MonsterWhisper(text, pPlayer->GetGUID());
	}

	void MainMenu(Player *pPlayer, Creature *pCreature)
	{
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|TInterface/ICONS/Thrown_1H_Harpoon_D_01Blue:35|t Legacy of Vengeance ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
		

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
			case GOSSIP_ACTION_INFO_DEF + 1: //vengeance
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(1, 4850.5976f, -1778.4901f, 1161.3669f, 5.2461f);

				break;
			/*case GOSSIP_ACTION_INFO_DEF + 2: //Sartharion
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(615, 3243.3017f, 455.6693f, 58.3878f, 1.4600f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 3: //anomalus
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(576, 635.9260f, -187.5305f, -14.4314f, 4.7899f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 4: // ionar
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(602, 1175.3867f, -261.9447f, 53.1228f, 3.1385f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 3:
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

void AddSc_Scriptleg_venge()
{
	new leg_venge();
}