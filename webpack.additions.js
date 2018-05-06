module.exports = {
  module: {
    rules: [
      {
        test: /\.tsx?$/,
        loader: 'tslint-loader',
        options: {
          emitErrors: true
        }
      }
    ]
  }
};
