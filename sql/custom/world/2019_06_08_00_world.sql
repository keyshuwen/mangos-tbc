-- ----------------------------
-- Table for table `command`
-- ----------------------------
INSERT INTO `command` VALUES ('ark ReloadMenu', 3, 'Syntax: .ark ReloadMenu'); 

-- ----------------------------
-- Table structure for _ark_npc_menu
-- ----------------------------
DROP TABLE IF EXISTS `_ark_npc_menu`;
CREATE TABLE `_ark_npc_menu`  (
  `menu_id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `npcEntry` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `option_icon` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `option_id` smallint(3) UNSIGNED NOT NULL DEFAULT 0,
  `option_text` text CHARACTER SET utf8 COLLATE utf8_general_ci NULL,
  `box_text` text CHARACTER SET utf8 COLLATE utf8_general_ci NULL,
  `faction` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `needType` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `needValue` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `needValue2` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `map` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `x` float NOT NULL DEFAULT 0,
  `y` float NOT NULL DEFAULT 0,
  `z` float NOT NULL DEFAULT 0,
  `o` float NOT NULL DEFAULT 0,
  PRIMARY KEY (`menu_id`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of _ark_npc_menu
-- ----------------------------
INSERT INTO `_ark_npc_menu` VALUES (1, 0, 90000, 0, 1, '|TInterface\\Icons\\Spell_Arcane_TeleportStormWind:28|t 主城-暴风城', NULL, 1, 0, 0, 0, 0, -8831.41, 625.35, 93.92, 0);
INSERT INTO `_ark_npc_menu` VALUES (2, 0, 90000, 0, 1, '|TInterface\\Icons\\Spell_Arcane_TeleportIronForge:28|t 主城-铁炉堡', NULL, 1, 0, 0, 0, 0, -4923.08, -952.88, 501.53, 0);
INSERT INTO `_ark_npc_menu` VALUES (3, 0, 90000, 0, 1, '|TInterface\\Icons\\Spell_Arcane_TeleportDarnassus:28|t 主城-达纳苏斯', NULL, 1, 0, 0, 0, 1, 9952.12, 2280.47, 1341.39, 0);
INSERT INTO `_ark_npc_menu` VALUES (4, 0, 90000, 0, 1, '|TInterface\\Icons\\Spell_Arcane_TeleportExodar:28|t 主城-埃索达', NULL, 1, 0, 0, 0, 530, -4074.26, -12017.2, -1.376, 1.331);
INSERT INTO `_ark_npc_menu` VALUES (5, 0, 90000, 0, 1, '|TInterface\\Icons\\Spell_Arcane_TeleportOrgrimmar:28|t 主城-奥格瑞玛', NULL, 2, 0, 0, 0, 1, 1605.77, -4388.93, 10, 0);
INSERT INTO `_ark_npc_menu` VALUES (6, 0, 90000, 0, 1, '|TInterface\\Icons\\Spell_Arcane_TeleportThunderBluff:28|t 主城-雷霆崖', NULL, 2, 0, 0, 0, 1, -1277.57, 123.413, 131.265, 0);
INSERT INTO `_ark_npc_menu` VALUES (7, 0, 90000, 0, 1, '|TInterface\\Icons\\Spell_Arcane_TeleportUnderCity:28|t 主城-幽暗城', NULL, 2, 0, 0, 0, 0, 1633.3, 240.18, -43.1, 0);
INSERT INTO `_ark_npc_menu` VALUES (8, 0, 90000, 0, 1, '|TInterface\\Icons\\Spell_Arcane_TeleportSilvermoon:28|t 主城-银月城', NULL, 2, 0, 0, 0, 530, 9336.9, -7278.4, 13.608, 4.06);
INSERT INTO `_ark_npc_menu` VALUES (9, 0, 90000, 0, 1, '|TInterface\\Icons\\Spell_Arcane_TeleportShattrath:28|t 中立-沙斯塔城', NULL, 0, 0, 0, 0, 530, -1820.32, 5312.88, -12.427, 1.972);
INSERT INTO `_ark_npc_menu` VALUES (10, 0, 90000, 0, 1, '|TInterface\\Icons\\Spell_Arcane_TeleportMoonglade:28|t 中立-黑暗之门', NULL, 0, 0, 0, 0, 530, -248.258, 921.199, 84.021, 1.555);
INSERT INTO `_ark_npc_menu` VALUES (100, 0, 90002, 0, 0, '新手帮助', NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `_ark_npc_menu` VALUES (101, 0, 90002, 1, 6, '新人装备', NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `_ark_npc_menu` VALUES (110, 100, 90002, 0, 0, '更新日志', NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `_ark_npc_menu` VALUES (111, 100, 90002, 0, 0, '玩法攻略', NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `_ark_npc_menu` VALUES (112, 100, 90002, 0, 0, '游戏设置', NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `_ark_npc_menu` VALUES (113, 100, 90002, 0, 999, '返回...', NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `_ark_npc_menu` VALUES (120, 110, 90002, 0, 999, '1.暂时无更新日志...', NULL, 0, 0, 0, 0, 100, 0, 0, 0, 0);
INSERT INTO `_ark_npc_menu` VALUES (130, 111, 90002, 0, 999, '1.暂无攻略', NULL, 0, 0, 0, 0, 100, 0, 0, 0, 0);
INSERT INTO `_ark_npc_menu` VALUES (140, 112, 90002, 0, 999, '服务器设置:\r\n经验:  30倍\r\n声望:  4倍\r\n掉落:  3倍\r\n专业:  每次涨3点, 可学所有商业技能. \r\n\r\n飞行点全开, 瞬飞免费.\r\n\r\n副本CD\r\n1. 什么鬼\r\n\r\n神器\r\n1. 职业神器,  神器任务请去沙塔斯查看.\r\n\r\n粉色装备\r\n1. 强大的效果, 世界掉落.. 所有BOSS都有几率掉落..', NULL, 0, 0, 0, 0, 100, 0, 0, 0, 0);
INSERT INTO `_ark_npc_menu` VALUES (200, 0, 90003, 0, 999, '衬衣详情', NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `_ark_npc_menu` VALUES (201, 0, 90003, 1, 6, '衬衣兑换', NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `_ark_npc_menu` VALUES (300, 0, 90001, 0, 2, '|TInterface\\Icons\\INV_Misc_Coin_04:28|t |cFF0041FF积分查询|r', NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `_ark_npc_menu` VALUES (301, 0, 90001, 0, 0, '|TInterface\\Icons\\INV_Misc_Coin_02:28|t |cFF0041FF兑换积分|r', NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `_ark_npc_menu` VALUES (302, 0, 90001, 0, 8, '|TInterface\\Icons\\inv_misc_rune_01:28|t |cFF0041FF绑定炉石|r', '你是否需要绑定炉石?', 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `_ark_npc_menu` VALUES (303, 0, 90001, 0, 6, '|TInterface\\Icons\\INV_Misc_Coin_01:28|t |cFF0041FF游戏商店|r', NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `_ark_npc_menu` VALUES (304, 0, 90001, 0, 0, '|cFFCC00CC[功　能]|cFF0041FF角色服务 |r', NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `_ark_npc_menu` VALUES (310, 301, 90001, 0, 10, '|cFF0041FF兑换1个积分|r', '你是否需要兑换1个积分货币？', 0, 3, 1, 0, 100000, 1, 0, 0, 0);
INSERT INTO `_ark_npc_menu` VALUES (311, 301, 90001, 0, 10, '|cFF0041FF兑换10个积分|r', '你是否需要兑换10个积分货币？', 0, 3, 10, 0, 100000, 10, 0, 0, 0);
INSERT INTO `_ark_npc_menu` VALUES (312, 301, 90001, 0, 10, '|cFF0041FF兑换100个积分|r', '你是否需要兑换100个积分货币？', 0, 3, 100, 0, 100000, 100, 0, 0, 0);
INSERT INTO `_ark_npc_menu` VALUES (320, 304, 90001, 0, 7, '|cFFCC00CC[50积分]|r|cFF0041FF修改角色名称|r', '你是否需要修改角色名称？', 0, 3, 50, 0, 0, 0, 0, 0, 0);