# Angular

> Note all these notes are base on Maximilian Schwarzmüller course on Udemy.

## Install

Requires Node for packing and optimize the project. Also npm will be used download all the dependencies and angualar cli itself.

`npm install -g @angular/cli` : Install angular Cli

`ng new my-app` :  Create a new project

`ng serve` : Serve or run the new project at port 4200 on local host with development server active, that is the server will refresh app whenever we save some files and changes are detected in those files. The `ng serve --open` flag will open the default browser at localhost:4200.

As angular cli sets up the project with a package.json file and we have npm installed with node, we can set up `npm start` command with required setup.

## Bootstrap

Adding bootstrap to our angular project.

With bootstrap download the bootstrap dependency `npm install --save bootstrap@3`.

In angular.json in the root of our project, add the location of the bootstrap dependency.

In "styles" array add: `node_modules/bootstrap/dist/css/bootstrap.min.css"`.

## Components

The angular cli helps us set up different components, modules and services to get us started.

We can use `ng generate <schematic> [options]` to get started with basic code for that schematic.

To generate components we use `ng generate component nameForComponent` or short `ng g c nameOfComponent`. The component is added in the `src\app` folder. We can specify a relative location with the name to add the component that location. To create a component named `image` inside `gallery` directory we will use `ng g c gallery/image`, so the new Components files will be placed in `src\app\gallery\image`.

While we generate a component with the cli we can use `--skipTests true` so that the test `.spec.ts` is not created.

### HTML template

Directly in the component.ts file :

```ts
@Component({
    selector: 'aap-servers',
    //This is html template that will be used with this component
    //We in this case do not need to define a new html file to hold the template for the compnent.
    template: `<app-server></app-server>`,
    styleUrl: ['./servers.component.css']
})
```

Even so this method is not recommened as it can get very complex even if we write a relatively small amount of code.

The other mehods is to add templateUrl that holds the relative location of the html template we want to use with the component script file.

### Styles

Similar to html templates direcly defined above we can also define our css by defining it in the component script file.

`styles: [' h3{ color: dodgerblue; } ']`

Or we can do it as it is recommended by the cli and use the component.css file create by the angular cli when we generate a component.

Note :
Angular Enforces style encapsulation that means that a css property defined for one component is not applied to other component even if the component is a child component of the component where the style is defined.

Angular does that by adding a custom property to all the elements of the particular component and adding style to that property.

This is done so that the page is supported on older browser that might not support shadow DOM that is implemented by modern browser that supports styles to be added to individual components and then be displayed.

This style Encapsulation behaviour of a component can be changed by adding `encapsulation: ViewEncapsulation.None` to the `@Component` declaration of the component that we dont need encapsulation for.

We can also choose `Native` as the porperty for the encapsulation which will use the Shadow DOM behaviour of the browers that support it. But we dont want to use it as there are browsers that might not support it especially the older version of the common browers.

The default value for `encapsulation` is `Emulated` which is the default behaviour as discussed above and does not need to be specified.

### Selector

Selectors can be html tags, or class or id.

* Normal Selector defined when generated is a html element.
`selector: 'app-servers'`
`<app-servers></app-servers>`

* Attribute :
`selector: '[app-servers]`
`<div app-servers></div>`

* Class :
`selector: '.app-servers'`
`<div class="app-servers"></div>`

All of the above selectors can be used to get similar results.

## Data Binding

* String Interpolation :

`value: string = This string will be displayed`
`{{ value }}` : This we put in HTML file.

Any value which at the end can be resolved to a string can be used here. But a multiline expresson cannot be used here.

* Property Binding

Binding To properties in HTML.

`<button class="btn btn-primary" [disabled]="allowNewServer">Add Server</button>`
`allowNewServer:boolean = false`

In the above html code we create a button. In it `disable` is a property of the button and default html code. It is not related to angular. The disable property will disable the button and we will not be able to click it.

In the above code we bind the disable property to the varible `allowNewServer` which is a variable in our js code.

* Event Binding

Similar to property binding we can bind to any event provided by that HTML element.

We use `()` to bind to the event as we used `[]` to bind to the properties.

* Bindable Properties and Events

How do you know to which Properties or Events of HTML Elements you may bind? You can basically bind to all Properties and Events - a good idea is to `console.log()`  the element you're interested in to see which properties and events it offers.

Important: For events, you don't bind to onclick but only to click `(=> (click))`.

The MDN (Mozilla Developer Network) offers nice lists of all properties and events of the element you're interested in. Googling for `YOUR_ELEMENT` properties  or `YOUR_ELEMENT` events  should yield nice results.

* Events

```ts
//We get a event from the event binding in the html.
onUpdateServerName(event: Event){
    //This will expilicitely tell ts that we know that this is the html event property.
    this.serverName = <HTMLInputElement>event.target.value;

}
```

* ngModel : Twp Way binding Directive

NgModel is used for two way databinding and is a directive provided by angular.

`ngModel` is not a part of the core module of angular and needs to be imported by adding the `FormsModule`  to the `imports[]`  array in the AppModule.
Then also need to add the import from `@angular/forms`  in the app.module.ts file:

`import { FormsModule } from '@angular/forms';`

* Two way Data Binding :

## Directives

### Structural Directives : Build In

In structural directives we use `*` to indicate that the directive is a structural directive. The star is not only there to tell the other programs that read the code that it is a structural directive but also to angular as angular need to change the code that in wrapped in the structural directive to from the code that it understands. `*` by itself is not a functional part of angular, but a way for us to write the code more inituitively.

So the code `*` gets converted into an ng-template that angular understands.

```html
<div *ngIf="!onlyOdd">
    <li *ngFor="let even of evenNumbers">{{even}}</li>
</div>

<!--The above code will be converted to the following code and similar for the ngFor inisde the existing code.-->
<ng-template [ngIf]= "!onlyOdd">
    <li *ngFor="let even of evenNumbers">{{even}}</li>
</ng-template>

<!--Now we see that we dont have the star and the ngIf is bound as a property instead-->
```

Note: We cannot have more than one structural directive on any one html element.

* *ngIf :

The `*` in the directive name tells that this directive will change the DOM and is a **structural directive**.

The value *ngIf should be set to an expression that return a boolean value.

* *ngIf with Else :

```html
<p *ngIf="serverCreated; else noServer">Server was created</p>
<ng-template #noServer>
<p>No Server was created</p>
</ng-template>
```

`#` in the code is called a local marker. It denotes what is to be shown when the condition of the `ngIf` is false.

* ngFor : This is also a structural directive.

* ngSwitch :

```html
<div [ngSwitch]="value">
    <p *ngSwitchCase="1">value 1</p>
    <p *ngSwitchCase="2">value 2</p>
    <p *ngSwitchDefault>value Default</p>
</div>
```

* **Custom Structural Directive** :

```ts
import{ Directive, Input } from '@angular/core';

@Directive({
    selector: '[appUnless]'
})
export class UnlessDirective{

    //set looks like a method but is just defines how or what value is set to the property it is used with. This does not converty the property by itself into a method, but will be executed when the value of the property changes outside to check the condition for setting the value of the property.
    //The name of the property and the selector of the directive need to match as we use the * and rely on angular to create the template for us. And as we saw above when angular create the template it will bind to the selector and this property if it has some other name. So we use the same name as that of the selector for the property to be bound correctly.
    @Input() set appUnless(condition: boolean){
        if(!condition){
            this.vcRef.createEmbeddedView(this.templateRef);
        }else{
            this.vcRef.clear();
        }
    }

    constructor(private templateRed TemplateRef<any>, private vcRed: ViewContainerRef){}
}

//After the directive is created remember to add the directive name in the app.module.ts in @NgModule -> declarations array.
```

