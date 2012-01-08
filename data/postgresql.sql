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

INSERT INTO config ( id, name, data ) VALUES( 1, 'one', 'PostgreSQL' );
INSERT INTO config ( id, name, data ) VALUES( 2, 'two', NULL );
INSERT INTO config ( id, name, data ) VALUES( 3, 'three', 'Mê¿ny b±d¼, chroñ pu³k twój i sze¶æ flag!' );
SELECT setval( 'config_id_seq', 3 );

GRANT SELECT,INSERT,UPDATE,DELETE ON config TO tress;
GRANT SELECT,UPDATE ON config_id_seq TO tress;

