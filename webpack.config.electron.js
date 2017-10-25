const webpack = require('webpack');
const path = require('path');
const { dependencies: externals } = require('./app/package.json');

module.exports = {
  devtool: 'source-map',
  module: {
    loaders: [{
      test: /\.json$/,
      loader: 'json-loader'
    }]
  },
  resolve: {
    extensions: ['.js', '.json'],
    modules: [
      path.join(__dirname, 'app'),
      'node_modules',
    ]
  },
  entry: ['./app/main'],
  output: {
    path: __dirname,
    filename: './app/dist/main.js',
    libraryTarget: 'commonjs2'

  },
  plugins: [
    new webpack.DefinePlugin({
      'process.env.NODE_ENV': JSON.stringify('production'),
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
