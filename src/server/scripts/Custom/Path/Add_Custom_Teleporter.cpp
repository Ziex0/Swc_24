/*
<--------------------------------------------------------------------------->
 - Developer(s): Zie
 - Complete: 100%
 - ScriptName: 'Teleporter' 
 - Comment: Need update for spell calss and clean code for future !!
<--------------------------------------------------------------------------->
*/ 

#include "ScriptPCH.h"
#include "Language.h"
#include "ScriptMgr.h"
#include "Player.h"
#include "Creature.h"
#include "ScriptedGossip.h"

enum eTexts
{
	TEXT_ON_DANCE = 95003,
	TEXT_ON_SALUTE = 95004,
	TEXT_ON_SPIT = 95005,
	TEXT_ON_LAUGH = 95006,
	TEXT_ON_BYE = 95007
};

enum eRidingSkills
{
	RIDING_APPRENTICE = 33388,
	RIDING_JOURNEYMAN = 33391,
	RIDING_EXPERT = 34090,
	RIDING_ARTISAN = 34091,
	COLD_WEATHER_FLYING = 54197
};


class Custom_teleporter : public CreatureScript
{
public:
	Custom_teleporter()
		: CreatureScript("Custom_teleporter")
	{
	}

	struct Custom_teleporterAI : public ScriptedAI
	{
		Custom_teleporterAI(Creature *c) : ScriptedAI(c){}
		
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
		return new Custom_teleporterAI(pCreature);
    }

	void CreatureWhisperBasedOnBool(const char *text, Creature *pCreature, Player *pPlayer, bool value)
	{
		if (value)
			ChatHandler(pPlayer->GetSession()).PSendSysMessage(text, pPlayer->GetGUID());
	}

	uint32 PlayerMaxLevel() const
	{
		return sWorld->getIntConfig(CONFIG_MAX_PLAYER_LEVEL);
	}

