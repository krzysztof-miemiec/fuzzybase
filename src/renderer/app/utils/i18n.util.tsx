import i18next from 'i18next';
import LanguageDetector from 'i18next-electron-language-detector';
import en from '../../../assets/locale/en.json';

i18next
  .use(LanguageDetector)
  .init({
    fallbackLng: 'en',
    interpolation: {
      escapeValue: false,
    },
    resources: {
      en,
    },
  });
export const i18n = i18next;
