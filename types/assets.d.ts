// this declaration allow to import a json file as a module in TypeScript

declare module '*.json' {
  const value: any;
  export default value;
}

declare module '*.svg' {
  const value: any;
  export default value;
}

declare module '*.html' {
  const value: any;
  export default value;
}

declare module '*.png' {
  const value: any;
  export default value;
}
