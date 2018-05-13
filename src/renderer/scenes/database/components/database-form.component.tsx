import { Save } from '@material-ui/icons';
import classNames from 'classnames';
import { Button, Card, CardActions, CardContent, withStyles } from 'material-ui';
import React from 'react';
import { DatabaseState } from '../../../../common/db/store/app';
import { FormInput } from '../../../shared/components/input.component';
import { i18n } from '../../../utils/i18n.util';
import { StyleProps } from '../../../utils/styles.util';
import { styles } from './database-form.styles';

interface Props {
  database: DatabaseState;
  onSubmit: (database: DatabaseState) => void;
}

interface State {
  database: DatabaseState;
}

export class DatabaseFormComponent extends React.PureComponent<Props & StyleProps<typeof styles>, State> {

  constructor(props: Props & StyleProps<typeof styles>) {
    super(props);
    this.state = { database: props.database };
  }

  componentWillUpdate(nextProps: Props) {
    if (nextProps.database !== this.props.database) {
      this.setState({ database: nextProps.database });
    }
  }

  onSubmit = () => {
    this.props.onSubmit(this.state.database);
  };

  render() {
    const { classes } = this.props;
    const { database } = this.state;
    return (
      <Card className={classes.container}>
        <CardContent >
          <FormInput
            form={database}
            id="name"
            label={i18n.t('database.name')}
            className={classes.input}
          />
          <FormInput
            form={database}
            id="host"
            label={i18n.t('database.host')}
            className={classes.input}
          />
          <FormInput
            form={database}
            id="port"
            label={i18n.t('database.port')}
            rowsMax={5}
            normalize={value => Number.parseInt(value, 10)}
            className={classNames([classes.input, classes.inputShort])}
          />
          <FormInput
            form={database}
            id="username"
            label={i18n.t('database.username')}
            className={classes.input}
          />
          <FormInput
            form={database}
            id="password"
            type="password"
            label={i18n.t('database.password')}
            className={classes.input}
          />
        </CardContent>
        <CardActions>
          <Button size="small" onClick={this.onSubmit}>
            <Save />
            {i18n.t('actions.save')}
          </Button>
        </CardActions>
      </Card>
    );
  }
}

export const DatabaseForm = withStyles(styles)(DatabaseFormComponent);
