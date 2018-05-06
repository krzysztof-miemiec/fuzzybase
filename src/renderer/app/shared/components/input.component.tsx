import { FormControl, Input, InputLabel } from 'material-ui';
import { InputProps } from 'material-ui/Input';
import * as React from 'react';

type ValueType = Array<string | number> | string | number;

interface Props extends InputProps {
  name: string;
  key: string;
  form: any;
}

interface State {
  value: ValueType;
}

export class FormInput extends React.PureComponent<Props, State> {

  constructor(props: Props) {
    super(props);
    this.state = { value: props.form[props.key] };
  }

  render() {
    const { className, key, name, form, ...rest } = this.props;

    return (
      <FormControl className={className}>
        <InputLabel htmlFor={key}>{name}</InputLabel>
        <Input
          id={key}
          value={this.state.value}
          onChange={event => {
            const value = event.target.value;
            this.setState({ value }, () => {
              form[key] = value;
            });
          }}
          {...rest}
        />
      </FormControl>
    );
  }
}
