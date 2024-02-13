/*
** Copyright (C) Ziex - Heaven-wow.com)
*/

#include "ScriptPCH.h"
#include "Language.h"

enum  defines
{
	level_token = 55559,
	max_lvl 	= 255,
};

class level_255 : public CreatureScript
{
public:
		level_255() : CreatureScript("level_255"){}

		bool OnGossipHello(Player * Player, Creature * pCreature)
		{
						
			Player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Achievement_Boss_Valanar:24|t|r I want to be level 255 ", GOSSIP_SENDER_MAIN, 0);
			Player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Achievement_Boss_Valanar:24|t|r I dont have 255 Token. ", GOSSIP_SENDER_MAIN, 1);
			Player->PlayerTalkClass->SendGossipMenu(9425, pCreature->GetGUID());
			return true;
		}
		
		bool OnGossipSelect(Player * Player, Creature * Creature, uint32 /*uiSender*/, uint32 uiAction)
		{
			if(!Player)
				return true;

			switch(uiAction)
			{
				
				case 0:
					
				if (Player->HasItemCount(level_token, 1))
					{
						Player->DestroyItemCount(level_token, 1, true, false);
						Player->GiveLevel(255);
						Player->GetSession()->SendNotification("Your level was set to 255.");
						Player->PlayerTalkClass->SendCloseGossip();
					}
					else
				if (Player->getLevel() >= 255 && (Player->HasItemCount(level_token, 0)))
					{
						Player->GetSession()->SendNotification("You already have level 255 and you don't need use me again :)");
						Player->PlayerTalkClass->SendCloseGossip();
						return false;
					}
					else
				if (Player->getLevel() <= 255 && (Player->HasItemCount(level_token, 0)))
					{
						Player->GetSession()->SendNotification("You need at least one Instant 255 level token!");
						Player->PlayerTalkClass->SendCloseGossip();
					}
				break;
				
				case 1:
					
				if (Player->HasItemCount(level_token, 2))
					{
						Player->DestroyItemCount(level_token, 2, true, false);
						Player->GiveLevel(0);
						Player->GetSession()->SendNotification("Sorry, you do not have the required Token.");
						Player->PlayerTalkClass->SendCloseGossip();
				    }
				break;

			}
			return true;
		}
		
};

void AddSC_level_255()
{
    new level_255();
}