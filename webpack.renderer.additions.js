const MonacoWebpackPlugin = require('monaco-editor-webpack-plugin');

module.exports = {
  devServer: {
    inline: true,
    port: 9080,
    historyApiFallback: true,
    stats: 'minimal',
  },
  module: {
    rules: [
      {
        test: /\.tsx?$/,
        loader: 'tslint-loader',
        options: {
          emitErrors: false
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
