import { Typography, withStyles } from '@material-ui/core';
import React from 'react';
import { StyleProps } from '../../../utils/styles.util';
import { styles } from './frame.styles';

interface Props {
  headline?: string;
  children?: React.ReactNode;
  footer?: React.ReactNode;
}

export const FrameComponent: React.SFC<Props & StyleProps<typeof styles>> = ({
  classes, headline, footer, children,
}) => (
  <div className={classes.container}>
    <div className={classes.frame}>
      <div className={classes.header}>
        <Typography
          variant="title"
          className={classes.headerText}
        >
          {headline}
        </Typography>
      </div>
      <div className={classes.content}>
        {children}
      </div>
    </div>
    <div className={classes.footer}>
      {footer}
    </div>
  </div>
);
export const Frame = withStyles(styles)<Props>(FrameComponent);
