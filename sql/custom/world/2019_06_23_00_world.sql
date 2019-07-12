-- ----------------------------
-- Table structure _ark_instance_template
-- ----------------------------
ALTER TABLE _ark_instance_template ADD Herolevel tinyint(3) UNSIGNED NOT NULL DEFAULT 0 AFTER Creaturelevel;
ALTER TABLE _ark_instance_template ADD HeroCreaturelevel tinyint(3) UNSIGNED NOT NULL DEFAULT 0 AFTER Herolevel;
