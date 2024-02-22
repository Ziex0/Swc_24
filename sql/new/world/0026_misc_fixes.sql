/* Quest adding injury to insult, fix mob speed run, from 2.2 to 1.0 */
UPDATE `creature_template` SET `speed_run` = 1 WHERE `entry` = 24238;

DELETE FROM spell_script_names WHERE spell_id = 38776;
INSERT INTO spell_script_names VALUES (38776,'spell_q9718_crow_transform'); 

DELETE FROM areatrigger_scripts WHERE entry = 4156;
INSERT INTO areatrigger_scripts VALUES (4156, 'at_naxxramas_frostwyrm_wing');

UPDATE `creature_template` SET `DamageModifier`=19.4 WHERE  `entry`=32313;

UPDATE `quest_template` SET `AddedInBuild`=12340 WHERE `Id`=26012;

UPDATE `creature_template` SET `modelid1`=30277, scale=0.5 WHERE `entry`=36794;
UPDATE `creature_template_addon` SET `mount`=27982 WHERE `entry`=36794;

DELETE FROM smart_scripts WHERE entryorguid=25216;
INSERT INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES
(25216, 0, 0, 0, 4, 0, 100, 1, 0, 0, 0, 0, 22, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Set Phase 1 on Aggro'),
(25216, 0, 1, 0, 4, 1, 100, 1, 0, 0, 0, 0, 21, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Stop Moving on Aggro'),
(25216, 0, 2, 0, 4, 1, 100, 1, 0, 0, 0, 0, 11, 9532, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Cast bolt on Aggro'),
(25216, 0, 3, 0, 9, 1, 100, 0, 0, 40, 3400, 4700, 11, 9532, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Cast bolt'),
(25216, 0, 4, 0, 9, 1, 100, 0, 40, 100, 0, 0, 21, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Start Moving when not in bolt Range'),
(25216, 0, 5, 0, 9, 1, 100, 0, 10, 15, 0, 0, 21, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Stop Moving at 15 Yards'),
(25216, 0, 6, 0, 9, 1, 100, 0, 0, 40, 0, 0, 21, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Stop Moving when in bolt Range'),
(25216, 0, 7, 0, 3, 1, 100, 0, 0, 15, 0, 0, 22, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Set Phase 2 at 15% Mana'),
(25216, 0, 8, 0, 3, 2, 100, 0, 0, 15, 0, 0, 21, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Start Moving at 15% Mana'),
(25216, 0, 9, 0, 3, 2, 100, 0, 30, 100, 100, 100, 22, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Set Phase 1 When Mana is above 30%'),
(25216, 0, 10, 0, 2, 2, 100, 1, 0, 15, 0, 0, 22, 3, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Set Phase 3 at 15% HP'),
(25216, 0, 11, 0, 2, 3, 100, 1, 0, 15, 0, 0, 25, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Flee at 15% HP'),
(25216, 0, 12, 0, 7, 3, 100, 1, 0, 0, 0, 0, 22, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Reset on Evade'),
(25216, 0, 13, 0, 2, 3, 100, 1, 0, 15, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Say Text at 15% HP'),
(25216, 0, 14, 0, 9, 1, 100, 0, 0, 5, 12300, 19800, 11, 50272, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Cast Unstable Magic on Close');

UPDATE `creature_template` SET `flags_extra`=128 WHERE `entry`=7863;
