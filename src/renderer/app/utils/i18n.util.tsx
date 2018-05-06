import i18next from 'i18next';
import en from '../../../assets/locale/en.json';

i18next
  .init({
    interpolation: {
      escapeValue: false,
    },
    resources: {
      en,
    },
  });

export const i18n = i18next;
