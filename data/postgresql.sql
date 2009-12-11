DROP DATABASE tress;
DROP USER tress;

CREATE USER tress WITH ENCRYPTED PASSWORD 'tr3ss' NOCREATEDB NOCREATEUSER;
CREATE DATABASE tress WITH OWNER tress ENCODING 'latin2';

\connect tress

CREATE TABLE config
	(
	id SERIAL,
	name VARCHAR(16) UNIQUE NOT NULL,
	value VARCHAR( 255 )
	);

INSERT INTO config ( id, name, value ) VALUES( 1, 'one', '1' );
INSERT INTO config ( id, name, value ) VALUES( 2, 'two', '22' );
INSERT INTO config ( id, name, value ) VALUES( 3, 'three', '333' );
INSERT INTO config ( id, name, value ) VALUES( 4, 'four', '4444' );

GRANT SELECT,INSERT,UPDATE,DELETE ON config TO tress;
GRANT SELECT,UPDATE ON config_id_seq TO tress;
