import * as React from 'react';
import { RouteComponentProps } from 'react-router';
import { Toolbar } from '../components/toolbar';

class Main extends React.Component<RouteComponentProps<any>, void> {
  public render() {
    return (
      <div className='main-page' >
        <Toolbar />
      </div>
    );
  }
}

export const MainPage = Main as any as React.StatelessComponent<{}>;
