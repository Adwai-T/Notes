# JavaScript

## JavaScript Objects

```javascript
//There are two basic ways to create an empty object:
var obj = new Object();

//Object literal syntax can be used to initialize an object in its entirety:
var obj = {
  name: 'Carrot',
  for: 'Max', // 'for' is a reserved word, use '_for' instead.
  details: {
    color: 'orange',
    size: 12
  }
};

//Attribute access can be chained together:
obj.details.color; // orange
obj['details']['size']; // 12

//Creates an object prototype(Person) and an instance of that prototype(you)
function Person(name, age) {
  this.name = name;
  this.age = age;
}

// Define an object
var you = new Person('You', 24);
// We are creating a new person named "You" aged 24.

//Once Create and object can be access in simlar way as shown above
var name = obj.name;
var name = obj['name'];
obj['name'] = 'Simon';
```

## Array

```javascript
//Method 1 :
var a = new Array();
a[0] = 'dog';
a[1] = 'cat';
a[2] = 'hen';
a.length; // 3

//Method 2 :
var a = ['dog', 'cat', 'hen'];
a[100] = 'fox';
a.length; // 101


//Query non existing array item will return undefined
typeof a[90]; // undefined

//Iterate over an array
for (const currentValue of a) {
  // Do something with currentValue
}

```

### Array Operations

|Array Method|Description|
|:---|:---|
|`a.toString()` | Returns a string with the toString() of each element separated by commas.|
|`a.toLocaleString()`|Returns a string with the toLocaleString() of each element separated by commas.|
|`a.concat(item1[, item2[, ...[, itemN]]])`|Returns a new array with the items added on to it.|
|`a.join(sep)`|Converts the array to a string — with values delimited by the sep param|
|`a.pop()`|Removes and returns the last item.|
|`a.push(item1, ..., itemN)`|Appends items to the end of the array.|
|`a.shift()`|Removes and returns the first item.|
|`a.unshift(item1[, item2[, ...[, itemN]]])`|Prepends items to the start of the array.|
|`a.slice(start[, end])`|Returns a sub-array.|
|`a.sort([cmpfn])`|Takes an optional comparison function.|
|`a.splice(start, delcount[, item1[, ...[, itemN]]])`|Lets you modify an array by deleting a section a`nd |replacing it with more items.|
|`a.reverse()`|Reverses the array.|

## Functions

```javascript
//The variable `...args` holds all the values that were passed into the function and can be accessed as an array.
function avg(...args) {
  var sum = 0;
  for (let value of args) {
    sum += value;
  }
  return sum / args.length;
}

avg(2, 3, 4, 5); // 3.5

//Recursion In function
function countChars(elm) {
  if (elm.nodeType == 3) { // TEXT_NODE
    return elm.nodeValue.length;
  }
  var count = 0;
  for (var i = 0, child; child = elm.childNodes[i]; i++) {
    count += countChars(child);
  }
  return count;
}

//Recursion with IIFEs : (Immediately Invoked Function Expressions)
var charsInBody = (function counter(elm) {
  if (elm.nodeType == 3) { // TEXT_NODE
    return elm.nodeValue.length;
  }
  var count = 0;
  for (var i = 0, child; child = elm.childNodes[i]; i++) {
    count += counter(child);
  }
  return count;
})(document.body);

```

```javascript
//Ternary Operator with multiple conditions
function findGreaterOrEqual(a, b) {
  return (a === b) ? "a and b are equal" : (a > b) ? "a is greater" : "b is greater";
}
```

## Object Oriented Programming in JavaScript

```javascript
//--- Constructor function
//By convention constructor functions are defined with capital
function Bird(name, color) {
  this.name = name;
  this.color = color;
  this.numLegs = 2;
}
//Create an object from the constructor
let blueBird = new Bird("Albert", "Red");
blueBird.color = "Blue";

//Check to see which function created the given object.
blueBird instanceof Bird; // => true

//Also this can be done by directly checking which is the contructor for the instance
console.log(blueBird.constructor === Bird);  //prints true

//---Iterate Over all properties of an Object instance created.
for (let property in duck) {
  if(duck.hasOwnProperty(property)) { //hasOwnProperty
    ownProps.push(property);
  } else {
    prototypeProps.push(property);
  }
}

//--- Using Prototype to reduce duplication
//Prototype properties of a constructor function work similar to static in other programming languages.
//All instances share the same value.
Bird.prototype.numLegs = 2; //Variable
Bird.prototype.eat = function() { //Function
  console.log("nom nom nom");
}

//Prototype of a constructor function can be direclty be set to a object
//These are easy to manage.
Bird.prototype = {
  constructor: Bird, // define the constructor property
  numLegs: 2,
  eat: function() {
    console.log("nom nom nom");
  },
  describe: function() {
    console.log("My name is " + this.name);
  }
}

//Sequence of inheritance
//Object -> Bird -> blueBird
Bird.prototype.isPrototypeOf(blueBird); //returns true.
Object.prototype.isPrototypeOf(Bird.prototype); // returns true

//Create Objects from Parent
//Animal Object/Constructor function is not shown here. Lets assume Animal.prototype has a eat function
Bird.prototype = Object.create(Animal.prototype);

let duck = new Bird("Donald");
duck.eat(); // prints "nom nom nom"
//duck inherits all of Animal's properties, including the eat method.

//Inheritance properties and functions can be overwritten in the the proptotype of the child object.

//--- Mixins
let flyMixin = function(obj) {
  obj.fly = function() {
    console.log("Flying, wooosh!");
  }
};

flyMixin(bird);
flyMixin(plane);

bird.fly(); // prints "Flying, wooosh!"
plane.fly(); // prints "Flying, wooosh!"

//---Closures to make varible private
function Bird() {
  let hatchedEgg = 10; // private variable

  /* publicly available method that a bird object can use */
  this.getHatchedEggCount = function() { 
    return hatchedEgg;
  };
}
let ducky = new Bird();
ducky.getHatchedEggCount(); // returns 10
```

## Fetch

Fetch function replaces the older XMLHttpRequest request methods and makes it easier.

Following examples shows fetching a raw file data from server with XMLHttpRequest and with fetch.

```js
//--- With XMLHttpRequest
function readTextFile(file)
{
    var rawFile = new XMLHttpRequest();
    rawFile.open("GET", file, false);
    rawFile.onreadystatechange = function ()
    {
        if(rawFile.readyState === 4)
        {
            if(rawFile.status === 200 || rawFile.status == 0)
            {
                var allText = rawFile.responseText;
                console.log(allText);//- logs text
            }
        }
    }
    rawFile.send(null);
}

readTextFile("path.txt");

//--- With fetch
function readTextFile(file) {
  fetch(file)
    .then(response => response.text()) //-- Details of response are described below
    .then(text => console.log(text)) //- logs text
} 

```

### [Response](https://developer.mozilla.org/en-US/docs/Web/API/Response)

Response has many **properties**, the important and often used are `Response.body` - is a `ReadableStream`, `Response.headers` - `Headers` object, `Response.ok` - Status of response whether it was sucessful (200-299), `Response.status` - gives response status code.

Response also has **methods** that help us process it. The response can be converted into arrayBuffers, blob, json, text etc. We use them as `Response.text()` or `Response.json()` to process the value and covert it to the desired from. These methods all return a **promise**.

```js
//--- Fetch Image
const image = document.querySelector('.my-image');
fetch('flowers.jpg')
.then(response => response.blob())
.then(blob => {
  const objectURL = URL.createObjectURL(blob);
  image.src = objectURL;
});
```
