# Webpack

Webpack is a MODULE BUNDLER.

There are other options like PARCEL which is new and needs almost no configuration to get running. It is good option for small projects. Other option is rollup.js which is good for tree shaking.

But if we have a large project we use Webpack, it is tested, and is used by many popular frameworks like React.

## Installing Webpack

`npm install --save-dev webpack webpack-dev-server webpack-cli`.

## Webpack config

Basic Setup for webpack.

```js
//webpack.config.js

module.exports = {
  entry: {
    './src/index.js'
  },
  output: {
    path: __dirname + '/dist',
    publicPath: '/',
    filename: 'bundle.js'
  },
  devServer: {
    contentBase: './dist'
  }
}
```

We can add a script to out npm file so that we use webpack-server to serve our project.

```json
{
  "scripts" : {
    "start" : "webpack-dev-server --config ./webpack.config.js --mode development"
  }
}
```

> Make webpack configuration easier and interactive at [createapp/dev](https://createapp.dev/).
