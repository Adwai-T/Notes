NodeJs
===

### Nodejs is an even driven non blocking I/O model that makes it Lightweight and efficient.

### It is important to note that nodejs currently does not support everything from ES6. A good example of it is import. We still have to use the require in nodejs.

### Nodejs documentation can be found at https://nodejs.org/dist/latest-v12.x/docs/api/

### All the code that is covered in the course can be found at: https://link.mead.io/nodecourse.

### Importing Modules : 

#### Importing Core Modules - 
```javascript
const fs = require('fs') //fs is a core module of node.

fs.writeFileSync('notes.txt', 'This file was created in nodejs.');
```
#### Import our own file - 
>test.js
```javascript
//Whenever require is used to call a file the file being called will be execute.
const name = require('./utils') 
console.log(name);
```
>utils.js
```javascript
console.log('Hello in utils.js');//Will be printed at require

const name = 'Adwait';

module.exports = name; //functions and variables should be exported later than they are created as they are not assigned until the assignement is already executed when the module is called.
```
All the files and modules have their own scope.

#### Import modules from npm -
Firstly we have to configure npm for our project, so that it can manage dependencies for our project and download necessary modules that we
might want to use. That is done by calling
>npm -init

in our project root directory. This will create a package.json file that has a lot of info about the porject in the from of a .json file.When we install a package when there is a package file created it will have added the module name to the package.json dependencies.

We can assign the module to variable in our module as :
```javascript 
const validate = require('validate') //with the package name of npm package itself.
```
When we have the package.json file with the dependecies, it can be helpful to install all the npm dependencies by using :
>npm install

And this will install all the dependencies that are in the package.json in our project root -> node_modules folder. It is necessay to note that we should be in the project root folder where the package.json file is placed to run the command. It should also be noted that all the `npm i` commands that are run from the project root folder for the package.json to be modified to have the module in dependencies updated.

`npm i chalk` is a module that is used control how the output is shown in the console.

#### Installing packages globally can be done by adding  a '-g' flag at the end of the istall like so : 
>npm install nodemon -g

`nodemon` is a utility package that can be used to run our script as soon as we save our file. 

#### Commandline arguments :
The arguments that are passed when the progam is run is stored in process.argv array and can be used as such: 
>console.log(process.argv);

>node ourApp.js Adwait

When Run it will give us an array as such :  
```js
[
  'C:\\Program Files\\nodejs\\node.exe',
  'C:\\Users\\Adwait\\Documents\\NpmFiles\\Node Course\\NodeClass\\NotesApp_3_1.js',
  'Adwait'
]
```

#### Parse tool for parsing commandline arguments : 
>npm i yargs

### JSON data in node:
`JSON.stringify(javascript object)` will be used to convert a node or javascript object to a Json object as a string.

`JSON.parse(JSONstring)` will return a javascript object from a JSON object string value.

### Handlebars. 

#### Customize the name and location of the views directory : 
```javascript
//absolute directory path of the views.
const viewsPath = path.join(__dirname,'../templates');
//setting the views folder to the path
app.set('views', viewPath);
```
#### Partial template to use in another pages.
```html
{{>nameOfPartialFile}}
```

### when using nodemon to run nodemon when any file in the project sepcified is changed :
`nodemon src/app.js -e js,hbs`
e => extensions

## Git and Heroku check List

#### `git init` : This will init git for us.
#### `git status` : Print status of files and how they are being monitered.
#### `.gitignore` : File constains names of file that we want git to ignore. It should be placed in the project root directory.
#### `git add folderOrfileName` : Add the file or folder to the staging area.
#### `git add .` : Adds all the files with the untracked status to the staging.
#### `git commit -m "Init commit" `: The first commit gets the message of "Init Commit" with the `-m` flag for message.

#### after we have created a coommit awe have tp make a new Repository in  our git account. WE can do that by using : 
`git remote add origin https://github.com/Adwai-T/SteamBot.git`

#### `$ ls -a -l ~/.ssh` : Check if you already have a ssh key folder or ssh initialized on your machaine. If any folder comes that means we have ssh on the machine.

#### `ssh-keygen -t rsa -b -4096 -C "waitforadi@gmail.com"` : Create a rsa ssh key for the encoding of the files being send to the git.
`-t` Type of encoding,
`-b` Bit encoding value,
`-C` Encoding message,

#### `eval $(ssh-agent -s)` : for windows
#### `eval "$(ssh-agent -s)"` : For linux and mac
The above commnad will get the ssh agent running. `-s` to start the agent. The result line is `eval Agent pid 1689`.

#### ` ssh-add ~/.ssh/id_rsa` 
Add the rsa file created previously to our agent.

### Setting up github to host our project : 
1. Login to github and create a new repository.
2. Copy the url from Push box. eg. git remote add origin git@github.com:Adwai-T/Node3-Weather-Server.git
3. Use it in the terminal form the project folder.
4. On github site go to settings > SSH and GPG keys tab > New SSH key > Give a title >
5. Get the content of the id_rsa.pub and copy them to the box below title.
6. To get the content use git bash and use `cat ~/.ssh/id_rsa.pub`.
7. Now we have added the ssh key to the github and we have our key in the PC.
8. Now in bash to check that we are connect and to for the first time to add the github server to the list of authenticated servers to our PC we use ` ssh -T git@github.com`.
9. This will give have some message with our user name on github and that we have successfully authenticated with github server.
10. This only needs to be done once and will work for all the future porjects that will use the same github account with the rsa key added to the account.

#### Now that we have the connection set up with github we can push out commit to the github repo by `git push -u origin master`.

### Deploying code to heroku : 
1. Add our previously created ssh key to the heroku. In terminal :  `heroku keys:add`.
2. Create a project/App on heroku : `heroku create uniqueProjectAppName` : Name should be unique amongst all the heroku apps globally.
3. In the `package.json` file under script key, add a key named `start` to define what heroku need to run in order to start the project correctly like so : `node src\index.js`.
4. we have set up a static port that we run the app locally at. Heroku provides a dynamic value for the port and we can get the value of the port that is set in the enviroment variables of the server created on heroku by using `process.env.PORT` and we can make it local safe by providing a fallback by using logical OR operater like so : `process.env.PORt || 3000`.
5. Change the code where ever required so that no address is set with localhost in the address.
6. Create a commit.
7. Use `git push` to push our code to github.
8. Use `git remote` to see all the remotes and we can see the one that we set up and the one that heroku set up for us.
9. Use `git push heroku master` to push our latest commit to heroku.

### Commit changes to the github and heroku : 
1. `git status`
2. `git commit -m "Change Description`
3. `git push` :  is equivalent to : `git push master` :  which pushes the changes to github.
4. `git push heroku master` : Push out changes to the heroku github repo.
5. The app is now ready with all changes made.

### Adding dev dependences 
So that no package need to be installed publically : `npm install nodemon --save-dev`. 
