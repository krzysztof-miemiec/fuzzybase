import * as React from 'react';

export class App extends React.Component {
  public render() {
    return (
      <div className='component--full-screen'>
        {this.props.children}
      </div>
    );
  }
}
