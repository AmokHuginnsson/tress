-- Create adminitrative user.

WHENEVER SQLERROR CONTINUE NONE
DROP USER tress CASCADE;

/*
 * IDENTIFIED BY - Assign password
 * DEFAULT TABLESPACE - Assign space for table and index segments
 * TEMPORARY TABLESPACE - Assign sort space */
CREATE USER tress
	IDENTIFIED BY tr3ss
	DEFAULT	TABLESPACE "USERS"
	TEMPORARY TABLESPACE "TEMP";

-- Allow login
GRANT CONNECT, RESOURCE TO tress;

-- Remember to give the user some space quota on its tablespaces.
ALTER USER tress QUOTA 4M ON "USERS";

CONNECT tress/tr3ss

WHENEVER SQLERROR CONTINUE NONE
DROP TABLE config;

CREATE TABLE config	(
	id INTEGER PRIMARY KEY,
	name VARCHAR(16) UNIQUE NOT NULL,
	data VARCHAR( 255 )
);

WHENEVER SQLERROR CONTINUE NONE
DROP SEQUENCE config_id_seq;

CREATE SEQUENCE config_id_seq START WITH 1 INCREMENT BY 1;

WHENEVER SQLERROR CONTINUE NONE
DROP TRIGGER tgg_config_insert;

CREATE TRIGGER tgg_config_insert
BEFORE INSERT ON config
FOR EACH ROW
DECLARE
	max_id number;
	cur_seq number;
BEGIN
	IF :new.id IS NULL THEN
		SELECT config_id_seq.nextval INTO :new.id FROM dual;
	ELSE
		SELECT GREATEST( nvl( max( id ), 0 ), :new.id ) INTO max_id FROM config;
		SELECT config_id_seq.nextval INTO cur_seq FROM dual;
		WHILE cur_seq < max_id
		LOOP
			SELECT config_id_seq.nextval INTO cur_seq FROM dual;
		END LOOP;
	END IF;
	DBMS_SESSION.SET_CONTEXT( 'CLIENTCONTEXT', 'LAST_INSERT_ID', config_id_seq.currval );
END;
/

WHENEVER SQLERROR CONTINUE NONE
DROP TABLE crud;

CREATE TABLE crud	(
	id INTEGER PRIMARY KEY,
	name VARCHAR(16) UNIQUE NOT NULL,
	data VARCHAR( 255 )
);

WHENEVER SQLERROR CONTINUE NONE
DROP SEQUENCE crud_id_seq;

CREATE SEQUENCE crud_id_seq START WITH 1 INCREMENT BY 1;

WHENEVER SQLERROR CONTINUE NONE
DROP TRIGGER tgg_crud_insert;

CREATE TRIGGER tgg_crud_insert
BEFORE INSERT ON crud
FOR EACH ROW
DECLARE
	max_id number;
	cur_seq number;
BEGIN
	IF :new.id IS NULL THEN
		SELECT crud_id_seq.nextval INTO :new.id FROM dual;
	ELSE
		SELECT GREATEST( nvl( max( id ), 0 ), :new.id ) INTO max_id FROM crud;
		SELECT crud_id_seq.nextval INTO cur_seq FROM dual;
		WHILE cur_seq < max_id
		LOOP
			SELECT crud_id_seq.nextval INTO cur_seq FROM dual;
		END LOOP;
	END IF;
	DBMS_SESSION.SET_CONTEXT( 'CLIENTCONTEXT', 'LAST_INSERT_ID', crud_id_seq.currval );
END;
/

INSERT INTO config ( id, name, data ) VALUES( 1, 'one', 'Oracle' );
INSERT INTO config ( id, name, data ) VALUES( 2, 'two', NULL );
INSERT INTO config ( id, name, data ) VALUES( 3, 'three', 'Mê¿ny b±d¼, chroñ pu³k twój i sze¶æ flag!' );

INSERT INTO crud ( id, name, data ) VALUES( 1, 'one', 'Oracle' );
INSERT INTO crud ( id, name, data ) VALUES( 2, 'two', NULL );
INSERT INTO crud ( id, name, data ) VALUES( 3, 'three', 'Mê¿ny b±d¼, chroñ pu³k twój i sze¶æ flag!' );

