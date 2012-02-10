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

CREATE TABLE config
	(
	id INTEGER PRIMARY KEY,
	name VARCHAR(16) UNIQUE NOT NULL,
	data VARCHAR( 255 )
	);

INSERT INTO config ( id, name, data ) VALUES( 1, 'one', 'Oracle' );
INSERT INTO config ( id, name, data ) VALUES( 2, 'two', NULL );
INSERT INTO config ( id, name, data ) VALUES( 3, 'three', 'Mê¿ny b±d¼, chroñ pu³k twój i sze¶æ flag!' );

