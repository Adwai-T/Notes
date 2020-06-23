# Angular Overview

![Parts Of Angular and how they work together](./NotesImages/AngularWorkingOverview.png)

* Together, a component and template define an Angular view.

1. A decorator on a component class adds the metadata, including a pointer to the associated template.
2. Directives and binding markup in a component's template modify views based on program data and logic.

* The dependency injector provides services to a component, such as the router service that lets you define navigation among views.

## File Structure

Type Script is automatically compiled/Converted to js by Angular Cli.

index.html : Contains `<app-root>` that is the entry point for our angular project.

polyfills.ts : Used for older browser that might not support the newer functions of javascript.

## Module

Split code into files that work independenly of each other.

*app.module.ts* : This file is used to register all the component that we will use in our project.

You launch your app by bootstrapping the root NgModule.

Organizing your code into distinct functional modules helps in managing development of complex applications, and in designing for reusability. In addition, this technique lets you take advantage of lazy-loading—that is, loading modules on demand—to minimize the amount of code that needs to be loaded at startup.

### NgModule

The @NgModule() decorator is a function that takes a single metadataobject, whose properties describe the module.

* declarations: The components, directives, and pipes that belong to this NgModule.

* exports: The subset of declarations that should be visible and usable in the component templates of other NgModules.

* imports: Other modules whose exported classes are needed by component templates declared in this NgModule.

* providers: Creators of services that this NgModule contributes to the global collection of services; they become accessible in all parts of the app. (You can also specify providers at the component level, which is often preferred.)

* bootstrap: The main application view, called the root component, which hosts all other app views. Only the root NgModule should set the bootstrap property.

### Angular libraries

Angular loads as a collection of JavaScript modules. You can think of them as library modules. Each Angular library name begins with the @angular prefix. Install them with the node package manager npm and import parts of them with JavaScript import statements.

For example, import Angular's Component decorator from the @angular/core library like this.

```javascript
import { Component } from '@angular/core';
```

## Decorators

What are decorator exactly?

A Python decorator is a function that takes another function, extending the behavior of the latter function without explicitly modifying it.

* Decorate a function/property inside of class.

```javascript
//basic class defination with the decorator that we define below
class Cat{
  @readonly
  meow(){ return `${this.name } say Meow!`;}
}

//Evaluating this class results in installing the meow function onto `Cat.prototype`, roughly like this:
Object.defineProperty(Cat.prototype, 'meow', {
  value: specifiedFunction,
  enumerable: false,
  configurable: true,
  writable: true
});

//We define now a decorator that will mark the function to be readOnly
function readonly(target, key, descriptor){
  descriptor.writable = false;
  return descriptor;
}

//Try to change the meow function after applying the decorator
var garfield = new Cat();
garfield.meow = function(){
  console.log('I want lasagne!');
}
//Exception : Attempt to assign to readonly property.
```

