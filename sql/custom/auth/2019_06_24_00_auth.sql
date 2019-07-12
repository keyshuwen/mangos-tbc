-- ----------------------------
-- Table structure for _ark_account_recharge
-- ----------------------------
DROP TABLE IF EXISTS `_ark_account_recharge`;
CREATE TABLE `_ark_account_recharge`  (
  `id` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `jf` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `amount` int(10) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Compact;


INSERT INTO _ark_account_recharge(id) SELECT id FROM account WHERE not exists (SELECT * FROM _ark_account_recharge WHERE _ark_account_recharge.id = account.id);
