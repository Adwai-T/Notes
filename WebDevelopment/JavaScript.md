# JavaScript

## JavaScript Objects

```javascript
//There are two basic ways to create an empty object:
var obj = new Object();

//Object literal syntax can be used to initialize an object in its entirety:
var obj = {
  name: "Carrot",
  for: "Max", // 'for' is a reserved word, use '_for' instead.
  details: {
    color: "orange",
    size: 12,
  },
};

//Attribute access can be chained together:
obj.details.color; // orange
obj["details"]["size"]; // 12

//Creates an object prototype(Person) and an instance of that prototype(you)
function Person(name, age) {
  this.name = name;
  this.age = age;
}

// Define an object
var you = new Person("You", 24);
// We are creating a new person named "You" aged 24.

//Once Create and object can be access in simlar way as shown above
var name = obj.name;
var name = obj["name"];
obj["name"] = "Simon";
```

## Array

```javascript
//Method 1 :
var a = new Array();
a[0] = "dog";
a[1] = "cat";
a[2] = "hen";
a.length; // 3

//Method 2 :
var a = ["dog", "cat", "hen"];
a[100] = "fox";
a.length; // 101

//Query non existing array item will return undefined
typeof a[90]; // undefined

//Iterate over an array
for (const currentValue of a) {
  // Do something with currentValue
}
```

### Array Operations

| Array Method                                         | Description                                                                       |
| :--------------------------------------------------- | :-------------------------------------------------------------------------------- |
| `a.toString()`                                       | Returns a string with the toString() of each element separated by commas.         |
| `a.toLocaleString()`                                 | Returns a string with the toLocaleString() of each element separated by commas.   |
| `a.concat(item1[, item2[, ...[, itemN]]])`           | Returns a new array with the items added on to it.                                |
| `a.join(sep)`                                        | Converts the array to a string — with values delimited by the sep param           |
| `a.pop()`                                            | Removes and returns the last item.                                                |
| `a.push(item1, ..., itemN)`                          | Appends items to the end of the array.                                            |
| `a.shift()`                                          | Removes and returns the first item.                                               |
| `a.unshift(item1[, item2[, ...[, itemN]]])`          | Prepends items to the start of the array.                                         |
| `a.slice(start[, end])`                              | Returns a sub-array.                                                              |
| `a.sort([cmpfn])`                                    | Takes an optional comparison function.                                            |
| `a.splice(start, delcount[, item1[, ...[, itemN]]])` | Lets you modify an array by deleting a section replacing it with more items. a`nd |
| `a.reverse()`                                        | Reverses the array.                                                               |

### Array Functions

```js
//Reduce allows to go through the array and returns an accumlated value from the whole operation
const arr = [1, 2, 5, 8, 2, 3];
const total = arr.reduce((acc, num) => {
  return acc + num;
});
//acc represents the accumalated value

//map
const squares = arr.map((num) => num * num);
//It will return a new array of the squares of the array elements.

//filter - also returns a new array
const greaterThan3 = arr.filter((num) => num > 3);
```

### Difference between For...in and For...of

**For...of** is used to iterate over enumerable string properties of an object.

**For...in** is used to iterate over sequence of values sourced from an iterable object such as an array, set, string etc.

```javascript
const arr = [1, 2, 3, 4];

for (let element of arr) {
  console.log(element);
}

const obj = {
  a: 1,
  b: 2,
  c: 3,
  d: 4,
};

for (let property in obj) {
  console.log(property + " : " + obj[property]);
}
```

## Spread Operator

- Converts String into Array.
- Combine array or add value to array.
- Combine object or add values to object.
- Create shallow copu of array and objects.
- As function parameter to get any number of arguments as an array.

Shallow copies break reference and both the arrays behave independently.

But say there are object inside of the array, they will still refer to the same object in memory. The arrays act as different array, but the object inside still have the same reference in memory and will change when one of the reference is changed.

```javascript
//String to array of characters
let alphabates = 'abcdefghi';
let aphabatesArr = [...alphabates];

let arr1 = ['ad', 'wa'];
let arr2 = ['it'];
let arr3 = [...arr1, ...arr2];
//All elements of both array will be added, even if there are duplicates

let obj1 = {name = 'adwait', lastInit = 's', favSubject = 'Science'};
let obj2 = {name = 'sakshi', lastInit= 's', age=10 };
let obj3 = {...obj1, ...obj2};
//resulting object will have name=sakshi, lastInit='s' favSubject and
//age fields that are unique and conflicting fields will be resolved by
//giving right side last object preference.

let arr = [{name = 'sakshi'}, {name="adwait"}, {name="vikas"}];
let arrShallowCopy = [...arr];
let arrShallowCopy.push[{name: 'sandi'}];
arr[0].name='Anu';
//The first object name for both arrays will change,
//but object with name=sandi will only be added to 
//ShallowCopy array.
```

> There is a hack to make a deep copy of an array or object, use `JSON.parse(JSON.stringify(arrObj))`.

## Destructuring

Arrays or objects can be distributed into multiple variables.

```javascript
let arr = ['adwait', 'vikas', 'sandi'];
let [name1, name2, name3] = arr;
console.log(name1); console.log(name2);

