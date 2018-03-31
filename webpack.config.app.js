'use strict';

const webpack = require('webpack');
const ExtractTextPlugin = require('extract-text-webpack-plugin');
const HtmlWebpackPlugin = require('html-webpack-plugin');
const path = require('path');
const { dependencies: externals } = require('./app/package.json');

const port = process.env.PORT || 3000;
const PROD = process.env.NODE_ENV === 'production';
const DEV = process.env.NODE_ENV === 'development';
const publicPath = PROD ? './dist/' : `http://localhost:${port}/dist/`;

module.exports = {
  devtool: PROD ? 'cheap-module-source-map' : 'inline-source-map',
  mode: PROD ? 'production' : 'development',
  entry: [
    ...DEV ? [
      `webpack-hot-middleware/client?path=http://localhost:${port}/__webpack_hmr&reload=true`
    ] : [],
    './app/src/index'
  ],
  output: {
    path: path.join(__dirname, 'app/dist'),
    filename: 'bundle.js',
    publicPath
  },
  resolve: {
    extensions: ['.js', '.tsx', '.json'],
    modules: [
      path.join(__dirname, 'app'),
      'node_modules',
    ]
  },
  module: {
    rules: [
      {
        test: /\.tsx?$/,
        loaders: 'babel-loader!ts-loader',
        exclude: /node_modules/
      }, {
        test: /\.json$/,
        loader: 'json-loader'
      },
      {
        test: /\.woff2?(\?v=\d+\.\d+\.\d+)?$/,
        use: {
          loader: 'url-loader',
          options: {
            limit: 10000,
            mimetype: 'application/font-woff',
          }
        },
      },
      {
        test: /\.ttf(\?v=\d+\.\d+\.\d+)?$/,
        use: {
          loader: 'url-loader',
          options: {
            limit: 10000,
            mimetype: 'application/octet-stream'
          }
        }
      },
      {
        test: /\.eot(\?v=\d+\.\d+\.\d+)?$/,
        use: 'file-loader',
      },
      {
        test: /\.svg(\?v=\d+\.\d+\.\d+)?$/,
        use: {
          loader: 'url-loader',
          options: {
            limit: 10000,
            mimetype: 'image/svg+xml',
          }
        }
      },
      {
        test: /\.(png|jpg|jpeg|gif)$/,
        loaders: [
          `url-loader?limit=10000&name=${PROD ? '[hash].[ext]' : '[name].[ext]?[hash]'}`,
          {
            loader: 'image-webpack-loader',
            options: {
              bypassOnDebug: true,
              query: {
                mozjpeg: {
                  progressive: true,
                },
                gifsicle: {
                  interlaced: false,
                },
                optipng: {
                  optimizationLevel: 7,
                }
              }
            }
          }
        ]
      },
      {
        test: /\.(?:ico|webp)$/,
        use: 'url-loader',
      }
    ]
  },
  plugins: [
    new webpack.NoEmitOnErrorsPlugin(),
    new webpack.DefinePlugin({
      'process.env.NODE_ENV': JSON.stringify('production'),
      'process.env.PORT': process.env.PORT,
      'process.env.HOT': process.env.HOT
    }),
    new ExtractTextPlugin('style.css'),
    new HtmlWebpackPlugin({
      filename: 'app.html',
      template: 'app/app.html',
      inject: false
    }),
    ...DEV ? [
      new webpack.HotModuleReplacementPlugin(),
      new webpack.LoaderOptionsPlugin({
        debug: true
      })
    ] : [],
    ...PROD ? [
      new webpack.optimize.OccurrenceOrderPlugin(),
    ] : []
  ],
  externals: Object.keys(externals || {}),
  target: 'electron-renderer'
};
