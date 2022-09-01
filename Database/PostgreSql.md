# PostgreSql

## Setup

When Postgre is being installed, a superuser for postgre will be created, a password will be asked to be set, and the default user name will be `postgre`.

Postgre server is installed as service on windows and can be seen in `run -> services.msc`.

After installing postgre, add the `bin` folder in postgre installation director to path so that we can use postgre from our Commandline/Terminal.

Open Command line terminal with `psql -U username` -> Enter password.

Creating a new Database on the server. `CREATE DATABASE`.

Connect to database using `\c databaseName`

Connection the database from Spring boot  : `application.properties`

```properites
spring.datasource.url=jdbc:postgresql://localhost:5432/postgres
spring.datasource.username=postgres
spring.datasource.password=wait
```

This is the minimum setup required to connect with the database. Other properites can be added.

> PostgreSQL is an advanced, enterprise class open source relational database that supports both SQL (relational) and JSON (non-relational) querying
