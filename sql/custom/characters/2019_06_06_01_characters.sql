-- ----------------------------
-- Table structure for _ark_characters_extra
-- ----------------------------
 CREATE TABLE `_ark_characters_extra` (
  `guid` int(11) unsigned NOT NULL DEFAULT '0' COMMENT 'Global Unique Identifier',
  `fly_last_date` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
  PRIMARY KEY  (`guid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC COMMENT='Player System';
