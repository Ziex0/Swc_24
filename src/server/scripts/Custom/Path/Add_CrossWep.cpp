/*
** Copyright (C) Ziex - Heaven-wow.com)
*/

#include "ScriptPCH.h"
#include "Language.h"

enum  defines
{
	cross_token = 29, // cahnge to custom ID
	spell_cust  = 28, // cahnge to custom ID
	max_lvl 	= 255,
};

class cross_spell : public CreatureScript
{
public:
	cross_spell()
		: CreatureScript("cross_spell") {}
	
	struct cross_spellAI : public ScriptedAI
	{
		cross_spellAI(Creature *c) : ScriptedAI(c) {}

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
		return new cross_spellAI(pCreature);
    }

	void CreatureWhisperBasedOnBool(const char *text, Creature *pCreature, Player *pPlayer, bool value)
	{
		if (value)
			pCreature->MonsterWhisper(text, pPlayer->GetGUID());
	}

	uint32 PlayerMaxLevel() const
	{
		return sWorld->getIntConfig(CONFIG_MAX_PLAYER_LEVEL);
	}

	void MainMenu(Player *pPlayer, Creature *pCreature) //main menu
	{
		
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, "|TInterface/ICONS/Achievement_general_stayclassy:24|t Learn Cross Weapon Spells ->", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, "|TInterface/ICONS/Achievement_reputation_guardiansofcenarius:24|t Learn Custom Spells ->", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
		pPlayer->SEND_GOSSIP_MENU(907, pCreature->GetGUID());
	}

	bool PlayerHasItemOrSpell(const Player *plr, uint32 itemId, uint32 spellId) const
	{
		return plr->HasItemCount(itemId, 1, true) || plr->HasSpell(spellId); //id use coin or token
	}

	bool OnGossipHello(Player* pPlayer, Creature* pCreature)
    {
		MainMenu(pPlayer, pCreature);

        return true;
    }
	
	bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 /*uiSender*/, uint32 uiAction)
    {
		if (pPlayer->IsInCombat())
		{
			pCreature->MonsterWhisper("You are in combat !!!!, wait until your combat is gone...ughhhhh .!!!", pPlayer->GetGUID());
			pPlayer->CLOSE_GOSSIP_MENU();

			return true;
		}

		pPlayer->PlayerTalkClass->ClearMenus();

		switch (uiAction)
		{			
			case GOSSIP_ACTION_INFO_DEF + 1: //cross spells
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|TInterface/ICONS/Achievement_arena_2v2_6:24|t One-Handed Swords", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 10);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|TInterface/ICONS/Achievement_arena_2v2_6:24|t One-Handed Maces", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|TInterface/ICONS/Achievement_arena_2v2_6:24|t One-Handed Axes", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 12);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|TInterface/ICONS/Achievement_arena_2v2_6:24|t Daggers", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 13);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|TInterface/ICONS/Achievement_arena_2v2_6:24|t Staves", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 14);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|TInterface/ICONS/Achievement_arena_2v2_6:24|t Two-Handed Swords", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 15);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|TInterface/ICONS/Achievement_arena_2v2_6:24|t Two-Handed Axes", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 16);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|TInterface/ICONS/Achievement_arena_2v2_6:24|t Two-Handed Maces", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 17);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|TInterface/ICONS/Achievement_arena_2v2_6:24|t Titan's Grip", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 18);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "<- [Back]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11);
				pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());
				break;
				
			case GOSSIP_ACTION_INFO_DEF + 10:
                if (pPlayer->HasItemCount(cross_token, 1)){
					pPlayer->DestroyItemCount(29, 1, true, false);
					pPlayer->CLOSE_GOSSIP_MENU();
					pPlayer->learnSpell(201, false);
					pCreature->MonsterWhisper("You have successfully acquired this spell.", pPlayer->GetGUID());
					break;

                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterWhisper("I'm sorry, but you don't have items to make this exchange!.", pPlayer->GetGUID());
                    return false;
                }
                break;
			
			case GOSSIP_ACTION_INFO_DEF + 11:
                if (pPlayer->HasItemCount(cross_token, 1)){
					pPlayer->DestroyItemCount(29, 1, true, false);
					pPlayer->CLOSE_GOSSIP_MENU();
					pPlayer->learnSpell(198, false);
					pCreature->MonsterWhisper("You have successfully acquired this spell.", pPlayer->GetGUID());
					break;

                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterWhisper("I'm sorry, but you don't have items to make this exchange!.", pPlayer->GetGUID());
                    return false;
                }
                break;
		
			case GOSSIP_ACTION_INFO_DEF + 12:
                if (pPlayer->HasItemCount(cross_token, 1)){
					pPlayer->DestroyItemCount(29, 1, true, false);
					pPlayer->CLOSE_GOSSIP_MENU();
					pPlayer->learnSpell(196, false);
					pCreature->MonsterWhisper("You have successfully acquired this spell.", pPlayer->GetGUID());
					break;

                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterWhisper("I'm sorry, but you don't have items to make this exchange!.", pPlayer->GetGUID());
                    return false;
                }
                break;
			
			case GOSSIP_ACTION_INFO_DEF + 13:
                if (pPlayer->HasItemCount(cross_token, 1)){
					pPlayer->DestroyItemCount(29, 1, true, false);
					pPlayer->CLOSE_GOSSIP_MENU();
					pPlayer->learnSpell(1180, false);
					pCreature->MonsterWhisper("You have successfully acquired this spell.", pPlayer->GetGUID());
					break;

                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterWhisper("I'm sorry, but you don't have items to make this exchange!.", pPlayer->GetGUID());
                    return false;
                }
                break;
			
			case GOSSIP_ACTION_INFO_DEF + 14:
                if (pPlayer->HasItemCount(cross_token, 1)){
					pPlayer->DestroyItemCount(29, 1, true, false);
					pPlayer->CLOSE_GOSSIP_MENU();
					pPlayer->learnSpell(227, false);
					pCreature->MonsterWhisper("You have successfully acquired this spell.", pPlayer->GetGUID());
					break;

                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterWhisper("I'm sorry, but you don't have items to make this exchange!.", pPlayer->GetGUID());
                    return false;
                }
                break;
			
			case GOSSIP_ACTION_INFO_DEF + 15:
                if (pPlayer->HasItemCount(cross_token, 1)){
					pPlayer->DestroyItemCount(29, 1, true, false);
					pPlayer->CLOSE_GOSSIP_MENU();
					pPlayer->learnSpell(202, false);
					pCreature->MonsterWhisper("You have successfully acquired this spell.", pPlayer->GetGUID());
					break;

                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterWhisper("I'm sorry, but you don't have items to make this exchange!.", pPlayer->GetGUID());
                    return false;
                }
                break;
			
			case GOSSIP_ACTION_INFO_DEF + 16:
                if (pPlayer->HasItemCount(cross_token, 1)){
					pPlayer->DestroyItemCount(29, 1, true, false);
					pPlayer->CLOSE_GOSSIP_MENU();
					pPlayer->learnSpell(197, false);
					pCreature->MonsterWhisper("You have successfully acquired this spell.", pPlayer->GetGUID());
					break;

                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterWhisper("I'm sorry, but you don't have items to make this exchange!.", pPlayer->GetGUID());
                    return false;
                }
                break;
			
			case GOSSIP_ACTION_INFO_DEF + 17:
                if (pPlayer->HasItemCount(cross_token, 1)){
					pPlayer->DestroyItemCount(29, 1, true, false);
					pPlayer->CLOSE_GOSSIP_MENU();
					pPlayer->learnSpell(199, false);
					pCreature->MonsterWhisper("You have successfully acquired this spell.", pPlayer->GetGUID());
					break;

                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterWhisper("I'm sorry, but you don't have items to make this exchange!.", pPlayer->GetGUID());
                    return false;
                }
                break;
			
			case GOSSIP_ACTION_INFO_DEF + 18:
                if (pPlayer->HasItemCount(cross_token, 1)){
					pPlayer->DestroyItemCount(29, 1, true, false);
					pPlayer->CLOSE_GOSSIP_MENU();
					pPlayer->learnSpell(46917, false);
					pCreature->MonsterWhisper("You have successfully acquired this spell.", pPlayer->GetGUID());
					break;

                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterWhisper("I'm sorry, but you don't have items to make this exchange!.", pPlayer->GetGUID());
                    return false;
                }
                break;

			case GOSSIP_ACTION_INFO_DEF + 2: //custom spells
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|TInterface/ICONS/Inv_inscription_minorglyph01:24|t Ahn'Qiraj Reward Buff Melee", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 20);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|TInterface/ICONS/Inv_inscription_minorglyph01:24|t Ahn'Qiraj Reward Buff Caster", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 21);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|TInterface/ICONS/Inv_inscription_minorglyph01:24|t Berserk", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 28);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|TInterface/ICONS/Inv_inscription_minorglyph01:24|t Nitrous Boost", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 27);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "<- [Back]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11);
				pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());
				break;
				
			case GOSSIP_ACTION_INFO_DEF + 20:
                if (pPlayer->HasItemCount(spell_cust, 1)){
					pPlayer->DestroyItemCount(28, 1, true, false);
					pPlayer->CLOSE_GOSSIP_MENU();
					pPlayer->learnSpell(25794, false);
					pCreature->MonsterWhisper("You have successfully acquired this spell.", pPlayer->GetGUID());
					break;

                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterWhisper("I'm sorry, but you don't have items to make this exchange!.", pPlayer->GetGUID());
                    return false;
                }
                break;
			
			case GOSSIP_ACTION_INFO_DEF + 21:
                if (pPlayer->HasItemCount(spell_cust, 1)){
					pPlayer->DestroyItemCount(28, 1, true, false);
					pPlayer->CLOSE_GOSSIP_MENU();
					pPlayer->learnSpell(25797, false);
					pCreature->MonsterWhisper("You have successfully acquired this spell.", pPlayer->GetGUID());
					break;

                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterWhisper("I'm sorry, but you don't have items to make this exchange!.", pPlayer->GetGUID());
                    return false;
                }
                break;

			case GOSSIP_ACTION_INFO_DEF + 23:
                if (pPlayer->HasItemCount(spell_cust, 1)){
					pPlayer->DestroyItemCount(28, 1, true, false);
					pPlayer->CLOSE_GOSSIP_MENU();
					pPlayer->learnSpell(27746, false);
					pCreature->MonsterWhisper("You have successfully acquired this spell.", pPlayer->GetGUID());
					break;

                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterWhisper("I'm sorry, but you don't have items to make this exchange!.", pPlayer->GetGUID());
                    return false;
                }
                break;

			case GOSSIP_ACTION_INFO_DEF + 27:
                if (pPlayer->HasItemCount(spell_cust, 1)){
					pPlayer->DestroyItemCount(28, 1, true, false);
					pPlayer->CLOSE_GOSSIP_MENU();
					pPlayer->learnSpell(27746, false);
					pCreature->MonsterWhisper("You have successfully acquired this spell.", pPlayer->GetGUID());
					break;

                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterWhisper("I'm sorry, but you don't have items to make this exchange!.", pPlayer->GetGUID());
                    return false;
                }
                break;
		    
			case GOSSIP_ACTION_INFO_DEF + 28:
                if (pPlayer->HasItemCount(spell_cust, 1)){
					pPlayer->DestroyItemCount(28, 1, true, false);
					pPlayer->CLOSE_GOSSIP_MENU();
					pPlayer->learnSpell(41924, false);
					pCreature->MonsterWhisper("You have successfully acquired this spell.", pPlayer->GetGUID());
					break;

                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterWhisper("I'm sorry, but you don't have items to make this exchange!.", pPlayer->GetGUID());
                    return false;
                }
                break;

		}

        return true;
	}
};

void AddSc_cross_spell()
{
	new cross_spell();
}