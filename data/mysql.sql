use mysql;
DELETE FROM user WHERE user='tress' AND host='localhost';
DROP DATABASE IF EXISTS tress;
INSERT INTO user (host, user, password) VALUES ('localhost','tress',PASSWORD('tr3ss'));
FLUSH PRIVILEGES;

CREATE DATABASE tress;
use tress;

CREATE TABLE IF NOT EXISTS config
	(
	id INTEGER(10) UNSIGNED PRIMARY KEY AUTO_INCREMENT,
	name VARCHAR(16) UNIQUE NOT NULL,
	data VARCHAR( 255 )
	) CHARACTER SET = 'latin2';

GRANT SELECT,INSERT,UPDATE,DELETE ON tress.* TO tress@localhost;
FLUSH PRIVILEGES;

INSERT INTO config ( id, name, data ) VALUES( 1, 'one', 'MySQL' );
INSERT INTO config ( id, name, data ) VALUES( 2, 'two', NULL );
INSERT INTO config ( id, name, data ) VALUES( 3, 'three', 'M�ny b�d�, chro� pu�k tw�j i sze�� flag!' );

