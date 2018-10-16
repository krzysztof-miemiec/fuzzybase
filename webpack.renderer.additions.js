const MonacoWebpackPlugin = require('monaco-editor-webpack-plugin');

module.exports = {
  devServer: {
    historyApiFallback: true,
  },
  module: {
    rules: [
      {
        test: /\.tsx?$/,
        loader: 'tslint-loader',
        options: {
          emitErrors: true
        },
      }
    ],
  },
  plugins: [
    new MonacoWebpackPlugin({
      languages: ['pgsql'],
    })
  ],
};
