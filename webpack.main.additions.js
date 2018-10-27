module.exports = {
  devServer: {
    inline: true,
    port: 9080,
    historyApiFallback: true,
    stats: 'none',
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
};
