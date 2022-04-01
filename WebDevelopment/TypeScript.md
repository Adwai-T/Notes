# TypeScript

[Installing TypeScript](https://www.typescriptlang.org/)

We need typescript compiler that will convert our typescript code into javascript so that it can be run in the browser.

Invoking TypeScript Compiler will remove all typescript specific code and convert it into javascript that the browser can run. It will also display any errors in the code.

Typescript can also be used with nodejs in a similar way.

Invoking Typescript `npx tsc name-typescript-file.ts`.

## Type inference

```ts
//In tha below case ts will infere that the name variable is of type string, and we dont have to specify that it is a string explicitly.
let name = 'Adwait';

//this will give an error as the we initialized the varaible as string and typescript inferes that it will always store a string.
name = 1;
```

## Objects

```ts
//Describing an object
//This is not assignment it is definiation of the object
let person: {
  name:string;
  age:number;
};
//the we can assign as following
person = {
  name: 'Adwait',
  age:7
};

//We can also define array of objects as
let people: {
  name:string;
  age: number;
}[];

//Or we can use an Alias
type Person = {
  name: string;
  age: number
}

let person: Person;
let people: Person[];
```

## Functions

We can specify types for parameters and return value in the function.

```ts
function add(a:number, b:number) :number{
  return a + b;
}

//function return value could also be void for function that do not return any value..
function log(message:string): void{
  console.log(message);
}
```

## Other

If we know that the any value is not going to be null or undefined but the compiler can't eliminate null or undefined, we can use the **type assertion** operator to manually remove them.

The Syntax is postfix `!:`.

```ts
// If you are sure that these objects or fields exist, the
// postfix ! lets you short circuit the nullability
user!.email!.length;

//Or
let name!: string;
```
