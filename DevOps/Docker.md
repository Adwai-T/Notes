# Docker

## Installing Docker

Install from [Docker website](https://docs.docker.com/get-docker/).

## Setup

In our project we build an image for that project.

In this we are using the node docker container image.

```DockerFile
FROM node:carbon

CND["/bin/bash"]
```

We can also specify node version directly

```DockerFile
FROM node:8.11.1

CND["/bin/bash"]
```

## Docker Commands

[Docker Commands Reference](https://docs.docker.com/engine/reference/builder/#usage)

Building docker from cmd pathed in the project directory use `docker build -t superawesomecontainer .`

Then we can run docker container using `docker run -it superawesomecontainer`. `-it` is used to go inside of the container when we run the container.

This will take us inside out docker container.

We can then check if we have node inside of the container using `node -v`. Check to see if the version that we got is the version that was expected.

If we want to run the docker container in the background and not go into the container in the terminal we could use the flag `-d` like `docker run -it -d superawesomecontainer`.

To see all the container that are running we use `docker ps`.

Out docker container is running in the background, if we want to go into the container we use `docker exec -it containerid bash`. If we want to stop the contianer we use `docker stop containerid`.

We can also speciify some other functions in the Dockerfile.

Comments in docker file start with `#`. 

```DockerFile
FROM node:8.11.1

# We set our working directory by this. So now when we are in the docker bash, it will run from this directory
WORKDIR /usr/src/app-folder

# After we have set our working directory we can then copy files to that directory.
# The first is what we want to copy and the send to copy to.
# In the below case we want to copy all files from the root directory, so we use `./`, but we could also specify file name if we want specific files to be copied to specific location.
COPY ./ ./

# RUN is used to run commands, and we want that once project files are copied we want to install all dependencies from npm.
RUN npm install
# A docker file can run many run steps that layer on top of one another.

# There can be only one CMD. It runs when we launch the build image. It is mostly places at the end of the DockerFile.
CMD["/bin/bash"]
```

We can not do an npm start to start the application. This will run the application at port 3000 or as specified by in the terminal when we run the appication. But we cannot go to our computer browser to access the port as local host as the docker port that the application is running as is not the same as computers local host port.

So we need to expose the Dockers port to the computers localhost port. We do that by using `docker run -it -p 3000:3000 superawesomecontainer` to run the docker image and set the docker port 3000 to be exposed to localhost port 3000, the we run the application by using `npm start`. We can then go to localhost:3000 to look at the app.

## Docker Compose

When we want to combine a lot of services we use docker compose to orchestrate all the services.

We will create a docker compose file which is a `.yml` configuration file.