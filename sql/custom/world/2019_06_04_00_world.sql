-- ----------------------------
-- Table structure for _ark_config
-- ----------------------------
DROP TABLE IF EXISTS `_ark_config`;
CREATE TABLE `_ark_config`  (
  `entry` varchar(60) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `value` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `cost` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `Comment` text CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  PRIMARY KEY (`entry`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Compact;

-- ----------------------------
-- Table structure for _ark_vip_system
-- ----------------------------
DROP TABLE IF EXISTS `_ark_vip_system`;
CREATE TABLE `_ark_vip_system`  (
  `entry` int(10) UNSIGNED NOT NULL,
  `title` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `nameColor` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `chatColor` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `reqItem` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `jfCost` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `everyDayItem` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `addAutojf` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `lootRate` float UNSIGNED NOT NULL DEFAULT 0,
  `HealthRate` float UNSIGNED NOT NULL DEFAULT 0,
  `dmgRate` float UNSIGNED NOT NULL DEFAULT 0,
  `cureRate` float UNSIGNED NOT NULL DEFAULT 0,
  `xpRate` float UNSIGNED NOT NULL DEFAULT 0,
  `reputationRate` float UNSIGNED NOT NULL DEFAULT 0,
  `adduppro` float UNSIGNED NOT NULL DEFAULT 0,
  `aura` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `talent` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `description` text CHARACTER SET utf8 COLLATE utf8_general_ci NULL,
  PRIMARY KEY (`entry`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Compact;

-- ----------------------------
-- Table _ark_config
-- ----------------------------
INSERT INTO _ark_config VALUES ('Player.login', 0, 0, '【登录提示】value：是否开启 0=关闭  1=开启新人提示 2=开启老人提示 3=开启全部提示\n cost：0=名字显示前缀前面 1=名字显示前缀后面');
INSERT INTO _ark_config VALUES ('Player.vipSystem', 0, 0, '【VIP 功能】value：是否开启 0=关闭  1=开启');
INSERT INTO _ark_config VALUES ('Player.world.chat', 0, 0, '【世界聊天】value：\n 0=关闭 \n 1=开启(名字显示前缀前面) cost=消耗的金币数量 \n 2=开启(名字显示前缀前面) cost=消耗的积分数量\n 3=开启(名字显示前缀前面) cost=消耗的物品ID \n 4=开启(名字显示前缀后面) cost=消耗的金币数量 \n 5=开启(名字显示前缀后面) cost=消耗的积分数量\n 6=开启(名字显示前缀后面) cost=消耗的物品ID');
INSERT INTO _ark_config VALUES ('Player.world.Facttion.chat', 0, 0, '【阵营聊天】value：\n 0=关闭 \n 1=开启(名字显示前缀前面) cost=消耗的金币数量 \n 2=开启(名字显示前缀前面) cost=消耗的积分数量\n 3=开启(名字显示前缀前面) cost=消耗的物品ID \n 4=开启(名字显示前缀后面) cost=消耗的金币数量 \n 5=开启(名字显示前缀后面) cost=消耗的积分数量\n 6=开启(名字显示前缀后面) cost=消耗的物品ID');

-- ----------------------------
-- Table command 
-- ---------------------------- 
INSERT INTO command VALUES ('ark jf', 3, 'Syntax: .ark jf $amount'); 
INSERT INTO command VALUES ('ark ReloadVipSystem', 3, 'Syntax: .ark ReloadVipSystem');
INSERT INTO command VALUES ('ark vip', 3, 'Syntax: .ark vip');
INSERT INTO command VALUES ('ark ReloadConfig', 3, 'Syntax: .ark ReloadConfig');
INSERT INTO command VALUES ('sj', 0, 'Syntax: .sj or Lack of cost');
INSERT INTO command VALUES ('zy', 0, 'Syntax: .zy or Lack of cost');

-- ----------------------------
-- Table mangos_string 
-- ---------------------------- 
INSERT INTO mangos_string VALUES (90000, '|cffffcc00[Server]: |r |cff00ff00%s Account surplus jf %u points, add %d points, usable jf %u points. |r', NULL, NULL, NULL, '|cffffcc00[系统提示]: |r |cff00ff00%s拥有%u点积分, 增加%d点, 可用积分%u点. |r', NULL, NULL, NULL, NULL);
INSERT INTO mangos_string VALUES (90001, '|TInterface\\COMMON\\VOICECHAT-SPEAKER:18:18:4:-3|tWelcome new people [%s%s] to World of Warcraft, Race belongs to %s, Cheers for him!', NULL, NULL, NULL, '|TInterface\\COMMON\\VOICECHAT-SPEAKER:18:18:4:-3|t欢迎新人[%s%s]来到魔兽世界, 种族属于%s, 为他欢呼!', NULL, NULL, NULL, NULL);
INSERT INTO mangos_string VALUES (90002, '|TInterface\\COMMON\\VOICECHAT-SPEAKER:18:18:4:-3|t[%s%s]: Set foot on the journey again, in order to %s!', NULL, NULL, NULL, '|TInterface\\COMMON\\VOICECHAT-SPEAKER:18:18:4:-3|t[%s%s]: 再次踏上征程, 为了%s!', NULL, NULL, NULL, NULL);
INSERT INTO mangos_string VALUES (90003, 'Changing VIP level, [%s] The current VIP level is set to %u.', NULL, NULL, NULL, '改变VIP等级, [%s]当前VIP等级设置为%u.', NULL, NULL, NULL, NULL);
INSERT INTO mangos_string VALUES (90004, '[WorldChat]%s[%s%s]: %s', NULL, NULL, NULL, '[世界频道]%s[%s%s]: %s', NULL, NULL, NULL, NULL);
INSERT INTO mangos_string VALUES (90005, '|cFF00CCCC[FacttionChat]|r%s[%s%s]: %s', NULL, NULL, NULL, '|cFF00CCCC[阵营频道]|r%s[%s%s]: %s', NULL, NULL, NULL, NULL);
INSERT INTO mangos_string VALUES (90006, '|cFF33CCFFCongratulations! Your jf increased by %u points.|r', NULL, NULL, NULL, '|cFF33CCFF恭喜你! 你的积分增加%u点.|r', NULL, NULL, NULL, NULL);
INSERT INTO mangos_string VALUES (90007, '|cFF33CCFFYou spent jf %u points.|r', NULL, NULL, NULL, '|cFF33CCFF你花费了%u点积分.|r', NULL, NULL, NULL, NULL);
INSERT INTO mangos_string VALUES (90008, '|cFF33CCFFSorry, Your jf is not enough!|r', NULL, NULL, NULL, '|cFF33CCFF对不起, 你的积分不足!|r', NULL, NULL, NULL, NULL);