let obj = {
  subject='Science',
  special='Biology'
}
let {subject, special} = obj;
//It is important that the name of the variable defined is same
//as the name of the key in the object.
```

## String Interpolation

Use backtick and `${ }`.

Any type of variable can be interpolated.

```javascript
let name = 'Adwait';
let friend = 'Vikas';

console.log(`${name} is firends with ${firend}.`)
```

## Import, Export and Modules

Use `export` keyword to export variables, objects, functions or classes from a javasript file.

`default export` is used to export only one a single variable, function, object or class.

Use `import` to import exported vairables, objects, functions or classes from other javascript files.

`import {canvas, draw} from './canvas.js` - to import multiples.
`import * as canvas from './canvas.js` - to import all.
`import helper from './helper.js'` - to import default

To use import and export keywords in a javascript file, it should be declared as module in the html.

`<script type="module" src= "./index.js"></script>`

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
  if (elm.nodeType == 3) {
    // TEXT_NODE
    return elm.nodeValue.length;
  }
  var count = 0;
  for (var i = 0, child; (child = elm.childNodes[i]); i++) {
    count += countChars(child);
  }
  return count;
}

//Recursion with IIFEs : (Immediately Invoked Function Expressions)
var charsInBody = (function counter(elm) {
  if (elm.nodeType == 3) {
    // TEXT_NODE
    return elm.nodeValue.length;
  }
  var count = 0;
  for (var i = 0, child; (child = elm.childNodes[i]); i++) {
    count += counter(child);
  }
  return count;
})(document.body);
```

```javascript
//Ternary Operator with multiple conditions
function findGreaterOrEqual(a, b) {
  return a === b
    ? "a and b are equal"
    : a > b
    ? "a is greater"
    : "b is greater";
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
console.log(blueBird.constructor === Bird); //prints true

//---Iterate Over all properties of an Object instance created.
for (let property in duck) {
  if (duck.hasOwnProperty(property)) {
    //hasOwnProperty
    ownProps.push(property);
  } else {
    prototypeProps.push(property);
  }
}

//--- Using Prototype to reduce duplication
//Prototype properties of a constructor function work similar to static in other programming languages.
//All instances share the same value.
Bird.prototype.numLegs = 2; //Variable
Bird.prototype.eat = function () {
  //Function
  console.log("nom nom nom");
};

//Prototype of a constructor function can be direclty be set to a object
//These are easy to manage.
Bird.prototype = {
  constructor: Bird, // define the constructor property
  numLegs: 2,
  eat: function () {
    console.log("nom nom nom");
  },
  describe: function () {
    console.log("My name is " + this.name);
  },
};

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
let flyMixin = function (obj) {
  obj.fly = function () {
    console.log("Flying, wooosh!");
  };
};

flyMixin(bird);
flyMixin(plane);

bird.fly(); // prints "Flying, wooosh!"
plane.fly(); // prints "Flying, wooosh!"

//---Closures to make varible private
function Bird() {
  let hatchedEgg = 10; // private variable

  /* publicly available method that a bird object can use */
  this.getHatchedEggCount = function () {
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
function readTextFile(file) {
  var rawFile = new XMLHttpRequest();
  rawFile.open("GET", file, false);
  rawFile.onreadystatechange = function () {
    if (rawFile.readyState === 4) {
      if (rawFile.status === 200 || rawFile.status == 0) {
        var allText = rawFile.responseText;
        console.log(allText); //- logs text
      }
    }
  };
  rawFile.send(null);
}

readTextFile("path.txt");

//--- With fetch
function readTextFile(file) {
  fetch(file)
    .then((response) => response.text()) //-- Details of response are described below
    .then((text) => console.log(text)); //- logs text
}
```

### [Response](https://developer.mozilla.org/en-US/docs/Web/API/Response)

Response has many **properties**, the important and often used are `Response.body` - is a `ReadableStream`, `Response.headers` - `Headers` object, `Response.ok` - Status of response whether it was sucessful (200-299), `Response.status` - gives response status code.

Response also has **methods** that help us process it. The response can be converted into arrayBuffers, blob, json, text etc. We use them as `Response.text()` or `Response.json()` to process the value and covert it to the desired from. These methods all return a **promise**.

```js
//--- Fetch Image
const image = document.querySelector(".my-image");
fetch("flowers.jpg")
  .then((response) => response.blob())
  .then((blob) => {
    const objectURL = URL.createObjectURL(blob);
    image.src = objectURL;
  });
```

## Working With HTMLElements

### DOM Document

Dom Document provides a variety of methods that help manipulate the docuement and elements contained in it.

### QuerySelector

`document.querySelector(selector)` and `document.querySelectorAll(selector)` can be used to return the first matching element and and array of all matching elements respectively.

The `selector` argument passed in the javascript is the same as the CSS selector that would be used for the element.

There are other methods that could also be used.

- `document.getElementById("id-value");`
- `document.getElementsByTagName("div");`
- `document.getElementsByClassName("class-name");`

### Add and Delete Elements

- `document.createElement(element)` - create a new element of type element, like div, p, etc.
- `document.appendChild(element)` - append the given child element to the document. The method `appendChild(element)` can be used with other elements as well to append children to those elements.
- `docuement.removeChild(element)` - Remove the given child from document. This method can also be used with other elements to remove their children.
- `document.replaceChild(new, old)` - Replace elements.

### Change element Attributes

- `element.innerHTML = 'content'`
- `element.attribute = 'value'`
- `element.style.property = 'css style'`
- `element.setAttribute('attribute-name', 'value')`

> [A complete List of all methods of document can be found on this mdn page](https://developer.mozilla.org/en-US/docs/Web/API/Document).

### Events

#### Predefined Events

`element.addEventListener(event)` is used to add predefined events to elements.

`element.removeEventListener(event)` is used to remove events from an element.

Functions can also be invoked from markup by using attributes.

`<div onclick="functionName()">Click Me</div>`

#### Event Propogation

Events propogate from child to parent.

```javascript
<div onclick="alert('Grand Parent')">Grand Parent
  <div onclick="alert('Parent')">Parent
    <div onclick="alert('child')">Child</div>
  </div>
</div>
```

Consider the above example, when clicked on child, the first alert would be child, then parent and then grand parent.

If parent is called, the first parent will be called and the grand parent will be called. In this case child will not be called and so on.

#### Event()

The `Event()` constructor creates a new Event object. Unlike the events fired by the browser, these can be fired/dispatched from a script.

These events are also called as Synthetic event.

`new Event(type)`
`new Event(type, options)`

- type - A string name of the event.
- options - Object with properites like `bubbles`, `cancelable`, `composed`

`const event = new Event('find', {"bubbles" = false})`

Once a event is defined it can be dispatched from any element by using `element.dispatchEvent(event)`

#### Custom Event

Custom event that other elements can listen to can also be created.

To create a new custom event use `new CustomEvent(type)` or `new CustomEvent(type, options)`.

- `type` - A string name for the event.
- `options` - other than all the options in `Event()` it also has `detail` which itself can be an object.

```javascript
//This method is invoked by some element or function.
function customEvent() {
  let custEvent = new CustomEvent("find", {
    detail: {
      name: 'adwait'
    }
  });
}

//Add a event listener of the above custom event
element.addEventListener('find', (e)=> {
  e.detail.name;
});

//Now in other function this event is fired
//The above element will get the value
element2.dispatchEvent(custEvent)
```

#### Difference between Event and Custom Event

The detail property of a custom event cannot be changed once set, where as for a event the detail option for these events can be changed later or set and then changed later.

In strict mode when value for custom event is changed later, it will throw an error.

```javascript
let event = new CustomEvent('find', {detail: 'adwait'});
event.detail = 'sakshi'; //throws error in strict mode.
//also the value will remain adwait


let event2 = new Event('find');
event.detail = 'adwait';
event.detail = 'sakshi';//will not throw error and value is changed
```

### Get position of an HTMLElement

```javascript
const el = document.getElementById("element-id");
const rect = el.getBoundingClientRect();
//we can then access the values for the rect
console.log(rect);
console.log(rect.bottom, rect.top, rect.left, rect.right);
```

### Communication with iframe

> Important the `postMessage` and `onMessage` are methods of the `Window` that means that they can be used with any window. Check the pages for details { [mozilla](https://developer.mozilla.org/en-US/docs/Web/API/Window/postMessage), [javascript.info](https://javascript.info/cross-window-communication) }

I-frames are used to display a different page in our website, we can communicate with the javascript in the i-frames page.

**Parent -> Iframe** communication:

We use the `postMessage(message, targetOrigin, transfer)` or `postMessage(message, targetOrigin)` property of the `iframe.contentWindow`.

- message : can be string, object, or arrays. There are more that are [supported](https://developer.mozilla.org/en-US/docs/Web/API/Web_Workers_API/Structured_clone_algorithm).

- targetOrigin : `"*"` can be used for any origin, or a URL can be set specifically, if the target is not matched the event will not be dipatched.

> Always provide a specific targetOrigin, not `*`, if you know where the other window's document should be located. Failing to provide a specific target discloses the data you send to any interested malicious site.

Ex. `postMessage("message", "http://example.com");` will only be sent if `<iframe src="http://example.com">`

- target : (Optional) Is a sequence of transferable objects that are transferred with the message.

Get message in the iframe:

We can use the `onmessage` method to get the meesage sent.

The `event` object has special properties:

`data` : The data from `postMessage`.

`origin` : The origin of the sender.

`source` : The reference to the sender window. We can immediately `source.postMessage(...)` back if we want.

```javascript
// --- parent -> iframe

//i-frame.contentWindow.postMessage(message, targetOrigin, [transfer]);
i - frame.contentWindow.postMessage("message", "*");

//in iframe
window.onmessage = function (e) {
  console.log(e);
  console.log(e.data); //message
};
```
