DELIMITER //
CREATE PROCEDURE `add_record`(IN `feed_id` INT, IN `hash` CHAR(32), IN `guid` VARCHAR(1024), IN `date` BIGINT, IN `link` VARCHAR(1024), IN `title` VARCHAR(2048), IN `description` TEXT)
    MODIFIES SQL DATA
    DETERMINISTIC
BEGIN
	INSERT INTO records (feed_id, hash, guid,date,link,title,description, state)
	VALUES(feed_id, hash, guid,date,link,title,description, 0) ON DUPLICATE KEY UPDATE    
	guid=guid,date = date,link = link,title=title,description=description, state=1;
END//
DELIMITER ;


CREATE TABLE IF NOT EXISTS `feeds` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `url` varchar(1024) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

CREATE TABLE IF NOT EXISTS `records` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `feed_id` int(11) NOT NULL,
  `hash` char(32) NOT NULL,
  `guid` varchar(1024) DEFAULT NULL,
  `date` bigint(20) NOT NULL,
  `link` varchar(1024) DEFAULT NULL,
  `title` varchar(2048) DEFAULT NULL,
  `description` text DEFAULT NULL,
  `state` tinyint(4) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `idx_feed_hash` (`feed_id`,`hash`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

DELIMITER //
CREATE DEFINER=`root`@`localhost` PROCEDURE `set_record_state`(IN `id` INT, IN `state` TINYINT)
    MODIFIES SQL DATA
BEGIN
	update records set records.state=state where records.id=id;
END//
DELIMITER ;
