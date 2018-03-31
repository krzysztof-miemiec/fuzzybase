const webpack = require('webpack');
const path = require('path');
const { dependencies: externals } = require('./app/package.json');

module.exports = {
  devtool: 'source-map',
  mode: 'production',
  module: {
    rules: [{
      test: /\.json$/,
      loader: 'json-loader'
    }]
  },
  resolve: {
    extensions: ['.js', '.json'],
    modules: [
      path.join(__dirname, 'app'),
      './app/node_modules',
    ]
  },
  entry: ['./app/main'],
  output: {
    path: __dirname,
    filename: './app/dist/main.js',
  },
  plugins: [
    new webpack.DefinePlugin({
      'process.env.NODE_ENV': process.env.NODE_ENV,
      'process.env.PORT': process.env.PORT,
      'process.env.HOT': process.env.HOT
    })
  ],
  target: 'electron-main',
  node: {
    __dirname: false,
    __filename: false
  },
  externals: Object.keys(externals || {})
};
