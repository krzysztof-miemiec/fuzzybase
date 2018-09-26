import { isArray, isString } from 'lodash';
import { CSSProperties } from 'react';
import React  from 'react';
import { Omit } from 'react-redux';

export type StyleProp = string | CSSProperties | (string | CSSProperties)[];

type DivProps = Omit<React.DetailedHTMLProps<React.HTMLAttributes<HTMLDivElement>, HTMLDivElement>, 'style'>;

export interface ViewProps extends DivProps {
  style?: StyleProp;
}

const isCSSProperties = (element: string | CSSProperties): element is CSSProperties => !isString(element);

export const View: React.SFC<ViewProps> = ({ style, ...props }) => {
  let className: any;
  let styles: any;
  if (isString(style)) {
    className = style;
  } else if (isArray(style)) {
    className = style.filter(isString).join(' ');
    styles = style.filter(isCSSProperties).reduce((object, style) => Object.assign(object, style), {});
  } else {
    styles = style;
  }
  return (
    <div {...props as any} className={className} style={styles} />
  );
};
