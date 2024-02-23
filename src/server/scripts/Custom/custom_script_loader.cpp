/*
 * Copyright (C) 2008-2016 TrinityCore <http://www.trinitycore.org/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

// This is where scripts' loading functions should be declared:
	/********************* PATH *************/
	void AddSc_Script_CustomTeleporter();
	void AddSC_universal_npc();
	void AddSC_pet_tut();
	void AddSC_premium_rate();
	void AddSC_level_255();
	void AddSc_Scriptquest_freya();
/********************* Intance tele *************/
	void AddSc_ScriptAshes_Fates();
	void AddSc_Scriptblood_forg();
	void AddSc_Scriptcustom_porterz();
	void AddSc_ScriptDawn_sand();
	void AddSc_Scripttele_icc();
	void AddSc_Scriptleg_venge();
	void AddSc_Scriptsmol_warlor();
	void AddSc_Scripttwis_void();
	
	
// The name of this function should match:
// void Add${NameOfDirectory}Scripts()
void AddCustomScripts()
{
	/********************* PATH *************/
	AddSc_Script_CustomTeleporter();
	AddSC_universal_npc();
	AddSC_pet_tut();
	AddSC_premium_rate();
	AddSC_level_255();
	AddSc_Scriptquest_freya();
/********************* Intance tele *************/
	AddSc_ScriptAshes_Fates();
	AddSc_Scriptblood_forg();
	AddSc_Scriptcustom_porterz();
	AddSc_ScriptDawn_sand();
	AddSc_Scripttele_icc();
	AddSc_Scriptleg_venge();
	AddSc_Scriptsmol_warlor();
	AddSc_Scripttwis_void();
}
