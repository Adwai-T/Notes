//We dont use the mongodb directly to create and manage our database.
//WE use the mongoose lib to do that more effectively.
//This file is just an example on how we can set up our database just by using mongodb default library.
const mongodb = require('mongodb');

const dbAddress = 'mongodb://127.0.0.1:27017';
const dbName = 'task-manager';

//Create the client
const MongoClient = mongodb.MongoClient;

//Connect the client
MongoClient.connect(dbAddress, { useNewUrlParser : true, useUnifiedTopology : true }, (error, client)=>{
    if(error){
        return console.log('There was error connecting to the db');
    }
    //Now that we have connected to the databaseClient we can refer to a particular db at the Server by :
    const db = client.db(dbName);//If the bd does not exist a new one is created.
    db.collection('Users').insertOne({//insertMany can be used to insert multiple doucments. Each document need to be individual object.
            name : 'Adwait',
            age : 25,
        }, (error, result)=> { //As the operation of adding a document to the db async it needs to have a callback to tell if the operation was successful.
            if(error){
                return console.log('Unable to insert the document.')
            }
            console.log(result.ops);
        });
});