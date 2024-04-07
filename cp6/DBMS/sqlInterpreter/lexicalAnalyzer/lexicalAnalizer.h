#ifndef _SEMANTIC_ANALIZER_H_
#define _SEMANTIC_ANALIZER_H_

#define NUM_KEYWORDS 19
#define NUM_KEYPHRASES 7

typedef enum {
    SELECT,         // "SELECT"
    FROM,           // "FROM"
    WHERE,          // "WHERE"
    INSERT,         // "INSERT"
    UPDATE,         // "UPDATE"
    DELETE,         // "DELETE"
    JOIN,           // "JOIN"
    INNER,          // "INNER"
    OUTER,          // "OUTER"
    LEFT,           // "LEFT"
    RIGHT,          // "RIGHT"
    GROUP_BY,       // "GROUP BY"
    ORDER_BY,       // "ORDER BY"
    AND,            // "AND"
    OR,             // "OR"
    NOT,            // "NOT"
    IN,             // "IN"
    LIKE,           // "LIKE"
    BETWEEN,        // "BETWEEN"
    UNION,          // "UNION"
    ALL,            // "ALL"
    DISTINCT,       // "DISTINCT"
    IDENTIFIER,     // идентификатор (название таблицы, столбца и т.д.)
    STRING,         // строковый литерал
    NUMBER,         // числовой литерал
    EQUAL,          // "=="
    NOT_EQUAL,      // "!="
    LESS_THAN,      // "<"
    GREATER_THAN,   // ">"
    LESS_THAN_OR_EQUAL,     // "<="
    GREATER_THAN_OR_EQUAL,  // ">="
    PLUS,           // "+"
    MINUS,          // "-"
    MULTIPLY,       // "*"
    DIVIDE,         // "/"
    COMMA,          // ","
    DOT,            // "."
    SEMICOLON,      // ";"
    LEFT_PARENTHESIS,       // "("
    RIGHT_PARENTHESIS,      // ")"
    COMMENT,        // комментарий
    VARIABLE,       // переменная
    FUNCTION,       // функция
    TRIGGER,        // триггер
    ERROR           // ошибка
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

const char* keyPhrases[] = {
    "EXISTS", "IN", "ANY", "ALL", "EXCEPT", "INTERSECT", "LIKE", "BETWEEN"
};

lexer* createLexer(char *input);
void destroyLexer(lexer **Lexer);
token getNextToken(lexer **Lexer);

#endif