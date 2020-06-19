## Maven

1. Run application with maven : `./mvnw spring-boot:run`

2. Build a jar file with maven  : `./mvnw clean package` : It will clean the precious builds and create a new one.

3. Run the jar that is build from target folder :  java -jar build/libs/jarName.jar


## Gradle :

1. Run : ./gradlew bootRun

2. Build into jar : ./gradlew build

3. Run the jar that is build from target folder :  java -jar build/libs/jarName.jar


## MongoDB

* Setting up :

1. Create a new DataBase or start the already existing bd at file path :
`"C:\Users\Adwait\Documents\NpmFiles\mongodb\bin\mongod.exe" --dbpath="C:\Users\Adwait\Documents\NpmFiles\Database"`

2. Use Roto-3T to access the database locally at 27017 port : which is the default port for MongoDB.

3. A model of how the data should be stored with what properties to be made as a java object. A repository interface
extends the MongoRepository need to be created.

4. The methods specified in the interface are automatically implemented as should by Spring.

5. They could then be used with a @Autowired instance of the interface.

6. https://docs.spring.io/spring-data/mongodb/docs/current/api/org/springframework/data/mongodb/repository/MongoRepository.html





