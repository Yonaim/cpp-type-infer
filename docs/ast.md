최상위 구조(Top Level)
```
ASTNode
 ├── Decl       (선언, Declaration)
 ├── Stmt       (문장, Statement)
 └── Type       (타입)
```

Statement 계층
```
Stmt
 ├── Expr (표현식, Express)
 ├── IfStmt
 ├── ForStmt
 ├── WhileStmt
 ├── ReturnStmt
 └── DeclStmt (선언을 문장처럼 감싸는 wrapper)
```

Declaration 계층
```
Decl
 ├── VarDecl
 ├── FunctionDecl
 ├── ParmVarDecl
 ├── FieldDecl
 ├── RecordDecl (struct/class)
 └── EnumDecl
```

Type 계층
```
Type
 ├── BuiltinType
 ├── PointerType
 ├── FunctionProtoType
 └── ArrayType
```
