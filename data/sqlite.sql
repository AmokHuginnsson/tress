DROP TABLE config;
CREATE TABLE config
	(
	id INTEGER PRIMARY KEY,
	name VARCHAR(16) NOT NULL,
	value VARCHAR( 255 )
	);

INSERT INTO config ( id, name, value ) VALUES( 1, 'one', '1' );
INSERT INTO config ( id, name, value ) VALUES( 2, 'two', '22' );
INSERT INTO config ( id, name, value ) VALUES( 3, 'three', '333' );
INSERT INTO config ( id, name, value ) VALUES( 4, 'four', '4444' );

