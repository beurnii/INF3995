BEGIN TRANSACTION;
CREATE TABLE users (username VARCHAR(256) UNIQUE, password VARCHAR(256));
COMMIT;