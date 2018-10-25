const MonacoWebpackPlugin = require('monaco-editor-webpack-plugin');

module.exports = {
  devServer: {
    historyApiFallback: true,
    stats: 'minimal',
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
