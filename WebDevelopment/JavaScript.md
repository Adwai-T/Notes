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
