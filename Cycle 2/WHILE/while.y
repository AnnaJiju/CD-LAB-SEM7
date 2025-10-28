%{
    #include<stdio.h>
    #include<stdlib.h>

    int yylex(void);
    int yyerror(const char *s);
%}

%token WHILE ID NUM LE GE EQ NE OR AND INCR DECR
%right "="
%left OR AND
%left ">" "<" LE GE EQ NE
%left "+" "-"
%left "*" "/"
%right UNIMINUS
%left "!"

%%

S:     ST { printf("Accepted\n"); exit(0); };

ST:    WHILE "(" E ")" DEF;

DEF:   "{" BODY "}"
     | E
     | ST
     |
     ;

BODY:  BODY BODY
     | E
     | ST
     |
     ;

E:     ID '=' E
     | ID "=" NUM
     | E '+' E
     | E '-' E
     | E '*' E
     | E '/' E
     | E '<' E
     | E '>' E
     | E LE E
     | E GE E
     | E EQ E
     | E NE E
     | E OR E
     | E AND E
     | ID INCR
     | ID DECR
     | NUM
     | ID
     ;

%%

int main()
{
    printf("Enter the WHILE loop: ");
    yyparse();
    return 0;
}

int yyerror(const char *s)
{
    fprintf(stderr,"ERROR: %s\n", s);
    return 0;
}
