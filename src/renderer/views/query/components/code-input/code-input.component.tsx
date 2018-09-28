import React from 'react';
import { Controlled } from 'react-codemirror2';
import { View } from '../../../../shared/components/view';
import { styles } from './code-input.styles';

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

  onContainerRef = (ref) => {
    if (!ref && this.container) {
      this.container.removeEventListener('keydown', this.onKeyDown);
    } else if (!this.container && ref) {
      ref.addEventListener('keydown', this.onKeyDown);
    } else if (this.container && ref && this.container !== ref) {
      this.container.removeEventListener('keydown', this.onKeyDown);
      ref.addEventListener('keydown', this.onKeyDown);
    }
    this.container = ref;
  };

  render() {
    const { className, text, onTextChanged } = this.props;

    return (
      <View divRef={this.onContainerRef} style={[styles.container, className]}>
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
      </View>
    );
  }
}
