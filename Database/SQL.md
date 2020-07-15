# SQL

Notes Taken from Youtube channel : ![Socratica](https://www.youtube.com/channel/UCW6TXMZ5Pq6yL6_k5NZ2e0Q)

Structured Query Language

Made for CRUD : Create Read Update Delete

Relational Database :

**Database** *is* -> **Collection** of tables *has*-> Rows and Columns -> Each row is called as a **Record**

Data in tables can be related to each other, that is why they are called as relational database.

Taken together the collection of tables in a database is called as **Schema**.

## Commands

```sql
/*Create a new database with name name_table*/
CREATE DATABASE name_table;
/*Create a new table in the database with name name_table and define its columns*/
CREATE TABLE users(
    user_id int,
    first_name VARCHAR(100),
    last_name VARCHAR(100),
    email VARCHAR(255)
);

/*Update the database with name name_table and add a new column with name encrypted_password. It does not actually encrypt password, the name of the column is encrypted password */
ALTER TABLE users ADD encrypted_password VARCHAR(1000);

/*delete/remove column email from name_table*/
ALTER TABLE user DROP COLUMN email;

/*delete/remove table from database*/
DROP TABLE user;

/*Remove/Delete Complete database with all its tables and entries.*/
DROP DATABASE name_table;
```

## Interacting with DataBase

```sql
/*Insert a record/row to the movies table*/
INSERT INTO movies (movies_id, title, description, price) VALUES(1, 'Gattaca', 'Movie or documentary', 4.99);
/*View All entries of movies table*/
SELECT * FROM movies;
/*select a particular column to be viewed, they are in no praticular order. FROM selects tables and SELECT for columns*/
SELECT title, price FROM movies;
/*Select table by desc order*/
SELECT title, price FROM movies ORDER BY price DESC;
/*rows are selected with WHERE*/
UPDATE movies SET price = 0.99 WHERE title = 'Jaws';
/**/
DELETE FROM movies WHERE title = 'Star Wars'
/*Gives us the number of rows in the tables*/
SELECT COUNT(*) FROM movies
/*Select by price range*/
SELECT * FROM movies WHERE price >= 1 AND price <= 5;
/*Use the number of rows that are given*/
LIMIT 10;
```

```sql
SELECT *
FROM table_name
WHERE condition1 OR condition2
ORDER BY column_name ASC
LIMIT 10;

/*Gives min and max value in the table column*/
SELECT MIN(column_name), MAX(column_name)

/*Only show distinct entries*/
SELECT DISTINCT column_name FROM table_name
```

* In the above `INSERT` we specified an ID(movies_id), these are used as unique identifiers for that entry. Most database softwares will generate an ID automatically and will not have to provide an id manually.

## Joins

```sql
SELECT * FROM table1
INNER JOIN table2
ON table1.base_id = table2.base_id
```

JOIN type :

1. `INNER JOIN` : Only joins the rows that have a match in both the tables.
2. `FULL JOIN` : Joins table irrespective if whether or not there is a matching id and puts null for the values that are not matched.
3. `LEFT JOIN` and `RIGHT JOIN` : Shows all the record from one of the tables whether there is a common id or not, but leaves the other tables entries that dont have a matching id with the other table.

Note : Not all database support all the four types of joins. For example MySQL does not support full join.

## Views

When we create Views it Give permission to a view instead of the whole table and can hide sensitive data. A view also returns a table but without the sensitive data.

```sql
CREATE VIEW people_on_mars AS
SELECT CONCAT('m',martian_id), first_name, last_name, 'Martian' AS status
FROM martian_public
UNION
SELECT CONCAT('v',visitor_id), first_name, last_name, 'Visitor' AS status
FROM visitor;

/**/
SELECT *
FROM people_on_mars
ORDER BY last_name;
```

## Create Index

```sql
CREATE INDEX person_first_name_idx
ON person (fist_name);
```
