# Heroku

- Create a new application

`heroku create` : Create app with random name

`heroku create appName`: Create app with custom name

`heroku apps:rename` : Rename an application.

- Deploy app to heroku.

`git push heroku master` : The application should be create and a git commit needs to be done before that as the last commit will be pushed to heroku.

## Setup Enviroment Variables

After creating a project we can set up enviroment varibles.

`heroku config:set key=value`
`heroku config`
`heroku config:unset key`

## Open Application

After the application has been deployed we can open the application by using `heroku open`.

## View Logs

`heroku logs --tail`.

## User profile Info and Application info

`heroku pg`

## Fixing App not found

- Check for the current url
  `git remote -v`

- remove remote url
  `git remote rm heroku`

- re-add the remote url
  `git remote add heroku git@heroku.com:boiling-inlet-6957.git`

## Dyno Management

- List of dynos for an application : `heroku ps`

- Restart all dynos : `heroku ps:restart`

- Adding a name to the above will restart that dyno : `heroku ps:restart web`

- View Logs : `heroku logs` or `heroku logs --tail`

- Get help : `heroku ps --help`

## Using Enviroment Varaibles

### With Java

```yml
admin:
  password: ${ADMIN_PASSWORD}
```
