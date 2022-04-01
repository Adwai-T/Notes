# Testing

## Basic types of test

### Unit Tests

Are used to test pure functions. They arent used to test *Contracts*, that is connection between function, classes or components.

### Integration Tests

In this test the different parts of software, may it be classes, functions, components, modules etc are put together and tested as a group.

They are expensive to run and also are complicated to write.

First start with Unit test and then write integration test as needed.

### Automation Test or End to End Test

They are used to check interation of user with the software. They test things that the website completely put together works as intended.

These are the hardest to setup and also expensive to run.

Most only large companies do Automation Testing or end to end tests.

## Testing with Jest

React uses [Jest library](https://jestjs.io/) for testing.

[Jest Cheat Sheet](https://github.com/sapegin/jest-cheat-sheet)

To install jest `npm install --save-dev jest`, we add it as dev dependency as it is not need in production.

Setting up Jest in npm package.json. We can just have `"test" : "jest"` but it will have to be run over and over again. Rather we could run it once and jest will observe any changes made to js files and will run test automatically. This will give us continues test result.

```json
{
  "scripts" : {
    "test" : "jest --watch *.js"
  }
}
```

Following is a simple example

```js
const foogleDatabase = [
  'cats.com',
  'adwait.in',
  'dogs.com',
  'catspic.com',
  'dogspic.com'
]

const foogleSearch(search, dbase) {
  const matches = dbase.filter(website => {
    return website.includes(search);
  })
  return matches.length > 3 ? matches.slice(0,3) : matches;
}

foogleSearch('cat', foogleDatabase)
module.exports = foogleSearch;

//---test file
//WE dont want to import the database from the original function, we want create a mock database for the test as importing original will be expensive.

const foogleSearch = require('./script.js')

let mockdb= [
  'dog.com'
  'cat.com;
  'ad.com'
]

//This is test1, it does not have any result
it('this is a test', ()=> {
  expect('hello').toBe('hello')
  foogleSearch('testtest', mockdb);
});

//Another test, we can have as many as we want
it('is searching foogle', ()=>{
  expect(foogleSearch('testtest', mockdb)).toEqual([]);
  expect(foogleSearch('dog', mockdb)).toEqual(['dog.com'])
});
//In the above test as we have create the mockdb we know what the values of the db are and we want to equal it to the values that we expect from the funciton.

//for undefined or null input
it('work with undefined or null input', ()=>{
  expect(foogleSearch(undefined, mockdb)).toEqual([]);
  expect(foogleSearch(null, mockdb)).toEqual([]);
});
```

The more test we have the more area of the software. As the test do not effect the production build, we can have them as many as we want.

Note that just because all test pass, does not mean that the function will alway run as intentended as there might be cases that we have not written test for.

For example in the above test we did not check if the result always has less than 4 values in returned array.

### Testing Async Function

Note we will use `node-fetch` for requests, it gives functionality just like browsers fetch function.

```js
//--swapi.js function file
const fetch = require('node-fetch');

//-We pass the fetch function provided by node as parameter.
//Function using async-await
const getPeople =  async (fetch) => {
  const request =  await fetch('requestUrl/response.json');
  const data = await request.json();
  console.log(data);
  return {
    count: data.count,
    results: data.results
  }
}

//Same function using promise
const getPeoplePromise = fetch => {
  return fetch('requestUrl/response.json')
    .then(response => reponse.json())
    .then(data => return {
      count: data.count,
      results: data.results,
    });
}

module.exports = {
  getPeople, //same as getPeople:getPeople according to ES6
  getPeoplePromise
}

//--- One important thing to check is that our test acutally testing what we want it to check. We can do that is by making the test fail. Some times the test might complete before it checks all parameters, this mostly happens with async code.

//--test.spec.js
const fetch = require('node-fetch');
const swapi = require('./script2');

//For a aync function the test might complete without before it gets value and still pass
//Thus we can use done, that gets automatically passed to test function. The test will only end when the done() function is called. We usually put done after an expect call.
it('calls swapi to get people', (done)=>{
  expect.assertions(1) //assertions takes in a value representing number of expect that should run in this test. In this case only one. 
  swapi.getPeople(fetch).then(data => {
    expect(data.count).toEqual(87)
    done();
  })
});

//Another method without using done, we can return.
it('calls swapi to get people', ()=>{
  expect.assertions(2)//-- here we check for 2 assertions and below we have 2 assertions
  //here we return the promise, this prevents the test from returning before the value of the promise is returned.
  return swapi.getPeople(fetch).then(data => {
    expect(data.count).toEqual(87)//87 is arbitory, we need to put the number of data points
    expect(data.results.length).toBeGreaterThan(5);
  })
});
```

When doing syncronous tests always use `expect.assertions` to check all that all the expect are run.

While testing async function use one of above 2 methods.

### Mocks and Spies

We don't always have asyn fcuntions dependent on server to run when we are testing. The functions that are dependent on server for response take time and might also need the function to fetch a lot of data.

To avoid this we can create a mock function that gives a response similar to the server.

For example in the above tests we have used `fetch` function of the node and swapi servers for response, we know that fetch and swapi both work as intended and do not need to be tested, thus we create mock function that will behave like fetch and return data similar to the swapi api.

```js
//--script.js function to be tested
const fetch = require('node-fetch');

//We pass fetch as a dependency or paramter to our getPeople function, this will help us to inject or pass our mock function as a parameter to the function while testing as done below.
const getPeople =  async (fetch) => {
  const request =  await fetch('requestUrl/response.json');
  const data = await request.json();
  console.log(data);
  return {
    count: data.count,
    results: data.results
  }
}

module.exports = {
  getPeople,
}

//--test.spec.js
const fetch = require('node-fetch');
const swapi = require('./script');

//Previous Test code using fetch function
it('calls swapi to get people', (done)=>{
  expect.assertions(2) 
  swapi.getPeople(fetch).then(data => {
    expect(data.count).toEqual(87)
    expect(data.results.length).toBeGreaterThan(5);
    done();
  })
});

//-Mock function
it('getPeople return count and results', ()=>{

  //jest.fn() creates the mock function
  const mockFetch = jest.fn().mockReturnValue(
    //the return value of fetch is a promise which resolves to json which is itself a promise.
    Promise.resolve({ 
      json: () => Promise.resolve({
        count:87,
        result: [0,1,2,3,4,5,6]
      })
    })

    expect.assertions(4);
    //As the mock function returns a promise making it async, we use the return, to make sure that all the test are completed. We also use expect.assertions
    //We pass the mock function to the functiont that we are testing.
    return swapi.getPeople(mockFetch).then(data=>{
      //The jest.fn() lets us spy on it and check what it does inside of the function being tested. We use this to test how many times the mock function was called.
      expect(mockFetch.mock.calls.length).tobe(1);
      expect(mockFetch).toBeCalledWith('https://swapi.co/api/people');
      expect(data.count).toEqual(87);
      expect(data.results.length).toBeGreaterThan(5);
    })
  )
});
```
