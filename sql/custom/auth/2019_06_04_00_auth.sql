-- ----------------------------
-- Table structure for _ark_account_extra
-- ----------------------------
DROP TABLE IF EXISTS `_ark_account_extra`;
CREATE TABLE `_ark_account_extra`  (
  `id` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `viplevel` int(10) NOT NULL DEFAULT 0,
  `jf` int(10) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Compact;
