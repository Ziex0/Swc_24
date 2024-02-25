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

class smol_warlor : public CreatureScript
{
public:
	smol_warlor()
		: CreatureScript("smol_warlor") 
	{
	}
	
	struct smol_warlorAI : public ScriptedAI
	{
		smol_warlorAI(Creature *c) : ScriptedAI(c){}
		
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
		return new smol_warlorAI(pCreature);
    }

	void CreatureWhisperBasedOnBool(const char *text, Creature *pCreature, Player *pPlayer, bool value)
	{
		if (value)
			ChatHandler(pPlayer->GetSession()).PSendSysMessage(text, pPlayer->GetGUID());
	}

	void MainMenu(Player *pPlayer, Creature *pCreature)
	{
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|TInterface/ICONS/Thrown_1H_Harpoon_D_01Blue:35|t Smoldering Warlords ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
		

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
			case GOSSIP_ACTION_INFO_DEF + 1: //Smoldering war
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(532, -11059.9892f, -1952.3623f, 273.7211f, 0.1552f);

				break;
			
			
			pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());
		}

        return true;
	}
};

void AddSc_Scriptsmol_warlor()
{
	new smol_warlor();
}