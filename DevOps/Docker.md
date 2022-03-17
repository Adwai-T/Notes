# Docker

## Installing Docker

Install from [Docker website](https://docs.docker.com/get-docker/).

## Setup

In our project we build an image for that project.

```DockerFile
FROM node:carbon

CND["/bin/bash"]
```

Building docker from cmd pathed in the project directory use `docker build -t superawesomecontainer .`

Then we can run docker container using `docker run -it superawesomecontainer`. `-it` is used to go inside of the container when we run the container.

This will take us inside out docker container.

We can then check if we have node inside of the container using `node -v`. Check to see if the version that we got is the version that was expected.

If we want to run the docker container in the background and not go into the container in the terminal we could use the flag `-d` like `docker run -it -d superawesomecontainer`.

To see all the container that are running we use `docker ps`.

Out docker container is running in the background, if we want to go into the container we use `docker exec -it containerid bash`. If we want to stop the contianer we use `docker stop containerid`.