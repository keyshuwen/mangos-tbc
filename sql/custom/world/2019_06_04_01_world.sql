-- ----------------------------
-- Table structure for autobroadcast
-- ----------------------------
DROP TABLE IF EXISTS `_ark_autobroadcast`;
CREATE TABLE `_ark_autobroadcast`  (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `text` longtext CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 1 CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table for table `mangos_string`
-- ----------------------------
INSERT INTO `mangos_string` VALUES (90009, '|cffffcc00[autobroadcast]: |r|cff00ff00%s|r', NULL, NULL, NULL, '|cffffcc00[游戏提示]: |r|cff00ff00%s|r', NULL, NULL, NULL, NULL);

-- ----------------------------
-- Table for table `command`
-- ----------------------------
INSERT INTO `command` VALUES ('ark autobroadcast', 3, 'Syntax: .ark autobroadcast\nReload autobroadcast table.'); 