	void MainMenu(Player *pPlayer, Creature *pCreature)
	{
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|TInterface/ICONS/Achievement_bg_masterofallbgs:32:32|t|r|cff040414 Teleport Menu ->", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11);
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|TInterface/ICONS/INV_MISC_GEM_AMETHYST_03:32:32|t|r|cff040414 Professions ->", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 196);
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|TInterface/ICONS/Achievement_reputation_argentcrusader:32:32|t|r|cff040414 Learn Spells ->", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 460);
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|TInterface\\icons\\Achievement_bg_trueavshutout:32:32|t|r|cff040414 Advance my weapon skills to max.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9);
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|TInterface\\icons\\Ability_mount_spectraltiger:32:32|t|r|cff040414 Give me maximum riding skill.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 186);
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|TInterface/ICONS/Ability_DualWieldSpecialization:32:32|t|r|cff040414 Player Tools ->", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 450);
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|TInterface/icons/Ability_priest_soulwarding:32:32|t|r|cff040414 Buff Me UP", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2500);
		//pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|TInterface/ICONS/Achievement_Zone_Blackrock_01:32:32|t|rcffff0000 Free Mounts ->", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 177);
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|TInterface/ICONS/Achievement_dungeon_nexusraid_normal:32:32|t|r|cff040414 The Heaven Shop", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1110); 
		//pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|TInterface/ICONS/Achievement_Zone_Azshara_01:32:32|t|r|cffff0000 VIP Area", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9999); 
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|TInterface\\icons\\Achievement_boss_thorim:32:32|t|r|cff040414 Heaven Tier's Farming", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9000); 
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|TInterface\\icons\\Achievement_boss_lordmarrowgar:32:32|t|r|cff040414 High Level Tiers Questing", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1111);
		
		pPlayer->SEND_GOSSIP_MENU(907, pCreature->GetGUID());
	}

	bool PlayerHasItemOrSpell(const Player *plr, uint32 itemId, uint32 spellId) const
	{
		return plr->HasItemCount(itemId, 1, true) || plr->HasSpell(spellId);
	}

	bool OnGossipHello(Player* pPlayer, Creature* pCreature)
    {
		MainMenu(pPlayer, pCreature);

        return true;
    }

	bool PlayerAlreadyHasTwoProfessions(const Player *pPlayer) const
	{
		uint32 skillCount = 0;

		if (pPlayer->HasSkill(SKILL_MINING))
			skillCount++;
		if (pPlayer->HasSkill(SKILL_SKINNING))
			skillCount++;
		if (pPlayer->HasSkill(SKILL_HERBALISM))
			skillCount++;

		if (skillCount >= 2)
			return true;

		for (uint32 i = 1; i < sSkillLineStore.GetNumRows(); ++i)
		{
			SkillLineEntry const *SkillInfo = sSkillLineStore.LookupEntry(i);
			if (!SkillInfo)
				continue;

			if (SkillInfo->categoryId == SKILL_CATEGORY_SECONDARY)
				continue;

			if ((SkillInfo->categoryId != SKILL_CATEGORY_PROFESSION) || !SkillInfo->canLink)
				continue;

			const uint32 skillID = SkillInfo->id;
			if (pPlayer->HasSkill(skillID))
				skillCount++;

			if (skillCount >= 2)
				return true;
		}

		return false;
	}

	bool LearnAllRecipesInProfession(Player *pPlayer, SkillType skill)
	{
		ChatHandler handler(pPlayer->GetSession());
        char* skill_name;

        SkillLineEntry const *SkillInfo = sSkillLineStore.LookupEntry(skill);
		skill_name = SkillInfo->name[handler.GetSessionDbcLocale()];

        LearnSkillRecipesHelper(pPlayer, SkillInfo->id);

        uint16 maxLevel = pPlayer->GetPureMaxSkillValue(SkillInfo->id);
        pPlayer->SetSkill(SkillInfo->id, pPlayer->GetSkillStep(SkillInfo->id), maxLevel, maxLevel);
        handler.PSendSysMessage(LANG_COMMAND_LEARN_ALL_RECIPES, skill_name);
		
		return false;
	}
	// See "static void HandleLearnSkillRecipesHelper(Player* player,uint32 skill_id)" from cs_learn.cpp 
	void LearnSkillRecipesHelper(Player *player, uint32 skill_id)
	{
		uint32 classmask = player->getClassMask();

        for (uint32 j = 0; j < sSkillLineAbilityStore.GetNumRows(); ++j)
        {
            SkillLineAbilityEntry const *skillLine = sSkillLineAbilityStore.LookupEntry(j);
            if (!skillLine)
                continue;

            // wrong skill
            if (skillLine->skillId != skill_id)
                continue;

            // not high rank
            if (skillLine->forward_spellid)
                continue;

            // skip racial skills
            if (skillLine->racemask != 0)
                continue;

            // skip wrong class skills
            if (skillLine->classmask && (skillLine->classmask & classmask) == 0)
                continue;

            SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(skillLine->spellId);
            if (!spellInfo || !SpellMgr::IsSpellValid(spellInfo))
                continue;

            player->learnSpell(skillLine->spellId);
        }
	}

	bool IsSecondarySkill(SkillType skill) const
	{
		return skill == SKILL_COOKING || skill == SKILL_FIRST_AID;
	}

	void CompleteLearnProfession(Player *pPlayer, Creature *pCreature, SkillType skill)
	{
		if (PlayerAlreadyHasTwoProfessions(pPlayer) && !IsSecondarySkill(skill))
			//ChatHandler(pPlayer->GetSession()).PSendSysMessage("You already know two professions!", pPlayer->GetGUID());
			ChatHandler(pPlayer->GetSession()).PSendSysMessage("Success! You was teleported.");
		else
		{
			if (!LearnAllRecipesInProfession(pPlayer, skill))
				ChatHandler(pPlayer->GetSession()).PSendSysMessage("Enjoy !!",pPlayer->GetGUID());
		}
	}

	void CreatureWhisperBasedOnRidingSkill(Creature *pCreature, const Player *pPlayer, eRidingSkills skill)
	{
		const uint64 &plrGuid = pPlayer->GetGUID();

		switch (skill)
		{
		case RIDING_APPRENTICE:
			ChatHandler(pPlayer->GetSession()).PSendSysMessage("I taught you Apprentice riding!", plrGuid);
			break;
		case RIDING_JOURNEYMAN:
			ChatHandler(pPlayer->GetSession()).PSendSysMessage("I taught you Journeyman riding!", plrGuid);
			break;
		case RIDING_EXPERT:
			ChatHandler(pPlayer->GetSession()).PSendSysMessage("I taught you Expert riding!", plrGuid);
			break;
		case RIDING_ARTISAN:
			ChatHandler(pPlayer->GetSession()).PSendSysMessage("I taught you Artisan riding!", plrGuid);
			break;
		}
	}



	void GiveRidingSkill(Player *pPlayer, Creature *pCreature)
	{
		if (pPlayer->getLevel() <= 19)
			ChatHandler(pPlayer->GetSession()).PSendSysMessage("Your level is not high enough!", pPlayer->GetGUID());
		else if (pPlayer->getLevel() >= 20 && pPlayer->getLevel() <= 39)
		{
			if (pPlayer->HasSpell(RIDING_APPRENTICE))
				ChatHandler(pPlayer->GetSession()).PSendSysMessage("You already know Apprentice riding!", pPlayer->GetGUID());
			else
			{
				pPlayer->learnSpell(RIDING_APPRENTICE);
				CreatureWhisperBasedOnRidingSkill(pCreature, pPlayer, RIDING_APPRENTICE);
			}
		}
		else if (pPlayer->getLevel() >= 40 && pPlayer->getLevel() <= 59)
		{
			if (pPlayer->HasSpell(RIDING_JOURNEYMAN))
				ChatHandler(pPlayer->GetSession()).PSendSysMessage("You already know Journeyman riding!", pPlayer->GetGUID());
			else
			{
				pPlayer->learnSpell(RIDING_JOURNEYMAN);
				CreatureWhisperBasedOnRidingSkill(pCreature, pPlayer, RIDING_JOURNEYMAN);
			}
		}
		else if (pPlayer->getLevel() >= 60 && pPlayer->getLevel() <= 69)
		{
			if (pPlayer->HasSpell(RIDING_EXPERT))
				ChatHandler(pPlayer->GetSession()).PSendSysMessage("You already know Expert riding!", pPlayer->GetGUID());
			else
			{
				pPlayer->learnSpell(RIDING_EXPERT);
				CreatureWhisperBasedOnRidingSkill(pCreature, pPlayer, RIDING_EXPERT);
			}
		}
		else if (pPlayer->getLevel() >= 70)
		{
			if (pPlayer->getLevel() >= 77 && !pPlayer->HasSpell(COLD_WEATHER_FLYING))
			{
				pPlayer->learnSpell(COLD_WEATHER_FLYING);
				ChatHandler(pPlayer->GetSession()).PSendSysMessage("I taught you Cold Weather Flying!", pPlayer->GetGUID());
			}

			if (pPlayer->HasSpell(RIDING_ARTISAN))
				ChatHandler(pPlayer->GetSession()).PSendSysMessage("You already know Artisan riding!", pPlayer->GetGUID());
			else
			{
				pPlayer->learnSpell(RIDING_ARTISAN);
				CreatureWhisperBasedOnRidingSkill(pCreature, pPlayer, RIDING_ARTISAN);
			}
		}
	}

    bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 /*uiSender*/, uint32 uiAction)
    {
		if (pPlayer->IsInCombat())
		{
			ChatHandler(pPlayer->GetSession()).PSendSysMessage("You are in combat, wait until your combat is gone.", pPlayer->GetGUID());
			pPlayer->CLOSE_GOSSIP_MENU();

			return true;
		}

		pPlayer->PlayerTalkClass->ClearMenus();

		switch (uiAction)
		{

			case GOSSIP_ACTION_INFO_DEF + 1:
				pPlayer->DurabilityRepairAll(false, 0.0f, true);
				ChatHandler(pPlayer->GetSession()).PSendSysMessage("I repaired all your items, including items from bank.", pPlayer->GetGUID());
				pPlayer->CLOSE_GOSSIP_MENU();

				break;
			case GOSSIP_ACTION_INFO_DEF + 8:
				MainMenu(pPlayer, pCreature);
			
				break;
			case GOSSIP_ACTION_INFO_DEF + 9:
				pPlayer->UpdateSkillsToMaxSkillsForLevel();
				ChatHandler(pPlayer->GetSession()).PSendSysMessage("Your weapon skills have been advanced to maximum level.", pPlayer->GetGUID());
				pPlayer->CLOSE_GOSSIP_MENU();

				break;
			case GOSSIP_ACTION_INFO_DEF + 10:
			{
				pPlayer->GiveLevel((uint8)PlayerMaxLevel());
				pPlayer->InitTalentForLevel();
				pPlayer->SetUInt32Value(PLAYER_XP, 0);
				std::ostringstream ostr;
				ostr << PlayerMaxLevel();
				ChatHandler(pPlayer->GetSession()).PSendSysMessage(("You have been advanced to level " + ostr.str()).c_str(), pPlayer->GetGUID());
		
				pPlayer->CLOSE_GOSSIP_MENU();
	
				break;
			}

			case GOSSIP_ACTION_INFO_DEF + 9000:
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|TInterface/Icons/Achievement_zone_grizzlyhills_05:35:35|t|r Legacy of Vengeance (T1)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9005);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|TInterface/Icons/Achievement_zone_zuldrak_12:35:35|t|r Smoldering Warlords (T2)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9006);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|TInterface/Icons/Achievement_zone_wetlands_01:35:35|t|r Legacy of Bornstellar (T3)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9001);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|TInterface/Icons/Achievement_zone_bloodmystisle_01:35:35|t|r Dawn of Sands of Time (T4)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9002);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|TInterface/Icons/Achievement_zone_stonetalon_01:35:35|t|r Ashes of T. Fates (T5)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9003);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|TInterface/Icons/Achievement_zone_zuldrak_09:35:35|t|r Blood Forged (T6)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9004);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|TInterface/Icons/Achievement_dungeon_ulduarraid_irondwarf_01:35:35|t|r Twisted Void (T7)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9007);	
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "<- [Back]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11);
				pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());
				break;

			case GOSSIP_ACTION_INFO_DEF + 9001:    //  icc spawn
					pPlayer->SummonCreature(60026,pPlayer->GetPositionX()+2 ,pPlayer->GetPositionY(), pPlayer->GetPositionZ(), 0,TEMPSUMMON_TIMED_DESPAWN,20000);
					pPlayer->CLOSE_GOSSIP_MENU();
					break;
			   
           case GOSSIP_ACTION_INFO_DEF +9002: 
					pPlayer->SummonCreature(60027,pPlayer->GetPositionX() ,pPlayer->GetPositionY()+2, pPlayer->GetPositionZ(), 0,TEMPSUMMON_TIMED_DESPAWN,20000);
					pPlayer->CLOSE_GOSSIP_MENU();
					break;

           case GOSSIP_ACTION_INFO_DEF +9003:
					pPlayer->SummonCreature(60028,pPlayer->GetPositionX() ,pPlayer->GetPositionY()+2, pPlayer->GetPositionZ(), 0,TEMPSUMMON_TIMED_DESPAWN,20000);
					pPlayer->CLOSE_GOSSIP_MENU();
					break;

			case GOSSIP_ACTION_INFO_DEF +9004:
					pPlayer->SummonCreature(60029,pPlayer->GetPositionX()+2 ,pPlayer->GetPositionY(), pPlayer->GetPositionZ(), 0,TEMPSUMMON_TIMED_DESPAWN,20000);
					pPlayer->CLOSE_GOSSIP_MENU();
					break;

            case GOSSIP_ACTION_INFO_DEF +9005:
					pPlayer->SummonCreature(60030,pPlayer->GetPositionX(),pPlayer->GetPositionY()+2, pPlayer->GetPositionZ()+2, 0,TEMPSUMMON_TIMED_DESPAWN,20000);
					pPlayer->CLOSE_GOSSIP_MENU();
					break;
			   
            case GOSSIP_ACTION_INFO_DEF +9006:
					pPlayer->SummonCreature(60031,pPlayer->GetPositionX()+2 ,pPlayer->GetPositionY(), pPlayer->GetPositionZ(), 0,TEMPSUMMON_TIMED_DESPAWN,20000);
					pPlayer->CLOSE_GOSSIP_MENU();
					break;
			   
            case GOSSIP_ACTION_INFO_DEF +9007:
					pPlayer->SummonCreature(60032,pPlayer->GetPositionX() ,pPlayer->GetPositionY()+2, pPlayer->GetPositionZ(), 0,TEMPSUMMON_TIMED_DESPAWN,20000);
					pPlayer->CLOSE_GOSSIP_MENU();
					break;
					
			/*case GOSSIP_ACTION_INFO_DEF +8:              
					pPlayer->SummonCreature(60033,pPlayer->GetPositionX() ,pPlayer->GetPositionY()+2, pPlayer->GetPositionZ(), 0,TEMPSUMMON_TIMED_DESPAWN,20000);
					pPlayer->CLOSE_GOSSIP_MENU();
					break;
					
			case GOSSIP_ACTION_INFO_DEF +70:
					pPlayer->SummonCreature(190108,pPlayer->GetPositionX() ,pPlayer->GetPositionY()+2, pPlayer->GetPositionZ(), 0,TEMPSUMMON_TIMED_DESPAWN,40000);
					pPlayer->CLOSE_GOSSIP_MENU();
					break;
					
			case GOSSIP_ACTION_INFO_DEF +71:
					pPlayer->SummonCreature(190109,pPlayer->GetPositionX() ,pPlayer->GetPositionY()+2, pPlayer->GetPositionZ(), 0,TEMPSUMMON_TIMED_DESPAWN,40000);
					pPlayer->CLOSE_GOSSIP_MENU();
					break;
					
			case GOSSIP_ACTION_INFO_DEF +72:
					pPlayer->SummonCreature(190110,pPlayer->GetPositionX() ,pPlayer->GetPositionY()+2, pPlayer->GetPositionZ(), 0,TEMPSUMMON_TIMED_DESPAWN,40000);
					pPlayer->CLOSE_GOSSIP_MENU();
					break;
					
			case GOSSIP_ACTION_INFO_DEF +73:
					pPlayer->SummonCreature(190111,pPlayer->GetPositionX() ,pPlayer->GetPositionY()+2, pPlayer->GetPositionZ(), 0,TEMPSUMMON_TIMED_DESPAWN,40000);
					pPlayer->CLOSE_GOSSIP_MENU();
					break;
			   
			case GOSSIP_ACTION_INFO_DEF +8:               
					pPlayer->SummonCreature(190112,pPlayer->GetPositionX() ,pPlayer->GetPositionY()+2, pPlayer->GetPositionZ(), 0,TEMPSUMMON_TIMED_DESPAWN,40000);
					pPlayer->CLOSE_GOSSIP_MENU();
					break;
					
			case GOSSIP_ACTION_INFO_DEF +9:               
					pPlayer->SummonCreature(190113,pPlayer->GetPositionX() ,pPlayer->GetPositionY()+4, pPlayer->GetPositionZ(), 0,TEMPSUMMON_TIMED_DESPAWN,40000);
					pPlayer->CLOSE_GOSSIP_MENU();
					break;
			case GOSSIP_ACTION_INFO_DEF +80:
					pPlayer->SummonCreature(210200,pPlayer->GetPositionX()+2 ,pPlayer->GetPositionY(), pPlayer->GetPositionZ(), 0,TEMPSUMMON_TIMED_DESPAWN,40000);
					pPlayer->CLOSE_GOSSIP_MENU();
					break; */

			case GOSSIP_ACTION_INFO_DEF + 12:
			{
				switch (pPlayer->GetTeamId())
				{
				case HORDE:
					pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Orgrimmar", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 13);
					pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Thunderbluff", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 14);
					pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Silvermoon", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 15);
					pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Undercity", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 16);

					break;
				case ALLIANCE:
					pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Stormwind", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 17);
					pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Ironforge", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 18);
					pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Exodar", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 19);
					pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Darnassus", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 20);

					break;
				}

				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "<- [Back]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11);
				pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());

				break;
			}
			case GOSSIP_ACTION_INFO_DEF + 13:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(1, 1629.36f, -4373.39f, 31.2564f, 3.54839f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 14:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(1, -1277.37f, 124.804f, 131.287f, 5.22274f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 15:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(530, 9487.69f, -7279.2f, 14.2866f, 6.16478f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 16:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, 1584.07f, 241.987f, -52.1534f, 0.049647f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 17:
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
				pPlayer->TeleportTo(1, 9949.56f, 2284.21f, 1341.4f, 1.59587f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 21:
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Dalaran", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 22);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Shattrath", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 23);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Booty Bay", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 24);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Gadgetzan", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 25);

				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "<- [Back]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11);
				pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());

				break;
			case GOSSIP_ACTION_INFO_DEF + 22:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(571, 5804.15f, 624.771f, 647.767f, 1.64f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 23:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(530, -1838.16f, 5301.79f, -12.428f, 5.9517f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 24:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, -14297.2f, 530.993f, 8.77916f, 3.98863f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 25:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(1, -7177.15f, -3785.34f, 8.36981f, 6.10237f);

				break;

			case GOSSIP_ACTION_INFO_DEF + 9999:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(530, 6119.060059f, 5665.311523f, 5.151441f, 1.027398f);

				break;

			case GOSSIP_ACTION_INFO_DEF + 26:
			{
				uint32 currHp = pPlayer->GetHealth();
				uint32 maxHp = pPlayer->GetMaxHealth();

				if (currHp == maxHp)
					ChatHandler(pPlayer->GetSession()).PSendSysMessage("Your HP is already full.", pPlayer->GetGUID());
				else
				{
					uint32 hdiff = maxHp - currHp;
					std::ostringstream ostr;
					ostr << "I have healed you for " << hdiff << " HP points.";
					pPlayer->SetHealth(maxHp);
					ChatHandler(pPlayer->GetSession()).PSendSysMessage(ostr.str().c_str(), pPlayer->GetGUID());
				}

				pPlayer->CLOSE_GOSSIP_MENU();
				break;
			}
			case GOSSIP_ACTION_INFO_DEF + 27:
			{
				if (pPlayer->HasAura(15007))
				{
					pPlayer->RemoveAura(15007);
					ChatHandler(pPlayer->GetSession()).PSendSysMessage("I have removed your ressurection sickness.", pPlayer->GetGUID());
				}
				else
					ChatHandler(pPlayer->GetSession()).PSendSysMessage("You don't have ressurection sickness.", pPlayer->GetGUID());

				pPlayer->CLOSE_GOSSIP_MENU();
				break;
			}
			case GOSSIP_ACTION_INFO_DEF + 28:
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Gurubashi Arena", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 29);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Circle of Blood Arena", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 30);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "The Ring of Trials", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 31);

				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "<- [Back]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11);
				pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());
				
				break;
			case GOSSIP_ACTION_INFO_DEF + 29:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, -13277.4f, 127.372f, 26.1418f, 1.11878f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 30:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(530, 2839.44f, 5930.17f, 11.1002f, 3.16284f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 31:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(530, -1999.94f, 6581.71f, 11.32f, 2.36528f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 32:
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "[Dungeons (1-60)] ->", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 33);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "[Dungeons (60-70)] ->", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 34);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "[Dungeons (70-80)] ->", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 35);

				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "<- [Back]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11);
				pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());
				
				break;
			case GOSSIP_ACTION_INFO_DEF + 33:
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Ragefire Chasm (15-21)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 36);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "The Deadmines (15-21)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 37);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Wailing Caverns (15-25)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 38);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Shadowfang Keep (16-26)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 39);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Blackfathom Deeps (20-30)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 40);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Stormwind Stockade (20-30)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 41);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Gnomeregan (24-34)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 42);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Scarlet Monastery (26-42)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 43);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Razorfen Kraul (30-40)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 44);

				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "[More] ->", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 45);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "<- [Back]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 32);

				pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());

				break;
			case GOSSIP_ACTION_INFO_DEF + 45:
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Maraudon (30-46)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 46);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Uldaman (35-45)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 47);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Razorfen Dawns (35-43)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 48);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Zul Farrak (40-48)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 49);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Sunken Temple (45-55)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 50);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Dire Maul (50-60)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 51);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Blackrock Depths (50-60)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 52);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Blackrock Spire (50-60)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 53);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Scholomance (50-60)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 54);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Stratholme (50-60)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 55);

				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "<- [Back]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 33);

				pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());
			
				break;
			case GOSSIP_ACTION_INFO_DEF + 36:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(1, 1811.78f, -4410.5f, -18.4704f, 5.20165f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 37:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, -11208.7f, 1673.52f, 24.6361f, 1.51067f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 38:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(1, -805.049f, -2032.03f, 95.8796f, 6.18912f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 39:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, -234.675f, 1561.63f, 76.8921f, 1.24031f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 40:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(1, 4249.99f, 740.102f, -25.671f, 1.34062f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 41:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, -8773.32f, 839.031f, 91.6376f, 0.648292f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 42:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, -5163.54f, 925.423f, 257.181f, 1.57423f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 43:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, -2843.0068f, -692.6104f, 139.3309f, 4.9819f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 44:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(1, -4470.28f, -1677.77f, 81.3925f, 1.16302f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 46:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(1, -1419.13f, 2908.14f, 137.464f, 1.57366f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 47:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, -6071.37f, -2955.16f, 209.782f, 0.015708f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 48:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(1, -4657.3f, -2519.35f, 81.0529f, 4.54808f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 49:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(1, -6801.19f, -2893.02f, 9.00388f, 0.158639f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 50:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, -10177.9f, -3994.9f, -111.239f, 6.01885f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 51:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(1, -3521.29f, 1085.2f, 161.097f, 4.7281f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 52:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, -7179.34f, -921.212f, 165.821f, 5.09599f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 53:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, -7527.05f, -1226.77f, 285.732f, 5.29626f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 54:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, 1269.64f, -2556.21f, 93.6088f, 0.620623f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 55:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, 3352.92f, -3379.03f, 144.782f, 6.25978f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 34:
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Hellfire Citadel (60-68)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 56);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Coilfang Reservoir (60-69)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 57);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Auchindoun (60-70)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 58);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Tempest Keep (60-70)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 59);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Caverns of Time (60-70)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 60);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Magisters' Terrace (68-72)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 61);

				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "<- [Back]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 32);

				pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());
			
				break;
			case GOSSIP_ACTION_INFO_DEF + 56:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(530, -390.863f, 3130.64f, 4.51327f, 0.218692f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 57:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(530, 735.066f, 6883.45f, -66.2913f, 5.89172f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 58:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(530, -3324.49f, 4943.45f, -101.239f, 4.63901f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 59:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(530, 3099.36f, 1518.73f, 190.3f, 4.72592f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 60:
			case GOSSIP_ACTION_INFO_DEF + 73:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(1, -8204.88f, -4495.25f, 9.0091f, 4.72574f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 61:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(530, 12884.6f, -7317.69f, 65.5023f, 4.799f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 35:
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Utgarde Keep (70-72)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 62);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "The Nexus (71-73)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 63);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Azjol-Nerub (72-74)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 64);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Ahn'Kahet: The Old Kingdom (73-75)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 65);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Drak'Tharon Keep (74-76)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 66);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "The Violet Hold (75-77)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 67);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Gundrak (76-78)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 68);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Halls of Stone (77-79)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 69);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Halls of Lightning (80)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 70);

				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "[More] ->", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 71);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "<- [Back]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 32);

				pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());

				break;
			case GOSSIP_ACTION_INFO_DEF + 71:
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "The Oculus (80)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 72);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Culling of Stratholme (80)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 73);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Utgarde Pinnacle (80)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 74);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Trial of Champion (80)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 75);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Pit of Saron (80)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 76);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Forge of Souls (80)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 77);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Halls of Reflection (80)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 78);

				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "<- [Back]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 35);

				pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());

				break;
			case GOSSIP_ACTION_INFO_DEF + 62:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(571, 1219.72f, -4865.28f, 41.2479f, 0.313228f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 63:
			case GOSSIP_ACTION_INFO_DEF + 72:
			case GOSSIP_ACTION_INFO_DEF + 101:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(571, 3781.81f, 6953.65f, 104.82f, 0.467432f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 64:
			case GOSSIP_ACTION_INFO_DEF + 65:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(571, 3707.86f, 2150.23f, 36.76f, 3.22f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 66:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(571, 4774.6f, -2032.92f, 229.15f, 1.59f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 67:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(571, 5696.73f, 507.4f, 652.97f, 4.03f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 68:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(571, 6898.72f, -4584.94f, 451.12f, 2.34455f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 69:
			case GOSSIP_ACTION_INFO_DEF + 70:
			case GOSSIP_ACTION_INFO_DEF + 102:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(571, 9049.37f, -1282.35f, 1060.19f, 5.8395f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 74:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(571, 1259.33f, -4852.02f, 215.763f, 3.48293f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 75:
			case GOSSIP_ACTION_INFO_DEF + 104:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(571, 8515.89f, 629.25f, 547.396f, 1.5747f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 76:
			case GOSSIP_ACTION_INFO_DEF + 77:
			case GOSSIP_ACTION_INFO_DEF + 78:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(571, 5638.26f, 2053.01f, 798.046f, 4.59295f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 79:
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "[Level 100 raids] ->", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 80);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "[Level 150 raids] ->", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 81);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "[Level 255 raids] ->", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 82);

				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "<- [Back]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11);

				pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());

				break;
			case GOSSIP_ACTION_INFO_DEF + 80:
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Zul'Gurub", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 83);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Molten Core", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 84);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Blackwing Lair", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 85);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Ahn'Qiraj Ruins", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 86);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Ahn'Qiraj Temple", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 87);

				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "<- [Back]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 79);

				pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());

				break;
			case GOSSIP_ACTION_INFO_DEF + 83:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, -11916.7f, -1215.72f, 92.289f, 4.72454f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 84:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(230, 1126.64f, -459.94f, -102.535f, 3.46095f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 85:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(229, 164.789f, -475.305f, 116.842f, 0.022714f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 86:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(1, -8409.82f, 1499.06f, 27.7179f, 2.51868f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 87:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(1, -8240.09f, 1991.32f, 129.072f, 0.941603f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 81:
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Karazhan", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 88);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Gruul's Lair", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 89);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Magtheridon's Lair", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 90);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Zul'Aman", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 91);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Serpentshrine Cavern", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 92);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Tempest Keep: The Eye", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 93);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Hyjal", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 94);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Black Temple", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 95);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Sunwell Plateau", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 96);

				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "<- [Back]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 79);
				pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());
			
				break;
			case GOSSIP_ACTION_INFO_DEF + 88:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, -11118.9f, -2010.33f, 47.0819f, 0.649895f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 89:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(530, 3530.06f, 5104.08f, 3.50861f, 5.51117f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 90:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(530, -312.7f, 3087.26f, -116.52f, 5.19026f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 91:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(530, 6851.78f, -7972.57f, 179.242f, 4.64691f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 92:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(530, 820.025f, 6864.93f, -66.7556f, 6.28127f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 93:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(530, 3088.49f, 1381.57f, 184.863f, 4.61973f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 94:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(1, -8177.89f, -4181.23f, -167.552f, 0.913338f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 95:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(530, -3649.92f, 317.469f, 35.2827f, 2.94285f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 96:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(530, 12574.1f, -6774.81f, 15.0904f, 3.13788f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 82:
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Naxxramas", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 97);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Obsidian Sanctum", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 98);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Ruby Sanctum", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 99);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Vault of Archavon", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 100);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Eye of Eternity", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 101);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Ulduar", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 102);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Icecrown Citadel", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 103);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Trial of the Crusader", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 104);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Onyxia's Lair", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 105);

				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "<- [Back]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 79);

				pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());

				break;
			case GOSSIP_ACTION_INFO_DEF + 97:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(571, 3668.72f, -1262.46f, 243.622f, 4.785f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 98:
			case GOSSIP_ACTION_INFO_DEF + 99:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(571, 3479.66f, 264.625f, -120.144f, 0.097f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 100:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(571, 5453.72f, 2840.79f, 421.28f, 0.0f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 103:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(571, 5873.82f, 2110.98f, 636.011f, 3.5523f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 105:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(1, -4708.27f, -3727.64f, 54.5589f, 3.72786f);

				break;
				case GOSSIP_ACTION_INFO_DEF + 2301:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, -1688.336182f, -4273.490723f, 1.998409f, 2.593258f);

				break;
				case GOSSIP_ACTION_INFO_DEF + 2303:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, 2499.770020f, -41.674599f, 24.625900f, 2.940340f);

				break;
				case GOSSIP_ACTION_INFO_DEF + 2304:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(1, -7721.725586f, -3542.335693f, 37.024323f, 5.384436f);

				break;
				case GOSSIP_ACTION_INFO_DEF + 2306:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(530, -2543.280273f, 934.985901f, 87.440941f, 5.518139f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 106:
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "[Eastern Kingdoms] ->", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 107);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "[Kalimdor] ->", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 108);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "[Outland] ->", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 109);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "[Northrend] ->", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 110);

				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "<- [Back]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11);
				pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());

				break;
			case GOSSIP_ACTION_INFO_DEF + 107:
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Eversong Woods (1-10)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 111);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Tirisfal Glades (1-10)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 112);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Dun Morogh (1-10)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 113);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Elwynn Forest (1-10)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 114);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Ghostlands (10-20)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 115);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Silverpine Forest (10-20)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 116);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Westfall (10-20)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 117);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Loch Modan (10-20)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 118);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Redridge Mountains (15-25)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 119);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Duskwood (18-30)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 120);

				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "[More] ->", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 121);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "<- [Back]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 106);
				pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());

				break;
			case GOSSIP_ACTION_INFO_DEF + 121:
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Wetlands (20-30)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 122);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Hillsbrad Foothills (20-30)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 123);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Alterac Mountains (30-40)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 124);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Arathi Highlands (30-40)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 125);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Stranglethorn Vale (30-45)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 126);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Swamp of Sorrows (35-45)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 127);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Badlads (35-45)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 128);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "The Hinterlands (40-50)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 129);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Searing Gorge (43-50)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 130);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Blasted Lands (45-55)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 131);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Burning Steppes (50-58)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 132);

				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "[More] ->", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 133);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "<- [Back]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 107);
				pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());

				break;
			case GOSSIP_ACTION_INFO_DEF + 133:
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Western Plaguelands (51-58)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 134);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Eastern Plaguelands (53-60)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 135);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Deadwind Pass (55-60)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 136);

				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "<- [Back]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 121);
				pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());

				break;
			case GOSSIP_ACTION_INFO_DEF + 111:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(530, 9079.92f, -7193.23f, 55.6013f, 5.94597f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 112:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, 2036.02f, 161.331f, 33.8674f, 0.143896f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 11:
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Mall ->", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 910);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "[Home cities] ->", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 12);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "[Neutral cities] ->", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 21);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "[Arenas] ->", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 28);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "[Dungeons] ->", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 32);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "[Raids] ->", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 79);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "[Zones] ->", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 106);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "[World Bosses] ->", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 310);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "[Quest/Armor Zones] ->", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 610);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "[|cffFF0000Hell's|r Legion Lv.255] ->", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 619);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "[Event Zone] ->", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 810);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "[Leveling zone] ->", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8000);
				//pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "[Farm Zone]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 710);
				
				if (pPlayer->GetTeamId() == HORDE)
				{					
					pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Horde Demon of The Sky", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 302);
				}
				else
				{					
					pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Alliance Demon of The Sky", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 303);
				}
				
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "<- [Main menu]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);

				pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());
				break;
				
			case GOSSIP_ACTION_INFO_DEF + 113:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, -5451.55f, -656.992f, 392.675f, 0.66789f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 114:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, -9617.06f, -288.949f, 57.3053f, 4.72687f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 115:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(530, 7360.86f, -6803.3f, 44.2942f, 5.83679f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 116:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, 878.74f, 1359.33f, 50.355f, 5.89929f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 117:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, -10235.2f, 1222.47f, 43.6252f, 6.2427f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 118:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, -5202.94f, -2855.18f, 336.822f, 0.37651f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 119:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, -9551.81f, -2204.73f, 93.473f, 5.47141f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 120:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, -10898.3f, -364.784f, 39.2681f, 3.04614f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 122:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, -3242.81f, -2469.04f, 15.9226f, 6.03924f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 123:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, -436.657f, -581.254f, 53.5944f, 1.25917f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 124:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, 370.763f, -491.355f, 175.361f, 5.37858f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 125:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, -1508.51f, -2732.06f, 32.4986f, 3.35708f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 126:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, -12644.3f, -377.411f, 10.1021f, 6.09978f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 127:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, -10345.4f, -2773.42f, 21.99f, 5.08426f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 128:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, -6779.2f, -3423.64f, 241.667f, 0.647481f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 129:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, 119.387f, -3190.37f, 117.331f, 2.34064f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 130:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, -7012.47f, -1065.13f, 241.786f, 5.63162f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 131:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, -11182.5f, -3016.67f, 7.42235f, 4.0004f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 132:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, -8118.54f, -1633.83f, 132.996f, 0.089067f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 134:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, 1728.65f, -1602.25f, 63.429f, 1.6558f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 135:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, 2300.97f, -4613.36f, 73.6231f, 0.367722f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 136:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, -10438.8f, -1932.75f, 104.617f, 4.77402f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 108:
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Teldrassil (1-10)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 137);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Azuremyst Isle (1-10)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 138);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Durotar (1-10)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 139);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Mulgore (1-10)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 140);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Bloodmyst Isle (10-20)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 141);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Darkshore (10-20)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 142);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "The Barrens (10-25)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 143);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Stonetalon Mountains (15-27)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 144);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Ashenvale (18-30)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 145);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Thousand Needles (25-35)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 146);

				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "[More] ->", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 147);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "<- [Back]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 106);
				pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());

				break;
			case GOSSIP_ACTION_INFO_DEF + 147:
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Desolace (30-40)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 148);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Dustwallow Marsh (35-45)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 149);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Tanaris (40-50)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 150);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Feralas (40-50)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 151);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Azshara (45-55)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 152);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Felwood (48-55)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 153);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Un'Goro Crater (45-55)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 154);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Silithus (55-60)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 155);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Winterspring (55-60)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 156);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Moonglade (1-80)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 157);

				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "<- [Back]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 108);
				pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());

				break;
			case GOSSIP_ACTION_INFO_DEF + 137:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(1, 10111.3f, 1557.73f, 1324.33f, 4.04239f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 138:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(530, -4216.87f, -12336.9f, 4.34247f, 6.02008f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 139:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(1, 1007.78f, -4446.22f, 11.2022f, 0.20797f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 140:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(1, -2192.62f, -736.317f, -13.3274f, 0.487569f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 141:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(530, -1993.62f, -11475.8f, 63.9657f, 5.29437f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 142:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(1, 5756.25f, 298.505f, 20.6049f, 5.96504f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 143:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(1, 884.54f, -3548.45f, 91.8532f, 2.95957f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 144:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(1, 1570.92f, 1031.52f, 137.959f, 3.33006f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 145:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(1, 1928.34f, -2165.95f, 93.7896f, 0.205731f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 146:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(1, -4969.02f, -1726.89f, -62.1269f, 3.7933f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 148:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(1, -606.395f, 2211.75f, 92.9818f, 0.809746f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 149:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(1, -4043.65f, -2991.32f, 36.3984f, 3.37443f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 150:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(1, -7931.2f, -3414.28f, 80.7365f, 0.66522f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 151:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(1, -4841.19f, 1309.44f, 81.3937f, 1.48501f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 152:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(1, 3341.36f, -4603.79f, 92.5027f, 5.28142f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 153:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(1, 4102.25f, -1006.79f, 272.717f, 0.790048f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 154:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(1, -7943.22f, -2119.09f, -218.343f, 6.0727f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 155:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(1, -7426.87f, 1005.31f, 1.13359f, 2.96086f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 156:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(1, 6759.18f, -4419.63f, 763.214f, 4.43476f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 157:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(1, 7654.3f, -2232.87f, 462.107f, 5.96786f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 109:
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Hellfire Peninsula (58-63)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 158);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Zangarmarsh (60-64)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 159);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Terokkar Forest (62-65)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 160);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Nagrand (64-67)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 161);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Blade's Edge Mountains (65-68)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 162);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Shadowmoon Valley (67-70)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 163);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Netherstorm (67-70)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 164);

				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "<- [Back]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 106);
				pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());

				break;
			case GOSSIP_ACTION_INFO_DEF + 158:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(530, -211.237f, 4278.54f, 86.5678f, 4.59776f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 159:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(530, -54.8621f, 5813.44f, 20.9764f, 0.081722f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 160:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(530, -2000.47f, 4451.54f, 8.37917f, 4.40447f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 161:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(530, -1145.95f, 8182.35f, 3.60249f, 6.13478f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 162:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(530, 3037.67f, 5962.86f, 130.774f, 1.27253f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 163:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(530, -3179.6f, 2716.43f, 68.6444f, 4.16414f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 164:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(530, 3830.23f, 3426.5f, 88.6145f, 5.16677f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 110:
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Borean Tundra (68-72)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 165);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Howling Fjord (68-72)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 166);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Dragonblight (71-74)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 167);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Grizzly Hills (73-75)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 168);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Zul'Drak (74-77)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 169);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Sholazar Basin (76-78)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 170);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Crystalsong Forest (77-80)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 171);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "The Storm Peaks (77-80)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 172);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Icecrown (77-80)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 173);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Wintergrasp (PvP)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 174);

				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "<- [Back]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 106);
				pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());

				break;
			case GOSSIP_ACTION_INFO_DEF + 165:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(571, 3256.57f, 5278.23f, 40.8046f, 0.246367f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 166:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(571, 1902.15f, -4883.91f, 171.363f, 3.11537f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 167:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(571, 4103.36f, 264.478f, 50.5019f, 3.09349f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 168:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(571, 4391.73f, -3587.92f, 238.531f, 3.57526f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 169:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(571, 5560.23f, -3211.66f, 371.709f, 5.55055f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 170:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(571, 5323, 4942, -133.5f, 2.17f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 171:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(571, 5659.35f, 359.053f, 158.214f, 3.69933f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 172:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(571, 7527.14f, -1260.89f, 919.049f, 2.0696f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 173:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(571, 7253.64f, 1644.78f, 433.68f, 4.83412f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 174:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(571, 4760.7f, 2143.7f, 423, 1.13f);

				//mall faction
				break;
			case GOSSIP_ACTION_INFO_DEF + 175:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(1, 7492.0600f, -1509.7900f, 161.61099f, 5.03353f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 176:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, 23.7815f, -1599.3199f, 195.4190f, 1.5944f);
				break;
				
				//custom zones
				case GOSSIP_ACTION_INFO_DEF + 310:
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Scorched Guardian Relics", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 304);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Unholy Dragon PvE", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 305);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Eve's Bags PvE", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 306);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Gold Dragon Quest Lv.255", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 307);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "The Verdant Passage Weapons", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 308);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Church of Holy Light PvE", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 309);
				//pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Dawn of Vengeance (Tier1)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 311);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Magistery Keep PvE", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 313);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Forgotten lands Bags PvE", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 314);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Beast Me Up PvE", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 315);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Take Down The LK PvE", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 316);
				
				//pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "[More] ->", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3100);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "<- [Back]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11);
				pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());
				break;
				
				case GOSSIP_ACTION_INFO_DEF + 3100:
				//pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Hearth of Shapirra", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 317);
				//pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Magister Boss", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 318);
				//pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Legend Boss in Naxxramas", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 319);
				//pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Mr. Pumpkin", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 320);
				
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "<- [Back]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 310);
				pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());
				break;
				
				
				case GOSSIP_ACTION_INFO_DEF + 710:
				//pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Gold", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7101);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Farm Boss", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7102);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Blue Temple", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7104);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Wrath King", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7105);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Soul Skulls", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7106);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "King Zarak", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7107);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Leader Slayer ( Achievement)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7103);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "<- [Back]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11);
				pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());
				break;
				
				//gold
			case GOSSIP_ACTION_INFO_DEF + 7101:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, -5351.8266f, -2534.0097f, 484.1956f, 0.6969f);
				break;				
				//farm boss
			case GOSSIP_ACTION_INFO_DEF + 7102:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(571, 7085.63f, -1805.78f, 822.603f, 1.88154f);
				break;
			case GOSSIP_ACTION_INFO_DEF + 7105:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(1, 1540.15f, -2824.33f, 183.328f, 5.55234f);
				break;
			case GOSSIP_ACTION_INFO_DEF + 7106:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(530, 3081.04f, 6914.85f, 367.948f, 3.31771f);
				break;
			case GOSSIP_ACTION_INFO_DEF + 7107:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(530, -1633.28f, -10671.1f, 146.859f, 0.227153f);
				break;
			case GOSSIP_ACTION_INFO_DEF + 7103:				
				if(pPlayer->GetTeamId() == HORDE)
					{
					pPlayer->CLOSE_GOSSIP_MENU();
					pPlayer->TeleportTo(0, -8552.08f, 471.941f, 105.800f, 5.38456f);				
					}
						else
					{
					pPlayer->CLOSE_GOSSIP_MENU();
					pPlayer->TeleportTo(1, 1934.77f, -4366.29f, 23.9682f, 1.6695f);				
					}
					break;
			case GOSSIP_ACTION_INFO_DEF + 7104:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(530, -3795.17f, 2664.97f, 104.262f, 4.72127f);
				break;
				
				//Mall non pvp
			case GOSSIP_ACTION_INFO_DEF + 910:
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Starting Tier's Questing", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9101);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Dark Portal Mall", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9102);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "<- [Back]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11);
			pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());
				break;
				
			case GOSSIP_ACTION_INFO_DEF + 9101: //Frozen city
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(1,7419.6625f, -1579.8883f, 179.8158f, 5.4945f);
				break;
			case GOSSIP_ACTION_INFO_DEF + 9102:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(530, -248.5119f, 934.2169f, 85.1288f, 1.5998f);
				break;
				//horde demon of sky boss
			case GOSSIP_ACTION_INFO_DEF + 302:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(571, 2799.4099f, -3788.6699f, 256.1020f, 2.1587f);
				break;
				//ally demon of sky boss
			case GOSSIP_ACTION_INFO_DEF + 303:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(571, 2799.4099f, -3788.6699f, 256.1020f, 2.1587f);
				break;
				//ult reward
			case GOSSIP_ACTION_INFO_DEF + 304:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(309,-12019.5996f, -2585.6699f,-29.66220f, 2.9838f);
				break;
				//unholy dragon
			case GOSSIP_ACTION_INFO_DEF + 305:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(309,-10896.0000f,-1345.2600f,53.4098f,2.9731f);
				break;
				//nice bags
			case GOSSIP_ACTION_INFO_DEF + 306:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(571,6058.3798f,774.1829f,563.7009f,1.0925f);
				break;
				//gold dragon
			case GOSSIP_ACTION_INFO_DEF + 307:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(530,-3877.0300f,295.90600f,137.1739f,3.9089f);
				break;
				//The Verdant
			case GOSSIP_ACTION_INFO_DEF + 308:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(1, -2940.6501f, 1914.4202f, 35.0868f, 5.8639f);
				break;
				//supr killer
			case GOSSIP_ACTION_INFO_DEF + 309:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, 1631.6723f, -5487.9555f, 101.7927f, 1.2080f);
				break;
				//vengeance
			case GOSSIP_ACTION_INFO_DEF + 311:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(1, 4850.5976f, -1778.4901f, 1161.3669f, 5.2461f);
				break;
				//scarl
			case GOSSIP_ACTION_INFO_DEF + 313:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(571, 5672.1997f, 1014.8188f, 175.2920f, 0.0738f);
				break;
				//Forgotten
			case GOSSIP_ACTION_INFO_DEF + 314:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(571, 2353.2099f, 6643.8999f, 49.9217f, 5.2893f);
				break;
				//Beast
			case GOSSIP_ACTION_INFO_DEF + 315:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(571,7381.1391f,-528.4933f,1897.4967f,6.1771f);
				break;
				//LK
			case GOSSIP_ACTION_INFO_DEF + 316:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(571,5631.6811f,2022.5500f,1544.6900f,5.1317f);
				break;
				//shappira
			case GOSSIP_ACTION_INFO_DEF + 317:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, -8378.66f, -2536.41f, 136.621f, 0.0882246f);
				break;
				//masigister
			case GOSSIP_ACTION_INFO_DEF + 318:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, -7684.96f, -711.271f, 184.706f, 6.24926f);
				break;
			case GOSSIP_ACTION_INFO_DEF + 319:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(533, 3498.33f, -5350.11f, 144.968f, 1.37456f);
				break;
			case GOSSIP_ACTION_INFO_DEF + 320:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(571, 4298.77f, 1868.45f, 354.036f, 4.77382f);
				break;
				
				//Hell's legion Lv.255
				case GOSSIP_ACTION_INFO_DEF + 619:
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|cffFF0000Hell's|r Exiled Lv.1 Jewels", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 640);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|cffFF0000Hell's|r Orbital Lv.1 Weapons", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 641);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|cffFF0000Hell's|r Extinct Lv.2 Jewels", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 642);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|cffFF0000Hell's|r Extinct Lv.2 Weapons", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 643);
				//pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "The Inventor's Library", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 644);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|cffFF0000Hell's|r Enigmatic Lv.3 Jewels", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 645);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|cffFF0000Hell's|r Enigmatic Lv.3 Weapons", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 647);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Valkyrion (Gems's)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 646);

				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "<- [Back]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11);
				pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());

				break;

				//Band of Variance
				case GOSSIP_ACTION_INFO_DEF + 640:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(571, 3876.1599f, 6984.4399f, 106.9290f, 6.2790f);
				break;

				//Waygate Basin
				case GOSSIP_ACTION_INFO_DEF + 641:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(571, 4914.9125f, 5189.9370f, -92.2451f, 0.4303f);
				break;

				//Thor Modan Hills
				case GOSSIP_ACTION_INFO_DEF + 642:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(571, 4659.0219f, -4378.7290f, 186.6241f, 5.5198f);
				break;

				//Terrace of the Makers
				case GOSSIP_ACTION_INFO_DEF + 643:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(571, 7760.9150f, -2163.4450f, 1233.8795f, 1.4836f);
				break;

				//The Inventor's Library
				case GOSSIP_ACTION_INFO_DEF + 644:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(571, 8211.4589f, -772.6856f, 963.2974f, 4.4799f);
				break;

				//Hall of the Conquered Kings
				case GOSSIP_ACTION_INFO_DEF + 645:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(619, 377.7231f, -1081.1236f, 48.3137f, 0.6070f);
				break;

				//Valkyrion
				case GOSSIP_ACTION_INFO_DEF + 646:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(571, 7161.6733f, -124.4768f, 773.1715f, 0.6885f);
				break;

				//Fallen Temple of Ahn'Kahet
				case GOSSIP_ACTION_INFO_DEF + 647:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(619, 483.9133f, -799.3528f, -23.2977f, 2.5694f);
				break;

				//Armor zones
				case GOSSIP_ACTION_INFO_DEF + 610:
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Underworld Drake's PvE", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 611);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Curse of the Blood Weapons & Gear PvE", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 612);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Labyrinth Depths PvE", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 613);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Prison of Immol'thar PvE", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 616);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Supremacy of Jewelrys & Weapons ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 617);
				//pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Forgotten quarries (Raid T2)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 614);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Reverse Blackwing Lair PvE", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 615);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Middle earth of Battles", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 618);
				
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "<- [Back]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11);
				pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());

				break;
				
				//Bonech
				case GOSSIP_ACTION_INFO_DEF + 611:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(530, 2262.7087f, 5398.8842f, 146.5232f, 2.3385f);
				break;
				
				//fatty
				case GOSSIP_ACTION_INFO_DEF + 612:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(530, 6666.8823f, -6462.0043f, 30.1492f, 2.7261f);
				break;
				
				//dream
				case GOSSIP_ACTION_INFO_DEF + 613:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(230, 683.0274f, 159.4824f, -71.6449f, 4.1701f);
				break;
				
				//Immol
				case GOSSIP_ACTION_INFO_DEF + 616:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(429, 50.3194f, 506.7799f, -22.8355f, 1.5719f);
				break;
				
				//skull
				case GOSSIP_ACTION_INFO_DEF + 614:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(532, -11059.9892f, -1952.3623f, 273.7211f, 0.1552f);
				break;
				
				//Frozen
				case GOSSIP_ACTION_INFO_DEF + 615:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(469, -7587.7597f, -1261.4300f, 482.0328f, 0.6100f);
				break;
				
				//Supremacy of Jewelrys
				case GOSSIP_ACTION_INFO_DEF + 617:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, -785.3831f, 1541.9107f, 21.7619f, 2.6789f);
				break;

				//Middle earth of Battles Lv.255
				case GOSSIP_ACTION_INFO_DEF + 618:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(571, 1647.1600f, -4122.1000f, 275.9630f, 0.2373f);
				break;

				//event zones
				case GOSSIP_ACTION_INFO_DEF + 810:
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Stair Event", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 811);
				//pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Empty Event ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 812);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Impossible Event ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 813);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Maze Event ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 814);
				
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "<- [Back]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11);
				pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());
				break;
				
				//easy
				case GOSSIP_ACTION_INFO_DEF + 811:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(1,2920.26f, 2974.38f, 1.61716f, 4.19481f);
				break;
				case GOSSIP_ACTION_INFO_DEF + 812:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(1, 2031.44f, 2020.12f, 131.414f, 6.25565f);
				break;
				case GOSSIP_ACTION_INFO_DEF + 813:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, -7076.0283f, -157.9863f, 62.0753f, 4.9801f);
				break;
				case GOSSIP_ACTION_INFO_DEF + 814:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, -7388.9252f, 795.6946f, 132.2962f, 3.0955f);
				break;
				
				//Leveling zone
				case GOSSIP_ACTION_INFO_DEF + 8000:
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Leveling -> Path of Glory", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8001);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Leveling -> Hyjal", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8002);
				
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "<- [Back]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11);
				pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());
				break;
				
				//zone 2
				case GOSSIP_ACTION_INFO_DEF + 8001:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(530, -244.589f, 1201.62f, 41.3002f,1.48212f);
				break;
				
				//zone 2
				case GOSSIP_ACTION_INFO_DEF + 8002:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(1, 4630.5698f, -3832.1559f, 943.40002f, 1.1481f);
				break;
				
				case GOSSIP_ACTION_INFO_DEF + 2500:
					pPlayer->AddAura(48161, pPlayer); // target, spellid, triggered-e
					pPlayer->AddAura(33077, pPlayer);
					pPlayer->AddAura(20217, pPlayer);
					pPlayer->AddAura(48932, pPlayer);
					pPlayer->AddAura(48469, pPlayer);
					pPlayer->AddAura(48469, pPlayer);
					pPlayer->AddAura(42995, pPlayer);
					pPlayer->AddAura(20911, pPlayer);
					pPlayer->AddAura(48073, pPlayer);
					pPlayer->AddAura(48169, pPlayer);
					pPlayer->AddAura(7764,  pPlayer);
					pPlayer->AddAura(16612, pPlayer);
					pPlayer->AddAura(33078, pPlayer);
					pPlayer->AddAura(33079, pPlayer);
					pPlayer->AddAura(33080, pPlayer);
					pPlayer->AddAura(33081, pPlayer);
					pPlayer->AddAura(33082, pPlayer);
					pPlayer->AddAura(24705, pPlayer);
					pPlayer->AddAura(26035, pPlayer);
					
					pCreature->MonsterSay("Enjoy your buffs, and remember to vote!", LANG_UNIVERSAL, NULL);
					pPlayer->CLOSE_GOSSIP_MENU();
					break;
			
			case GOSSIP_ACTION_INFO_DEF + 177:
				 pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Dark War Talbuk (ground)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 178);
				 pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Deathcharger (ground)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 179);
				 pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Swift Zulian Tiger (ground)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 180);
				 pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "White Polar Bear (ground)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 181);
				 pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Great Brewfest Kodo (ground)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 182);
				 pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Cobalt Netherwing Drake (flying)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 183);
				 pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Reins of Raven Lord (ground)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 184);
				 pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Ironbound Proto-Drake (flying)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 185);

				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "<- [Back]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 450);
				pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());

				break;
			case GOSSIP_ACTION_INFO_DEF + 178:
				if (PlayerHasItemOrSpell(pPlayer, 29228, 34790))
					pPlayer->SendEquipError(EQUIP_ERR_CANT_CARRY_MORE_OF_THIS, NULL, NULL);
				else
				{
					pPlayer->AddItem(29228, 1);
					ChatHandler(pPlayer->GetSession()).PSendSysMessage("Enjoy your Dark War Talbuk!", pPlayer->GetGUID());
				}
				pPlayer->CLOSE_GOSSIP_MENU();
				break;
			case GOSSIP_ACTION_INFO_DEF + 179:
				if (PlayerHasItemOrSpell(pPlayer, 13335, 17481))
					pPlayer->SendEquipError(EQUIP_ERR_CANT_CARRY_MORE_OF_THIS, NULL, NULL);
				else
				{
					pPlayer->AddItem(13335, 1);
					ChatHandler(pPlayer->GetSession()).PSendSysMessage("Enjoy your Deathcharger!", pPlayer->GetGUID());
				}
				pPlayer->CLOSE_GOSSIP_MENU();
				break;
			case GOSSIP_ACTION_INFO_DEF + 180:
				if (PlayerHasItemOrSpell(pPlayer, 19902, 24252))
					pPlayer->SendEquipError(EQUIP_ERR_CANT_CARRY_MORE_OF_THIS, NULL, NULL);
				else
				{
					pPlayer->AddItem(19902, 1);
					ChatHandler(pPlayer->GetSession()).PSendSysMessage("Enjoy your Swift Zulian Tiger!", pPlayer->GetGUID());
				}
				pPlayer->CLOSE_GOSSIP_MENU();
				break;
			case GOSSIP_ACTION_INFO_DEF + 181:
				if (PlayerHasItemOrSpell(pPlayer, 43962, 54753))
					pPlayer->SendEquipError(EQUIP_ERR_CANT_CARRY_MORE_OF_THIS, NULL, NULL);
				else
				{
					pPlayer->AddItem(43962, 1);
					ChatHandler(pPlayer->GetSession()).PSendSysMessage("Enjoy your White Polar Bear!", pPlayer->GetGUID());
				}
				pPlayer->CLOSE_GOSSIP_MENU();
				break;
			case GOSSIP_ACTION_INFO_DEF + 182:
				if (PlayerHasItemOrSpell(pPlayer, 37828, 49379))
					pPlayer->SendEquipError(EQUIP_ERR_CANT_CARRY_MORE_OF_THIS, NULL, NULL);
				else
				{
					pPlayer->AddItem(37828, 1);
					ChatHandler(pPlayer->GetSession()).PSendSysMessage("Enjoy your Great Brewfest Kodo!", pPlayer->GetGUID());
				}
				pPlayer->CLOSE_GOSSIP_MENU();
				break;
			case GOSSIP_ACTION_INFO_DEF + 183:
				if (PlayerHasItemOrSpell(pPlayer, 32859, 41515))
					pPlayer->SendEquipError(EQUIP_ERR_CANT_CARRY_MORE_OF_THIS, NULL, NULL);
				else
				{
					pPlayer->AddItem(32859, 1);
					ChatHandler(pPlayer->GetSession()).PSendSysMessage("Enjoy your Cobalt Netherwing Drake!", pPlayer->GetGUID());
				}
				pPlayer->CLOSE_GOSSIP_MENU();
				break;
			case GOSSIP_ACTION_INFO_DEF + 184:
				if (PlayerHasItemOrSpell(pPlayer, 32458, 40192))
					pPlayer->SendEquipError(EQUIP_ERR_CANT_CARRY_MORE_OF_THIS, NULL, NULL);
				else
				{
					pPlayer->AddItem(32768, 1);
					ChatHandler(pPlayer->GetSession()).PSendSysMessage("Enjoy your Reins of Raven Lord!", pPlayer->GetGUID());
				}
				pPlayer->CLOSE_GOSSIP_MENU();
				break;
			case GOSSIP_ACTION_INFO_DEF + 185:
				if (PlayerHasItemOrSpell(pPlayer, 45801, 63956))
					pPlayer->SendEquipError(EQUIP_ERR_CANT_CARRY_MORE_OF_THIS, NULL, NULL);
				else
				{
					pPlayer->AddItem(45801, 1);
					ChatHandler(pPlayer->GetSession()).PSendSysMessage("Enjoy your Ironbound Proto-Drake!", pPlayer->GetGUID());
				}
				pPlayer->CLOSE_GOSSIP_MENU();
				break;
				
			case GOSSIP_ACTION_INFO_DEF + 186:
				GiveRidingSkill(pPlayer, pCreature);
				pPlayer->CLOSE_GOSSIP_MENU();
				break;
			/*case GOSSIP_ACTION_INFO_DEF + 187:
				if(pPlayer->GetClass() == CLASS_BERSERKER)
				{
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Reset Talents",GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7100);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Reset Spells", GOSSIP_SENDER_MAIN,GOSSIP_ACTION_INFO_DEF + 7200);
				}
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "<- [Back]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 450);
				pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());
				break;*/
				
			case GOSSIP_ACTION_INFO_DEF +7100: // Reset Talents
                        pPlayer->resetTalents(true);
                        pPlayer->SendTalentsInfoData(false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                        break;
            case GOSSIP_ACTION_INFO_DEF +7200: // Reset Spells
                        pPlayer->resetSpells();
                        pPlayer->CLOSE_GOSSIP_MENU();
                        break;

			//spell classess			
			case GOSSIP_ACTION_INFO_DEF + 460:				
					if(pPlayer->getClass() == CLASS_WARRIOR)
						{
						pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Learn for my class spell.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3000);
						}
					if(pPlayer->getClass() == CLASS_DEATH_KNIGHT)
						{
						pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Learn for my class spell.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3001);
						}			 
					if(pPlayer->getClass() == CLASS_DRUID)
						{
						pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Learn for my class spell.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3002);
						}			 
					if(pPlayer->getClass() == CLASS_HUNTER)
						{
						pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Learn for my class spell.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3003);
						}			 
					if(pPlayer->getClass() == CLASS_MAGE)
						{
						pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Learn for my class spell.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3004);
						}			 
					if(pPlayer->getClass() == CLASS_PALADIN)
						{
						pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Learn for my class spell.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3005);
						}			 
					if(pPlayer->getClass() == CLASS_PRIEST)
						{
						pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Learn for my class spell.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3006);
						}			 
					if(pPlayer->getClass() == CLASS_ROGUE )
						{
						pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Learn for my class spell.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3007);
						}			 
					if(pPlayer->getClass() == CLASS_SHAMAN)
						{
						pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Learn for my class spell.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3008);
						}			 
					if(pPlayer->getClass() == CLASS_WARLOCK)
						{
						pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Learn for my class spell.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3009);
						}
					/*if(pPlayer->GetClass() == CLASS_BERSERKER)
						{
						pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Learn for my class spell.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3010);
						}*/
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "<- [Back]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
				pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());
				break;
			case GOSSIP_ACTION_INFO_DEF + 3010:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->learnSpell(2457);
				pPlayer->learnSpell(1715);
				pPlayer->learnSpell(2687);
				pPlayer->learnSpell(71);
				pPlayer->learnSpell(355);
				pPlayer->learnSpell(7384);
				pPlayer->learnSpell(72);
				pPlayer->learnSpell(694);
				pPlayer->learnSpell(2565);
				pPlayer->learnSpell(676);
				pPlayer->learnSpell(20230);
				pPlayer->learnSpell(12678);
				pPlayer->learnSpell(5246);
				pPlayer->learnSpell(1161);
				pPlayer->learnSpell(871);
				pPlayer->learnSpell(2458);
				pPlayer->learnSpell(20252);
				pPlayer->learnSpell(18449);
				pPlayer->learnSpell(1680);
				pPlayer->learnSpell(6552);
				pPlayer->learnSpell(34428);
				pPlayer->learnSpell(23920);
				pPlayer->learnSpell(3411);
				pPlayer->learnSpell(55694);
				pPlayer->learnSpell(47450);
				pPlayer->learnSpell(60220);
				pPlayer->learnSpell(47867);
				pPlayer->learnSpell(47889);
				pPlayer->learnSpell(48018);
				pPlayer->learnSpell(47811);
				pPlayer->learnSpell(14063);				
				//lang
				pPlayer->learnSpell(668);
				pPlayer->learnSpell(669);
				pPlayer->learnSpell(46917);
				pPlayer->learnSpell(674);
				pPlayer->learnSpell (23881);
				pPlayer->learnSpell (100);
				pPlayer->learnSpell (59653);
				pPlayer->learnSpell (12162);
				pPlayer->learnSpell (12850);
				pPlayer->learnSpell (12868);
				pPlayer->learnSpell (12834);
				pPlayer->learnSpell (5308);
				pPlayer->learnSpell (58367);
				pPlayer->learnSpell (63326);
				pPlayer->learnSpell (65156);
				pPlayer->learnSpell (64976);
				pPlayer->learnSpell (12975);
				pPlayer->learnSpell (50783);
				pPlayer->learnSpell (12328);
				pPlayer->learnSpell (53385);

				pPlayer->learnSpell (20911);
				pPlayer->learnSpell (25899);
				pPlayer->learnSpell (51722);
				pPlayer->learnSpell (68066);
				break;
				
			case GOSSIP_ACTION_INFO_DEF + 3000:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->learnSpell(2457);
				pPlayer->learnSpell(1715);
				pPlayer->learnSpell(2687);
				pPlayer->learnSpell(71);
				pPlayer->learnSpell(355);
				pPlayer->learnSpell(7384);
				pPlayer->learnSpell(72);
				pPlayer->learnSpell(694);
				pPlayer->learnSpell(2565);
				pPlayer->learnSpell(676);
				pPlayer->learnSpell(20230);
				pPlayer->learnSpell(12678);
				pPlayer->learnSpell(5246);
				pPlayer->learnSpell(1161);
				pPlayer->learnSpell(871);
				pPlayer->learnSpell(2458);
				pPlayer->learnSpell(20252);
				pPlayer->learnSpell(18449);
				pPlayer->learnSpell(1680);
				pPlayer->learnSpell(6552);
				pPlayer->learnSpell(11578);
				pPlayer->learnSpell(1719);
				pPlayer->learnSpell(34428);
				pPlayer->learnSpell(23920);
				pPlayer->learnSpell(3411);
				pPlayer->learnSpell(55694);
				pPlayer->learnSpell(47450);
				pPlayer->learnSpell(47465);
				pPlayer->learnSpell(47520);
				pPlayer->learnSpell(47436);
				pPlayer->learnSpell(47502);
				pPlayer->learnSpell(47437);
				pPlayer->learnSpell(47475);
				pPlayer->learnSpell(47440);
				pPlayer->learnSpell(47471);
				pPlayer->learnSpell(57755);
				pPlayer->learnSpell(57823);
				pPlayer->learnSpell(47488);
				break;
				
				case GOSSIP_ACTION_INFO_DEF + 3001:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->learnSpell(48778);
				pPlayer->learnSpell(48266);
				pPlayer->learnSpell(50977);
				pPlayer->learnSpell(49576);
				pPlayer->learnSpell(49142);
				pPlayer->learnSpell(46584);
				pPlayer->learnSpell(48263);
				pPlayer->learnSpell(48528);
				pPlayer->learnSpell(45524);
				pPlayer->learnSpell(3714);
				pPlayer->learnSpell(48792);
				pPlayer->learnSpell(45529);
				pPlayer->learnSpell(56222);
				pPlayer->learnSpell(48743);
				pPlayer->learnSpell(56815);
				pPlayer->learnSpell(48707);
				pPlayer->learnSpell(48265);
				pPlayer->learnSpell(41999);
				pPlayer->learnSpell(47568);
				pPlayer->learnSpell(57623);
				pPlayer->learnSpell(49941);
				pPlayer->learnSpell(49909);
				pPlayer->learnSpell(42650);
				pPlayer->learnSpell(49930);
				pPlayer->learnSpell(49938);
				pPlayer->learnSpell(49895);
				pPlayer->learnSpell(49924);
				pPlayer->learnSpell(49921);
				break;
				case GOSSIP_ACTION_INFO_DEF + 3002:
							pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->learnSpell(5487);
				pPlayer->learnSpell(6795);
				pPlayer->learnSpell(18960);
				pPlayer->learnSpell(5229);
				pPlayer->learnSpell(8946);
				pPlayer->learnSpell(1066);
				pPlayer->learnSpell(768);
				pPlayer->learnSpell(2782);
				pPlayer->learnSpell(2893);
				pPlayer->learnSpell(5209);
				pPlayer->learnSpell(783);
				pPlayer->learnSpell(5225);
				pPlayer->learnSpell(22842);
				pPlayer->learnSpell(9634);
				pPlayer->learnSpell(20719);
				pPlayer->learnSpell(29166);
				pPlayer->learnSpell(22812);
				pPlayer->learnSpell(8983);
				pPlayer->learnSpell(18658);
				pPlayer->learnSpell(33357);
				pPlayer->learnSpell(33786);
				pPlayer->learnSpell(26995);
				pPlayer->learnSpell(40120);
				pPlayer->learnSpell(62078);
				pPlayer->learnSpell(49802);
				pPlayer->learnSpell(53307);
				pPlayer->learnSpell(52610);
				pPlayer->learnSpell(48575);
				pPlayer->learnSpell(48476);
				pPlayer->learnSpell(48560);
				pPlayer->learnSpell(49803);
				pPlayer->learnSpell(48443);
				pPlayer->learnSpell(48562);
				pPlayer->learnSpell(53308);
				pPlayer->learnSpell(48577);
				pPlayer->learnSpell(53312);
				pPlayer->learnSpell(48574);
				pPlayer->learnSpell(48465);
				pPlayer->learnSpell(48570);
				pPlayer->learnSpell(48378);
				pPlayer->learnSpell(48480);
				pPlayer->learnSpell(48579);
				pPlayer->learnSpell(48477);
				pPlayer->learnSpell(50213);
				pPlayer->learnSpell(48461);
				pPlayer->learnSpell(48470);
				pPlayer->learnSpell(48467);
				pPlayer->learnSpell(48568);
				pPlayer->learnSpell(48451);
				pPlayer->learnSpell(48469);
				pPlayer->learnSpell(48463);
				pPlayer->learnSpell(48441);
				pPlayer->learnSpell(50763);
				pPlayer->learnSpell(49800);
				pPlayer->learnSpell(48572);
				pPlayer->learnSpell(48447);
					break;
				case GOSSIP_ACTION_INFO_DEF + 3003:
						pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->learnSpell(75);
				pPlayer->learnSpell(1494);
				pPlayer->learnSpell(13163);
				pPlayer->learnSpell(5116);
				pPlayer->learnSpell(883);
				pPlayer->learnSpell(2641);
				pPlayer->learnSpell(6991);
				pPlayer->learnSpell(982);
				pPlayer->learnSpell(1515);
				pPlayer->learnSpell(19883);
				pPlayer->learnSpell(20736);
				pPlayer->learnSpell(2974);
				pPlayer->learnSpell(6197);
				pPlayer->learnSpell(1002);
				pPlayer->learnSpell(19884);
				pPlayer->learnSpell(5118);
				pPlayer->learnSpell(34074);
				pPlayer->learnSpell(781);
				pPlayer->learnSpell(3043);
				pPlayer->learnSpell(1462);
				pPlayer->learnSpell(19885);
				pPlayer->learnSpell(3045);
				pPlayer->learnSpell(19880);
				pPlayer->learnSpell(13809);
				pPlayer->learnSpell(13161);
				pPlayer->learnSpell(5384);
				pPlayer->learnSpell(1543);
				pPlayer->learnSpell(19878);
				pPlayer->learnSpell(3034);
				pPlayer->learnSpell(13159);
				pPlayer->learnSpell(19882);
				pPlayer->learnSpell(14327);
				pPlayer->learnSpell(19879);
				pPlayer->learnSpell(19263);
				pPlayer->learnSpell(14311);
				pPlayer->learnSpell(19801);
				pPlayer->learnSpell(34026);
				pPlayer->learnSpell(27044);
				pPlayer->learnSpell(34600);
				pPlayer->learnSpell(34477);
				pPlayer->learnSpell(53271);
				pPlayer->learnSpell(49071);
				pPlayer->learnSpell(53338);
				pPlayer->learnSpell(49067);
				pPlayer->learnSpell(48996);
				pPlayer->learnSpell(49052);
				pPlayer->learnSpell(49056);
				pPlayer->learnSpell(49045);
				pPlayer->learnSpell(49001);
				pPlayer->learnSpell(61847);
				pPlayer->learnSpell(60192);
				pPlayer->learnSpell(61006);
				pPlayer->learnSpell(48990);
				pPlayer->learnSpell(53339);
				pPlayer->learnSpell(49048);
				pPlayer->learnSpell(58434);
						break;
				case GOSSIP_ACTION_INFO_DEF + 3004:
						pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->learnSpell(130);
				pPlayer->learnSpell(475);
				pPlayer->learnSpell(1953);
				pPlayer->learnSpell(12051);
				pPlayer->learnSpell(7301);
				pPlayer->learnSpell(32271);
				pPlayer->learnSpell(3562);
				pPlayer->learnSpell(3567);
				pPlayer->learnSpell(32272);
				pPlayer->learnSpell(3561);
				pPlayer->learnSpell(3563);
				pPlayer->learnSpell(2139);
				pPlayer->learnSpell(45438);
				pPlayer->learnSpell(3565);
				pPlayer->learnSpell(3566);
				pPlayer->learnSpell(32266);
				pPlayer->learnSpell(11416);
				pPlayer->learnSpell(11417);
				pPlayer->learnSpell(32267);
				pPlayer->learnSpell(10059);
				pPlayer->learnSpell(11418);
				pPlayer->learnSpell(11419);
				pPlayer->learnSpell(11420);
				pPlayer->learnSpell(12826);
				pPlayer->learnSpell(66);
				pPlayer->learnSpell(30449);
				pPlayer->learnSpell(53140);
				pPlayer->learnSpell(42917);
				pPlayer->learnSpell(43015);
				pPlayer->learnSpell(43017);
				pPlayer->learnSpell(42985);
				pPlayer->learnSpell(43010);
				pPlayer->learnSpell(42833);
				pPlayer->learnSpell(42914);
				pPlayer->learnSpell(42859);
				pPlayer->learnSpell(42846);
				pPlayer->learnSpell(43012);
				pPlayer->learnSpell(42842);
				pPlayer->learnSpell(43008);
				pPlayer->learnSpell(43024);
				pPlayer->learnSpell(43020);
				pPlayer->learnSpell(43046);
				pPlayer->learnSpell(42897);
				pPlayer->learnSpell(43002);
				pPlayer->learnSpell(42921);
				pPlayer->learnSpell(42940);
				pPlayer->learnSpell(42956);
				pPlayer->learnSpell(61316);
				pPlayer->learnSpell(61024);
				pPlayer->learnSpell(42973);
				pPlayer->learnSpell(47610);
				pPlayer->learnSpell(58659);
				if (pPlayer->GetTeamId() == HORDE) {
						pPlayer->learnSpell(11418);
						pPlayer->learnSpell(11420);
						pPlayer->learnSpell(11417);
						pPlayer->learnSpell(32267);
						pPlayer->learnSpell(32272);
						pPlayer->learnSpell(3567);
						pPlayer->learnSpell(3563);
						pPlayer->learnSpell(3566);
				}
					else {
						pPlayer->learnSpell(11419);
						pPlayer->learnSpell(32266);
						pPlayer->learnSpell(11416);
						pPlayer->learnSpell(10059);
						pPlayer->learnSpell(3565);
						pPlayer->learnSpell(32271);
						pPlayer->learnSpell(3562);
						pPlayer->learnSpell(3561);	
					}
						break;
				case GOSSIP_ACTION_INFO_DEF + 3005:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->learnSpell(21084);
				pPlayer->learnSpell(20271);
				pPlayer->learnSpell(498);
				pPlayer->learnSpell(1152);
				pPlayer->learnSpell(53408);
				pPlayer->learnSpell(31789);
				pPlayer->learnSpell(62124);
				pPlayer->learnSpell(25780);
				pPlayer->learnSpell(1044);
				pPlayer->learnSpell(5502);
				pPlayer->learnSpell(19746);
				pPlayer->learnSpell(20164);
				pPlayer->learnSpell(10326);
				pPlayer->learnSpell(1038);
				pPlayer->learnSpell(53407);
				pPlayer->learnSpell(19752);
				pPlayer->learnSpell(20165);
				pPlayer->learnSpell(642);
				pPlayer->learnSpell(10278);
				pPlayer->learnSpell(20166);
				pPlayer->learnSpell(4987);
				pPlayer->learnSpell(6940);
				pPlayer->learnSpell(10308);
				pPlayer->learnSpell(23214);
				pPlayer->learnSpell(25898);
				pPlayer->learnSpell(25899);
				pPlayer->learnSpell(34767);
				pPlayer->learnSpell(32223);
				pPlayer->learnSpell(33776);
				pPlayer->learnSpell(31884);
				pPlayer->learnSpell(54428);
				pPlayer->learnSpell(54043);
				pPlayer->learnSpell(48943);
				pPlayer->learnSpell(48936);
				pPlayer->learnSpell(48945);
				pPlayer->learnSpell(48938);
				pPlayer->learnSpell(48947);
				pPlayer->learnSpell(48817);
				pPlayer->learnSpell(48788);
				pPlayer->learnSpell(48932);
				pPlayer->learnSpell(48942);
				pPlayer->learnSpell(48801);
				pPlayer->learnSpell(48785);
				pPlayer->learnSpell(48934);
				pPlayer->learnSpell(48950);
				pPlayer->learnSpell(48819);
				pPlayer->learnSpell(48806);
				pPlayer->learnSpell(48782);
				pPlayer->learnSpell(53601);
				pPlayer->learnSpell(61411);
				if (pPlayer->GetTeamId() == HORDE) 
						{
						pPlayer->learnSpell(53736);				
						}
					else 
						{
						pPlayer->learnSpell(31801);	
						}
				break;
							
				case GOSSIP_ACTION_INFO_DEF + 3006:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->learnSpell(586);
				pPlayer->learnSpell(2053);
				pPlayer->learnSpell(528);
				pPlayer->learnSpell(6346);
				pPlayer->learnSpell(453);
				pPlayer->learnSpell(8129);
				pPlayer->learnSpell(605);
				pPlayer->learnSpell(552);
				pPlayer->learnSpell(6064);
				pPlayer->learnSpell(1706);
				pPlayer->learnSpell(988);
				pPlayer->learnSpell(10909);
				pPlayer->learnSpell(10890);
				pPlayer->learnSpell(10955);
				pPlayer->learnSpell(34433);
				pPlayer->learnSpell(32375);
				pPlayer->learnSpell(48072);
				pPlayer->learnSpell(48169);
				pPlayer->learnSpell(48168);
				pPlayer->learnSpell(48170);
				pPlayer->learnSpell(48120);
				pPlayer->learnSpell(48063);
				pPlayer->learnSpell(48135);
				pPlayer->learnSpell(48171);
				pPlayer->learnSpell(48300);
				pPlayer->learnSpell(48071);
				pPlayer->learnSpell(48127);
				pPlayer->learnSpell(48113);
				pPlayer->learnSpell(48123);
				pPlayer->learnSpell(48173);
				pPlayer->learnSpell(48073);
				pPlayer->learnSpell(48078);
				pPlayer->learnSpell(48087);
				pPlayer->learnSpell(53023);
				pPlayer->learnSpell(48161);
				pPlayer->learnSpell(48066);
				pPlayer->learnSpell(48162);
				pPlayer->learnSpell(48074);
				pPlayer->learnSpell(48068);
				pPlayer->learnSpell(48158);
				pPlayer->learnSpell(48125);
								break;
		case GOSSIP_ACTION_INFO_DEF + 3007:
			pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->learnSpell(921);
				pPlayer->learnSpell(1776);
				pPlayer->learnSpell(1766);
				pPlayer->learnSpell(1804);
				pPlayer->learnSpell(51722);
				pPlayer->learnSpell(1725);
				pPlayer->learnSpell(2836);
				pPlayer->learnSpell(1833);
				pPlayer->learnSpell(1842);
				pPlayer->learnSpell(2094);
				pPlayer->learnSpell(1860);
				pPlayer->learnSpell(6774);
				pPlayer->learnSpell(26669);
				pPlayer->learnSpell(8643);
				pPlayer->learnSpell(11305);
				pPlayer->learnSpell(1787);
				pPlayer->learnSpell(26889);
				pPlayer->learnSpell(31224);
				pPlayer->learnSpell(5938);
				pPlayer->learnSpell(51724);
				pPlayer->learnSpell(57934);
				pPlayer->learnSpell(48674);
				pPlayer->learnSpell(48659);
				pPlayer->learnSpell(48668);
				pPlayer->learnSpell(48672);
				pPlayer->learnSpell(48691);
				pPlayer->learnSpell(48657);
				pPlayer->learnSpell(57993);
				pPlayer->learnSpell(51723);
				pPlayer->learnSpell(48676);
				pPlayer->learnSpell(48638);
			break;
			case GOSSIP_ACTION_INFO_DEF + 3008:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->learnSpell(30671);
				pPlayer->learnSpell(2484);
				pPlayer->learnSpell(526);
				pPlayer->learnSpell(57994);
				pPlayer->learnSpell(8143);
				pPlayer->learnSpell(2645);
				pPlayer->learnSpell(2870);
				pPlayer->learnSpell(8166);
				pPlayer->learnSpell(131);
				pPlayer->learnSpell(10399);
				pPlayer->learnSpell(6196);
				pPlayer->learnSpell(546);
				pPlayer->learnSpell(556);
				pPlayer->learnSpell(8177);
				pPlayer->learnSpell(20608);
				pPlayer->learnSpell(36936);
				pPlayer->learnSpell(8012);
				pPlayer->learnSpell(8512);
				pPlayer->learnSpell(6495);
				pPlayer->learnSpell(8170);
				pPlayer->learnSpell(3738);
				pPlayer->learnSpell(2062);
				pPlayer->learnSpell(2894);
				pPlayer->learnSpell(57960);
				pPlayer->learnSpell(49276);
				pPlayer->learnSpell(49236);
				pPlayer->learnSpell(58734);
				pPlayer->learnSpell(58582);
				pPlayer->learnSpell(58753);
				pPlayer->learnSpell(49231);
				pPlayer->learnSpell(49238);
				pPlayer->learnSpell(49277);
				pPlayer->learnSpell(55459);
				pPlayer->learnSpell(49271);
				pPlayer->learnSpell(49284);
				pPlayer->learnSpell(51994);
				pPlayer->learnSpell(61657);
				pPlayer->learnSpell(58739);
				pPlayer->learnSpell(49233);
				pPlayer->learnSpell(58656);
				pPlayer->learnSpell(58790);
				pPlayer->learnSpell(58745);
				pPlayer->learnSpell(58796);
				pPlayer->learnSpell(58757);
				pPlayer->learnSpell(49273);
				pPlayer->learnSpell(51514);
				pPlayer->learnSpell(60043);
				pPlayer->learnSpell(49281);
				pPlayer->learnSpell(58774);
				pPlayer->learnSpell(58749);
				pPlayer->learnSpell(58704);
				pPlayer->learnSpell(58643);
				pPlayer->learnSpell(58804);
				break;
			case GOSSIP_ACTION_INFO_DEF + 3009:
					pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->learnSpell(59671);
				pPlayer->learnSpell(688);
				pPlayer->learnSpell(696);
				pPlayer->learnSpell(697);
				pPlayer->learnSpell(5697);
				pPlayer->learnSpell(698);
				pPlayer->learnSpell(712);
				pPlayer->learnSpell(126);
				pPlayer->learnSpell(5138);
				pPlayer->learnSpell(5500);
				pPlayer->learnSpell(132);
				pPlayer->learnSpell(691);
				pPlayer->learnSpell(18647);
				pPlayer->learnSpell(11719);
				pPlayer->learnSpell(1122);
				pPlayer->learnSpell(17928);
				pPlayer->learnSpell(6215);
				pPlayer->learnSpell(18540);
				pPlayer->learnSpell(23161);
				pPlayer->learnSpell(29858);
				pPlayer->learnSpell(50511);
				pPlayer->learnSpell(61191);
				pPlayer->learnSpell(47884);
				pPlayer->learnSpell(47856);
				pPlayer->learnSpell(47813);
				pPlayer->learnSpell(47855);
				pPlayer->learnSpell(47888);
				pPlayer->learnSpell(47865);
				pPlayer->learnSpell(47860);
				pPlayer->learnSpell(47857);
				pPlayer->learnSpell(47823);
				pPlayer->learnSpell(47891);
				pPlayer->learnSpell(47878);
				pPlayer->learnSpell(47864);
				pPlayer->learnSpell(57595);
				pPlayer->learnSpell(47893);
				pPlayer->learnSpell(47820);
				pPlayer->learnSpell(47815);
				pPlayer->learnSpell(47809);
				pPlayer->learnSpell(60220);
				pPlayer->learnSpell(47867);
				pPlayer->learnSpell(47889);
				pPlayer->learnSpell(48018);
				pPlayer->learnSpell(47811);
				pPlayer->learnSpell(47838);
				pPlayer->learnSpell(57946);
				pPlayer->learnSpell(58887);
				pPlayer->learnSpell(47836);
				pPlayer->learnSpell(61290);
				pPlayer->learnSpell(47825);
					break;
					
				case GOSSIP_ACTION_INFO_DEF + 3011:
						pPlayer->CLOSE_GOSSIP_MENU();
						pPlayer->SendTalentWipeConfirm(pCreature->GetGUID());
						break;
				case GOSSIP_ACTION_INFO_DEF + 3012:
						pPlayer->SetDrunkValue(100);
						pCreature->MonsterSay("Sweet... You're drunk now and will die soon  !", LANG_UNIVERSAL, NULL);
						break;
				case GOSSIP_ACTION_INFO_DEF + 3013:
							pPlayer->SetDrunkValue(0, 9);
							pCreature->MonsterSay("It's never to late to get drunk again.", LANG_UNIVERSAL, NULL);
						break;
				case GOSSIP_ACTION_INFO_DEF + 3014:
							  pPlayer->CLOSE_GOSSIP_MENU();
							pPlayer->SetBindPoint(pCreature->GetGUID());
						break;
						
			case GOSSIP_ACTION_INFO_DEF + 196:
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Alchemy", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 197);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Blacksmithing", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 198);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Leatherworking", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 199);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Tailoring", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 200);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Engineering", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 201);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Enchanting", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 202);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Jewelcrafting", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 203);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Inscription", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 204);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Cooking", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 205);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "First Aid", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 206);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Fishing", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 207);

				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "<- [Back]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);

				pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());
				break;

					case GOSSIP_ACTION_INFO_DEF + 450:		
					pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "I want to repair my items.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
					pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "I want to get DRUNK!.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3012);
					pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Ugh, Sober me up, I've had enough...", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3013);
					pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Heal me.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 26);
					//pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Advance my weapon skills to max.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9);
		            //pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Give me maximum riding skill.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 186);
					//pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Reset My talent and Spell. ( Carefull if you have Mounts or another spells)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 187);
					pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "<- [Back]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
					pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());
					break;
					
			case GOSSIP_ACTION_INFO_DEF + 197:
				CompleteLearnProfession(pPlayer, pCreature, SKILL_ALCHEMY);

				pPlayer->CLOSE_GOSSIP_MENU();
				break;
			case GOSSIP_ACTION_INFO_DEF + 198:
				CompleteLearnProfession(pPlayer, pCreature, SKILL_BLACKSMITHING);

				pPlayer->CLOSE_GOSSIP_MENU();
				break;
			case GOSSIP_ACTION_INFO_DEF + 199:
				CompleteLearnProfession(pPlayer, pCreature, SKILL_LEATHERWORKING);

				pPlayer->CLOSE_GOSSIP_MENU();
				break;
			case GOSSIP_ACTION_INFO_DEF + 200:
				CompleteLearnProfession(pPlayer, pCreature, SKILL_TAILORING);

				pPlayer->CLOSE_GOSSIP_MENU();
				break;
			case GOSSIP_ACTION_INFO_DEF + 201:
				CompleteLearnProfession(pPlayer, pCreature, SKILL_ENGINEERING);

				pPlayer->CLOSE_GOSSIP_MENU();
				break;
			case GOSSIP_ACTION_INFO_DEF + 202:
				CompleteLearnProfession(pPlayer, pCreature, SKILL_ENCHANTING);

				pPlayer->CLOSE_GOSSIP_MENU();
				break;
			case GOSSIP_ACTION_INFO_DEF + 203:
				CompleteLearnProfession(pPlayer, pCreature, SKILL_JEWELCRAFTING);

				pPlayer->CLOSE_GOSSIP_MENU();
				break;
			case GOSSIP_ACTION_INFO_DEF + 204:
				CompleteLearnProfession(pPlayer, pCreature, SKILL_INSCRIPTION);

				pPlayer->CLOSE_GOSSIP_MENU();
				break;
			case GOSSIP_ACTION_INFO_DEF + 205:
				CompleteLearnProfession(pPlayer, pCreature, SKILL_COOKING);
				pPlayer->CLOSE_GOSSIP_MENU();
				break;
				
			case GOSSIP_ACTION_INFO_DEF + 206:
				CompleteLearnProfession(pPlayer, pCreature, SKILL_FIRST_AID);
				pPlayer->CLOSE_GOSSIP_MENU();
				break;
			case GOSSIP_ACTION_INFO_DEF + 207:
				CompleteLearnProfession(pPlayer, pCreature, SKILL_FISHING);
				pPlayer->CLOSE_GOSSIP_MENU();
				break;
				
			case GOSSIP_ACTION_INFO_DEF + 1110:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(571, 7308.9501f, -736.6033f, 792.1558f, 1.5730f);
				break;

			case GOSSIP_ACTION_INFO_DEF + 1111:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(571, 1296.5100f, -5109.1801f, 174.9918f, 2.0970f);
				break;
		}

        return true;
	}
};

void AddSc_Script_CustomTeleporter()
{
	new Custom_teleporter();
}