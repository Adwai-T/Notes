# Angular

## Install

Requires Node for packing and optimize the project. Also npm will be used download all the dependencies and angualar cli itself.

## Bootstrap

Adding bootstrap to our angular project.

With bootstrap download the bootstrap dependency `npm install --save bootstrap@3`.

In angular.json in the root of our project, add the location of the bootstrap dependency.

In "styles" array add: `node_modules/bootstrap/dist/css/bootstrap.min.css"`.

## Components

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

This will create a new object of type EventEmmitter and we also pass in the type of object that the event emitter will emit.

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

---

## From Project : Special Use Cases

### Drop Down Directive

```ts
import {Directive, ElementRef, HostBinding, HostListener} from '@angular/core';

@Directive({
  selector: '[appDropdown]'
})
export class DropdownDirective {

  @HostBinding('class.open') isOpen = false;

  //This will also close the dropdown if we click at any other location in our app.
  @HostListener('document:click', ['$event']) toggleOpen(event: Event) {
    this.isOpen = this.elRef.nativeElement.contains(event.target) ? !this.isOpen : false;
  }
  constructor(private elRef: ElementRef) {}
}
```
