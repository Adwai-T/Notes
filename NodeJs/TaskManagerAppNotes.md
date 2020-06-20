## MongoDB :
It is an opensource database.

### Difference btn SQL and NoSQL :
|SQL | NoSQL|
 :---: |  :---: 
Both have data base | Both have a data base
looks like a list(rosen) | looks like json with fields.
Table | Collection
Has Rows and columns | Has Documents with fields

### Set up MongoDb

1. Download and extract the zip file to desired directory.
2. Create a folder where our data needs to be stored locally. 
3. Form the command prompt in vs code `C:\Users\Adwait\Documents\NpmFiles\mongodb\bin\mongod.exe --dbpath=C:\Users\Adwait\Documents\NpmFiles\mongodb-data`
4. First is the path to mongodb executable and the other is the path to the location that our data needs to be stored.
5. This will start our data base for the first time and print some messages to the console.
6. The message of interest is the message about 4-5 messages before the end that contains the ` NETWORK  [listener] waiting for connections on port 27017` at which the data-base can be heard from.
7. Now once the data base is runnint we have to leave the command in the command promt running until we need to access the database.
8. We can create and use multiple terminals to run our project.
9. Keep the mongodb database running so that we can access it form the robot 3t application.

Mongodb GUI admin tool :
1. We will `Robot 3T` as our mongobd admin tool.
2. Search and download.
3. Once downloaded and installed open.
4. Create a new connection
5. For now for the local host connection just change the name of the Connection as other setting are to be changed only when deploying the app.

### Connect and edit database :
1. Download the drivers for the node mongodb from npm.
2. In the file require mongodb.
3. Create a client with `mongodb.MongoClient`. We will use this client to connect to the database and perform all operations.
4. With our mongodb running locally the address to connect to it is `mongodb://127.0.0.1:27017`.
5. To connect to mongodb we use `MongoClient.connect(bdURL, {options Object}, callbackFunction`. We will use 1 option right now that is `useNewUrlParser : true` as the older version of this parser is depricated.
6. The conncet operation is a async operation and will take some time to run and hence the callback funtion has a error parameter.
7. To create a document object in a collection use `const db =client.db(databaseName)` and db will provide a reference to this dataBase.
8. To add an object to this document we will use `db.collection('users').insertOne({ name : 'Adwait' , age : 25});`

### Promises : 
1. They are used to manage our async code and are use to solve the problems that callback code might bring.
2. The promise builds on the concept of callback function.


### Mongoose : 
1. Mongoose is a ODM : Object Document mapper.
2. Mongoose wraps around the mongodb library and provides us even more features and also make the use of the existing features in the mongole bd library even simpler.
3. As mongoose is build around mongodb it is very similar in operation to the mongodb.
4. Mongoose maps data as models. 
5. Connecting to the mongodb with mongoose : 
```javascript
mongoose.connect('mongodb://127.0.0.1:27017/task-manager-api', {
    useNewUrlParser : true,
    useCreateIndex : true, //Index is created so that we can quickly access data from the db
    useUnifiedTopology: true,   
})
```
6. To create a model in mongooese We use `mongoose.model('name' , { fields we want to define })`. It will act as a blueprint to create the document for the collection in the db.
7.  We create a new entry to be added to the collection in the db by using the `new` on the model that we created.
8. Now to actually save the created document from above to the db we use `save()` and it returns a promise.

## Rest Api : 

### Route Handling with express: 
1. Create a new Rounter : `const router = new express.Router();` 
2. Like we use `app.get` or `app.post` where app is a new express server we use the `router.get` or `router.post`.
3. Export the router from the file.
4. Use `app.use(router)` to get the router to work with our created server.

### Authentication and Security : 

1. Hash passwords : We use the bcryptjs to hash our password. It hashes our password that means once converted to a value the value cannot be reversed to original.
2. To hash our password with the library we use `cont myHashPassword = await bcryptjs.hash('plainTextPassword', numberOfRounds)`. 8 is the recommended number of `numberOfRounds` as it does not take too long and it is safe.
3. To compare the given password with the hashed password from our database we could use : `const isMatch = await bcyptjs.compare('PlainTextPassword', ourHashedPassword);` gives a boolean values.

### Mongoose Middleware : 
1. When we create a mongoose model and pass our object of options in, mongoose converts it into a schema.
2. To manually create the schema we use `const userSchema = new mongoose.Schema({object of options})`.
3. Now we can pass this schema to our model to set the model up and we can also use middle-ware on the schema.
4. To use middle ware just before saving the user to database we use : 
```javascript
//Using middleware just before we save user to database to check if our password is changed and hash it if it was changed.
//We use the normal function as the 'this' of this funtion will give us access to the current user being updated.
userSchema.pre('save',async function(){
    //To make it more clear what 'this' in the context of the function is we will set this to be a variable named user.
    const user = this;    
    if(user.isModified('password')){
        user.password = await bcrypt.hash(user.password, 8);
    }

    next(); //if next is not called it will hang here and will never finish this function.
});
```
5. Some of the functions of mongoose like findbyIdAndUpdate by pass middleware and validation. They thus cannot be used when we are using middle ware with them. 
6. So we edit the function to use more traditional functions like findById and then modify the users individual properties.

### Loggin a user in : 
1. Create Custom functions on the user schema that can be user to do custom things : 
```javascript 
//Statics below represents that it is a static function and can be directly used on userSchema or model.
userSchema.statics.findUserByCredentials = async (email, password)=>{
    const user = await User.findOne({ email });
    if(!user) {
        throw new Error('Enable to login.')    
    }
    
    const isMatch = await bcrypt.compare(password, user.password);
    if(!isMatch){
        throw new Error('Enable to login');
    }
    return user;
}
```

