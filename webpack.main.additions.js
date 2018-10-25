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
};
