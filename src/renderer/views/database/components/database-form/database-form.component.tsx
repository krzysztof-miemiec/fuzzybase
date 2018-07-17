import { Button, Typography, withStyles } from '@material-ui/core';
import React from 'react';
import { DatabaseState } from '../../../../../common/db/store/app';
import { createDatabaseState } from '../../../../../common/db/store/db.utils';
import { Frame } from '../../../../shared/components/frame';
import { FormInput } from '../../../../shared/components/input';
import { i18n } from '../../../../utils/i18n.util';
import { StyleProps } from '../../../../utils/styles.util';
import { styles } from './database-form.styles';

interface Props {
  database?: DatabaseState | undefined;
  onSubmit: (database: DatabaseState) => void;
  onCancel: () => void;
}

interface State {
  database?: DatabaseState;
}

const getDatabase = (database: DatabaseState) => database ? { ...database } : createDatabaseState();

export class DatabaseFormComponent extends React.Component<Props & StyleProps<typeof styles>, State> {
  constructor(props: Props & StyleProps<typeof styles>) {
    super(props);
    this.state = {
      database: getDatabase(props.database),
    };
  }

  componentDidUpdate(oldProps: Props) {
    const { database } = this.props;
    if (oldProps.database !== database || !this.state.database) {
      this.setState({ database: getDatabase(database) });
    }
  }

  onSubmit = () => {
    this.props.onSubmit(this.state.database);
  };

  onValueChange = () => {
    this.forceUpdate();
  };

  renderFooter = () => {
    const { classes, onCancel } = this.props;
    return (
      <Typography variant="caption">
        Or <span className={classes.link} onClick={onCancel}>Cancel</span> if you don't want to create connection now.
      </Typography>
    );
  };

  render() {
    const { classes, database: sourceDatabase } = this.props;
    const { database } = this.state;
    return database ? (
      <Frame
        headline="Create a new database connection"
        footer={this.renderFooter}
      >
        <FormInput
          form={database}
          id="name"
          label={i18n.t('database.name')}
          validator={value => !value ? 'Connection name can\'t be empty.' : ''}
          onValueChange={this.onValueChange}
        />
        <FormInput
          form={database}
          id="host"
          label={i18n.t('database.server')}
          validator={value => !value ? 'Server can\'t be empty.' : ''}
          onValueChange={this.onValueChange}
        />
        <FormInput
          form={database}
          id="port"
          label={i18n.t('database.port')}
          type="number"
          rowsMax={5}
          normalize={value => Number.parseInt(value, 10) || ''}
          validator={value => !value ? 'Port must be defined' : ''}
          className={classes.inputShort}
          onValueChange={this.onValueChange}
        />
        <FormInput
          form={database}
          id="database"
          validator={value => !value ? 'Database can\'t be empty.' : ''}
          label={i18n.t('database.database')}
          onValueChange={this.onValueChange}
        />
        <div className={classes.divider} />
        <FormInput
          form={database}
          id="username"
          label={i18n.t('database.username')}
          onValueChange={this.onValueChange}
        />
        <FormInput
          form={database}
          id="password"
          type="password"
          label={i18n.t('database.password')}
          onValueChange={this.onValueChange}
        />
        <Button
          onClick={this.onSubmit}
          disabled={!database.name || !database.port || !database.host || !database.database}
        >
          {i18n.t(sourceDatabase ? 'actions.save' : 'actions.create')}
        </Button>
      </Frame>
    ) : (
      null
    );
  }
}

export const DatabaseForm = withStyles(styles)<Props>(DatabaseFormComponent);
