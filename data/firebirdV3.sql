-- Allow RemoteAccess to security.db before running this script.

COMMIT;
CONNECT 'localhost:security.db' USER 'sysdba' ROLE 'RDB$ADMIN';

DROP USER tress;

COMMIT;
CREATE DATABASE 'localhost:firebird_context'; -- Fallback for DROP DATABASE if CONNECT to tress fails.

COMMIT;
CONNECT 'localhost:firebird_context' USER 'sysdba' ROLE 'RDB$ADMIN';
CONNECT 'localhost:tress' USER 'sysdba' ROLE 'RDB$ADMIN';

DROP DATABASE;

COMMIT;
CONNECT 'localhost:' USER 'sysdba' ROLE 'RDB$ADMIN';

CREATE DATABASE 'localhost:tress';

COMMIT;
CONNECT 'localhost:tress' USER 'sysdba' ROLE 'RDB$ADMIN';

CREATE USER tress PASSWORD 'tr3ss';
GRANT RDB$ADMIN TO tress;

COMMIT;
CONNECT 'localhost:tress' USER 'tress' PASSWORD 'tr3ss' ROLE 'RDB$ADMIN';

DROP TABLE config;
CREATE TABLE config (
	id INTEGER PRIMARY KEY,
	name VARCHAR(16) UNIQUE NOT NULL,
	data VARCHAR( 255 )
);
CREATE GENERATOR gen_config_id;
SET GENERATOR gen_config_id TO 0;

set term !! ;
CREATE TRIGGER tgg_config_insert FOR config
ACTIVE BEFORE INSERT POSITION 0
AS
BEGIN
if ( NEW.ID is NULL ) then NEW.ID = GEN_ID( gen_config_id, 1 );
RDB$SET_CONTEXT('USER_SESSION', 'LAST_INSERT_ID', NEW.ID);
END!!
set term ; !!

DROP TABLE crud;
CREATE TABLE crud (
	id INTEGER PRIMARY KEY,
	name VARCHAR(16) UNIQUE NOT NULL,
	data VARCHAR( 255 )
);
CREATE GENERATOR gen_crud_id;
SET GENERATOR gen_crud_id TO 0;

set term !! ;
CREATE TRIGGER tgg_crud_insert FOR crud
ACTIVE BEFORE INSERT POSITION 0
AS
BEGIN
if ( NEW.ID is NULL ) then NEW.ID = GEN_ID( gen_crud_id, 1 );
RDB$SET_CONTEXT('USER_SESSION', 'LAST_INSERT_ID', NEW.ID);
END!!
set term ; !!

COMMIT;

CONNECT 'localhost:tress' USER 'sysdba' ROLE 'RDB$ADMIN';
REVOKE RDB$ADMIN FROM tress;
COMMIT;

CONNECT 'localhost:firebird_context' USER 'sysdba' ROLE 'RDB$ADMIN';
DROP DATABASE;
COMMIT;

CONNECT 'localhost:tress' USER 'tress' PASSWORD 'tr3ss';

INSERT INTO config ( id, name, data ) VALUES( 1, 'one', 'Firebird' );
INSERT INTO config ( id, name, data ) VALUES( 2, 'two', NULL );
INSERT INTO config ( id, name, data ) VALUES( 3, 'three', 'Mężny bądź, chroń pułk twój i sześć flag!' );

INSERT INTO crud ( id, name, data ) VALUES( 1, 'one', 'Firebird' );
INSERT INTO crud ( id, name, data ) VALUES( 2, 'two', NULL );
INSERT INTO crud ( id, name, data ) VALUES( 3, 'three', 'Mężny bądź, chroń pułk twój i sześć flag!' );

SET GENERATOR gen_config_id TO 3;
SET GENERATOR gen_crud_id TO 3;

