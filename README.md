
## Tokenizer and Lexer for custom programming language

### WIP

input:
```
func(1, 2, 1 != 2) + 1;

if (a == b) {
  print(1);
}
```

output:
```
Body: {
  RegularStatement: {
    expr: BinaryExpr: {
      left: CallExpr: {
        id: func
        arg0: LiteralExpr: { 1 }
        arg1: LiteralExpr: { 2 }
        arg2: BinaryExpr: {
          left: LiteralExpr: { 1 }
          op: NOT_EQUALS
          right: LiteralExpr: { 2 }
        }
      }
      op: ADD
      right: LiteralExpr: { 1 }
    }
  }
  IfStatement: {
    condition: BinaryExpr: {
      left: SymbolExpr: { a }
      op: EQUALS
      right: SymbolExpr: { b }
    }
    Body: {
      RegularStatement: {
        expr: CallExpr: {
          id: print
          arg0: LiteralExpr: { 1 }
        }
      }
    }
    Body: {
    }
  }
}
```
