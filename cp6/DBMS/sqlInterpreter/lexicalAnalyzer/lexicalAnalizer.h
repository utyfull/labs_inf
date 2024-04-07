#ifndef _SEMANTIC_ANALIZER_H_
#define _SEMANTIC_ANALIZER_H_

#define NUM_KEYWORDS 19
#define NUM_DATATYPES 2
#define NUM_KEYPHRASES 7

typedef enum {
    KEYWORD,//
    IDENTIFIER,//
    SYMBOL,//
    LITERAL,//
    OPERATOR,//
    COMMENT,//
    FUNCTION,//??? kak nibud potom
    DATATYPE,//
    KEYPHRASE,//
    SPECIALCONSTRUCTION,//??? toje potom
    ALIASE,//?? _'|'_ i eto toje
    SORTDIRECTIONINDICATOR,////oy yoy yoy
    ERROR // u menya git slomalsy, spasibo
} tokenType;

typedef struct {
    tokenType type;
    char lexeme[100];
} token;

typedef struct {
    char *input;
    int position;
} lexer;

const char* keyWords[] = {
    "SELECT", "INSERT", "UPDATE", "DELETE", "FROM", "WHERE", "JOIN",
    "INNER", "OUTER", "LEFT", "RIGHT", "ON", "GROUPBY", "ORDERBY", "HAVING",
    "LIMIT", "AND", "OR", "NOT"
};

const char* dataTypes[] = {
    "FLOAT", "INT", "CHAR"
};

const char* keyPhrases[] = {
    "EXISTS", "IN", "ANY", "ALL", "EXCEPT", "INTERSECT", "LIKE", "BETWEEN"
};

lexer* createLexer(char *input);
void destroyLexer(lexer **Lexer);
token getNextToken(lexer **Lexer);

#endif