DROP DATABASE IF EXISTS tress;
DROP USER IF EXISTS tress;

CREATE USER tress WITH ENCRYPTED PASSWORD 'tr3ss' NOCREATEDB;
CREATE DATABASE tress WITH OWNER tress ENCODING 'UTF-8';

\connect tress

CREATE TABLE config (
	id SERIAL,
	name VARCHAR(16) UNIQUE NOT NULL,
	data VARCHAR( 255 )
) WITH OIDS;

CREATE TABLE crud (
	id SERIAL,
	name VARCHAR(16) UNIQUE NOT NULL,
	data VARCHAR( 255 )
) WITH OIDS;

INSERT INTO config ( id, name, data ) VALUES( 1, 'one', 'PostgreSQL' );
INSERT INTO config ( id, name, data ) VALUES( 2, 'two', NULL );
INSERT INTO config ( id, name, data ) VALUES( 3, 'three', 'Mężny bądź, chroń pułk twój i sześć flag!' );

INSERT INTO crud ( id, name, data ) VALUES( 1, 'one', 'sqlite3' );
INSERT INTO crud ( id, name, data ) VALUES( 2, 'two', NULL );
INSERT INTO crud ( id, name, data ) VALUES( 3, 'three', 'Mężny bądź, chroń pułk twój i sześć flag!' );

SELECT setval( 'config_id_seq', 3 );
SELECT setval( 'crud_id_seq', 3 );

GRANT SELECT,INSERT,UPDATE,DELETE ON config TO tress;
GRANT SELECT,UPDATE ON config_id_seq TO tress;

GRANT SELECT,INSERT,UPDATE,DELETE ON crud TO tress;
GRANT SELECT,UPDATE ON crud_id_seq TO tress;

