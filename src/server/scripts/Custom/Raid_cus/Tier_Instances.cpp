/////////////////////////////////////////////////////////////////////////////
//         				   Developed by Zie                                //
//                     Copyright (C) 2015 Zie                              //
//                          Thesatria.Com                                  //
/////////////////////////////////////////////////////////////////////////////

#include "ScriptPCH.h"

class tier_instance : public CreatureScript
{
public:
    tier_instance() : CreatureScript("tier_instance") { }
	
    bool OnGossipHello(Player *player, Creature *_creature)
    {
        if (player->IsInCombat())
        {
            player->CLOSE_GOSSIP_MENU();
            _creature->MonsterWhisper("You are in combat!", player->GetGUID());
            return true;
        }
        else
        {			
            //player->ADD_GOSSIP_ITEM( 4, "|cff003233|TInterface\\icons\\Achievement_bg_winwsg:24|t25000 Honor to 250 Arena"      						, GOSSIP_SENDER_MAIN, 3); //Change the ID below
            //player->ADD_GOSSIP_ITEM( 4, "|cff003233|TInterface\\icons\\Achievement_bg_winwsg:24|t250 Arena to 20000 Honor"       						, GOSSIP_SENDER_MAIN, 4); //Change the ID below
            player->ADD_GOSSIP_ITEM( 4, "|cff003233|TInterface\\icons\\Achievement_bg_winbyten:24|tSmoldering Warlords T2 Symbol"                               , GOSSIP_SENDER_MAIN, 10); //Change the stats below
			player->ADD_GOSSIP_ITEM( 4, "|cff003233|TInterface\\icons\\Achievement_bg_winbyten:24|tLegacy of Bornstellar T3 Symbol" 							, GOSSIP_SENDER_MAIN, 5); //Change the stats below
            player->ADD_GOSSIP_ITEM( 4, "|cff003233|TInterface\\icons\\Achievement_bg_winbyten:24|tDawn of Sands of Time T4 Symbol"   	                    	, GOSSIP_SENDER_MAIN, 6); //Change the stats below
			player->ADD_GOSSIP_ITEM( 4, "|cff003233|TInterface\\icons\\Achievement_bg_winbyten:24|tAshes of T. Fates T5 Symbol"   						        , GOSSIP_SENDER_MAIN, 7); //Change the stats below
			player->ADD_GOSSIP_ITEM( 4, "|cff003233|TInterface\\icons\\Achievement_bg_winbyten:24|tBlood - Forged T6 Symbol"   					        		, GOSSIP_SENDER_MAIN, 8); //Change the stats below
			player->ADD_GOSSIP_ITEM( 4, "|cff003233|TInterface\\icons\\Achievement_bg_winbyten:24|tTwisted Void T7 Symbol"   									, GOSSIP_SENDER_MAIN, 9); //Change the stats below
			//player->ADD_GOSSIP_ITEM( 4, "|cff003233|TInterface\\icons\\Achievement_bg_winbyten:24|tEnigmatic Weapon Symbol #3 to 1 Enigmatic Weapon Coin #3"    , GOSSIP_SENDER_MAIN, 10); //Change the stats below
			
			//player->ADD_GOSSIP_ITEM( 4, "|cff003233|TInterface\\icons\\Xp_icon:20|tSupremacy Spell Staff to 50 Firdaus PvP Credit"   					, GOSSIP_SENDER_MAIN, 23); //Change the stats below
			player->PlayerTalkClass->SendGossipMenu(907, _creature->GetGUID());
        }

        player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, _creature->GetGUID());         
        return true;
    }

    bool OnGossipSelect(Player *player, Creature *_creature, uint32 sender, uint32 uiAction)
    {
        if (sender == GOSSIP_SENDER_MAIN)
        {
            player->PlayerTalkClass->ClearMenus();
            switch(uiAction)
            {
			case 3: //Honor
			if (player->GetHonorPoints() >= 25000)
                {
                    player->CLOSE_GOSSIP_MENU();
                    player->ModifyHonorPoints(-25000);
                    player->ModifyArenaPoints(+250);
                    _creature->MonsterWhisper("You exchanged succesfully!", player->GetGUID());
                }
                else
                {
                    player->CLOSE_GOSSIP_MENU();
                     _creature->MonsterWhisper("I'm sorry, but you don't have enough honor points to make this exchange!.", player->GetGUID());
                    return false;
                }break;
				
			case 4:	//Arena
			if (player->GetArenaPoints() >= 250)
                {
                    player->CLOSE_GOSSIP_MENU();
                    player->ModifyArenaPoints(-250);
                    player->ModifyHonorPoints(+20000);
                    _creature->MonsterWhisper("You exchanged succesfully!", player->GetGUID());
                }
                else
                {
                    player->CLOSE_GOSSIP_MENU();
                     _creature->MonsterWhisper("I'm sorry, but you don't have enough arena points to make this exchange!.", player->GetGUID());
                    return false;
                }break;
				
            case 5: // TIER 3
                if (player->HasItemCount ( 95504,1,false ) && player->HasItemCount ( 95505,1,false ) && player->HasItemCount( 95506,1,false ) && player->HasItemCount( 95507,1,false )) // TIER 3
                {
                    player->CLOSE_GOSSIP_MENU();
                    player->DestroyItemCount(95504, 1, true, false);
                    player->DestroyItemCount(95505, 1, true, false);
                    player->DestroyItemCount(95506, 1, true, false);
                    player->DestroyItemCount(95507, 1, true, false);
                    player->AddItem(110011, 1 );
                    _creature->MonsterWhisper("You exchanged successfully!", player->GetGUID());
                }
                else
                {
                    player->CLOSE_GOSSIP_MENU();
                    _creature->MonsterWhisper("I'm sorry, but you don't have items to make this exchange!.", player->GetGUID());
                    return false;
                }
                break;
			case 6: //Supremacy Polearm
               if (player->HasItemCount ( 95508,1,false ) && player->HasItemCount ( 95509,1,false ) && player->HasItemCount( 95510,1,false ) && player->HasItemCount( 95511,1,false )) // TIER 3
                {
                    player->CLOSE_GOSSIP_MENU();
                    player->DestroyItemCount(95508, 1, true, false);
                    player->DestroyItemCount(95509, 1, true, false);
                    player->DestroyItemCount(95510, 1, true, false);
                    player->DestroyItemCount(95511, 1, true, false);
                    player->AddItem(110012, 1 );
                    _creature->MonsterWhisper("You exchanged successfully!", player->GetGUID());
                }
                else
                {
                    player->CLOSE_GOSSIP_MENU();
                    _creature->MonsterWhisper("I'm sorry, but you don't have items to make this exchange!.", player->GetGUID());
                    return false;
                }
                break;
				case 7: // Supremacy Mace
                if (player->HasItemCount ( 95512,1,false ) && player->HasItemCount ( 95513,1,false ) && player->HasItemCount( 95514,1,false ) && player->HasItemCount( 95515,1,false )) // TIER 3
                {
                    player->CLOSE_GOSSIP_MENU();
                    player->DestroyItemCount(95512, 1, true, false);
                    player->DestroyItemCount(95513, 1, true, false);
                    player->DestroyItemCount(95514, 1, true, false);
                    player->DestroyItemCount(95515, 1, true, false);
                    player->AddItem(110013, 1 );
                    _creature->MonsterWhisper("You exchanged successfully!", player->GetGUID());
                }
                else
                {
                    player->CLOSE_GOSSIP_MENU();
                    _creature->MonsterWhisper("I'm sorry, but you don't have items to make this exchange!.", player->GetGUID());
                    return false;
                }
                break;
				case 8: //Supremacy Hunt Bow
                if (player->HasItemCount ( 95516,1,false ) && player->HasItemCount ( 95517,1,false ) && player->HasItemCount( 95518,1,false ) && player->HasItemCount( 95519,1,false )) // TIER 3
                {
                    player->CLOSE_GOSSIP_MENU();
                    player->DestroyItemCount(95516, 1, true, false);
                    player->DestroyItemCount(95517, 1, true, false);
                    player->DestroyItemCount(95518, 1, true, false);
                    player->DestroyItemCount(95519, 1, true, false);
                    player->AddItem(110014, 1 );
                    _creature->MonsterWhisper("You exchanged successfully!", player->GetGUID());
                }
                else
                {
                    player->CLOSE_GOSSIP_MENU();
                    _creature->MonsterWhisper("I'm sorry, but you don't have items to make this exchange!.", player->GetGUID());
                    return false;
                }
                break;
				case 9: // Supremacy Spell Dagger
                if (player->HasItemCount ( 95520,1,false ) && player->HasItemCount ( 95521,1,false ) && player->HasItemCount( 95522,1,false ) && player->HasItemCount( 95523,1,false )) // TIER 3
                {
                    player->CLOSE_GOSSIP_MENU();
                    player->DestroyItemCount(95520, 1, true, false);
                    player->DestroyItemCount(95521, 1, true, false);
                    player->DestroyItemCount(95522, 1, true, false);
                    player->DestroyItemCount(95523, 1, true, false);
                    player->AddItem(110015, 1 );
                    _creature->MonsterWhisper("You exchanged successfully!", player->GetGUID());
                }
                else
                {
                    player->CLOSE_GOSSIP_MENU();
                    _creature->MonsterWhisper("I'm sorry, but you don't have items to make this exchange!.", player->GetGUID());
                    return false;
                }
                break;
				case 10: // Supremacy Spell Sword
                if (player->HasItemCount ( 95500,1,false ) && player->HasItemCount ( 95501,1,false ) && player->HasItemCount( 95502,1,false ) && player->HasItemCount( 95503,1,false )) // TIER 3
                {
                    player->CLOSE_GOSSIP_MENU();
                    player->DestroyItemCount(95500, 1, true, false);
                    player->DestroyItemCount(95501, 1, true, false);
                    player->DestroyItemCount(95502, 1, true, false);
                    player->DestroyItemCount(95503, 1, true, false);
                    player->AddItem(110010, 5 );
                    _creature->MonsterWhisper("You exchanged successfully!", player->GetGUID());
                }
                else
                {
                    player->CLOSE_GOSSIP_MENU();
                    _creature->MonsterWhisper("I'm sorry, but you don't have items to make this exchange!.", player->GetGUID());
                    return false;
                }
                break;
				
            } 
        } 
        return true;
    } 
};

void AddSC_tier_instance()
{
    new tier_instance();
}