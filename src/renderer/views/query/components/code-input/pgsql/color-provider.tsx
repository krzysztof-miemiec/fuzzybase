import { editor, languages } from 'monaco-editor/esm/vs/editor/editor.api';

type TextModel = editor.ITextModel;
type ColorInformation = languages.IColorInformation;
type ColorPresentation = languages.IColorPresentation;

export class PostgresColorProvider implements languages.DocumentColorProvider {
  provideColorPresentations(model: TextModel, colorInfo: ColorInformation): languages.IColorPresentation[] {

    return undefined;
  }

  provideDocumentColors(model: TextModel): languages.IColorInformation[] {
    return undefined;
  }

}
