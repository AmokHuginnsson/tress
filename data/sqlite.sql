DROP TABLE IF EXISTS test_item;
DROP TABLE IF EXISTS test;
DROP TABLE IF EXISTS test_dict;
DROP TABLE IF EXISTS crud;
DROP TABLE IF EXISTS config;

CREATE TABLE config (
	id INTEGER PRIMARY KEY,
	name VARCHAR( 16 ) UNIQUE NOT NULL,
	data VARCHAR( 255 )
);

CREATE TABLE crud (
	id INTEGER PRIMARY KEY,
	name VARCHAR( 16 ) UNIQUE NOT NULL,
	data VARCHAR( 255 )
);

CREATE TABLE test_dict (
	id INTEGER PRIMARY KEY,
	name VARCHAR(128)
);

CREATE TABLE test (
	id INTEGER PRIMARY KEY,
	id_test_dict INTEGER,
	v_text VARCHAR( 255 ),
	v_int INTEGER,
	v_real FLOAT,
	v_date DATE,
	v_time TIME,
	v_datetime DATETIME
);

CREATE TABLE test_item (
	id INTEGER PRIMARY KEY,
	id_test INTEGER NOT NULL,
	name VARCHAR( 16 ),
	data VARCHAR( 255 ),
	value FLOAT
);

INSERT INTO config ( id, name, data ) VALUES( 1, 'one', 'sqlite3' );
INSERT INTO config ( id, name, data ) VALUES( 2, 'two', NULL );
INSERT INTO config ( id, name, data ) VALUES( 3, 'three', 'Mê¿ny b±d¼, chroñ pu³k twój i sze¶æ flag!' );

INSERT INTO crud ( id, name, data ) VALUES( 1, 'one', 'sqlite3' );
INSERT INTO crud ( id, name, data ) VALUES( 2, 'two', NULL );
INSERT INTO crud ( id, name, data ) VALUES( 3, 'three', 'Mê¿ny b±d¼, chroñ pu³k twój i sze¶æ flag!' );

INSERT INTO "test_dict" VALUES(1,'mensa_pangram');
INSERT INTO "test_dict" VALUES(2,'Matrix');
INSERT INTO "test_dict" VALUES(3,'Invictus');

INSERT INTO "test" VALUES(1,3,'I am the master of my fate, I am the captain of my soul',187,1.41421356237309514547e+00,'2001-09-21','22:11:00','2011-03-15 14:30:18');
INSERT INTO "test" VALUES(2,2,'There is no spoon!',13,2.7182818459045,'1995-05-19','03:45:21','2014-10-07 16:18:44');
INSERT INTO "test" VALUES(3,1,'Mê¿ny b±d¼, chroñ pu³k Twój i sze¶æ flag!',7,3.14159265358979311599e+00,'1989-08-24','13:45:57','2014-10-07 17:30:39');

