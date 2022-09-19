# Webpack

Webpack is a MODULE BUNDLER.

There are other options like PARCEL which is new and needs almost no configuration to get running. It is good option for small projects. Other option is rollup.js which is good for tree shaking.

But if we have a large project we use Webpack, it is tested, and is used by many popular frameworks like React.

## Installing Webpack

`npm install --save-dev webpack webpack-dev-server webpack-cli`.

## Webpack config

Basic Setup for webpack development mode.

```js
//webpack.config.js

const path = require("path");

module.exports = {
  entry: "./index.js",
  mode: "development", //could be set to production default is none
  output: {
    path: path.resolve(__dirname, "dist"),
    filename: "bundle.js",
  },
  devServer: {
    static: path.join(__dirname, "dist"),
    compress: true,
    port: 4200, //can be set to any default is 8080
  },
};
```

We can add a script to out npm file so that we use webpack-server to serve our project.

```json
{
  "scripts": {
    "start": "webpack-dev-server --config ./webpack.config.js"
  }
}
```

> Make webpack configuration easier and interactive at [createapp/dev](https://createapp.dev/).

## Building with webpack

`"build" : "webpack --config webpack.config.js"`

We can have multiple configuration files for different tasks like in development, testing and production. We name them in convention like `webpack.dev.config.js` or `webpack.prod.config.js` and so on.
