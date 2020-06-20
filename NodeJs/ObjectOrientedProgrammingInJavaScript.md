## Object oriented Programming : 

1. `child instanceof parent` :
```javascript
let Bird = function(name, color) {
  this.name = name;
  this.color = color;
  this.numLegs = 2;
}

let crow = new Bird("Alexis", "black");

crow instanceof Bird; // => true
```

2. `child.hasOwnProperty(propertyName)` => returns True or false.
```javascript
let ownProps = [];

for (let property in duck) {
  if(duck.hasOwnProperty(property)) {
    ownProps.push(property);
  }
}
```
3. Properties in the `prototype` are shared among ALL instances of Bird.
```javascript
Bird.prototype.numLegs = 2; 
```
4. Adding prototypes more efficiently by setting it to an object : 
```javascript
Bird.prototype = {
  numLegs: 2, 
  eat: function() {
    console.log("nom nom nom");
  },
  describe: function() {
    console.log("My name is " + this.name);
  }
};
```
5. Check who shares prototype from a constructor function : 
`Bird.prototype.isPrototypeOf(duck);`

6. Every constructor function that we create inherits its prototype form the javascript Object :
`Object.prototype.isPrototypeOf(Bird.prototype);`

7. There is another way of creating an object from a prototype object that is better than using `new` :
`let animal = Object.create(Animal.prototype);`

### Difference between New and Object.create :
```javascript 
function Dog(){
    this.pupper = 'Pupper';
};

Dog.prototype.pupperino = 'Pups.';
var maddie = new Dog();
var buddy = Object.create(Dog.prototype);

//Using Object.create()
console.log(buddy.pupper); //Output is undefined
console.log(buddy.pupperino); //Output is Pups.

//Using New Keyword
console.log(maddie.pupper); //Output is Pupper
console.log(maddie.pupperino); //Output is Pups.
```

The key thing to note in this example is:
`console.log(buddy.pupper); //Output is undefined`
Notice the output of buddy.pupper is undefined. Even though Object.create() sets its prototype to Dog, buddy does not have access to this.pupper in the constructor. This is due to the important difference that new Dog actually runs constructor code, whereas `Object.create` will not execute the constructor code.

8. When an object inherits its prototype from another object, it also inherits the supertype's constructor property.
```javascript
function Bird() { }
Bird.prototype = Object.create(Animal.prototype);
let duck = new Bird();
duck.constructor // function Animal(){...}

//So the property of the real parent need to be reset: 
Bird.prototype.constructor = Bird;
duck.constructor // function Bird(){...}
```

9. Methods inheritted form the parent can be overwriten.

10. MixinFunctions : When there are two different object that are not the same but have some same porperties we use mixinFunctions : 
```javascript
let bird = {
  name: "Donald",
  numLegs: 2
};

let boat = {
  name: "Warrior",
  type: "race-boat"
};

// Only change code below this line
let glideMixin = function(obj){
  obj.glide = function(){
    console.log("Glide right.")
  }
}

glideMixin(bird);
glideMixin(boat);
```

11. Making variables private outside of the function :
```javascript
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