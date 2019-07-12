-- ----------------------------
-- Table for table `command`
-- ----------------------------
INSERT INTO `command` VALUES ('ark ReloadEnchantment', 3, 'Syntax: .ark ReloadEnchantment'); 

-- ----------------------------
-- Table structure for _ark_item_enchantment
-- ----------------------------
DROP TABLE IF EXISTS `_ark_item_enchantment`;
CREATE TABLE `_ark_item_enchantment`  (
  `entry` int(10) UNSIGNED NOT NULL,
  `title1` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `title2` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `title3` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `title4` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `title5` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `enchantmentid1` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `enchantmentid2` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `enchantmentid3` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `enchantmentid4` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `enchantmentid5` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `inventoryType` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `chance` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `jf` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `gold` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `vipLevel` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `reqItem1` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `reqItem2` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `reqItem3` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `reqItem4` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `reqItem5` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `reqCount1` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `reqCount2` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `reqCount3` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `reqCount4` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `reqCount5` int(10) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`entry`) USING BTREE
) ENGINE = MyISAM CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Fixed;


-- ----------------------------
-- Table for table item_template
-- ----------------------------
INSERT INTO item_template VALUES (100010, 15, 3, -1, '附魔前缀重铸宝石', 43108, 5, 512, 1, 0, 0, 0, -1, -1, 70, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 1, '|cFF00FF00使用: 重铸指定装备附魔属性.|r', 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 'ark_item_enchantment', 0, 0, 0, 0, 0, 0);
