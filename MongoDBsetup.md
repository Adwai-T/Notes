# MongoDB

## Setting up

1. Create a new DataBase or start the already existing bd at file path :
`"C:\Users\Adwait\Documents\NpmFiles\mongodb\bin\mongod.exe" --dbpath="C:\Users\Adwait\Documents\NpmFiles\Database"`

2. Use Roto-3T to access the database locally at 27017 port : which is the default port for MongoDB.

3. A model of how the data should be stored with what properties to be made as a java object. A repository interface
extends the MongoRepository need to be created.

4. The methods specified in the interface are automatically implemented as should by Spring.

5. They could then be used with a @Autowired instance of the interface.

6. [Mongo Docs Spring Boot](https://docs.spring.io/spring-data/mongodb/docs/current/api/org/springframework/data/mongodb/repository/MongoRepository.html)

7. [Spring Boot with Remote Mongo Repository](https://www.opencodez.com/java/use-mongodb-atlas-with-spring-boot.htm).

8. [Spring Working with NOSQL databases](https://docs.spring.io/spring-boot/docs/current/reference/html/spring-boot-features.html#boot-features-nosql).

## Creating Account

Use the MongoDB official site to create a free tier account : [Mongo Atlas](https://www.mongodb.com/cloud/atlas).

WhiteList the ip so that the repository can be used with that particular id or set it to `0.0.0.0/0` so that all ip's are whitelisted and can be used from any where.

Even when we whitelist all ips we dont need to worry as the database is protected by a username and password.

## Access Remote Repo

Robo 3t does not support connecting to remote mongo databases so we use the default software **mongo compass**.

Link to accessdatabase : "mongodb+srv://learn:passwordHere@cluster0.dszax.mongodb.net/nameofdatabasehere?retryWrites=true&w=majority".
