import { FormControl, FormHelperText, Input, InputLabel } from '@material-ui/core';
import classNames from 'classnames';
import React, { ChangeEvent } from 'react';
import { styles } from './input.styles';

type ValueType = Array<string | number> | string | number;

interface Props {
  id: string;
  className?: string;
  form: any;
  label: string;
  validator?: (value: ValueType) => string;
  type?: string;
  normalize?: (value: string) => any;
  rowsMax?: number;
  onValueChange?: () => void;
}

interface State {
  value: ValueType;
  errorText: string;
}

const validate = (validator: ((value: ValueType) => string) | undefined, value: ValueType) =>
  validator ? validator(value) : '';

export class FormInput extends React.PureComponent<Props, State> {
  constructor(props: Props) {
    super(props);
    const value = props.form[props.id] || '';
    this.state = {
      value,
      errorText: '',
    };
  }

  componentDidUpdate(oldProps: Props, oldState: State) {
    const { value } = this.state;
    const { validator, form, id } = this.props;
    if (oldProps.form !== form) {
      this.setState({ value: form[id] || '', errorText: '' });
    } else if (oldProps.validator !== validator || oldState.value !== value) {
      this.setState({ errorText: validate(validator, value) });
    }
  }

  onChange = (event: ChangeEvent<HTMLInputElement>) => {
    const { normalize, onValueChange, form, id } = this.props;
    const value = event.target.value;
    form[id] = value;
    this.setState({
      value: normalize ? normalize(value) : value,
    }, onValueChange);
  };

  render() {
    const { id, label, rowsMax, type, className } = this.props;
    const { errorText, value } = this.state;

    return (
      <FormControl
        error={!!errorText}
        aria-describedby={`${id}-input-description`}
        className={classNames([className])}
      >
        <InputLabel
          htmlFor={`${id}-input`}
          shrink={true}
          className={styles.label}
        >
          {label}
        </InputLabel>
        <Input
          id={`${id}-input`}
          value={value}
          type={type}
          className={styles.input}
          rowsMax={rowsMax}
          onChange={this.onChange}
        />
        <FormHelperText
          id={`${id}-input__description`}
          className={styles.description}
        >
          {errorText}
        </FormHelperText>
      </FormControl>
    );
  }
}
