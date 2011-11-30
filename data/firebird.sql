CONNECT 'firebird_context';
DROP DATABASE;
CREATE DATABASE 'firebird_context';
COMMIT;
CONNECT 'firebird_context';

DROP USER tress;
DROP DATABASE;

CONNECT 'tress';
DROP DATABASE;

CREATE DATABASE 'tress';
COMMIT;

CONNECT 'tress';

CREATE USER tress PASSWORD 'tr3ss';
COMMIT;

CONNECT 'tress' USER 'tress' PASSWORD 'tr3ss';

DROP TABLE config;
CREATE TABLE config
	(
	id INTEGER PRIMARY KEY,
	name VARCHAR(16) UNIQUE NOT NULL,
	data VARCHAR( 255 )
	);

INSERT INTO config ( id, name, data ) VALUES( 1, 'one', '1' );
INSERT INTO config ( id, name, data ) VALUES( 2, 'two', '22' );
INSERT INTO config ( id, name, data ) VALUES( 3, 'three', '333' );
INSERT INTO config ( id, name, data ) VALUES( 4, 'four', '4444' );

