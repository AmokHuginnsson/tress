DROP TABLE IF EXISTS config;
CREATE TABLE config (
	id INTEGER PRIMARY KEY,
	name VARCHAR(16) UNIQUE NOT NULL,
	data VARCHAR( 255 )
);

CREATE TABLE crud (
	id INTEGER PRIMARY KEY,
	name VARCHAR(16) UNIQUE NOT NULL,
	data VARCHAR( 255 )
);

INSERT INTO config ( id, name, data ) VALUES( 1, 'one', 'sqlite3' );
INSERT INTO config ( id, name, data ) VALUES( 2, 'two', NULL );
INSERT INTO config ( id, name, data ) VALUES( 3, 'three', 'M�ny b�d�, chro� pu�k tw�j i sze�� flag!' );

INSERT INTO crud ( id, name, data ) VALUES( 1, 'one', 'sqlite3' );
INSERT INTO crud ( id, name, data ) VALUES( 2, 'two', NULL );
INSERT INTO crud ( id, name, data ) VALUES( 3, 'three', 'M�ny b�d�, chro� pu�k tw�j i sze�� flag!' );

