import { Button } from '@material-ui/core';
import React from 'react';
import { Controlled } from 'react-codemirror2';
import { styles } from './code-input.styles';

import Send from '@material-ui/icons/send';

interface Props {
  className?: string;
  text: string;
  onTextChanged: (text: string) => void;
  onSendTriggered?: () => void;
}

// registerHelper('hint', '');

export class CodeInput extends React.PureComponent<Props> {
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
    const { className, text, onTextChanged, onSendTriggered } = this.props;

    return (
      <div className={className}>
        <div ref={ref => this.container = ref} className={styles.container}>
          <Controlled
            value={text}
            className={styles.input}
            options={{
              mode: 'text/x-pgsql',
              theme: 'idea',
              lineNumbers: true,
              tabSize: 2,
              extraKeys: { 'Ctrl-Space': 'autocomplete' },
            }}
            onBeforeChange={(_editor, _data, value) => {
              if (onTextChanged) {
                onTextChanged(value);
              }
            }}
          />
          <Button variant="flat" className={styles.button} onClick={onSendTriggered}>
            <Send color="inherit" fontSize="inherit" />
          </Button>
        </div>
      </div>
    );
  }
}
