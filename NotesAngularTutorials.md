# Angular :

### Module is a way to split code into independent files that mean something on their own.

Modules are reusable. They simply split code into simpler files.

* index.html file and main.ts is the entry point to the application.

* Bootstrap : Enatilize

* Polyfills.ts : If the browser does not support some javascript code, then this will give the code that will try to mimik that funcationality.

* Component : Make code reusable. A view which can be repeated. @NgModule is the main thing that contains all components are registeded.

* Decorators : provide additional information but does not actually change the class or function itself. 

## Decorators :
It is a function wrapping another function. They make the code easy to maintain.
eg. `@Component` is a decorator provided by angular.

Creating our own decorator : 
1. Decorators to work we need to set up bable separately. Angular has them by default and do not need to be setup in the project.

```javascript
/*This code is just for reference and may not work as is. Make the changes as described in the code below */

//This is the decorator.
function (target, name, descriptor){
  console.log(target, name, descriptor);
  //the descriptor.value is actually the original function.
  //Store the original function in a varaible, manipulate as wanted.
  const original = descriptor.value;

  //The first desctiptor function and the second function should be used individually not together.

  //This function replaces the original function.
  descriptor.value = function(){
    console.log("this function was hacked");
  }
  original();//This will pring the above function as it has been modified a second time.
  //Do something manipulation with the descriptor

  //If we want to get the value of the origainl function we could use : This function assumes the function is defined with parameters as below
  //We use destructuring to get the args as an array.
  desctiptor.value = function(...args){
    const result = original.apply(this, args);
    console.log(result);
    //We need to return the result so that it can replace the original functiona and the return form the origianl function wont be considered.
    return result;
  }
    
  //Return the desctiptor
  return descriptor;

}
//Original Function being called:
@log
aSimpleMethod(){
  console.log("Hey there!");
}

@log
aSimpleMethod(a, b){
  return a*b;
}

//Call function in constructor : could be called in any function as requrired.
constructor(){
  aSimpleMethod(3, 5);
}

/*The above function call will print to the screen the value of result -> 15 from the console log and again the same value of result form console.log from the constructor.*/
```
-> ` Referance : 23:00 `

## Types of decorators :
1. Member Decorator :  The above example is member Decorator.

2. Class Decorator : 
```javascript
function log(className){
  console.log(className);

  return (...args) =>{
    conole.log("class arguments are : " , args);
    return new className(...args);
  }
}


//Our class
@log
class myExampleClass{
  constructor(args1, args2){
    console.log("Constructor Fired!");
  }
}
const myclass = new myExmapleClass(5, 4);
```
--------

## LifeCycle Hooks : Short explanation.
1. OnChanges : There is a change in input property
2. OnInit : componet is initialized. Fired only once. By the time the method is called your componet is ready to be displayed.
3. DoCheck : Fired by angular, when it thinks there is some change.
4. AfterContentInit : 
5. AfterContentCheck : 
6. AfterViewInit :
7. AfterViewChecked :
8. OnDestroyed : When  a component is removed is called.

---------

## Component : 
1. What is a Component : 
It is an indepent think or code that can be imported anywhere to use independently.

AppComponent contains all the logic for the component.

Create a new Component : `ng generate component hello`

When the above command is executed :
The component is created.
It also adds the componet to the app.module.ts file.

To use a component we need to declare the component in the module file with NgModule decorator. That is so that angular is aware of the component.

`Selector` value is used as a tag to import the component in the html file that it is being used.

## Interpolations and Expressions :

Interpolation : {{ myVar }} : Used in html to direclty use javascript values.

We should not call a method in interpolation as the method will be run every time the html is reloaded by angular and angular will refresh the html many times.

---

## Two way Data Bindin :

Sometimes we need to pass data from our view or script files to html files we use data binding.

1. For source to target -> [] : We use this to take data from our script file to our html file and manipulate our file accordingly.
```html
<app-root [name]= "nameFromScript" />
```

2. Source to : From html to our script. 
```html
<!--click is a event and can be found in docs-->
<button (click)="callMyFunction()">Hey there</button>
```
```javascript
//this is just a regular function.
callMyFunction(){
  console.log("Function called!");
}
```

  Referer -> 1:00:00

3. Two Way data binding : 

Two way data bingind is not a new type but an implementation of above both databinging together.

Can be used for mirroring example below >>
```html
<input type="text" [value]="text" (input)="updateValue($event)">
{{ text }}
```
updateValue need to be an event.

[value] and (input) are directives. We can create our custom directive.

```javascript
text = 'app';
updateValue(e){
  this.text = e.target.value;
  //This will print in the console.
  console.log(e);
}
```

Using the ngModule to achive the same thing as above : 

  Referer -> 01:11:30

----

## *ngFor : 

Use where ever we want to iterate our component.

It could actually be used with any iterable.

```javascript
//Ideally or practically we fetch this data from the some database.
records = [
  {
    name : 'adwait',
    online : true
  }
  {
    name : 'abhi',
    online : true
  }
  {
    name : 'ritesh',
    online : false
  }
]
```

```html
<table>
  <tr>
    <td>Sr No.</td>
    <td>Name</td>
    <td>Is online?</td>
  </tr>
  <tr *ngFor="let record of records let myIndex = index" >
  <!--The *ngFor provides many use ful functions like the above index or odd, even etc and can be refered to in the documents-->
    <td>{{myIndex}}</td>
    <td>{{record.name}}</td>
    <td>{{record.online}}</td>
  </tr>
</table> 
```
  Referer -> 01:18.25
## [ngClass]
It is a directive that applies conditional classes to the component it is used in.
Refer to the docs to see the full list of default functionality.
If multiple functions or conditions in this fit the class will have multiple class names.

---

## Services : 

  Referer -> 01:23:00

It is a singleton instance of file that can be injected into multiple components.

When we want to operate on data we want to use services.

A service can be for a particular component or for global scope. For global scope the service is provided in the providers in the app.modules file.

Create Service : `ng generate service records`

---

## HttpClient : 

Angular suggests that request be made by a service.

To use we import { HttpClientModule } from @angular/common/http
and { HttpClient }

```javascript
//DI is used to inject the instance of HttpClient
 constructor(private http: HttpClient){

 }

 //The interface of what they or formate of data we expect from the request.
interface myData{
  obj:Object
}

 getData(){
   //WE use rxjs subsribe to get the day asyncly
   return this.http.get<myData>('UrlOfTheSitetoGetDAta').subsribe((data)=>{
     console.log("we got", data);
   });
 }
```

We get the data but we might want to use a interface to retrive the data in a fromate we can conviniently use.

---
## Proxy Configuration :

  Referer -> 01:43:00

---

## Routing :
Showing different things on different pages is called as routing.

Also authenticated and not authenticated users can be shows different pages with routing.

  Referer -> 01:48:00

