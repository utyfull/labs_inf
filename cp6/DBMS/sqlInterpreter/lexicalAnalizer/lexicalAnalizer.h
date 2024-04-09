#ifndef _SEMANTIC_ANALIZER_H_
#define _SEMANTIC_ANALIZER_H_

#define NUM_KEYWORDS 28
#define NUM_KEYPHRASES 9
#define NUM_OPERATORS 5

typedef enum
{
    SELECT = 1,       // "SELECT"
    FROM = 2,         // "FROM"
    WHERE = 3,        // "WHERE"
    INSERT = 4,       // "INSERT"
    UPDATE = 5,       // "UPDATE"
    DELETE = 6,       // "DELETE"
    JOIN = 7,         // "JOIN"
    INNER = 8,        // "INNER"
    OUTER = 9,        // "OUTER"
    LEFT = 10,        // "LEFT"
    RIGHT = 11,       // "RIGHT"
    GROUPBY = 12,     // "GROUP BY"
    ORDERBY = 13,     // "ORDER BY"
    AND = 14,         // "AND"
    OR = 15,          // "OR"
    NOT = 16,         // "NOT"
    IN = 17,          // "IN"
    LIKE = 18,        // "LIKE"
    BETWEEN = 19,     // "BETWEEN"
    UNION = 20,       // "UNION"
    ALL = 21,         // "ALL"
    INTO = 22,        // INTO
    VALUES = 23,      // VALUES
    DISTINCT = 24,    // "DISTINCT"
    VALUES_LIST = 25, // VALUES LIST
    SET = 26,         // SET
    AS = 27,          // ASS (-0-0--)
    // DDL start
    CREATE = 28,     // DDL create
    ALTER = 29,      // DDL ALTER
    TABLE_DDL = 30,  // DDL Column
    ON = 31,         // DDL ON
    INDEX = 32,      // DDL INDEX
    DROP = 33,       // DDL DROP
    COLUMN_DDL = 34, // DDL Column
    ADD = 35,        // DDL add
    SCHEMA = 36,     // DDL Schema
    TO = 37,         // DDL to
    RENAME = 38,     // DDL rename
    VIEW = 39,       // DDL virtual table
    // DDL end
    IDENTIFIER = 40,            // идентификатор (название таблицы, столбца и т.д.)
    STRING = 41,                // строковый литерал
    NUMBER = 42,                // числовой литерал
    EQUAL = 43,                 // =
    EQUAL_TO = 44,              // "=="
    NOT_EQUAL = 45,             // "!="
    LESS_THAN = 46,             // "<"
    GREATER_THAN = 47,          // ">"
    LESS_THAN_OR_EQUAL = 48,    // "<="
    GREATER_THAN_OR_EQUAL = 49, // ">="
    PLUS = 50,                  // "+"
    MINUS = 51,                 // "-"
    MULTIPLY = 52,              // "*"
    DIVIDE = 53,                // "/"
    COMMA = 54,                 // ","
    DOT = 55,                   // "."
    SEMICOLON = 56,             // ";"
    LEFT_PARENTHESIS = 57,      // "("
    RIGHT_PARENTHESIS = 58,     // ")"
    COMMENT = 59,               // комментарий
    VARIABLE = 60,              // переменная
    FUNCTION = 61,              // функция
    TRIGGER = 62,               // триггер
    ERROR = 404,                // ошибка
    QUERY = 64,                 // start AST
    COLUMN = 65,                // Column
    TABLE = 66,                 // Table
    CHAR = 67,                  // Data type char
    INT = 68,                   // Data type INT
    FLOAT = 69,                 // DATA type float
    LIMIT = 70,
    HAVING = 71,
    EXISTS = 72,
    ANY = 73,
    EXCEPT = 74,
    INTERSECT = 75,
    DESC = 76,
    ASC = 77,
    COLUMN_LIST = 78

} tokenType;

typedef struct
{
    tokenType type;
    char lexeme[100];
} token;

typedef struct
{
    char *input;
    int position;
} lexer;

typedef struct TypeMapping
{
    const char *str;
    tokenType type;
} TypeMapping;

extern const TypeMapping keyWords[];
extern const TypeMapping keyPhrases[];
extern const TypeMapping operatorsList[];

lexer *createLexer(char *input);
void destroyLexer(lexer **Lexer);
token getNextToken(lexer **Lexer);

#endif