### JSON web-tokens : 
1. Basic use of JSON web-tokens is shown in the example related to jwtTokes.js.

### Express Middleware : 
1. Like mongoose has middle ware function/methods that can be create to do something before data is saved to database, express also has middle ware that could be use in between when we get the request and when we act on what we do with the request.
2. To use the middle ware provided by express : 
```javascript
app.use((req, res, next) =>{
    console.log(req.method); //logs method used to send request like post, get etc;
    console.log(req.path);//logs path of the request being send.
    next(); // The next method provided by express call a function that lets express run as it should and act on the request being send  and respond with appropriate data.
});
```
3. We use the express middleware to check for authentication of the user and their prevelage to check and access data.
4. To use a middle-ware for a particular request type we use it with middle-ware function as an argument passed to the route handler for type of request. 
```javascript
route.get('/user', middlewareFunction, async Callbackfunction);
```

### Sending back and using auth tokens : 
1. The jwt auth token is send back as a bearer token as a header with the request.
2. Headers are send as a key-value pair.
3. We send our token as `Authorization => Bearer token`.
4. We can de code the token and use our playload that we had send that is the user id in this case to find the user and give them access to their data.
5. `jwt.verify` is a sync function.
6. value can be added to the req property that we get as an input parameter. In our case we add the user that we authenticated to the request so that the user data can be used directly and will not have to be found once again.

### Advanced postman
1. Set up Enviroment varibles that can be used to have a variable url. Set `url => 'localhost:3000'` and then use `{{url}}` before the derired path so the when the enviroment is set all request have the desired url.
2. Pre-request script supports javascript with postman functions so that we can automate what happens before a request is send to the server through postman.
3. Tests in postman runs after we have recieved response from the server and provides us with function.
4. So the test Script for when we create a user :
```javascript 
//We check if the user was successfully created and only then run the below script
if (pm.response.code === 201) {
    //Set the enviroment varible named authToken to token responce value that we get from the server
    pm.environment.set('authToken', pm.response.json().token);
}
```
5. We dont want the test to run when we login the user or create the user so we set the authorization for the request to be noAuth.
6. All other request are set to have authorization set to inherit from parent.

### JSON.Stringify : 
1. When we send a res to the user express automatically calls the JSON.stringify method on the object being passed as paramters.
2. We can thus manipulate what the stringified object returns by creating a method toJSON().
```javascript
//Here we have an object for example.
const pet= {
    name : 'teli',
    age : 5
}

//This method governs what is returned when the JSON.stringify method is called.
pet.toJSON = function(){
    delete this.age;//We delete the property of the object 
    return this; //We return the object with the remaining properties.
}

console.log(JSON.stringify(pet));//The above toJSON method is called whenever we call the JSON.stringify method
//The log will show that the object only has name and does not have age as the property was removed in our above function.
```

### User Task relationship :
1. To set up the relationship between the tasks and the user we will set up a new field in the tasks database.
2. The field will store the user id that created them. 
3. For storing the id the type of the id will be :`mongoose.Schema.Types.ObjectId`.
4. When a task is created the users id should be now stored along with the req.body that was send with the req.
5. Setting up the `ref` property so that we can get the owner and his full profile using mongoose.
```javascript
const Task = require('./models/model_tasks');
const User = require('./models/model_user');
const main = async ()=>{
    //----- Find owner from task ---
    //To get the user's complete profile by using the the owner field that was set up in the model_task.
    const task = await Task.findById('taskid');
    await task.populate('owner').execPopulate();
    console.log(task.owner);//Prints out the complete profile of the user with the given id.

    //----- Find tasks from owner --- Refer the model_user.js
    const user =  await User.findById('userID');
    await user.populate('tasks').execPopulate();
    console.log(user.tasks);

}

//---- model_user.js ---- create virtual model property.
//There properties are virtual and define the relation between the user and task and is not actually stored in the user database.
userSchema.virtual('tasks', { //tasks is the name of the property that we can refer to populate our tasks from the tasks db.
    ref : 'Tasks', //name of the db that is used.
    localField : '_id', //name of property in local db
    foreignField : 'owner' //Name of the property in the field to be refered.
});

```

### Pagining and sorting : 
```javascript 
    //---2
    const match = {}
    if(req.query.completed){
        match.completed = req.query.completed === 'true' //As the req.query.completed returns a string value we want to convert it to boolean
    }
    //Use sort to sort data by completed or by time
    const sort = {}
    if(req.query.sortBy){
        const parts = req.query.sortBy.split(':');
        sort[parts[0]] = parts[1] === 'desc' ? -1 : 1;
    }

    try{
        // const tasks = await model_task.find({ owner : req.user._id });//---1
        // await req.user.populate('tasks').execPopulate(); //---2 this was used when we wanted to get all tasks for the user without any filter.
        //---2
        await req.user.populate({
            path : 'tasks', //Defines the path for the virtual property that we had created.
            match,
            //We use options for pagination. That is to see results a pages containing provided amount of results.
            options : {
                limit : parseInt(req.query.limit),//The number of reqults per page.
                skip : parseInt(req.query.skip),//The number of results to skipped and shown in the next page.
                sort
            }
        }).execPopulate();
        res.status(200).send(req.user.tasks);        
    }
```