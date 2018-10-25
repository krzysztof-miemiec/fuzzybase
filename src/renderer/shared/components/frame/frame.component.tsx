import { Typography } from '@material-ui/core';
import React from 'react';
import { styles } from './frame.styles';

interface Props {
  headline?: string;
  children?: React.ReactNode;
  footer?: React.ReactNode;
}

export const DialogFrame: React.SFC<Props> = ({
  headline, footer, children,
}) => (
  <div className={styles.scrollView}>
    <div className={styles.container}>
      <div className={styles.frame}>
        <div className={styles.header}>
          <Typography
            variant="title"
            className={styles.headerText}
          >
            {headline}
          </Typography>
        </div>
        <div className={styles.content}>
          {children}
        </div>
      </div>
      <div className={styles.footer}>
        {footer}
      </div>
    </div>
  </div>
);
