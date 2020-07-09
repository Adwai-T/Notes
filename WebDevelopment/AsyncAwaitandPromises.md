# Asycnhronous Programming

## Callbacks

```js
//Example without async programming
const posts = [
    {title: 'Post One', body: 'This is post one' },
    {title: 'Post Two', body: 'This is post two' }
];

function getPosts(){
    //As fetching from server might time we use setTimeout to imulate that time delay.
    setTimeout(()=>{
        posts.forEach((post, index)=>{
            output += `<li>${post.title}</li>`;
        });
        //We output it ot the DOM
        document.body.innerHTML = output;
    }, 1000)
}

function createPost(post){
    setTimeout(()=>{
        posts.push(post);
    }, 2000);
}

getPosts();

createPost({title: 'Post Three', body: 'This is post three' });
```

In the above example DOM will be painted as soon as getPosts is done as we have a method that changes the DOM in the getPosts method.

By that time our createPost method will not have completed as it takes 2 sec. Thus the thrid post will not be displayed on the DOM.

Aysnchronous programming can help us with this problem.

* In the below code that is the modification of the above code we will use **Callback Functions** to achive asychronous programming.

```js
const posts = [
    {title: 'Post One', body: 'This is post one' },
    {title: 'Post Two', body: 'This is post two' }
];

function getPosts(){

    setTimeout(()=>{
        posts.forEach((post, index)=>{
            output += `<li>${post.title}</li>`;
        });

        document.body.innerHTML = output;
    }, 1000)
}

function createPost(post, callback){
    setTimeout(()=>{
        posts.push(post);
        callback();
    }, 2000);
}

createPost({title: 'Post Three', body: 'This is post three' }, getPosts);
```

## Promises

We will use the same above example to see the use of Promises.

```js
const posts = [
    {title: 'Post One', body: 'This is post one' },
    {title: 'Post Two', body: 'This is post two' }
];

function getPosts(){

    setTimeout(()=>{
        posts.forEach((post, index)=>{
            output += `<li>${post.title}</li>`;
        });

        document.body.innerHTML = output;
    }, 1000);
}

function createPost(post){

    return new Promise((resolve, reject) => {
        setTimeout(()=>{
            posts.push(post);

            const error = false;

            //Before we resolve or reject our promise we need to check whether there was any error while we ran our code.
            if(!error){
                resolve();
            }else{
                reject('There was Some error');
            }
        }, 2000);
    });
}

createPost({title: 'Post Three', body: 'This is post three' })
    .then(getPosts) //Function to execute when the poromise is resolved is passed as argument
    .catch(err => console.log(err)); //Function to execute when the pomise is reject is passed with catch.
}

//There can be any number of 'then' statements attached to each other to resove any number of promises that there are. But we will only have one catch to catch the error.

//But there are times where we do not want to use .then many time. In those cases when we want our promises one by one we can do Promise.all and then use one .then and .catch act on the data that is returned by all the promises and catch any error that might occur while resolving any of the promises.

//If there is an error while having multiple promises, the later promises are skipped and directly catch block is executed.

const promise1 = Promise.resolve('Hello World');
const promise2 = 10;
const promise3 = new Promise((resolve, reject)=>{
    setTimeout(resolve, 2000, 'Goodbye')
});

//fetch works differently as it returns two promises. The first promise gives us the raw resoponse data, which we can convert to json in the first promise and the second promise gives us the processed data(In this case we get a json response and we convert the data to json object).
const promise4 = fetch('https://jsonplaceholder.typicode.com/users').then(res => res.json());

Promise.all([promise1, promise2, promise3, promise4]).then(value=>{
    console.log(values);
})
```

## Async Await

We extend on the above code and dont change it.

The Promise.all code has no effect on this code. We are only concerned with the code above it.

```js
async function init(){

    await createPost({ title: 'Post Three', body: 'this is body of post three' });

    getPosts();
}

init();
```

* We could also use it with fetch that is build in functions that return promises.

```js
async function fetchUsers(){
    const res = await fetch('http://jsonplaceholder.typicode.com/users');

    const data = await res.json();

    console.log(data);
}

fetchUsers();
```

> Note : Promises are different that rxjs Observables in the sence that they are eager function that is they will fetch data as soon as possible, on the other hand Observables only fetch data when they are subscribed to.
This becomes important when using frameworks like Angular.