```html
<div *appUnless="onlyOdd">
    <li *ngFor="let even of evenNumbers">
</div>
```

### Attribute Directives

Unlike structural directives these directive do not add or remove any elements. Thye only change the element they are placed on.

```html
<p [ngStyle]="{backgroundColor: getColor()}">This is a line</p>
<!--We could also have conditional styling like in the below example-->
<p [ngStyle]="{backgroundColor: odd%2 !== 0 ? 'grey': 'yellow'}">
```

The ngStyle by itself does not require the `[]` but was we are binging a value form our component.ts file to the style we need them. In the example above we bind the value from our script file to the backgroundColor Property of the ngStyle.

* ngClass : Conditionally add class to our element.
`[ngClass]="{odd: odd%2 !==2}"`

## Creating an Attribute directive

`ng g d better-highlighter`

```ts
import{ Directive } from '@angular/core';

@Directive({
    selector: '[appBasicHighlight]'
})
export class BasicHighlightDirective implements OnInit {

    constructor(private elementRef: ElementRef){}

    ngOnInit(){
        this.elementRef.nativeElement.style.backgroundColor = 'green';
    }
}

//Directives need to be added to app.module.ts in the declarations for angular to know that we have created that directive.
```

In the below example we dont use square brackets as we are not trying to select any attributes but trying just using our directive on our element.

```html
<p appBasicHighlight>Style me with bacic directive!</p>
```

Even if in the above example we change the style of our html element directly by using the reference to the element in our script file it is not recommened.

The better approach to changing the DOM from the script file is to use `Renderer` to make the style changes that we want to make. This is important as in some use cases like in services(Not referering to angular services here but general service programs) we might not have access to the DOM element.

### Create Directive with Renderer

```ts
//--Change 1 : Make the change background interactive so that the background of the element only changes when we hover our mouse over the element.

//--Change 2 : Use @HostBinding to bind to the properties of the html element.

//--Change 3 Make final code clear and Add selectable color properties in our script that can be bound from within our html element in our html template file.

import { Directive, OnInit, ElementRef, Renderer2 } from '@angular/core';

@Directive({
    selector: '[appBetterHighlight]'
})
export class BetterHighlighterDirective implements OnInit{

    //--Change 2
    //Here we bind to the backgroundColor property of host or the html element that the directive is used in. The argument that is passed in represents what we property of the host element we want to bind to and the outside backgroundColor is the varaible name that we use to refer to the bound property within our script and can be named as we wish.
    HostBinding('style.backgroundColor') backgroundColor: string = 'transparent'

    constructor(private elRef: ElementRef, private render: Renderer2){}

    ngOnInit(){
        //--Change 1
        //this.renderer.setStyle(this.elRef.nativeElement, 'background-color', 'blue');
    }

    //--Change 1
    //@HostListener will refer to the element that the directive is placed on.
    //This will activate when the mouse hover over our html element
    @HostListener('mouseenter') mouseover(eventData: Event){
        //--Change 2
        //this.rederer.setStyle(this.elRef.nativeElement, 'background-color', 'blue');
        this.backgroundColor = 'blue';
    }

    //--Change 1
    //This will proc when the mouse pointer leaves the area covered by the html element.
    @HostListener('mouseleave') mouseleave(eventData: Event){
        //This still uses the renderer form change 1.
        this.renderer.setStyle(this.elRef.nativeElement, 'background-color', 'transparent')
    }
}
```

Final Form of Example

```ts
@Directive({
    selector: '[appBetterHighligher]'
})
export class BetterHighlighterDirective implements OnInit{

    @Input() defaultColor: string = 'transparent';

    //If our directive has one important propertu that it need to bind to we can directly name or in other words use Alias that is the selector value of the directive and bind to the directive declaration itself in the html tag as show below in the html code.
    @Input('appBetterHighligher') highlightColor: string = 'blue';

    //We want to the element to initialize with the color so we initialize this in the ngOninit method.
    @HostBinging('style.backgroundColor') backgroundColor: string;

    constructor(private elRef: ElementRef, private renderer: RendererV2){}

    ngOnInit(){
        this.backgroundColor = this.defaultColor;
    }

    @HostListener('mouseenter') mouseOver(eventData: Event){
        this.backgroundColor = this.highlightColor;
    }

    @HostListener('mouseleave') mouseleave(eventData: Event){
        this.backgroundColor = this.defaultColor;
    }
}
```

HTML Code

```html
<p [appBetterHighlight]="'red'" [defaultColor]="yellow"> Style me with better Highlighter Directive.</p>
```

As we see in the previous section example we dont have to have `[]` to surround the directive selector but as we have named our @Input main property that the directive needs to achive to the name of the selector we have to now put the selector of the directive in the `[]`.

We also see that we put the *red* in double quotes and then single quotes, that is to signify that it is a string.

We can also bind to the properties direcly by omitting `[]` but only in the case that we are passing in a string and we also omit the single quotes that surround the string. But while using this case it should be very clear that it is not a native property of the element for other who read the code and also angular itself.

### Renderer

The above example shows the use of renderer to change the property background color of the host html element. As it is recommended that we should not change host elmenents properties, values and style from our script we use the renderer to change the properties, and styles for us.

