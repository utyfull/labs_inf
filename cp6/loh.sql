CREATE TABLE table_name (id FLOAT);
INSERT INTO table_name (id) VALUES (1.2);
INSERT INTO table_name (id) VALUES (2.2);
SELECT * FROM table_name;
SELECT id FROM table_name WHERE id == 1.2;
