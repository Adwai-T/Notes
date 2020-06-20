const mongoose = require('mongoose');

//Similar to the mongodb.mongoClient.connect we will connect to the mongodb by using mongoose.
//Unike mongodb though we provide the name of the db with the connection url.
//Like the mongodb if the db does not exist one with the given name is created.
mongoose.connect('mongodb://127.0.0.1:27017/task-manager-api', {
    useNewUrlParser : true,
    useCreateIndex : true, //Index is created so that we can quickly access data from the db
    useUnifiedTopology: true,

})

//Defining a model for our database. Now user stores a blueprint
//for the model and can be used to create the document that we 
//want to store in the db.
//'User' : Here is the name of the collection.
const User = mongoose.model('User', {
    name : {
        type : String,
        require : true, //Specify if the field is required and compulsory to save the doc to db.
    },
    age : {
        type : Number,
        validate(value){ //The validate funtion is used to put condition on what value is accepted and which are rejected.
            if(age < 0) throw new Error ('Entered as not valid');
        }//We can use the validator npm library to get a lot of predefined validators.
    }
});

//Create a document from the above model.
const user1 = new User({
    name : 'Adwait',
    age : 26,
});

//save the user created to the db that we are connected to.
//The save method call on the object created form model returns a promise.
user1.save().then(()=>{
    console.log(user1);
}).catch((error)=>{
    console.log('Error while saving : ' + error);
});