Note : For More Info on [Decorator](https://medium.com/google-developers/exploring-es7-decorators-76ecb65fb841#.x5c2ndtx0).

Example : `@Component` Is an internal decorator used in Angular.

```ts
//Here we defince the decorator function that will be used to modify the below function
function log(target, name, descriptor){
    console.log(traget, name, desctiptor);

    //This assigns the value of the original function to original.
    const original = descriptor.value

    //This will run the original function. This itself is a call to the function and the function will run twice whe  the function  is actually called.
    //Even so it will not inclued changes that are dont below as we have not yet returned the function value.
    //Change --1
    //original();

    //Change --2
    /*
    * Here we have changed the the original function itself. If we have this codeblock, the original function will never excute.
    * Instead we will have this defined function execute when the function below is called.
    */
    // descriptor.value = function(){
    //     console.log("This function was hacked!")
    // }

    //We will create a useful function that will work as a logger to console function.
    //Once we create this function the below function will not be executed. This function however uses the values for the below function.
    descriptor.value = function(...args){
        console.log("Arguments "), args, "were passed");
        //The .apply function used to apply this form the original function to the updated function.
        const result = original.apply(this, args);
        console.log("The result of the function is ", result);
        return result;
    }

    //We return the changed function.
    return descriptor;
}

export class AppComponent{
    title = 'app';
    constructor(){
        console.log('This statement was generated by constructor');
        this.aSimpleMethod(5);
    }

    //@log is the decorator for the function.
    @log
    aSimpleMethod(a){
        return a*a
    }
 }

```

### Class Decorator

Example : @Component.

Decorators can be applied to class, but they have to be immediately above the class name.
Multiple decorators could be added to classes.

Note : The class decorator will be fired before the class is exported or used.

```ts

//This will print the class a function as classes in javascript are basically prototype functions.
//Change --1
// function classFunction(classAsFunction){
//     console.log(classAsFunction);
// }

//Change --2
function classFunction(className){
    console.log(className);
    retrun (...args) => {
        console.log("Arguments passed to this class constructor are : "  + args);
        return new className(...args);
    }
}

@classFunction
class myExampleClass{
    constructor(arg1, arg2){
        console.log("Constructor Fired!")
    }
}

const myClass = new myExampleClass(5, 10);
```

## Lifecycle Hooks

Get the details of [Lifecycle Hooks](https://angular.io/guide/lifecycle-hooks)

1. ngOnChanges : Every time there is a change lets say input property.

2. ngOnInit : Whenever a componet is initailized. The code that is in the oninit method will be fired or invoked only once.

3. ngDoCheck : Fired by angular when it thinks there was a change.

4. ngAfterContentInit :

5. ngAfterContentCheck :

6. AfterViewInit :

7. OnDestroy : Called when some componet is destroied or removed.

You don't have to implement all (or any) of the lifecycle hooks, just the ones you need.

## Components

### What is Component

A component controls a patch of screen called a view.

Lets take the example of header for a page. This header will be then usable on multiple pages. This thus can be made to be a component in Angular.

*app.component.ts* contains all the logic for the component that we create.

Create a new component : `ng generate component hello`.

When we create a new component Angular cli will automatically add the component name to app.modile.ts in the @NgModule -> declarations array.

This is where all the component that we create will automatically be added or we will need to add if we add a component manually. This will make angular aware of all the component that are being used by us to render them as needed.

We after creating a component we need to import the component in the other component.ts file of the component that uses the custom component.

## Interpolation

`{{ myVar }}` : This represents the javascript value in the html file.

Not all javascript expression can be used in this. For example bitwise operation can be performed in the interpolation.

This is because Angular has Pipes that perform some functions with `|`.

Also functions should not be called from Interpolation on the html page as they are called multilpe times whenever change is detected on the page.

## Data Binding

![Data Bindind in Angular Image](NotesImages/DataBindingInAngular.png)

*Property binding* lets you interpolate values that are computed from your application data into the HTML.

*Event binding* lets your app respond to user input in the target environment by updating your application data.

The following is what sets the attribute value of the text box to the value of the variable.

```html
<input type="text" [value]="myVariable" />
```

There is also a value property to the textbox itself. If we use the following code we bind the data to the value of the text box. The above code is recommended even though the following code appears to work similarly.

```html
<input type="text" value="{{myVariable}}" />
```

### Source to Target

`()` : Round brackets are used for traget to source databinding.

```html
<button (click)="callMyFunction()"></button>
```

The callMyFunction is defined in the component.ts file of the component that is being used.

### Two way Data Binding

Angualarjs use to come with Two way Data Binding inbuild but Angualar 2 onwards does not come with it inbuild. Even som it can mimic it with Single way data binding as we used above.

```html
<input type="text" [value]="text" (input)="updateValue($event)">
{{text}}
```

```javascript
//This is the initial value initailzied in the exported class scope
text = 'app';
//e here is a Input event object.
updateValue(e){
    this.text = e.target.value;
    //Gives actual value of what is typed.
    console.log(e.target.value);
}
```

The above `value` and `input` are the directives properties that Angular provides out of the box.

The `ngModel` *directive*, which implements two-way data binding, is an example of an attribute directive. `ngModel` modifies the behavior of an existing element (typically `<input>`) by setting its display value property and responding to change events.

```html
<input type="text" [(ngModel)]="text" />
```

`ngModel` is not a part of the basic Angular app, thus it need to be imported it in `app.module.ts` like :
`import { FormsModule } from '@angular/forms`
Also add `NgModel` to the imports array of the same file.

NgModule finally can be said as an inbuild two way databinding directive that is provided by Angular.

## ngFor

Could be used where ever we want to use iterable.

```js
export class AppComponent{
    records = [
        {
            name: 'Mehul',
            online: false
        },
        {
            name: 'Adwait',
            online: true
        }
    ]
}
```

```html
<table>
    <tr>
        <td>Sr no</td>
        <td>Name</td>
        <td>Is online</td>
    <tr>
    <tr> *ngFor= "let record of records; let myIndex = index; let evenRecord=even; let oddRecord=odd;let firstRecord=first; let lastRecord=last;" [ngClass]={odd: oddRecord, even: evenRecord}>
        <td>{{myIndex + 1}}</td>
        <td>{{record.name}}</td>
        <td>{{record.online}}</td>
    </tr>
</table>
```

The even and odd seperates even and odd records and returns a boolean value. Also first and last gives the first and the last record in the iterable.

The `[ngClass]` Applies conditional class to the element in html.

## Services

It is a singleton instance of a file that can be ingected into multiple components.

A *component* can delegate certain tasks to services, such as fetching data from the server, validating user input, or logging directly to the console. By defining such processing tasks in an injectable *service* class, you make those tasks available to any *component*. You can also make your app more adaptable by injecting different providers of the same kind of *service*, as appropriate in different circumstances.

A *service* class definition is immediately preceded bythe `@Injectable()` decorator. The decorator provides themetadata that allows other providers to be injected asdependencies into your class.

### Dependency Injection

*Dependency injection (DI)* lets you keep your *component* classes lean and efficient. They don't fetch data from the *server*, validate user input, or log directly to the console; they delegate such tasks to *services*.

* The *injector* is the main mechanism. Angular creates an application-wide *injector* for you during the bootstrap process, and additional *injectors* as needed. You don't have to create *injectors*.

* An *injector* creates *dependencies*, and maintains a *container* of dependency instances that it reuses if possible.

* A *provider* is an object that tells an *injector* how to obtain or create a dependency.

`constructor(private service: HeroService) { }`

Example :

If we want to fetch data, we can create a service to do that.
Or if we want to create a login authentication then we can create a service for login.

Creating a new Service : `ng generate service records`

Example : Create a data service

```javascript
//record.service.ts class
@Injectable()
export class RecordsService{
    constructor(){}

    getData(){
        return [
            {
                name : 'Mehul,
                online: true
            },
            {
                name : 'Adwait',
                online : false
            }
        ]
    }
}


//app.component.ts

import { RecordsService } from ./

export class AppComponent{

    records = {}

    //This is type Script code where we Inject our service privatly into the constructor.
    constructor(private myFirstService : RecordsService){

    }

    //We here initialize our data from the service so that we can use it where ever we want to.
    ngOnInit(){
        this.records = this.myFirstService.getData;
    }
}

//app.module.ts

import { RecordsService } from ./serviceFileLocation

@NgModule({
    //All the stuff that we are not concerned here

    providers: [RecordsService]

    //All other things here
})
```

Service Can be specific to a component, we can inject the service to the component directly.

But most of the time we want our service to be shared by multiple component in our Angular project. To do that we add that service in our  app.module.ts

`ngOnInit()` is a life cycle hook that run only once when the component is created. Thus it becomes a perfect place for runnning code that need to be run only one like initialize our data to be used in our application components.

## HttpClient

```ts
//app.module.ts

import { HttpClientModule } from '@angular/common/http'

@NgModule({

    //Other code here

    imports: [
        BrowserModule,
        HttpClientModule
    ]

    //Other code here
})

//We can not inject the HttpClient module in our Service.

//records.service.ts

import { HttpClient } from '@angular/common/http'

//This tells that this service can have some injectable in the service like the HttpClient.
@Injectable
export class RecordsService{
    //Here we inject the service to the file
    constructor(private http: HttpClient){

    }

    //The subscribe comes from RxJs event.
    getData(){
      return this.http.get<myData>
      ('http://urlforthedataserverhere.com')
      //Rather than to subscribe here we can subscribe where we want to fetch the data when it is required.
      // .subscribe(data => {
      //   console.log('We got data ', data);
      })
    }

}

//app.component.ts

//This is an interface that provides details on how the HttpClient should retrive data.
interface myData {
  obj : Object
}

//all the codes and imports in the class remain as they should have been.
export class AppComponent {
  records = [];

  constructor(private myFirstService : RecordsSerivce){
  }

  //This is where we want ot subscribe to data rather than in the service as we want to actually fetch data when the component is created and not before that.
  ngOnInit(){
    this.myFirstService.getData().subscribe(data => {
      this.records = data.obj;
    })
  }
}

```

## Proxy Configuration

Cross Orgin Resource Sharing : Standard set of implementation how frontend can access other servers code.

This is a security implementation by browsers.

For development we need to proxy our request from angular server to our remote server.

Working flow of request send by Angular :

| Angular 4200 | --> makes an API call --> | API Server 1234 |

|Angular 4200 | --> make API call to /api/* --> webpack dev server --> | API server 1234|

How to set up the proxy server for our request :

In the `package.json` file --> under `scripts` set the value of `start` to `"ng serve --proxy-config proxyconfig.json"`. This will set the Angular developement server setting to take configuration instruction from proxyconfig.json file that we create in the root of our project.

proxyconfig.json

```json
{
  "/api":{
    "traget":"http://localhost:1234",
    "secure": false,
    "changeOrigin": true
  }
}
```

Whatever is written at the proxyConfig path is appended at the end of the traget address.

In this case we will have `http://localhost:1234/api`. So we will have to file that are to be served from the other proxyfied address will have to be placed in the folder named by the address like in our case it will be `api`. In our case the final path of the file from that was created in previous examples will be : `projectRoot/test/api/file.json` where `file.json` is the data file being served at the proxy address.

Now that we have set the proxy we can run our program to start our developer server by : `npm start`.

## Routing

The Angular Router NgModule provides a service that lets you define a navigation path among the different application states and view hierarchies in your app.

Click the browser's back and forward buttons and the browser navigates backward and forward through the history of pages you've seen.

The router interprets a link URL according to your app's view navigation rules and data state. You can navigate to new views when the user clicks a button or selects from a drop box, or in response to some other stimulus from any source. The router logs activity in the browser's history, so the back and forward buttons work as well.

Need routing for displaying large amount of content in chunks on the website, or for creating special authorized access-only pages.

Example:

1. create two components Home and Data.

`ng g c Home` and `ng g c Data`

```ts 1:50:52
//app.module.ts

import { RouterModule } from '@anfular/router'
//All other imports here

@NgModule({
  //other data here

  imports: [
    //Other imports here

    //To the router module we pass in an array of the required routes.
    /*The routes that can match multiple paths should be placed lower on the list to the routes that are more specific.
    Example /data1/data2 should be placed above /data1 as Angular will match /data1 as soon as the first match is found and serve the component for that route.
    */
    RouterModule.forRoot([
      {
        path: 'data',// localhost:4200/data
        component: DataComponent
      },
      {
        path: '',
        component: HomeComponent
      }
    ])
  ]
})
```

The html Page for the routing.

```html
<!-- Main app.component html file -->
This will always display : Anything that is outside of our router outlet tags will always display irrespecitve of which route we are on as it is indepent of the routing that we have set.
<router-outlet></router-outlet>

