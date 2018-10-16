import * as monacoEditor from 'monaco-editor/esm/vs/editor/editor.api';
import { editor } from 'monaco-editor/esm/vs/editor/editor.api';
import React from 'react';
import { processSize } from './utils';

const noop = () => void 0;

export type ChangeHandler = (
  value: string,
  event: editor.IModelContentChangedEvent
) => void;

export type EditorDidMount = (
  editor: editor.IStandaloneCodeEditor,
  monaco: typeof monacoEditor
) => void;

interface Props {
  /**
   * Width of editor. Defaults to 100%.
   */
  width?: string | number;

  /**
   * Height of editor. Defaults to 500.
   */
  height?: string | number;

  /**
   * The initial value of the auto created model in the editor.
   */
  defaultValue?: string;

  /**
   * The initial language of the auto created model in the editor. Defaults to 'javascript'.
   */
  language?: string;

  /**
   * Theme to be used for rendering.
   * The current out-of-the-box available themes are: 'vs' (default), 'vs-dark', 'hc-black'.
   * You can create custom themes via `monaco.editor.defineTheme`.
   */
  theme?: string | null;

  /**
   * Optional, allow to config loader url and relative path of module, refer to require.config.
   */
  requireConfig?: any;

  /**
   * Optional, allow to pass a different context then the global window onto which the monaco instance will be loaded.
   * Useful if you want to load the editor in an iframe.
   */
  context?: any;

  /**
   * Value of the auto created model in the editor.
   * If you specify value property, the component behaves in controlled mode.
   * Otherwise, it behaves in uncontrolled mode.
   */
  value?: string | null;

  /**
   * Refer to Monaco interface {monaco.editor.IEditorConstructionOptions}.
   */
  options?: editor.IEditorConstructionOptions;

  /**
   * An event emitted when the editor has been mounted (similar to componentDidMount of React).
   */
  editorDidMount?: EditorDidMount;

  /**
   * An event emitted when the content of the current model has changed.
   */
  onChange?: ChangeHandler;
}

export class MonacoEditor extends React.Component<Props> {
  static defaultProps: Partial<Props> = {
    width: '100%',
    height: '100%',
    value: null,
    defaultValue: '',
    language: 'javascript',
    theme: null,
    options: {},
    editorDidMount: noop,
    onChange: noop,
  };

  containerElement = undefined;
  private currentValue: string | null;
  private preventTriggerChangeEvent: boolean;
  private editor: editor.IStandaloneCodeEditor;

  constructor(props: Props) {
    super(props);
    this.currentValue = props.value;
  }

  componentDidMount() {
    this.initMonaco();
  }

  componentDidUpdate(prevProps: Props) {
    if (this.props.value !== this.currentValue) {
      // Always refer to the latest value
      this.currentValue = this.props.value;
      // Consider the situation of rendering 1+ times before the editor mounted
      if (this.editor) {
        this.preventTriggerChangeEvent = true;
        this.editor.setValue(this.currentValue);
        this.preventTriggerChangeEvent = false;
      }
    }
    if (prevProps.language !== this.props.language) {
      editor.setModelLanguage(this.editor.getModel(), this.props.language);
    }
    if (prevProps.theme !== this.props.theme) {
      editor.setTheme(this.props.theme);
    }
    if (
      this.editor &&
      (this.props.width !== prevProps.width || this.props.height !== prevProps.height)
    ) {
      this.editor.layout();
    }
  }

  componentWillUnmount() {
    this.destroyMonaco();
  }

  editorDidMount(editor: editor.IStandaloneCodeEditor) {
    this.props.editorDidMount(editor, monacoEditor);
    editor.onDidChangeModelContent((event) => {
      const value = editor.getValue();

      // Always refer to the latest value
      this.currentValue = value;

      // Only invoking when user input changed
      if (!this.preventTriggerChangeEvent) {
        this.props.onChange(value, event);
      }
    });
  }

  initMonaco() {
    const value = this.props.value !== null ? this.props.value : this.props.defaultValue;
    const { language, theme, options } = this.props;
    if (this.containerElement) {
      // Before initializing monaco editor
      this.editor = editor.create(this.containerElement, {
        value,
        language,
        ...options,
      });
      if (theme) {
        editor.setTheme(theme);
      }
      // After initializing monaco editor
      this.editorDidMount(this.editor);
    }
  }

  destroyMonaco() {
    if (typeof this.editor !== 'undefined') {
      this.editor.dispose();
    }
  }

  assignRef = (component) => {
    this.containerElement = component;
  };

  render() {
    const { width, height } = this.props;
    const fixedWidth = processSize(width);
    const fixedHeight = processSize(height);
    const style = {
      width: fixedWidth,
      height: fixedHeight,
    };

    return <div ref={this.assignRef} style={style} className="react-monaco-editor-container" />;
  }
}
