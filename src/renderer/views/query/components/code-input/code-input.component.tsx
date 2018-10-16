import * as monacoEditor from 'monaco-editor/esm/vs/editor/editor.api';
import { IDisposable, IKeyboardEvent, KeyCode } from 'monaco-editor/esm/vs/editor/editor.api';
import React from 'react';
import ReactResizeDetector from 'react-resize-detector';
import { DatabaseMetadata } from '../../../../../common/db/store/db.state';
import { View } from '../../../../shared/components/view';
import { MonacoEditor } from '../monaco-editor';
import { styles } from './code-input.styles';
import { PostgresColorProvider, PostgresCompletionItemProvider } from './pgsql';

const POSTGRES = 'pgsql';

interface Props {
  className?: string;
  text: string;
  databaseMetadata: Partial<DatabaseMetadata>;
  onTextChanged: (text: string) => void;
  onSendTriggered?: () => void;
}

interface State {
  width: number;
  height: number;
}

export class CodeInput extends React.PureComponent<Props, State> {
  container: any;
  state: State = { width: undefined, height: undefined };
  private completionItemProvider = new PostgresCompletionItemProvider();
  private completionItemProviderDisposable: IDisposable;
  private colorProvider = new PostgresColorProvider();
  private colorProviderDisposable: IDisposable;

  componentDidMount() {
    const { databaseMetadata } = this.props;
    this.completionItemProvider.setMetadata(databaseMetadata);
  }

  componentDidUpdate(oldProps: Props) {
    const { databaseMetadata } = this.props;
    if (databaseMetadata !== oldProps.databaseMetadata) {
      this.completionItemProvider.setMetadata(databaseMetadata);
    }
  }

  componentWillUnmount() {
    if (this.completionItemProviderDisposable) {
      this.completionItemProviderDisposable.dispose();
    }
    if (this.colorProviderDisposable) {
      this.colorProviderDisposable.dispose();
    }
  }

  editorDidMount = (editor: monacoEditor.editor.IStandaloneCodeEditor, monaco: typeof monacoEditor) => {
    editor.onKeyDown(this.onKeyDown);
    this.colorProviderDisposable = monaco.languages
      .registerColorProvider(POSTGRES, this.colorProvider);
    this.completionItemProviderDisposable = monaco.languages
      .registerCompletionItemProvider(POSTGRES, this.completionItemProvider);
  };

  onKeyDown = (event: IKeyboardEvent) => {
    const { onSendTriggered } = this.props;
    if (event.keyCode === KeyCode.Enter && (event.ctrlKey || event.metaKey)) {
      if (onSendTriggered) {
        onSendTriggered();
      }
      event.preventDefault();
      event.stopPropagation();
    }
  };

  onResize = (width: number, height: number) => {
    this.setState(state => {
      if (state.width === width && state.height === height) {
        return null;
      }
      return { width, height };
    });
  };

  onChange = (value: string) => {
    const { onTextChanged } = this.props;
    if (onTextChanged) {
      onTextChanged(value);
    }
  };

  render() {
    const { className, text } = this.props;
    const { width, height } = this.state;

    return (
      <View style={[styles.container, className]}>
        <ReactResizeDetector
          handleWidth={true}
          handleHeight={true}
          onResize={this.onResize}
        >
          <MonacoEditor
            editorDidMount={this.editorDidMount}
            width={width}
            height={height}
            language="pgsql"
            theme="vs"
            value={text}
            options={{
              lineNumbers: 'on',
              selectOnLineNumbers: true,
              fontFamily: 'Fira Code',
              fontSize: 13,
              fontLigatures: true,
              folding: true,
              contextmenu: false,
              showFoldingControls: 'always',
            }}
            onChange={this.onChange}
          />
          {/*<Controlled
          value={text}
          className={styles.input}
          options={{
            mode: 'text/x-pgsql',
            theme: 'idea',
            lineNumbers: true,
            tabSize: 2,
            extraKeys: {
              'Ctrl-Space': 'autocomplete',
            },
            showCursorWhenSelecting: true,
            lineWrapping: true,
          }}
          onBeforeChange={(_editor, _data, value) => {
            if (onTextChanged) {
              onTextChanged(value);
            }
          }}
        />*/}
        </ReactResizeDetector>
      </View>
    );
  }
}
