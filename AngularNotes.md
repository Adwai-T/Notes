# Angular First Project :

The page that we see first when we run the app is the application shell. The shell is controlled by an Angular component named AppComponent.

Components are the fundamental building blocks of Angular applications. They display data on the screen, listen for user input, and take action based on that input.

* Create A new Project : `ng new name-of-project`.

* Create and start the development server and run the app in browser : `ng serve --open`.

* Set up the application wide css at src/styles.css.

* Create the Hero component : 

  `ng generate component heroes` or `ng g c heroes`.

  The CLI creates a new folder, src/app/heroes/, and generates the three files of the HeroesComponent along with a test file.

## Basic of components : 
You always import the Component symbol from the Angular core library and annotate the component class with @Component.

@Component is a decorator function that specifies the Angular metadata for the component.

The CLI generated three metadata properties:

1. selector— the component's CSS element selector
2. templateUrl— the location of the component's template file.
3. styleUrls— the location of the component's private CSS styles.

The CSS element selector, 'app-heroes', matches the name of the HTML element that identifies this component within a parent component's template.

The ngOnInit() is a lifecycle hook. Angular calls ngOnInit() shortly after creating a component. It's a good place to put initialization logic.

Always export the component class so you can import it elsewhere ... like in the AppModule.

## Adding the component: 
  app-heroes is the element selector for the HeroesComponent. So add an <app-heroes> element to the AppComponent template file, just below the title.
  `<app-heroes/>`.

### [Pipes](https://angular.io/guide/pipes) are a good way to format strings, currency amounts, dates and other display data. Angular ships with several built-in pipes and you can create your own.

## Two-way binding :
  [(ngModel)] is Angular's two-way data binding syntax.

  ```html
    <label>name:
    <input [(ngModel)]="hero.name" placeholder="name"/>
    </label>
  ```
####  Note : Although ngModel is a valid Angular directive, it isn't available by default. It belongs to the optional FormsModule and you must opt-in to using it.

## AppModule

Angular needs to know how the pieces of your application fit together and what other files and libraries the app requires. This information is called metadata.

Some of the metadata is in the @Component decorators that you added to your component classes. Other critical metadata is in @NgModule decorators.

The most important @NgModule decorator annotates the top-level AppModule class.

The Angular CLI generated an AppModule class in src/app/app.module.ts when it created the project. This is where you opt-in to the FormsModule.

## Declare HeroesComponent:

Every component must be declared in exactly one NgModule.

You didn't declare the HeroesComponent. So why did the application work?

It worked because the Angular CLI declared HeroesComponent in the AppModule when it generated that component.

Open src/app/app.module.ts and find HeroesComponent imported near the top.

### The `*ngFor` is Angular's repeater directive. It repeats the host element for each element in a list.

## Add a click event binding
Add a click event binding to the <li> like this:
  heroes.component.html (template excerpt) content_copy
  ```html
  <li *ngFor="let hero of heroes" (click)="onSelect(hero)">
  ```

This is an example of Angular's event binding syntax.

The parentheses around click tell Angular to listen for the <li> element's click event. When the user clicks in the <li>, 
Angular executes the onSelect(hero) expression.

### Hide empty details with *ngIf="Name-of-variable"

Use when a component usesa  variable that is initially empty and needs to be assigned by the activitys in the app.

When selectedHero is undefined, the ngIf removes the hero detail from the DOM. There are no selectedHero bindings to consider.

When the user picks a hero, selectedHero has a value and ngIf puts the hero detail into the DOM.

### `@Input() variable : variableType` is used to get the value of the variable from the parent into the client.

## Add services : 
Components shouldn't fetch or save data directly, they should focus on presenting data and delegate data access to a service.

### @Injectable() services : 
This marks the class as one that participates in the dependency injection system.

### Provide the HeroService
You must make the HeroService available to the dependency injection system before Angular can inject it into the HeroesComponent by registering a provider. A provider is something that can create or deliver a service; in this case it instantiates the HeroService class to provide the service.

To make sure that the HeroService can provide this service, register it with the injector, which is the object that is responsible for choosing and injecting the provider where the app requires it.

By default, the Angular CLI command ng generate service registers a provider with the root injector for your service by including provider metadata, that is providedIn: 'root' in the @Injectable() decorator.

```javascript
  @Injectable({
    providedIn: 'root',
  })
```

When you provide the service at the root level, Angular creates a single, shared instance of HeroService and injects into any class that asks for it. Registering the provider in the @Injectable metadata also allows Angular to optimize an app by removing the service if it turns out not to be used after all.


