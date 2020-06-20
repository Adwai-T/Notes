:) JavaScript Notes From freecode camp :)
===

### ES6 : 
ECMA script is standardized version of javascript. It was formed with the goal of unifying the language specification and features and how it is implemented in all the browsers.

## Escape Sequences in Strings : 
    
|Code	|Output|
|------|:------|
|\'	|single quote|
|\"	|double quote|
|\\	|backslash|
|\n	|newline|
|\r	|carriage return|
|\t	|tab|
|\b	|word boundary|
|\f|	form feed|

### String :
String in javascript are immutable. That is once created they cannot be altered in the way as shown below. But the variable that stores the String can be reassigned, so concat of Strings will also work.
```javascript
    var name = "Name";
    var nameLenth = name.lenth;
    var firstCharacterOfName = name[0];
    var name[0] = 'J';//cannot be done will give an error
    var name = "Adwait" //Will work. Reassign the variable.
```
All String can be accessed as if they were an array of character.

#### Arrays :
Array have multiple methods in java 
1. `pop()` : removes value at the end of the array and return it.
2. `push(value)` : Adds the value at the end of the array.
3. `shift()` : Removes the first element from the array and return it.
4. `unshift(value)` : Adds the given value to the start of the array.
5. `foreach((value)=>{})` : Loops through each value in the array.
6. `find(function)` : Returns the element from the array that returns true for the function.
7. `reduce(function)` : 
8. `filter(function)` : 
9. `map(function)` :

### Objects : 

1. `delete objectName.key` : can be used to delete value from the javascript objects.
2. `hasOwnProperty(propertyName)` : gives if the object has a key with the name.

### Parse values :
`parseInt(String, radius)` can be used where radius can have values like 2, 10, 16 representing the system(binary, decimal, hex respectively).

### Ternary Operators :
Ternary operator with multiple conditions.
```javascript
function findGreaterOrEqual(a, b){
    return (a===b)?"a and b are equal" : (a>b)?"a is greater than b":"b is greater than a";
}
```

### Recursion : 
Function calling itself inside of its declaration is recursion. Recursion makes much more sence when we know about call stack.
```javascript
function count(a,b){
    if(b<a) return [];
    else{
        let arrayCount = count(n-1);//The statement will keep looping till b<a and then return a blank array. 
        arrayCount.push(n);
        return arrayCount;
    }
}
```

### Arrow function and Regular functions :
1. Unlike regular functions the arrow functions do not have their own `this`.
```javascript
let user ={
    name = "Adwait",
    arrowFunction : ()=>{
        console.log("Hello " + this.name);//this.name will print undefined
    },
    regularFunction(){
        console.log("Hello to " + this.name);//This will print this.name as Adwait
    }
}
```
2. Argument object are not available in arrow function as they are available in the regular funtions.
```javascript
let user = {
    arrowFunction: ()=>{
        console.log("Arrow Function : " + arguments); //will not print any arguments values
    },
    regularFunction(){
        console.log("RegularFunction : " + arguments);
    }
}
user.arrowFunction(1, 2, 3);
user.regularFunction(1, 2, 3);//Prints the value of 1 2 3 to screen.
```

3. Regular functions are constructible that is they can be instanciated with `new` keyword.

4. Finally to conclude regular functions should moslty be used for methods and arrow functions for all other cases like use with callback methods.

### Rest Parameters:
when we have to create a function with varible number of arguments we use the Rest paramenter that return an array of all the arguments that were passed.
```javascript
function restParameter(...args){
    sum = args.map((a, sum) => {
        sum += a;
    })
}
```

### Spread Operator : 
It is used to spread an array into individual parameters to a function.
```javascript
let arr =[1, 35, 25, 50, 2, 10];
let maximum = Math.max.apply(null, arr);//regular without spread operator.
let maxiMum = Math.max(...arr);

let spreadArr = ...arr; //this will throw a error.
```




