CREATE TABLE `problem` (
	`id` INT(11) NOT NULL,
	PRIMARY KEY (`id`) USING BTREE
)
COLLATE='utf8mb4_uca1400_ai_ci'
ENGINE=InnoDB
;


CREATE TABLE `input` (
	`id` INT(11) NOT NULL AUTO_INCREMENT,
	`problem_id` INT(11) NOT NULL,
	`content` LONGTEXT NOT NULL COLLATE 'utf8mb4_uca1400_ai_ci',
	PRIMARY KEY (`id`) USING BTREE,
	INDEX `input_ibfk_1` (`problem_id`) USING BTREE,
	CONSTRAINT `input_ibfk_1` FOREIGN KEY (`problem_id`) REFERENCES `problem` (`id`) ON UPDATE RESTRICT ON DELETE CASCADE
)
COLLATE='utf8mb4_uca1400_ai_ci'
ENGINE=InnoDB
;

CREATE TABLE `output` (
	`id` INT(11) NOT NULL AUTO_INCREMENT,
	`input_id` INT(11) NOT NULL,
	`content` LONGTEXT NOT NULL COLLATE 'utf8mb4_uca1400_ai_ci',
	PRIMARY KEY (`id`) USING BTREE,
	INDEX `fk_input_id` (`input_id`) USING BTREE,
	CONSTRAINT `fk_input_id` FOREIGN KEY (`input_id`) REFERENCES `input` (`id`) ON UPDATE CASCADE ON DELETE CASCADE
)
COLLATE='utf8mb4_uca1400_ai_ci'
ENGINE=InnoDB
;


CREATE TABLE `problem_log` (
	`id` INT(11) NOT NULL AUTO_INCREMENT,
	`user_id` VARCHAR(20) NOT NULL COLLATE 'utf8mb4_uca1400_ai_ci',
	`problem_id` INT(11) NOT NULL,
	`incorrect_input_id` INT(11) NULL DEFAULT NULL,
	`create_at_time` DATETIME NOT NULL DEFAULT current_timestamp(),
	PRIMARY KEY (`id`) USING BTREE,
	INDEX `fk_problem_id` (`problem_id`) USING BTREE,
	INDEX `fk_incorrect_input_id` (`incorrect_input_id`) USING BTREE,
	CONSTRAINT `fk_incorrect_input_id` FOREIGN KEY (`incorrect_input_id`) REFERENCES `input` (`id`) ON UPDATE CASCADE ON DELETE CASCADE,
	CONSTRAINT `fk_problem_id` FOREIGN KEY (`problem_id`) REFERENCES `problem` (`id`) ON UPDATE CASCADE ON DELETE CASCADE
)
COLLATE='utf8mb4_uca1400_ai_ci'
ENGINE=InnoDB
;