<!-- Home component html file-->
<p>
  Home Works!
  <a routerLink="/data">Go to Data Page</a>
</p>
```

The routerLink is a special link and our app will not be reloaded completely.

So we also see that file.json will not be loaded at the '' path, it will only load the file when we call the rout '/data', as angular does not load all the component and related files all at once.

## Login App

This is an example that gives us basic of Angular.

Following features are covered under this mini Project :

1. App Components

2. Backend validation

3. Routing

4. Route Protection

## Route Guards

Verifies whether a user is allowed to access to a route.

Methods of RouteGuard :

1. Can Activate : Will only protects one route.

2. CanActivateChild : If it is set for `/admin` will also protect all the routes that are `/admin/*`

3. CanDeactivate : Can be used to keep some route active so that the user can access it again fast.

4. Resolve : Get some data from api server before the user actually needs or sees the data.

5. CanLoad : Lazily load the component after checking the user is allowed or has permission to access the route.

Creating a guard : `ng generate guard auth`

Using the Authguard that we created

```ts
//auth.guard.ts
@Injectable()
export class AuthGuard implements CanActivate{

  constructor(private auth: AuthSerivice) {
  }

  canActivate(
    //Default code here
    //--1 Change
    //return false// If return true auth will not be applied and we can directly access the admin page.
    //As we use false as our value we cannot access the admin Component and we are redirected to the home component.

    //We will let our AuthService handle the authentication and set the boolean value for the guard.
    return this.auth.isLoggedIn;
  )
}

//app.module.ts
import { AuthGuard } from './auth.guard';

import: [
  //other code here

  RouteModule.forRoot([
    //other code here
    {
      path: 'login',
      component: LoginComponent,
      canActivate: [AuthGuard]
    }
  ])
],
//Inject it into providers to get a singleton instance of the AuthGurad to be used.
providers: [AuthGuard, /*Other providers like*/ AuthService]

