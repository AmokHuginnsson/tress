SET NAMES 'utf8';
use mysql;
DROP USER IF EXISTS 'tress'@'localhost';
DROP DATABASE IF EXISTS tress;
CREATE USER 'tress'@'localhost' IDENTIFIED BY 'tr3ss';
GRANT USAGE ON *.* TO 'tress'@'localhost';
FLUSH PRIVILEGES;

CREATE DATABASE tress DEFAULT CHARACTER SET 'utf8';
use tress;

CREATE TABLE IF NOT EXISTS config (
	id INTEGER(10) UNSIGNED PRIMARY KEY AUTO_INCREMENT,
	name VARCHAR(16) UNIQUE NOT NULL,
	data VARCHAR( 255 )
) CHARACTER SET = 'utf8';

CREATE TABLE IF NOT EXISTS crud (
	id INTEGER(10) UNSIGNED PRIMARY KEY AUTO_INCREMENT,
	name VARCHAR(16) UNIQUE NOT NULL,
	data VARCHAR( 255 )
) CHARACTER SET = 'utf8';

GRANT SELECT,INSERT,UPDATE,DELETE ON tress.* TO tress@localhost;
FLUSH PRIVILEGES;

INSERT INTO config ( id, name, data ) VALUES( 1, 'one', 'MySQL' );
INSERT INTO config ( id, name, data ) VALUES( 2, 'two', NULL );
INSERT INTO config ( id, name, data ) VALUES( 3, 'three', 'Mężny bądź, chroń pułk twój i sześć flag!' );

INSERT INTO crud ( id, name, data ) VALUES( 1, 'one', 'sqlite3' );
INSERT INTO crud ( id, name, data ) VALUES( 2, 'two', NULL );
INSERT INTO crud ( id, name, data ) VALUES( 3, 'three', 'Mężny bądź, chroń pułk twój i sześć flag!' );

