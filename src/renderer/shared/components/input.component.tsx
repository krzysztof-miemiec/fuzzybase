import { TextField } from 'material-ui';
import { TextFieldProps } from 'material-ui/TextField';
import * as React from 'react';

type ValueType = Array<string | number> | string | number;

interface Props extends TextFieldProps {
  form: any;
  normalize?: (value: string) => any;
}

interface State {
  value: ValueType;
}

export class FormInput extends React.PureComponent<Props, State> {

  constructor(props: Props) {
    super(props);
    this.state = { value: props.form[props.id] };
  }

  render() {
    const { form, normalize, ...props } = this.props;

    return (
      <TextField
        {...props}
        value={this.state.value}
        onChange={event => {
          const value = event.target.value;
          this.setState({ value }, () => {
            form[props.id] = normalize ? normalize(value) : value;
          });
        }}
      />
    );
  }
}