A lot more can be done with the renderer than just change the style of the element. All the methods of the Renderer can be refered to [here : Renderer2](https://angular.io/api/core/Renderer2).

### @HostBinding and @HostListener

The above example show Hostbinding and HostListener in action.

HostBinding let us bind with the properties of the hosting html element.

HostListener listenes for the events that the html element my supports.

## Debugging Angular

A Tool named augury can be used to debug the angular code easily in chrome. It is a chrome extension and give wide and easy debugging options.

## Custom Property and Event Binding

We need to import @Input and @Output from @angular/core to use them in our components.

### `@Input()`

The @Input() allows the child component that is hosted in our parent component, where the property that we want to access is defined, to use this property.

So basically properites of parent component can be accessed by child component by using @Input().

`@Input() element: {type: string, name: string};`

We can also set an alias to the property, put simply we can pass to input a name that will be used to bind to the property.

`@Input('serverElement') element: {type: string, name: string};`

`[serverElement]="serverElementCreated"`

So as shown above we can bind to the name serverElement to access the property element in the parent component. Now that we have given then property an alias we cannot bind to the property with its original name.

### `@Output()`

The @Output() helps us to bind to a property in our child component and pass the data to the parent component to be used.

So basically opposite flow of @Input().

@Input() : Parent ==> Child
@Output() : Child ==> Parent.

`(serverCreated)="onServerAdded($event)`

This is the code we will use in the app-component tag in the html to bind to the property from the child class and pass data with `event` to the parent class.

As we see above out onServerAdded method needs an event paramenter. That means serverCreated should emmit an event.

To do that we have create a property in our child class that is of type event emiiter.

`@Output()  7serverCreated = new EventEmitter<{ServerName: string, serverContent: string}>()`

This will create a new object of type EventEmitter and we also pass in the type of object that the event emitter will emit.

Now that we have create the event emitter object we want to create a method that will actually emit the event from the child to be used in the parent.

```ts
onAddServer(){
    //The emit method takes the object that will be emitted by the event emitter when called.
    this.serverCreated.emit({
        serverName: this.newServerName,
        serverContent: this.newServerContent
    });
}
```

Similar to @Input we can also pass @Output a name so that the name can be used to bind to the property from the parent component.

### Local Reference to the HTML element

`#` is used to create a local reference in an element.

`<input type="text" c;ass="form-control" #LocalElementReferenceName>`

Note : Local References can only be used in the html template and not in the type script code of the component.

The local Reference will give us access to the element it self. For example if we create a local reference to an input field as shown above we will have access to the field itself and not its value direclty. But we can get the value of the input form the element that we get reference to by using `referenceName.value`.

In our script file if the local reference is passed as a parameter can specify the type of the arguments as `HTMLInputElement` for the above line of code example.

### @ViewChild()

`@ViewChild('serverContentInput', {static: true}) serverContentInput: ElementRef;`

The same change (add `{ static: true }` as a second argument) needs to be applied to ALL usages of `@ViewChild()` (and also `@ContentChild()` which you'll learn about later) IF you plan on accessing the selected element inside of `ngOnInit()`.

If you DON'T access the selected element in ngOnInit (but anywhere else in your component), set `{ static: false }` instead!

If you're using Angular 9, you only need to `add { static: true }` (if needed) but not `{ static: false }`.

To Use `@ViewChild()` we have to pass the local reference to the ViewChild as a paramenter which will be used as a *selector* for the element in HTML.

Unlike the above example where we pass the local referce to a method as a paramenter and get the html element itself in our script file, we get a `ElementRef` as the type which need to be imported form angular core.

Note: Even if we can get the html element in our script file it is not recommended to change the value of any other property of the html element directly throught the reference. We can use directives to change the value.

### ng-content

`<ng-content></ng-content>` is used in our component. This will be the place where the content placed between `<app-componentname-selector>Content</app-componentname-selector>` will be projected.

## Services And Dependency Injection

Note: The Service is defined with `@Injectable()`. Every angular class that we need to inject a service into needs to have a metadata defined about it. For Componenets it is @Componenet, but services by themselves do not have any metadata defined for them. Thus to inject a service into another service the service in which another service is to be injected need to have an `@Injectable()` to define the metadata for the service.

With the later versions of angular it is standart practice to define to define a service with `@Injectable()`.

From Angular 6 onwards we do not have to have providers defined in the app-modules.ts file as the service direcly defines it in metadata in the `@Injectable()` that it needs to be instanciated in the root of the project.

### Hierarchical Injector

```ts
//Service
export class NameOfService(){
    //Service Code here
}

//Component we use the service in.
@Component({
    //Other code here
    providers:[NameOfServiceHere]
})
export class NameComponent(){

}

@Component({
    //Meta data here.
    //no need for providers as we have defined it above.
})
export class ChildOfNameComponent(){

}
```

The instance for the service are created when we define the service in the providers for the Component. All the child components of the Compoenent will use the same instance of the service if we do not define the service in providers of the child component.

If we want a app wide single instance of the service or we want to inject one service into another we have to define the service in `@NgModules` -> `providers[]` of the `app-modules.ts` class.

So simply put the services declared in the parent passes down the same instance to the child if the service is not declared in providers of the child class.

## Routing

### Defining Routes in app.module.ts

```ts
import { Routes, RouteModule } from '@angular/router';

const appRoutes: Routes = [
    { path: '', component: HomeComponent },
    //We do not want / before the route name.
    { path: 'users', component: UserComponent }
]

@NgModule({
    //other code
    imports: [
        //Other Imports
        RouterModule.forRoot(appRoutes)
    ]
})
```

In our html we add `<router-outlet></router-outlet>` where we want to add the compoenent at the current route.

Note: `router-outlet` is a angular directive even if it looks like a html element.

* Adding links to the HTML code :

```html
<!--In the below we pass directly the route to the router link-->
<a routerLink="/servers">Servers</a>
<!--In the below example we bind to the routerLink and pass a string in '', otherwise the routerLink will try to find a property with that name.-->
<a [routerLink]="'/servers'">Servers</a>
<!--In the below example we pass in an array to the routerLink. It will help us create complicated routes. In the below exaple it will resolve to a link of /server/something-->
<a [routerLink]="['/server','/something']">special Server</a>
```

Note: Using `routerLink` in the anchor tag and not using a relative link direclty with `href` will prevent the default behaviour of the browser form reloading the complete page.

If we use the `href` the whole page will be reloaded and the state of our application might be lost. This can lead to unexpected behaviour that needs to be prevented.

Note: If we use 'servers' directly without `/` we will have a relative path. So on a servers page we have another link with a relative routerLink to as defined above the link will become `servers/servers` that is if we give the routerLink relative path without the `/`, that path will simply be appended to the current path of the component and not be the path that we have defined.

Useing relative path in routerLinks is not bad but we have to know that we define it properly to activate the path we want.

Relative path for routerLink can be defined as if we were accessing a file structure in terminal using `../` and `./` as it works in terminal.

* `routerLinkActive` and `routerLinkActiveOptions`:

`routerLinkActive` will add the class to the anchor tag whenever the link is active.

`routerLinkActiveOptions` : The '' or empty route is always avtive for all routes as it gets matcher for all routes. So want to add options to the routerLinkActive directive so that only the exact path is matched and only then the class is set to active.

```html
<li routerLinkActive="active">
    <a routerLink="/">Home</a>
</li>
<li routerLinkActive="active" [routerLinkOptions]="{exact: true}">
    <a routerLink="/servers">servers</a>
</li>
<li routerLinkActive="active">
    <a routerLink="/something">something</a>
</li>
```

* Loading Routes from Script

```html
<button class="btn btn-primary" (click)="onLoadServers()">Servers</button>
```

```ts
//--Change 1 Use Primary path.

import { Route } from '@angular/router'

export class HomeComponent implements OnInit{
    //other code here

    constructor(private router: Router, private route: ActivatedRoute){}

    onLoadServers(){
        //Some algorithm here
        this.route.navigate(['/servers'])
    }

    //In this we will use a relative route. Unline routerLink the script does not know the current route and using relative route the route is appended to the root, thus we have to specify the route we want to be relative to.
    //this.route will give the script the currently loaded path.
    onLoadServersSomething(){
        this.router.navigate(['something'], {relativeTo: this.route});
    }
}
```

* Passing Parameter to Route

`{ path: 'users/:id/:name', component: UserComponent }`

In the above code `:` is used to attach a dynamic parameter to the route.

Both id and name are parameters of the route.

* Fetching dynamic Path segment that we create above :

```ts
//Other imports here
import { ActiatedRoute, Params } from '@angular/router';

//Metadata with @Componenet here
export class UserComponent implements OnInit{

user:{id: number, name: string};

constructor(private route: ActivatedRoute){}
}

ngOnInit(){
    this.user = {
        id: this.route.snapshot.params['id'],
        name: this.route.snapshot.params['name']
    };

    //The above approach is good if we know that the data from the route is not going to change form within the componenet itself as angular will not reload the page to reflect the changes as we define the code in ngOnInit.
    //But if we have code that changes the data from within this component and we want to load the component again with that data we have to use an observable with the code defined above to know when the data on the url changes.
    //The route.params returns an observable and can be subscribed to, to get data whenever it changes.
    this.route.params.subscribe(
        (params: Params) => {
            this.user.id = params['id'];
            this.user.name = params['name'];
        }
    );
}

```

In the above example we do never unsubscribe from our subscriptions. It would not effect this as angular will unsubscribe for us when the component is destroied.

But we can explicitly describe in our code when we want to unsubscribe, in the above case we want to unsubscribe when the component is destroied.

In normal programs using rxjs we will always have to explicitly unsubscribe to our subscription.

```ts
//Only Changes to the above code

//Assign the subscription to a varible
paramsSubscription: Subscription;

ngOnInit(){
    //user code with snapshot
    this.paramsSubscription = this.route.params.subscribe(
        (params: Params) =>{
            //code as above
        }
    )
}

ngOnDestroy(){
    this.paramsSubscription.unsubscribe();
}
```

* Using Query Paramters

Both queryParams and fragment are properties of the routerLink itself.

There can only be one fragment per routerLink but there can be multiple queryParams.

```html
<a
    [routerLink]="['/servers',5, 'edit']"
    [queryParams]="{allowEdit: '1'}"
    fragement="loading"
    href="#"
>
```

We can get the paramters and the fragements by injecting `ActivatedRoute` and use the `route.snapshot.fragment` and `route.snapshot.queryParams` to retrive the current paramters and fragment.

As discussed above we only want to use `snapshot` if we know that the data of fragment or queryParams is not going to change from within the component, and if it is going to change we want to use the subscription methods as discussed in the previous examples.

* Using The QueryParams In our script file:

`this.router.navigate(['edit'], {relativeTo: this.route, queryParamsHandling: 'preserve or merge'});`

In the above piece of code we use the `relativeTo` to set the path `edit` relative to the current path and `queryParamsHandling` to `preserve` to preserve the same queryParameters or `merge` to add the new QueryParameters.

### WildCard Routing and Redirecting

* `redirectTo` :

```ts
{ path: 'not-found', component: PageNotFoundComponent },
//With this if we visit /something path we will be redirected to /not-found path.
{ path: 'something', redirectTo: '/not-found' },
//Also Since the default matching strategy is "prefix" , Angular checks if the path you entered in the URL does start with the path specified in the route. Of course every path starts with ''  (Important: That's no whitespace, it's simply "nothing").This route will now ALWAYS redirect you. So we add the pathMatch to full so that angular matches the full path.
{ path: '', redirectTo: '/somewhere-else', pathMatch: 'full' }
//To cover all the path that are not defined we use **, it is called the Wildcard Route.
{ path: '**', redirectTo: '/not-found' }
//Note that we want to place the wildcard route at the last as it will match and always redirect.
```

### Child Or Nested Routers

```js

//In the app.module.ts file where we define routes as above

const appRoutes: Routes = [
    { path: '', component: HomeComponent },

    { path: 'users', component: UserComponent, children:[
        { path: ':id/:name', component: UserComponent }
    ] },

    { path: 'servers', component: ServersComponent, children: [
        {path: ':id', component: ServerComponent },
        {path: ':id/edit', component: EditServerComponent }
    ] }
];
```

Now we have our main `<router-outlet>` where we have entry point for our main routes and whenever we have a `<router-outlet>` in the component loaded from the main routes, they will be the entry point for our child routes.

There are no special properties to the router-outlet where the child path are loaded, just the placement of thse in the component loading them is how angular determines children of which route can be loaded.

### Defining route Module outside of the app.module.ts file

```ts

const appRoutes: Routes = [
    //All our routes here
]

@NgModule({
    imports: [
        RouterModule.forRoot(appRouters)
    ],
    exports:[RouterModule]
})
export class AppRoutingModule{

}

//We have created our custom routing module above but it also need to be added to the app.module.ts file to the imports array.
imports: [
    //all other imports
    AppRoutingModule
]
```

## Route Guards

### CanActivate

```ts
//File named auth-guard.service.ts

import{ CanActivate, ActivatedRouteSnapshot, RouteStateSnapshot } from '@angular/router';
import{ Observanle } from 'rxjs/Observable';

@Injectable()
export class AuthGuard implements CanActivate{

    constructor(private authService: AuthService, private route: Router)

    //The arguments to the canActivate methods are passed by angular when we try to activate the route the gurad is put on, just before it is activated.
    canActivate(route: ActivatedRouteSnapshot, state: RouterStateSnapshot): Observable<boolean> | Promise<boolean>| boolean{
        return this.authService.isAuthenticated()
            .then(
                (authenticated: boolean) => {
                    if(authenticated){
                        return true;
                    }else{
                        this.router.navigate(['/']);
                    }
                }
            );
    }
}

//AuthService file
export class AuthService {
    loggedIn = false;

    isAuthenticated(){
        const promise = new Promise(
            (resolve, reject) => {
                setTimeout(()=>{
                    resolve(this.loggedIn)
                }, 800);
            }
        );
        return promise;
    }
}

//Add the services that we created to the app.module.ts to the providers array
providers: [/*Other services*/, AuthService, AuthGuard]

//AppRoutingModule
{ path: 'servers', canActivate: [AuthGuard], component: ServerComponent, children:[/*Children path here*/]}

//Not that when we put canActivate on the parent route we also add it to all the children automatically.
```

### Protecting Children

In the above code we protect the parent path and the children path with it, but if we want to only protect the child route and still be able to access the parent route we can add `canActivateChild` to our AuthGuard file.

```ts
//This code adds to the above code. We keep the above code same as is.
canActivateChild(route: ActivateRouteSnapshot. state: RouterStateSnapshot):Observable<boolean>| promise<boolean>|boolean{
    //We use te canActivate method as the we wnat to keep the logic the same.
    return this.canActivate(route, state);
}

//Now we want to remove the canActivate from the route and put in canActivateChild in its place
{ path: 'servers', canActivateChild: [AuthGuard], component: ServerComponent, children: [/*Children path here*/]}

```

## Observable

Observable and Observer are provided by rxjs and not by angular itself.

All the observable that are given by Angular are managed by angular and Angular will unsubscribe the observable when we are done using the observable, so we dont have to explicitly unsubscribe to the Observable.

* Creating our own observable

```ts
import { interval, Subscription } from 'rxjs'

export class HomeComponent implements OnInit {
    //othe code

    private firstObsSubscription: Subscription;

    //This is a simple observable but it is not build from ground up. It is just for an example.
    ngOnInit(){
        this.firstObsSubscription = interval(1000).subscribe(count => {
            console.log(count);
        });
    }

    ngOnDestroy(){
        this.firstObsSubscription.unsubscribe();
    }
}
```

* Creating Observable from scratch

Now we create our own observable from scratch that does the same task as the above example.

```ts
//All the class description code here

private firstObsSubscription: Subscription;

ngOnInit(){
    const customIntervalObservable = Observable.create(observer = {
        let count = 0;
        setInterval(( => {
            observer.next(count);
            count++;
        }, 1000);
    });

    //Here we subscribe to our observable and we get the count ever 1000ms.
    this.firstObsSubscription = CustomIntervalObservable.subscribe(data => {
        console.log(data);
    });

    ngOnDestroy(){
        this.firstObsSubscription.unsubscribe();
    }
}
```

* Errors and Completion

Whenever an error is thrown from the Observable the subscription ends.

* Operterators

> TODO : Add rxjs Notes.

## Forms

There are two Approaches that angular offeres to handle forms.

1. Template Driven : Angular Infers thte form Object from the DOM.

2. Reactive : From is created programmatically and synchronized with the DOM.

### Template Driven Forms

Import FormsModule in the NgModule -> imports[] -> FormsModule in the app.module.ts file to use the approach.

Angular does not detect the form controls automatically so we have to make angular aware of the form control. This is done by using `ngModel` which is a part of FormsModule.

```html
<input type="text" id="username" class="form-control" ngModel name="username">
```

`name` is a property of the html element and not of angular. It will be used by angular to identify the element. ngModel will tell angular that this is a form control.

```html
<form (ngSubmit)= "onSubmit(f)" #f= "ngForm">
    <!--Our html form here as shown above-->
</form>
```

Submitting a Form.

The `ngSubmit` takes over the submit functionality of the HTML form, which is present by default, and gives us the control to submit the from as we want from our script. We pass in the local reference of the form to the submit method to use it to get the values that angular parsed for us.

We put a *local Reference* to the from above and assign it to the `ngForm` which will give us the access to the from object that angular created for us and makes it easy for us to access the values of the form.

```ts
import { NgFrom } from '@angular/froms';

export class AppComponent{

    //Other code here

    onSubmit(from: NgFrom){
        //This will print the the form object to the console and we can see all its properties.
        console.log(form);
    }
}
```

* Accessing from with `@ViewChild` as we have see before to access the *Local Reference* on the form.

This method of getting the form objects helps us access the data that the form contains at any time **before the from is submitted**.

```ts
export class AppComponent{
    @ViewChild('f') signupForm: NgFrom;

    onSubmit(){
        console.log(this.signupForm);
    }
}
```

* **Validation**

Some Build in properties of the HTML like required can be used to validate the form.

There are also directive provided by angular that can be used to validate the form input such as email.

The are not a definitive check though as the front end application can be tricked, there should always be validation of data on server side so that we dont get invalid data in our persistance.

* [Build in validators](https://angular.io/api/forms/Validators) : These are all built-in validators, though that are the methods which actually get executed(and which can be add when using the reactive approach).

* [Build in directives](https://angular.io/api?type=directive) : Everything marked with "D" is a directive and can be added to your template.

Additionally, you might also want to enable HTML5 validation (by default, Angular disables it). You can do so by adding the `ngNativeValidate`  to a control in your template.

* NgModel :

NgModel can be used with local reference to the form control.

We can also have a default value for the control including `<Select>` as shown below.

`[NgModel]="pet"`

The above example above shows one way binding and we can also use NgModel with two way binding.

`[(ngModel)]= "answer"` : answer is a property of the script that the html element is placed on.

We can then use interpolation else were where we want to print the value of the answer property.

* Grouping from Controls

We can put `ngModelGroup="controlGroup"` on a div that holds the form controls that need to be grouped.

This will create a individual object like the form object that we get for the group and thus we can assess the validity of the from and values of the group independently.

We can also put a Local Reference on the group div and get access to the group object in our script as well as other places in the template itself.

* Setting an patching values

We can set default valies to our from controls, by using the `patchValue` method of `form`.

```ts

const suggestedName = 'SuperUser';

this.signupForm.form.patchValue({
    userData: {
        username: suggestedName
    }
});
```

The above approach to set the value for the form on a event will not reset the whole form, just set the value of the form element that we want to target.

The Other approach might be to set the value directly by using `this.signupForm.setValue({})` and pass in the object with the values that we want ot add to our from, but it will reset the form and thus all the values that the user had entered and thus the above approach is much more convenient and useful in most cases.

* Resetting Form

`this.signupForm.reset();` this will reset the form to empty as if the page was reloaded and the form was never used.

If we want the form to have defualt values set as we set wtih `setValues`, we could pass in the object to the reset property and the default values will be set as if we were to use the setValues property after the form is reset.

### Reactive Approach

In the reactive approach we create the from programatically.

In NgModules we need `ReactiveFromsModule` to be added to the `imports[]`. We do not need the NgFormModule that we used in the previous template driven apprach.

```ts
import { FormGroup, FromControl } from '@angular/froms'

//@Component here
export class AppComponent implement onInit{

    gender = ['male', 'female'];

    signupForm: FormGroup;

    //Creating our from.
    ngOnInit(){
        this.signupForm = new FormGroup({
            'username': new FromControl(null),
            'email' : new FormControl(null),
            'gender': new FormControl('male') //Here we set a default initialization value for our form control.
        });
    }
}
```

Synchronize our script from with the HTML from in our html template.

```html
<form [formGroup="signupFrom"] (ngSumbit)="onSubmit()">
    <div>
        <label for="username">UserName</label>
        <input type="text" id=" username" formControlName="username" class="form-control">
    </div>
     <div>
        <label for="email">Email</label>
        <input type="text" id=" email" formControlName="email" class="form-control">
    </div>
    <div ckass="radio" *ngFor="let gender of genders">
        <label>
            <input type="radio" [value]="gender" fromControlName="gender">{{gender}}
        </label>
    <div>
</form>
```

In the above html code we attached or linked our script Form object with the HTML template containing the Form control component. We use formControlName to connect the respective HTML form elements with the Object in script.

* Submitting Form

As we create the from object in the script it self we already have access to the from object in the script.

We still add the `ngSubmit` to the form to get the final values.

```ts
onSubmit(){
    //This is the form we created in the script above in the ngOnInit  method.
    console.log(this.signupForm);
}
```

* Adding Validation In the Reactive Approach

As we dont configure our html form elements in our HTML template, adding validator to the HTML template code does not work in the case of reactive aproach.

We can validate the input from a form control by passing an array of `Validators` as the second argument to the `FormControl` with first being the default value for that element.

Validators provides us with the methods for different validations and we can get them from the Vallidators class, but we dot call them we just pass the reference to the validator methods, that is we dont add `()` at the end of them, Angular calls or executes the methods when it needs to.

We import `Validators` from `@angular/froms`

`'email': new FormControl(null, [Validators.required, Validators.email]);`

* Showing message if the form is Invalid

```html
<span *ngIf="!signupFrom.get('email').valid && signupForm.get('email').touched" class="help-block">Please Enter a valid Email Address
</span>
```

Note : If we want to specifically change some css for some property, the class are added to the html element accroding to its state such as `ng-untouched ng-pristine ng-invalid` and many others.

* Grouping Control

We can have nested from groups to create groups of from elements as we did in the Template Approach.

For this we just nest `FormGroup` in the main `FromGroup` and put the properties representing the html elements in the object in this new FormGroup.

We also need to add all the html element that we add to the from group in our script object to be put in a HTML element `<div formGroupName="userData">`. Here userData is the name of the group that we used in our script.

* FromArray

> TODO : Dynamically adding FormControl and FromArray Lecture 209

* Creating Custom Validator

```ts

//As forbiddentNames will be called by angular to check the validity from outside of this calls the `this` keyword wont work. To bind the this keyword to this class we use bind where we call the method.

'username' : new FormControl(null. [Validators.required, this.frobiddenNames.bind(this)]),

//The above code is a part of the signupFrom.

const forbiddenUserName = ["Adwait", "Abhi"];

forbiddenNames(control: FormControl):{[s: string]: boolean}{
    if(this.forbiddenUsernames.indexOf(control.value) !== -1){ //The value will return a -1 and -1 will be interpreted as true as a value exist by javascript. So we explicitly tell it to check if it is -1 then we want it to be false
        return{'nameIsForbidden': true};
    }
    //We have to return null or empty if the validation fails. We dont wnat to pass the object above with a false value.
    return null;
}

```

* Using Error Codes

In the form object angular will add the validation error in the error property of the object of the individual FormControl. Angular may or may not add it to the overall form error.

To check what is contained in the error we might want to console.log the from and check for the error values of the from object.

* Async Validations

We sometimes want our validations to come from the server, for example check if the email already exist, in this case we want to have a asyc Validator.

Async validators are passed as the third argument to a FormControl Object as an array of as many async validator as we need.

If `this` is used in the validator as above, we want ot bind the this to this from our class where we use it as shown above, as angular will execute this method ourside of the class where this will not be availabe and we will have an error.

```ts
forbiddenEmails(control: FromControl): Promise<any> | Observable<any>{
    //We create a new Promise here that will be returned by the validator. This is just an example we use setTimeout here but in real programs where we validate data at server we will have a http request that might return a promise or an Observable.
    const promise = new Promise((resolve, reject) => {

        setTimeout(()=>{
            if(control.value === 'test@test.com'){
                resolve({'emailIsForbidden': true});
            }else{
                resolve(null);
            }
        }, 1500);
    });
    return promise;
}

```

* Reacting to Status and Value Changes

```ts
this.signupFrom.valueChanges.subscribe((value=>{
    //This will print our the object that is the from every time there is a change in any of the value of any of the element in the object.
    console.log(value);
}))

//Similar to valueChange we have status change that return ths status of the form on whether the form is valid or not.

this.signupForm.statusChanges.subscribe((value=>{
    console.log(value);
}))
```

These can also be applied on individual from controls.

* Setting and Patching Values

We can update our from on our own by using setValue and patch value as we did in the Template Approach.

```ts
this.signupFrom.setValue({
    //the whole from object with set value for example we set the gender
    'gender' : 'male',
    //and so on fro every property of this form object.
})

this.signupForm.patchValue({
    'userData' : {
        'username': 'Anna'
    }
})
```

* Reset From

Like we used in the Template Approach we also can use reset as `this.signupForm.reset();` and if we want to set any values to initiate the form after it has already been cleared we can pass a object containing the values to the reset method.

## Pipes

Transfrom output in our template.

* Adding parameters to pipe :

We can add parameters to a pipe by adding `:` after the name of the pipe.

`{{ server.started | date:'fullDate" }}`

* Chaining Multile pipes :

The order of the pipes is important. They are parsed from left to right.

`{{ server.started | date:'fullDate | uppercase }}`

* Create Custom pipes

`ng g p shortenpipe`

```ts
//FileName : shorten.pipe.ts

import { Pipetransfrom } from '@angular/core';

@Pipe({
    name: 'shorten'
})
export class ShortenPipe implements PipeTransfrom{

//Transform gets the value of interpolated string from our HTML template.
    transfrom(value:any, limit: number){
        return value.substr(0,number);
    }
}

//The limit here is a paramter for our pipe that can be passed as we saw for the inbuild pipes above.

//We need to aadd pupes to declarations array of NgModules of the app.module.ts
```

* Async Pipes

```js
//this is a methods in our component string
appStatus = new Promise((resolve)=>{
    setTimeout(()=>{
        resolve('stable');
    }, 2000);
});
```

```html
<h2> App Status: {{ appStatus | async }}</h2>

```

We use the async pipe as we know after some time the promise will be resolved and the data will be assigned to appStatus.

When we add a async to a object that is a promise or an Observable it automatically subscribes and in case or promises wait for the data to be resolved and then display data once the data is avaible.

## HTTP Requests

[Official Documents HTTP requests](https://angular.io/guide/http)

* We can set up BackEnd with Firebase.

### Post Requests

> Note : Add `HttpClientModule` to `imports[]` of `@NgModule` in the file `app.module.ts` by importing it from `@angular/common/http`

```ts
import { HttpClient } from '@angular/commom/http';

export class AppComponent implement OnInit{

    constructor(private http: HttpClient){}

    onCreatePost(postData:{ title: string; content: string}){

        //Send the request
        //We pass postData as the body and angualar will convert the object into a JSON when it is being send as REST apis need JSON data as the body.
        //This by itself will not send the request. The http post will return a observabel and the data is not send until we subscribe to the Observable.
        //this.http.post('https://ourURL', postData);
        this.http.post('https://resourceURL', postData).subscribe((responseData)=>{
            console.log(responseData);
        });
    }

}
```

Post with error handling and service.

```ts
//In our service file
CreateAndStorePost(title: string, content: string) {
  const postData: Post = { title: title, content: content };
  this.http
    .post<{ name: string }>(
      'https://ng-complete-guide-c56d3.firebaseio.com/posts.json',
      postData
    )
    .subscribe(
      responseData => {
        console.log(responseData);
      },
      //The second argument to the subscription is error handling
      error => {
        this.error.next(error.message);
      }
    );
}

//Our component file

onCreatePost(postData: Post) {
      // Send Http request
  this.postsService.createAndStorePost(postData.title, postData.content);
}
```

### Get Requests

```ts
private fetchPosts(){
    this.http.get('https://resourceURL').subscribe((post)=>{
        console.log(posts);
    })
}
```

We could outsource our data handling to a service and then subscribe to the data in our Component as it would be easier to manage as our app gets bigger.

We also handle the error that we might get

```ts
//In our service file
import { Injectable } from '@angular/core';
import { map, catchError } from 'rxjs/operators';
import { Subject, throwError } from 'rxjs';
import { HttpClient } from '@angular/common/http';

fetchPosts() {
  return this.http
    .get<{ [key: string]: Post }>(
      'https://ng-complete-guide-c56d3.firebaseio.com/posts.json'
    )
    .pipe(
      map(responseData => {
        const postsArray: Post[] = [];
        for (const key in responseData) {
          if (responseData.hasOwnProperty(key)) {
            postsArray.push({ ...responseData[key], id: key });
          }
        }
        return postsArray;
      }),
      catchError(errorRes => {
        // Send to analytics server
        return throwError(errorRes);
      })
    );
}

//In our component file
import { Component, OnInit, OnDestroy } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { map } from 'rxjs/operators';
import { Subscription } from 'rxjs';

//Variables
loadedPosts: Post[] = [];
isFetching = false;
error = null;
private errorSub: Subscription;

onFetchPosts() {
// Send Http request
    this.isFetching = true;
    this.postsService.fetchPosts().subscribe(
      posts => {
        this.isFetching = false;
        this.loadedPosts = posts;
      },
      error => {
        this.error = error.message;
        console.log(error);
      }
    );
}
```

### Transfroming data with Observables

```ts
import { map } from 'rxjs/operators';

private fetchPosts(){
    this.http.get('https://resourceURL').pipe(map(responseData => {
        const postArray = [];
        for(const key in responseData) {
            //We wnat to check the json data that we get from the get request has a key named key.
            if(responseData.hasOwnProperty(key)){
                //We push the data to that is key value pairs to the array that we created by using the spread operator.
                //Also add the id that we could use to uniquely identify the data that we get.
                postsArray.push({ ...responseData[key], id: key });
            }
        }
        return postArray;
        //The returned value will not be forwarded to the subscribe method.
    })).subscribe((post)=>{
        console.log(posts);
    })
}
```

* Using types with HTTP Request

We can add the type to the HTTP request methods by adding `post<type>` or `get<Type>`. The request methods are called as generic methods.

* Sending Delete Request

```ts

//This is in our service file that fetches the data and we return an observable from here that we can subscribe to in our component file where we need the data.
deletePosts(){

   return this.http.delete('https://resourceURL');
}

//This is in our Component file where we want the data and we subscribe to the Observable to get the data.
onClearPosts(){

    this.postService.deletePosts().subscrbe(()=>{
        this.loadedPosts = [];
    });
}
```

### Handling Errors

* Directly handling error when we subscibe in the component.

```ts
onClearPosts(){

    this.postService.deletePosts().subscrbe(()=>{
        this.loadedPosts = [];
    },
    //Here subscribe takes a second argument that represent the error. If an error occurs we will get the error as data for our subscription here and we can handle it as we want below.
    error=>{
        this.error = error.message;
        //The error might be an object depending on the backend server that we are using.
        console.log(error);
    });
}
```

* HTTP Headers

THe last paramter to any HTTP request like post, get, delete takes an object. The object can take query paramters, headers etc.

We put our headers in that object as a key and pass in a `new HttpHeaders({key: value, key: value})` to that key.

This will set our headers for our request with the required default headers if we do not specify them.

* Params with HttpRequests

In the last object that we pass to the request we add a `params: new HttpParams().set('print', 'pretty')`.

In the above we add print as the key and pretty as the value. We can add multiple such key value pairs.

* `observe`

We can also pass `observe: 'response'` to the object that takes header to get the whole response with headers, status and body of the response that we get from the server. The default value of observe is body and body thus gets parsed to json.

`observe` can also have a value of event, which will tell us about the event like request was 'sent', 'response' and some-others.

* `responseType` Used to tell the observable what type of data we get in response.

### Interceptors

They can be used to change or modify a request before it is send. So for example we can change the request headers before any request is send. This might be useful if we are enforcing an authentication system and want to send a authcode in the header.

We can not only interact with the outgoing request but also with the incoming response of all the request.

> Note : When we have multiple interceptor the order in which the interceptor are declared in  the `providers` array will be the order that they are exected in.

```ts
//Before we can use interceptor in our application we have to configure them in our app.module.ts file.
import { HttpClientModule, HTTP_INTERCEPTORS } from '@angular/common/http';
//In the @NgModule
  imports: [BrowserModule, FormsModule, HttpClientModule],
  providers: [
    {
      provide: HTTP_INTERCEPTORS,
      useClass: AuthInterceptorService,
      multi: true
    },
    {
      provide: HTTP_INTERCEPTORS,
      useClass: AuthInterceptorService,
      multi: true
    }
  ]

//In our auth-interceptor.service.ts file
import {
  HttpInterceptor,
  HttpRequest,
  HttpHandler
} from '@angular/common/http';

export class AuthInterceptorService implements HttpInterceptor {
    //The next.handle method sends the request further to what it should have done if interceptors was not present.
  intercept(req: HttpRequest<any>, next: HttpHandler) {
    //As the Httprequest object that we get 'rep' in the case is immutable, hence we clone that object and then return our newly created and modified object back.
    const modifiedRequest = req.clone({
      headers: req.headers.append('Auth', 'xyz')
    });
    return next.handle(modifiedRequest);
  }
}

//In our logging-interceptor
export class LoggingInterceptorService implements HttpInterceptor {
  intercept(req: HttpRequest<any>, next: HttpHandler) {
    console.log('Outgoing request');
    console.log(req.url);
    console.log(req.headers);
    return next.handle(req).pipe(
      tap(event => {
        if (event.type === HttpEventType.Response) {
          console.log('Incoming response');
          console.log(event.body);
        }
      })
    );
  }
}
```

## Angular Modules

[Official Docs](https://angular.io/guide/ngmodules)

[NgModules FAQ](https://angular.io/guide/ngmodule-faq)

We can split our angular app into different Angular modules to make the app leaner and more importantly to use the lazy loading features for reduced initial size of our application and loading different modules as the user needs them.

> Note 1 : Browser Module needs to be imported only once in our project in the main module file. If we want to use ngFor and ngIf we `import { CommonModule } from '@angular/common'`.
> Note 2 : Services do not need to be imported in our custom module as they are avaible app wide, that is they are all setup at the root.

### Separating Modules and it Routes

```ts
//Create a module.ts file for the part of the app that need to be separated. Here we take the example of recipies.
//recipies.module.ts
import { NgModule } from '@angular/core';//Import to set the meta data for the module.
import { CommonModule } from '@angular/common';//As stated above in notes, to use ngfor and similar directives.
import { RouterModule } from '@angular/router';
import { ReactiveFormsModule } from '@angular/forms';//As we use reactive form in the module and the reactiveforms import decalared in the app.module.ts file does carry to this file we have to put this import again in the import array for this module.

import { RecipesComponent } from './recipes.component';
import { RecipeListComponent } from './recipe-list/recipe-list.component';
import { RecipeDetailComponent } from './recipe-detail/recipe-detail.component';
import { RecipeItemComponent } from './recipe-list/recipe-item/recipe-item.component';
import { RecipeStartComponent } from './recipe-start/recipe-start.component';
import { RecipeEditComponent } from './recipe-edit/recipe-edit.component';

@NgModule({
  declarations: [
    //All the components that are a part of the module are declared here and can be removed from the app.module.ts file.
    RecipesComponent,
    RecipeListComponent,
    RecipeDetailComponent,
    RecipeItemComponent,
    RecipeStartComponent,
    RecipeEditComponent
  ],
  //All the imports of directives, pipes and modules have to be set again in our separated component as these will be carried from the app.module.ts file that we set for our whole app.
  //Our module is independent of the app and all imports have to be declared. Only services are app wide and do not have to be imported again. Hence the HttpClientModule does not need to be imported here again.
  imports: [RouterModule, CommonModule, ReactiveFormsModule],
  //We export all the components as they will be used in our main files
  exports: [
    //As our module has its own router we dont need to export the components our of the Module.
    //We would only want to export the component if we were using the components outside of this module that we created or if we had set the routing for the module in our main app routing file.
    // RecipesComponent,
    // RecipeListComponent,
    // RecipeDetailComponent,
    // RecipeItemComponent,
    // RecipeStartComponent,
    // RecipeEditComponent
  ]
})
export class RecipesModule {}

//We also want to separate Routing for our module.
//recipes-routing.module.ts
import { NgModule } from '@angular/core';
import { Routes, RouterModule } from '@angular/router';

import { RecipesComponent } from './recipes.component';
import { AuthGuard } from '../auth/auth.guard';
import { RecipeStartComponent } from './recipe-start/recipe-start.component';
import { RecipeEditComponent } from './recipe-edit/recipe-edit.component';
import { RecipeDetailComponent } from './recipe-detail/recipe-detail.component';
import { RecipesResolverService } from './recipes-resolver.service';

//We create routes object.
const routes: Routes = [
  {
    path: 'recipes',
    component: RecipesComponent,
    canActivate: [AuthGuard],
    children: [
      { path: '', component: RecipeStartComponent },
      { path: 'new', component: RecipeEditComponent },
      {
        path: ':id',
        component: RecipeDetailComponent,
        resolve: [RecipesResolverService]
      },
      {
        path: ':id/edit',
        component: RecipeEditComponent,
        resolve: [RecipesResolverService]
      }
    ]
  }
];

@NgModule({
    //We export the routes object and export the route.
  imports: [RouterModule.forChild(routes)],
  exports: [RouterModule]
})
export class RecipesRoutingModule {}

//recipes.component.html
<div class="row">
  <div class="col-md-5">
    <app-recipe-list></app-recipe-list>
  </div>
  <div class="col-md-7">
    <router-outlet></router-outlet>
  </div>
</div>

//app.module.ts
import { BrowserModule } from '@angular/platform-browser';
import { NgModule } from '@angular/core';
import { FormsModule, ReactiveFormsModule } from '@angular/forms';
import { HttpClientModule, HTTP_INTERCEPTORS } from '@angular/common/http';

import { AppComponent } from './app.component';
import { HeaderComponent } from './header/header.component';
import { ShoppingListComponent } from './shopping-list/shopping-list.component';
import { ShoppingEditComponent } from './shopping-list/shopping-edit/shopping-edit.component';
import { DropdownDirective } from './shared/dropdown.directive';
import { ShoppingListService } from './shopping-list/shopping-list.service';
import { AppRoutingModule } from './app-routing.module';
import { RecipeService } from './recipes/recipe.service';
import { AuthComponent } from './auth/auth.component';
import { LoadingSpinnerComponent } from './shared/loading-spinner/loading-spinner.component';
import { AuthInterceptorService } from './auth/auth-interceptor.service';
import { AlertComponent } from './shared/alert/alert.component';
import { PlaceholderDirective } from './shared/placeholder/placeholder.directive';
import { RecipesModule } from './recipes/recipes.module';

@NgModule({
//We remove the Component of recipe from the declarations
  declarations: [
    AppComponent,
    HeaderComponent,
    ShoppingListComponent,
    ShoppingEditComponent,
    DropdownDirective,
    AuthComponent,
    LoadingSpinnerComponent,
    AlertComponent,
    PlaceholderDirective
  ],
  imports: [
    BrowserModule,
    FormsModule,
    ReactiveFormsModule,
    HttpClientModule,
    AppRoutingModule,
    RecipesModule
  ],
  providers: [
    ShoppingListService,
    RecipeService,
    {
      provide: HTTP_INTERCEPTORS,
      useClass: AuthInterceptorService,
      multi: true
    }
  ],
  bootstrap: [AppComponent],
  entryComponents: [
    AlertComponent
  ]
})
export class AppModule {}

//app-routing.module.ts
//We removed the route of all the recipe
import { NgModule } from '@angular/core';
import { Routes, RouterModule } from '@angular/router';

import { ShoppingListComponent } from './shopping-list/shopping-list.component';
import { AuthComponent } from './auth/auth.component';

const appRoutes: Routes = [
  { path: '', redirectTo: '/recipes', pathMatch: 'full' },
  { path: 'shopping-list', component: ShoppingListComponent },
  { path: 'auth', component: AuthComponent }
];

@NgModule({
  imports: [RouterModule.forRoot(appRoutes)],
  exports: [RouterModule]
})
export class AppRoutingModule {}

//app.component.html
<app-header></app-header>
<div class="container">
  <div class="row">
    <div class="col-md-12">
      <router-outlet></router-outlet>
    </div>
  </div>
</div>

```

### Shared Modules

Shared modules are just modules as we declared above but containing the parts that are being shared by multiple modules in our project.

They declare and export these parts so we can import this shared module and use these components, directives or pipes.

> Note : All the components, directive, pipes and other parts that we create for our application should only be declared once in the application. So we cannot declare a component in the app.module.ts and also in shared.module.ts that we create.

In such a condition we just have to have the shared modules declared in the shared modules file and import the shared modules in the app.modules.ts in imports array.

### Core Module

This is used to make our main app.module.ts file leaner by declaring the providers in a different file that is the Core Modules file and then importing the module in the app.module.ts file.

> Note : If we are declaring a service with `@Injectable({ providedIn: 'root' }), then the service is already available everywhere in the project and is a prefered way of declaring a service, and does not need to be included in the provides of either the app.modules.ts or in Core module that we might create.

## Lazy Loading And other Optimizations

This is used for optimization.

We need multiple modules, that is our app should be divided into multiple modules to take advantage of Lazy Loading.

This will help us bundle the code in smaller parts and download only the required files when we start the code and as we use.

> Note : The example below shows the modern way of declaring route for lazing loading in the appRoutes. For older version we can delcare it as `{ path: 'recipes', loadChildren: './recipes/recipes.module#RecipesModule' }`. Only use this if the using older version of angular and the new apprach does not work as this older appraoch will give errors and might even bug the application while using newer version of angular.

Things to check when lazy loading component :

* Declare the route path to the component that need to be lazy loaded as `{ path: 'recipes', loadChildren: ()=> import('./recipes/recipes.module').then(m=>m.RecipesModule)}`

* Remove the declaration of the component we are trying to lazy load from the app.module.ts file as we are trying to lazy load it and if we have a decalaration in the main file we will be trying to also actively load it.

* Now we chagne the path that point to 'recipes' in our Recipes.module.ts or recipes.routes.ts file to be ''(empty string) as we have added that route to our main routes file as shown above.

### Pre-Load LazyLoaded Modules

In app=routing.module.ts file where we declare our root routing we can declare a strategy on how and which modules are preloaded.

```ts
imports:[
    RouterModule.forRoot(appRoutes, { preloadingStrategy: PreloadAllModules });
]
```

### Services and Modules Relations

Service can be declared in the following scopes and places :

|Service Declaration|Available To Use At|Injector Used by Angular|When to Use|
|---|---|---|---|
| AppModules in providers | Service available app wide | Use root Injector | Should be default |
| AppComponent(or Other Component) | Service availabe in the component-tree | Use Component-specific Injector| Use if service is only relevant for component tree |
| Eager-loaded Modules | Service avaliable application wide | Use root injector | Avoid using this as it might be confusing for other developers |
| Lazy-Loaded modules | Service avaliable in loaded module only | Angular creates and uses child injector | Use if service should be scoped to loaded module |

When we use the @Injectable to declare a service in the root it has the same effect as if it was declared in AppModules providers array.

## Prepare Angular project For deployment

Use `ng build --prod` to compile the application and let angular perform the optimization that it can to get it production ready.

### Ahead of time compilation

Just-In-Time Compilation :

When we are developing our app the template code that is the html has part of angular specific commands that need to be complied so that our brower can display them as they should. These commands are complied during development at the time the app runs in our browser just before it is displayed by angular template compiler which is shipped with our code while development.

But this complier is big and should not be a part of our production application as it increases the size of our application significantly and thus increase load times.

Thus we use Ahead of time compliation to compile these files before we upload the application to the server to make the application production ready.

This removes the need for the angular just in time complier to be shipped wiht our production app making the size of our app payload significantly smaller and also does other optimization that make the overall file size of our files smaller.

## Setting Up Proxy Server

During development we could have our backend running online or on a different localhost port. When we send a http request to our backend through our brower the browser actually sends a *Preflight Request* which is a request with a header for the backend to check if the frontend application has permissions to send the request and whether the backend will allow the operation that the request will contain.

In many cases when we use Spring or many other backend frameworks this will not be supported as Spring does not allow preflight request and will give us rather the browser a CORS(Cross Origin Resource Sharing) error.

> Note : Postman will not get such errors because Postman does not send preflight requests but our browsers do.

To fix this we can set up a proxy server.

> Note : Proxy servers will only work during developement that is they work with `ng serve` which set up a developement server and not with `ng build`. So we have to change our backend if are going to host our frontend on a different domain than that of our backend. For Spring boot it can be done by using : `@CrossOrigin(origins = "http://localhost:4200")` over our `@RequestMapping`.

For an Indetail explanation on creating proxy Servers [visit](https://medium.com/better-programming/setup-a-proxy-for-api-calls-for-your-angular-cli-app-6566c02a8c4d).

* Create `proxy.conf.json` in our project root that is in the same folder as `package.json`.

* We write our proxy Configuration in the file.

```json

{
  "/api": {
    "target": "http://localhost:8080",
    "secure": false
  }
}
```

Now to start our development server with the proxy configuration we do `ng serve --proxy-config proxy.conf.json`.

We can set up `"start": "ng serve --proxy-config proxy.conf.json"` in our package.json so that we dont have to type it every time we want to start the server, we can just use `npm start` and npm will run the command for us.

## `ng-eject`

> From : [stackoverflow](https://stackoverflow.com/questions/44110064/what-is-the-purpose-of-ng-eject).

angular-cli is something magic, everything is done in a simple and automatic way.

But sometimes, you may want to act on how the package is done, add a plugin or you are simply curious to see the Webpack configuration on which it is based.

When running ng eject, you generate a webpack.config.json file. Looking at the file package.json you will see that the commands to launch have slightly changed:

`ng serve` --> npm start
`ng build` --> npm run build
`ng e2e`  --> npm run e2

If you want to undo `ng eject`, you will have to edit your .angular.cli.json file and set ejected to false:

```json
"project": { 
  ...
  "ejected": false
}
```

## Display code

`<div><code><pre>{{code1}}</pre></code></div>` could be used to display code frosm the script file.

Or

`<div [innerText]="code1"></div>` But innerHTML might be prone to XSS attacks, especially when the code in being injected by the user or by user input.

The altenative to innerHTML when we just want to render text and not execute the *markup*, we could use `textContent`. As we know we want the code to show and not have any markup execute from the html we could use this approach.

```js
// Renders a string with escaped characters
// This would show up in the DOM as <img src=x onerror="alert('XSS Attack')"> instead of as an image element
div.textContent = '<img src=x onerror="alert(\'XSS Attack\')">';
```

### Sanitizing content before adding it to the DOM

As we might want to use innerHTML we would have to sanitize the content that is run.
