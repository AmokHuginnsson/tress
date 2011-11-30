DROP DATABASE tress;
DROP USER tress;

CREATE USER tress WITH ENCRYPTED PASSWORD 'tr3ss' NOCREATEDB NOCREATEUSER;
CREATE DATABASE tress WITH OWNER tress ENCODING 'latin2';

\connect tress

CREATE TABLE config
	(
	id SERIAL,
	name VARCHAR(16) UNIQUE NOT NULL,
	data VARCHAR( 255 )
	) WITH OIDS;

INSERT INTO config ( id, name, data ) VALUES( 1, 'one', '1' );
INSERT INTO config ( id, name, data ) VALUES( 2, 'two', '22' );
INSERT INTO config ( id, name, data ) VALUES( 3, 'three', '333' );
INSERT INTO config ( id, name, data ) VALUES( 4, 'four', '4444' );
SELECT setval( 'config_id_seq', 4 );

GRANT SELECT,INSERT,UPDATE,DELETE ON config TO tress;
GRANT SELECT,UPDATE ON config_id_seq TO tress;