//auth.service.ts
//We need an interface for the data that comes from the input stream from the http.post request. So we create an interface for that.
interface myData{
  success: boolean,
  message: string
}

@Injectable()
export class AuthService{

  //constructor
  constructor(private http: HttpClient){ }

  //This is a function but acts as a property or in simple terms we can access it like we access variables. We can see that we dont have to use () while we get the value from this function as we see above.
  //---1 Change
  // get isLoggedIn(){

  // }

  //Public property to be set from other class
  //--2 make the value private as we create setLoggedIn method to set the value for the variable.
  private loggedInStatus = false;

  //--2 Set value for loggedInStatus by using a method
  setLoggedIn(value: boolean){
    this.loggedInStatus = value;
  }

  //getter for loggedin
  get isLoggedIn(){
    return loggedInStatus;
  }

  //getUserDetails or other methods here.
  getUserDetails(username, password){
    return this.http.post<myData>('/api/auth.php',{
      username,
      password
    });
  }
}

//login.component.ts
import { Router } from '@angular/router';

export class LoginComponent implements OnInit{
  constructor(private Auth: AuthSerive, private router: Router) {}

  loginUser(event){
    //other code here

    this.auth.getUserDetails(username, password).subscribe(data=>{
      if(data.success){
        //here when the user is authenticated properly we redirect the user to admin or load the admin component.
        this.router.navigate(['admin']);
        this.Auth.setLoggedIn(true);
      }
      else{
        window.alert(data.message);
      }
    })
  }
}
```

The above code is still very insecure as the authentication code is authenticated at runtime.

## Pipes

### Inbuilt Pipes

1. Date
2. UpperCase
3. LowerCase
4. Currency
5. Percent

### Custom Pipes

`ng generate pipe name` : Create a Pipe

```ts

