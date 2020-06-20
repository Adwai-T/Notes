const express = require('express');
require('./db/mongoose') //We just need it in require so that the monodb client is connected.
const model_user = require('./db/model_user');
const model_task = require('./db/model_task');


//Defines which port we want epress to listen on for the incoming requests.
const port = process.env.PORT || 3000;
//Init our server.
const app = express();
app.use(express.json());

//when a post request is recieved at '/users'
app.post('/users', (req, res)=>{
    const userDoc = new model_user(req.body);
    userDoc.save().then(()=>{
        res.status(201).send(userDoc);
    }).catch((error)=>{
        res.status(400).send(error);
    });
});

//Send the user infromation when get request is send : 
app.get('/users', (req, res)=>{
    model_user.find({}).then((users)=>{
        res.send(users);
    }).catch((error)=>{
        res.status(400).send(error);
    });
});

//Send specific user as specified in the url : 
app.get('/users/:id', (req, res)=>{
   const _id = req.params.id;
    model_user.findById(_id).then((user)=>{
        res.send(user);
    }).catch((error)=>{
        res.status(404).send(error);
    });
});

//When a post request is made to /tasks : 
app.post('/tasks', (req, res)=> { 
    const taskDoc = new model_task(req.body);
    taskDoc.save().then(()=>{
        res.status(201).send(taskDoc);
    }).catch((error)=>{
        res.status(400).send(error);
    });
});

//Get Tasks : 
app.get('/tasks', (req, res)=>{
    model_task.find({}).then((tasks)=>{
        res.send(tasks);
    }).catch((error)=>{
        res.status(500).send(error);
    });
});

app.get('/tasks/:id', (req, res)=>{
    console.log("This runs");
    const _id = req.params.id;
    model_task.findById(_id).then((task)=>{
        if(task) res.send(task);
        res.status(404).send(_id +' : Not found')
    }).catch((error)=>{
        res.status(500).send(error);
    });
});

//Make our express server listen on the specified port
app.listen(port, ()=>{
    console.log('Server has started, listening at port : ' + port);
});

