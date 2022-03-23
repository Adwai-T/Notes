# Node package Manager

## Basic Commands

### Setting up

`npm init` : This will create the `package.json` and `package-lock.json` in the project folder. Now we can install packages from npm in the Directory/Project. It will walk us through basic inforamtion about the project that we can fill or skip.

`npm init --yes` : Skips all the inforamtion for initialization of npm, we can later update it in `package.json`

### Installing packages

`npm install package-name` : Intall packages locally.

`npm uninstall package-name` : Uninstalls local package.

`npm install --save-dev package-name` : Install package as developer dependency and will not be needed for running the application/program in production. Utility packages like webpack or developer server should be installed as developer dependencies.

`npm install -g package-name` : The package will be installed globally and can be used anywhere with npm. We want to only install packages that we want to use with multiple projects like clis, or project setups for react or angular globally.

### List of installed packages

We can look at the installed packages in `package.json`. We can look at all the packages with their dependencies in `package-lock.json`. But we can look at all the packages intalled in the current project directory by using `npm list` or `npm ls`.

`npm list --depth=0` : Shows all the installed packages in the current project without their dependecncies.

`npm list -g` : Shows all the packages installed globally with their dependencies.

`npm list -g --depth=0` : Shows all packages installed globally without thier dependencies.

`npm list --prod` : List of production packages installed.

`npm list --dev` : List of development packages installed with `--save-dev`.

`npm list --depth=0 --json` : Format the dependencies list with `--json` flag.
