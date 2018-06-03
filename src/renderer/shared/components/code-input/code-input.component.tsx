import { withStyles } from '@material-ui/core';
import React from 'react';
import { Controlled } from 'react-codemirror2';
import { StyleProps } from '../../../utils/styles.util';
import { styles } from './code-input.styles';

interface Props {
  className?: string;
  text: string;
  onTextChanged: (text: string) => void;
  onSendTriggered?: () => void;
}

class CodeInputComponent extends React.PureComponent<Props & StyleProps<typeof styles>> {
  container: any;

  onKeyDown = (keyEvent: KeyboardEvent) => {
    const { onSendTriggered } = this.props;
    if (keyEvent.key === 'Enter' && (keyEvent.ctrlKey || keyEvent.metaKey)) {
      if (onSendTriggered) {
        onSendTriggered();
      }
      return false;
    }
    return true;
  };

  componentDidMount() {
    this.container.addEventListener('keydown', this.onKeyDown);
  }

  componentWillUnmount() {
    this.container.removeEventListener('keydown', this.onKeyDown);
  }

  render() {
    const { classes, className, text, onTextChanged } = this.props;

    return (
      <div className={className}>
        <div ref={ref => this.container = ref} className={classes.container}>
          <Controlled
            value={text}
            className={classes.input}
            options={{
              mode: 'text/x-pgsql',
              theme: 'idea',
              lineNumbers: true,
              tabSize: 2,
            }}
            onBeforeChange={(_editor, _data, value) => {
              if (onTextChanged) {
                onTextChanged(value);
              }
            }}
          />
        </div>
      </div>
    );
  }
}

export const CodeInput = withStyles(styles)<Props>(CodeInputComponent);
