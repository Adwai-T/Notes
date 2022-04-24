# MongoDB

## Setting up

* Create a new DataBase or start the already existing bd at file path :
`"(location where mongodb is  installed)\mongodb\bin\mongod.exe" --dbpath="(location where the database exists)\Database"`

Or we can add the bin folder of mongodb to the path and then direcly.

* Use Roto-3T or Mongodb Compass to access the database locally at 27017 port : which is the default port for MongoDB.

## Creating Account

Use the MongoDB official site to create a free tier account : [Mongo Atlas](https://www.mongodb.com/cloud/atlas).

WhiteList the ip so that the repository can be used with that particular id or set it to `0.0.0.0/0` so that all ip's are whitelisted and can be used from any where.

Even when we have whitelist all ips, we don't need to worry as the database is still protected by a username and password.

## Access Remote Repo

Robo 3t does not support connecting to remote mongo databases so we use the default software **MongoDB Compass**.

Link to accessdatabase : `mongodb+srv://learn:passwordHere@cluster0.dszax.mongodb.net/nameofdatabasehere?retryWrites=true&w=majority`.

link to access local database : `mongodb://localhost:27017/?readPreference=primary&appname={AppNameWithoutBrackets}&ssl=false`

## Access Remote Repo from Spring Application

Defined in the SpringBoot.md file.

## Using MongoDB with Java

### Making a connection

> Note : [MongoBD Client Documentation](https://mongodb.github.io/mongo-java-driver/3.8/javadoc/com/mongodb/client/MongoClients.html)

Use `MongoClients.create()`, or `MongoClient()` for the legacy MongoClient API, to make a connection to a running MongoDB instance.

The `MongoClient` instance represents a pool of connections to the database; you will only need one instance of class MongoClient even with multiple threads.

> Note : [MongoDB Connection String Docs](mongodb://[username:password@]host1[:port1][,host2[:port2],...[,hostN[:portN]]][/[database.collection][?options]])

```java
//Connects to the default instance of mongodb client started at local host 27017
MongoClient mongoClient = MongoClients.create();
//Or
MongoClient mongoClient = new MongoClient();

//We could also specify Connection String with the create method

//It also supports multiple host connection
MongoClient mongoClient = MongoClients.create("mongodb://hostOne:27017,hostTwo:27018");

```

### Access Data-Base

* Use the `MongoClient.getDatabase()` method to access a database. If a database does not exist, MongoDB creates the database when we first store data for that database.

* Use its `getCollection()` method to access a collection. If a collection does not exist, MongoBD creates the collection when we first store data for that collection.

>Note : MongoDatabase instances are immutable.

* To create the document using the Java driver, use the `Document` class.

```java
MongoDatabase database = mongoClient.getDatabase("mydb");

MongoCollection<Document> collection = database.getCollection("test");
```

```json
  {
   "name" : "MongoDB",
   "type" : "database",
   "count" : 1,
   "versions": [ "v3.2", "v3.0", "v2.6" ],
   "info" : "{ x : 203, y : 102 }"
  }
```

```java
//To save the above object we use Document class
 Document doc = new Document("name", "MongoDB")
                .append("type", "database")
                .append("count", 1)
                .append("versions", Arrays.asList("v3.2", "v3.0", "v2.6"))
                .append("info", new Document("x", 203).append("y", 102));
```

>Note : The BSON type of array corresponds to the Java type java.util.List

* Insert One document into a collection use `insertOne` method of `MongoCollection` class.

* To insert multiple documents use the `insertMany` method of `MongoCollection` class, which takes a `List` of `Document`s to insert.

```java
collection.insertOne(doc);

List<Document> documents = new ArrayList<Document>();
for (int i = 0; i < 100; i++) {
    documents.add(new Document("i", i));
}
collection.insertMany(documents);
```

>Note : If no top-level `_id` field is specified in the document, MongoDB automatically adds the `_id` field to the inserted document.

* Count `Document`s in `MongoCollection` use `collection.countDocuments()`.

### Query the Collection

To query the collection, you can use the collection’s `find()` method. It `find()` returns a `FindIterable()`.

Using `find` without any paramters will return all the `Document`s stored in the `MongoCollection`.

The find().first() construct is useful for queries that should only match a single document or if we are interested in the first document only.

```java
Document myDoc = collection.find().first();
System.out.println(myDoc.toJson());

//Get all Documents and iterate throught them.
//Using for loop even though permitted is not recommended.
MongoCursor<Document> cursor = collection.find().iterator();
try {
    while (cursor.hasNext()) {
        System.out.println(cursor.next().toJson());
    }
} finally {
    cursor.close();
}

//Print the first document that matches the filter
myDoc = collection.find(eq("i", 71)).first();
System.out.println(myDoc.toJson());

//Get all documents that match the filter "i" > 50
Block<Document> printBlock = new Block<Document>() {
     @Override
     public void apply(final Document document) {
         System.out.println(document.toJson());
     }
};

collection.find(gt("i", 50)).forEach(printBlock);

//Get all documents with a filter being a range
//To specify a filter for a range, such as 50 < i <= 100, we can use the and helper:
collection.find(and(gt("i", 50), lte("i", 100))).forEach(printBlock);
```

### Update Collections

```java
//Update first document that matches the filter
collection.updateOne(eq("i", 10), new Document("$set", new Document("i", 110)));

//Update multiple documents
UpdateResult updateResult = collection.updateMany(lt("i", 100), inc("i", 100));
System.out.println(updateResult.getModifiedCount());
```

### Delete From Collections

```java
//Delete single
collection.deleteOne(eq("i", 110));

//delete multiple
DeleteResult deleteResult = collection.deleteMany(gte("i", 100));
System.out.println(deleteResult.getDeletedCount());
```

> Note : [Getting Started Guide](https://mongodb.github.io/mongo-java-driver/3.8/driver/getting-started/quick-start/)

## Using with Spring

* A model of how the data needs to be stored is created with a Java class.

* A repository interface that extends the `MongoRepository` need to be created. The methods specified in the interface are automatically implemented by Spring Boot.

* They could then be used with a `@Autowired` instance of the interface.

* [Mongo Docs Spring Boot](https://docs.spring.io/spring-data/mongodb/docs/current/api/org/springframework/data/mongodb/repository/MongoRepository.html)

* [Spring Boot with Remote Mongo Repository](https://www.opencodez.com/java/use-mongodb-atlas-with-spring-boot.htm).

* [Spring Working with NOSQL databases](https://docs.spring.io/spring-boot/docs/current/reference/html/spring-boot-features.html#boot-features-nosql).

> Note : Mongodb has Database which has collections which have fields. So In Spring we can name them with `@Document(collection = "Comments")` on Model, and `@Field(value = "userId")` on the fields.

### Setting Up

Mongodb with Spring-Boot needs minimum configuration. We just need to add the `spring-boot-starter-data-mongodb` dependency to our project.

Add the following to the `application.properites` file and Spring will auto-configure Mongodb for use in our application.

```properties
# ----- MongoDb Database Configuration ---- #
spring.data.mongodb.database=website
spring.data.mongodb.uri=mongodb://localhost:27017/?readPreference=primary&appname=website&ssl=false
```

```java
public interface CommentRepository extends MongoRepository<Comment, String> {
    public Optional<Comment> findById(String id);

    public List<Comment> findByTopic(String topic);

    public List<Comment> findByUser(String user);
}

@Document(collection = "Comments")
public class Comment {

    @Id
    private String id;

    private String comment;

    private String topic;

    @Field(value = "userId")
    private String user;

    public Comment(String comment, String topic, String user) {
        this.comment = comment;
        this.topic = topic;
        this.user = user;
    }

    //Getters, Setters and Constructors
}

//We autowire repository and can use it in the class we want
@Autowire
private CommentRepository repository;

repository.deleteAll();
repository.save(new Comment("Comment on topic Java", "Java", "Adwait"));
repository.save(new Comment("Comment on topic JavaScript", "JS", "Sandi"));
repository.save(new Comment("Comment on topic C++", "C++", "Anita")

for(Comment comment : repository.findAll()) {
    log.info(comment.toString());
}
```
