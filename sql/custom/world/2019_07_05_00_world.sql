-- ----------------------------
-- Table structure for _ark_stats_limit
-- ----------------------------
DROP TABLE IF EXISTS `_ark_stats_limit`;
CREATE TABLE `_ark_stats_limit`  (
  `class` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `Agility_crit` float UNSIGNED NOT NULL DEFAULT 0,
  `Agility_dodge` float UNSIGNED NOT NULL DEFAULT 0,
  `Intellect_crit` float UNSIGNED NOT NULL DEFAULT 0,
  `Comment` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  PRIMARY KEY (`class`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of _ark_stats_limit
-- ----------------------------
INSERT INTO `_ark_stats_limit` VALUES (1, 0, 0, 0, '战士');
INSERT INTO `_ark_stats_limit` VALUES (2, 0, 0, 0, '圣骑士');
INSERT INTO `_ark_stats_limit` VALUES (3, 0, 0, 0, '猎人');
INSERT INTO `_ark_stats_limit` VALUES (4, 0, 0, 0, '盗贼');
INSERT INTO `_ark_stats_limit` VALUES (5, 0, 0, 0, '牧师');
INSERT INTO `_ark_stats_limit` VALUES (7, 0, 0, 0, '萨满祭司');
INSERT INTO `_ark_stats_limit` VALUES (8, 0, 0, 0, '法师');
INSERT INTO `_ark_stats_limit` VALUES (9, 0, 0, 0, '术士');
INSERT INTO `_ark_stats_limit` VALUES (11, 0, 0, 0, '德鲁伊');
