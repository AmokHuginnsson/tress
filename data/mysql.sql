SET NAMES 'latin2';
use mysql;
GRANT USAGE ON *.* TO 'tress'@'localhost';
DROP USER 'tress'@'localhost';
DROP DATABASE IF EXISTS tress;
CREATE USER 'tress'@'localhost' IDENTIFIED BY 'tr3ss';
FLUSH PRIVILEGES;

CREATE DATABASE tress DEFAULT CHARACTER SET latin2;
use tress;

CREATE TABLE IF NOT EXISTS config (
	id INTEGER(10) UNSIGNED PRIMARY KEY AUTO_INCREMENT,
	name VARCHAR(16) UNIQUE NOT NULL,
	data VARCHAR( 255 )
) CHARACTER SET = 'latin2';

CREATE TABLE IF NOT EXISTS crud (
	id INTEGER(10) UNSIGNED PRIMARY KEY AUTO_INCREMENT,
	name VARCHAR(16) UNIQUE NOT NULL,
	data VARCHAR( 255 )
) CHARACTER SET = 'latin2';

GRANT SELECT,INSERT,UPDATE,DELETE ON tress.* TO tress@localhost;
FLUSH PRIVILEGES;

INSERT INTO config ( id, name, data ) VALUES( 1, 'one', 'MySQL' );
INSERT INTO config ( id, name, data ) VALUES( 2, 'two', NULL );
INSERT INTO config ( id, name, data ) VALUES( 3, 'three', 'Mê¿ny b±d¼, chroñ pu³k twój i sze¶æ flag!' );

INSERT INTO crud ( id, name, data ) VALUES( 1, 'one', 'sqlite3' );
INSERT INTO crud ( id, name, data ) VALUES( 2, 'two', NULL );
INSERT INTO crud ( id, name, data ) VALUES( 3, 'three', 'Mê¿ny b±d¼, chroñ pu³k twój i sze¶æ flag!' );

