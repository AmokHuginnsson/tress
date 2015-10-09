CONNECT 'localhost:firebird_context';
DROP DATABASE;
CREATE DATABASE 'localhost:firebird_context';
COMMIT;
CONNECT 'localhost:firebird_context';

DROP USER tress;
DROP DATABASE;

CONNECT 'localhost:tress';
DROP DATABASE;

CREATE DATABASE 'localhost:tress';
COMMIT;

CONNECT 'localhost:tress';

CREATE USER tress PASSWORD 'tr3ss';
COMMIT;

CONNECT 'localhost:tress' USER 'tress' PASSWORD 'tr3ss';

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

INSERT INTO config ( id, name, data ) VALUES( 1, 'one', 'Firebird' );
INSERT INTO config ( id, name, data ) VALUES( 2, 'two', NULL );
INSERT INTO config ( id, name, data ) VALUES( 3, 'three', 'Mê¿ny b±d¼, chroñ pu³k twój i sze¶æ flag!' );

INSERT INTO crud ( id, name, data ) VALUES( 1, 'one', 'Firebird' );
INSERT INTO crud ( id, name, data ) VALUES( 2, 'two', NULL );
INSERT INTO crud ( id, name, data ) VALUES( 3, 'three', 'Mê¿ny b±d¼, chroñ pu³k twój i sze¶æ flag!' );

SET GENERATOR gen_crud_id TO 3;
SET GENERATOR gen_crud_id TO 3;

