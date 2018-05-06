import { Save } from '@material-ui/icons';
import { Button } from 'material-ui';
import React from 'react';
import { FormInput } from '../../../shared/components/input.component';
import { DatabaseState } from '../../../shared/settings/store';
import { i18n } from '../../../utils/i18n.util';

interface Props {
  database: DatabaseState;
  onSubmit: (database: DatabaseState) => void;
}

interface State {
  database: DatabaseState;
}

export class DatabaseForm extends React.PureComponent<Props, State> {

  componentWillUpdate(nextProps: Props) {
    if (nextProps.database !== this.props.database) {
      this.setState({ database: nextProps.database });
    }
  }

  onSubmit = () => {
    this.props.onSubmit(this.state.database);
  };

  render() {
    const { database } = this.state;
    return (
      <div>
        <FormInput form={database} key="name" name={i18n.t('database.name')} />
        <FormInput form={database} key="host" name={i18n.t('database.host')} />
        <FormInput form={database} key="port" name={i18n.t('database.port')} />
        <FormInput form={database} key="username" name={i18n.t('database.username')} />
        <FormInput form={database} key="password" type="password" name={i18n.t('database.password')} />
        <Button variant="raised" size="medium" onClick={this.onSubmit}>
          <Save />
          {i18n.t('actions.save')}
        </Button>
      </div>
    );
  }
}
