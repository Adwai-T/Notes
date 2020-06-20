const mongoose = require('mongoose');
const model_tasks = require('../src/db/model_task');//Get the model for the task

//Connect to the mongodb.
mongoose.connect('mongodb://127.0.0.1:27017/task-manager-api', {
    useCreateIndex : true,
    useNewUrlParser : true,
    useUnifiedTopology: true
});

const id = '5eb01697beb3230d98cdb797'
//Following is the example of promise chaining
model_tasks.findByIdAndDelete(id).then((task)=>{//Returns the deleted task as the parameter to our promise
    console.log(task);
    //Return the next async task that needs to be performed after the first is completed.
    return model_tasks.countDocuments({completed : false});
}).then((num)=>{//This then gets the result of the returned async task above.
    console.log(num);
}).catch((error)=>{//This will print error when any of the above async operations fail.
    console.log(error);
});