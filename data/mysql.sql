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
	value VARCHAR( 255 )
	);

GRANT SELECT,INSERT,UPDATE,DELETE ON tress.* TO tress@localhost;
FLUSH PRIVILEGES;

INSERT INTO config ( id, name, value ) VALUES( 1, 'one', '1' );
INSERT INTO config ( id, name, value ) VALUES( 2, 'two', '22' );
INSERT INTO config ( id, name, value ) VALUES( 3, 'three', '333' );
INSERT INTO config ( id, name, value ) VALUES( 4, 'four', '4444' );

