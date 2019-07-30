-- ----------------------------
-- Table structure for _ark_titles
-- ----------------------------
DROP TABLE IF EXISTS `_ark_titles`;
CREATE TABLE `_ark_titles`  (
  `entry` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `aura` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `comment` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  PRIMARY KEY (`entry`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;