export class ReversePipe implements PipeTransform{

  transform(value: any, ...args): any {
    let newString = value
    if(args[0]){
      newString += "."
    }
    if(args[1] == "singlequote"){
      newString += "'" + newString + "'";
    }
    else if(args[1] == "doublequote"){
      newString = '"' + newString + '"';
    }

    return newString;
  }
}

```

```html
{{ "This is a String" | reverse:true:"doublequote" }}
```

## Directives

1. Adds custom behaviour to our HTML

2. They are attributes of our HTML tags.

A *component* is technically a directive. However, *components* are so distinctive and central to Angular applications that Angular defines the `@Component()` decorator, which extends the `@Directive()` decorator with template-oriented features.

### Inbuilt Directives

### Structural directives

Structural directives alter layout by adding, removing, and replacing elements in the DOM. The example template uses two built-in structural directives to add application logic to how the view is rendered.

* NgIf

```html
<div *ngIf="someVariable; then trueBlock else falseblock">
</div>

<!--These are ng-templates that can be given an id directly and used in the code as done above-->
<ng-template #trueBlock>
  <div><h1>Yes!!</h1></div>
</ng-template>

<ng-template #falseBlock>
  <div><h1>No!!!</h1></div>
</ng-template>
```

```ts
//*ngIf will evaluate the condition in the value and display content according to the evaluated value.
export class tsComponent{

  //This variable will be used to decide which block is actually shown in the html page.
  let someVariable:boolean = true;

}
```

* ngSwitch

* ngNonBindable : It is used to escape the special cases such as interpolation in the html.

```html
<span ngNonBindable>{{ ThisWillNotBeEvaluatedAsAExpression }}</span> is used to Interpolate varaibles from our script to our html.
```

* ngClass

```html
<ul>
  <span [ngClass] = "{
    'red': info.number === 'even',
    'blue': info.number === 'odd'
  }">
</ul>
```

In the above html ngClass will set the value for the class of the span according to the whether the condition is fulfilled. Multiple conditions can be fulfilled and multiple classes will be added to the tag.

### Attribute directives

Attribute directives alter the appearance or behavior of an existing element. In templates they look like regular HTML attributes, hence the name.

The `ngModel` *directive*, which implements two-way data binding, is an example of an attribute *directive*. `ngModel` modifies the behavior of an existing element (typically `<input>`) by setting its display value property and responding to change events.

### Custom Directives

`ng g directive directivename`

```ts
//vs code might get the import wrong
import { ElementRef } from '@angular/core';

@Directive({
  selector: [appDirectivename]
})
export class Directivename{

  element: ElementRef;
  //Get the reference to the element in our html
  constructor(private el: ElementRef){ 
    //We change the color of the element of which we set the custom directive.
    el.nativeElement.style.color = "red";
    this.element = el;
  }

  //As the directive set above will be applied before the element is actually created we dont have access to the inner html. Hence we use will place the code that access the element data in ngOnInit.
  ngOnInit(){
    this.element.nativeElement.innerText += "-Custom directive was used to formate this.";
  }
}
```

---

## Other Notes

### [Angular Glossary](https://angular.io/guide/glossary)
