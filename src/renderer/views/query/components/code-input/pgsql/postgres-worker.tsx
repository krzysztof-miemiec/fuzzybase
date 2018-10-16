enum PostgresTokenType {
  Value, // String literal, number, etc.
  Expression, // Operation performed with use of operators
  Function, // Function call
  Clause, //
}

interface PostgresToken {
  type: PostgresTokenType;
  subtokens: PostgresToken[];
  value: string;
}

export class PostgresWorker {
  tokens: PostgresToken[];

  tokenize: (input: string) => {
    for (let i=0; i<input.length; i++){}
};
}
