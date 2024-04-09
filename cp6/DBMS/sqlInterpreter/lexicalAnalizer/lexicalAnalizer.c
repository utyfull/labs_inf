
#include "lexicalAnalizer.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

const TypeMapping keyWords[] = {
    {"SELECT", SELECT}, {"INSERT", INSERT}, {"UPDATE", UPDATE}, {"DELETE", DELETE}, {"FROM", FROM}, {"WHERE", WHERE}, {"JOIN", JOIN}, {"INNER", INNER}, {"OUTER", OUTER}, {"LEFT", LEFT}, {"RIGHT", RIGHT}, {"ON", ON}, {"GROUPBY", GROUPBY}, {"ORDERBY", ORDERBY}, {"HAVING", HAVING}, {"LIMIT", LIMIT}, {"AND", AND}, {"OR", OR}, {"NOT", NOT}, {"INTO", INTO}, {"VALUES", VALUES}, {"SET", SET}, {"CREATE", CREATE}, {"ALTER", ALTER}, {"INDEX", INDEX}, {"DROP", DROP}, {"ADD", ADD}, {"DISTINCT", DISTINCT}};

const TypeMapping keyPhrases[] = {
    {"EXISTS", EXISTS}, {"IN", IN}, {"ANY", ANY}, {"ALL", ALL}, {"EXCEPT", EXCEPT}, {"INTERSECT", INTERSECT}, {"LIKE", LIKE}, {"BETWEEN", BETWEEN}, {"DESC", DESC}, {"ASC", ASC}};

const TypeMapping operatorsList[] = {
    {"EQUAL", EQUAL}, {"NOT_EQUAL", NOT_EQUAL}, {"LESS_THAN", LESS_THAN}, {"GREATER_THAN", GREATER_THAN}, {"LESS_THAN_OR_EQUAL", LESS_THAN_OR_EQUAL}, {"GREATER_THAN_OR_EQUAL", GREATER_THAN_OR_EQUAL}};

lexer *createLexer(char *input)
{
    lexer *Lexer = malloc(sizeof(lexer));
    Lexer->input = input;
    Lexer->position = 0;
    return Lexer;
}

void destroyLexer(lexer **Lexer)
{
    free(*Lexer);
}

token getNextToken(lexer **Lexer)
{
    token Token;
    char currentChar = (*Lexer)->input[(*Lexer)->position];

    // Пропустить пробелы и символы новой строки
    while (currentChar == ' ' || currentChar == '\n')
    {
        (*Lexer)->position++;
        currentChar = (*Lexer)->input[(*Lexer)->position];
    }
    if (currentChar == ',')
    {
        // Токен является символом ","
        Token.type = COMMA;
        Token.lexeme[0] = currentChar;
        Token.lexeme[1] = '\0';
        (*Lexer)->position++;
    }
    else if (currentChar == ';')
    {
        // Токен является символом ","
        Token.type = SEMICOLON;
        Token.lexeme[0] = currentChar;
        Token.lexeme[1] = '\0';
        (*Lexer)->position++;
    }
    else if (currentChar == '(')
    {
        // Токен является символом "("
        Token.type = LEFT_PARENTHESIS;
        Token.lexeme[0] = currentChar;
        Token.lexeme[1] = '\0';
        (*Lexer)->position++;
    }
    else if (currentChar == ')')
    {
        // Токен является символом ")"
        Token.type = RIGHT_PARENTHESIS;
        Token.lexeme[0] = currentChar;
        Token.lexeme[1] = '\0';
        (*Lexer)->position++;
    }
    else if (currentChar == '*')
    {
        // Токен является символом ")"
        Token.type = ALL;
        Token.lexeme[0] = currentChar;
        Token.lexeme[1] = '\0';
        (*Lexer)->position++;
    }

    // Определить тип токена на основе текущего символа
    else if (isalpha(currentChar) || currentChar == '_')
    {
        // Токен является идентификатором (именем таблицы, столбца и т. д.)
        Token.type = IDENTIFIER;
        int i = 0;
        while (isalnum(currentChar) || currentChar == '_')
        {
            Token.lexeme[i++] = currentChar;
            (*Lexer)->position++;
            currentChar = (*Lexer)->input[(*Lexer)->position];
        }
        Token.lexeme[i] = '\0';

        // Udalenie probelov i proverka na keyword
        int j = 0;
        for (i = 0; Token.lexeme[i] != '\0'; i++)
        {
            if (!isspace(Token.lexeme[i]))
            {
                Token.lexeme[j++] = Token.lexeme[i];
            }
        }
        Token.lexeme[i] = '\0';

        for (int k = 0; k < NUM_KEYWORDS; k++)
        {
            if (strcmp(Token.lexeme, keyWords[k].str) == 0)
            {
                Token.type = keyWords[k].type;
                break;
            }
        }

        for (int k = 0; k < NUM_KEYPHRASES; k++)
        {
            if (strcmp(Token.lexeme, keyPhrases[k].str) == 0)
            {
                Token.type = keyPhrases[k].type;
                break;
            }
        }

        if (strcmp(Token.lexeme, "TABLE") == 0)
            Token.type = TABLE_DDL;
        if (strcmp(Token.lexeme, "COLUMN") == 0)
            Token.type = COLUMN_DDL;
    }
    else if (currentChar == '-' && (*Lexer)->input[(*Lexer)->position + 1] == '-')
    {
        // Proverka na odnostrochniy comment
        int i = -1;
        (*Lexer)->position++;
        while (1)
        {
            if (currentChar == '\n')
                break;
            Token.lexeme[i++] = currentChar;
            (*Lexer)->position++;
            currentChar = (*Lexer)->input[(*Lexer)->position];
        }
        Token.type = COMMENT;
        Token.lexeme[i] = '\0';
    }
    else if (currentChar == '/' && (*Lexer)->input[(*Lexer)->position + 1] == '*')
    {
        // Proverka na mnogostrochniy comment
        char *endComment = strstr((*Lexer)->input, "*/");
        if (endComment)
        {
            Token.type = COMMENT;
            strncpy(Token.lexeme, (*Lexer)->input, endComment - (*Lexer)->input + 2);
            Token.lexeme[endComment - (*Lexer)->input + 2] = '\0';

            (*Lexer)->position = endComment - (*Lexer)->input + 2;
        }
        else
        {
            Token.type = ERROR;
            strcpy(Token.lexeme, "Wrong comment");
            (*Lexer)->position = strlen((*Lexer)->input);
        }
    }
    else if (isdigit(currentChar))
    {
        // Токен является числовым литералом
        Token.type = NUMBER;
        int i = 0;
        while (isdigit(currentChar) || currentChar == '.')
        {
            Token.lexeme[i++] = currentChar;
            (*Lexer)->position++;
            currentChar = (*Lexer)->input[(*Lexer)->position];
        }
        Token.lexeme[i] = '\0';
    }
    else if (currentChar == '\'' || currentChar == '"')
    {
        // Токен является строковым литералом
        Token.type = STRING;
        int i = 0;
        char quoteChar = currentChar;
        Token.lexeme[i++] = currentChar;
        (*Lexer)->position++;
        currentChar = (*Lexer)->input[(*Lexer)->position];
        while (currentChar != '\0' && currentChar != quoteChar)
        {
            Token.lexeme[i++] = currentChar;
            (*Lexer)->position++;
            currentChar = (*Lexer)->input[(*Lexer)->position];
        }
        if (currentChar == quoteChar)
        {
            Token.lexeme[i++] = currentChar;
            (*Lexer)->position++;
        }
        Token.lexeme[i] = '\0';
    }
    else if (currentChar == '=' || currentChar == '<' || currentChar == '>' || currentChar == '!')
    {
        // Token yavlyetsya operatorom
        int i = 0;
        if (currentChar == '=')
        {
            Token.type = EQUAL;
        }
        else if (currentChar == '<')
        {
            Token.type = LESS_THAN;
        }
        else if (currentChar == '>')
        {
            Token.type = GREATER_THAN;
        }
        else if (currentChar == '!')
        {
            Token.type = ERROR;
        }
        Token.lexeme[i++] = currentChar;
        (*Lexer)->position++;
        currentChar = (*Lexer)->input[(*Lexer)->position];
        if ((currentChar == '=' && (Token.lexeme[0] == '=' || Token.lexeme[0] == '<' || Token.lexeme[0] == '>' || Token.lexeme[0] == '!')))
        {
            if (currentChar == '=' && Token.lexeme[0] == '=')
            {
                Token.type = EQUAL_TO;
            }
            else if (currentChar == '=' && Token.lexeme[0] == '<')
            {
                Token.type = LESS_THAN_OR_EQUAL;
            }
            else if (currentChar == '=' && Token.lexeme[0] == '>')
            {
                Token.type = GREATER_THAN_OR_EQUAL;
            }
            else if (currentChar == '=' && Token.lexeme[0] == '!')
            {
                Token.type = NOT_EQUAL;
            }
            else
            {
                Token.type = ERROR;
            }
            Token.lexeme[i++] = currentChar;
            (*Lexer)->position++;
        }
        Token.lexeme[i] = '\0';
    }
    else
    {
        // ERROR huy znaet chto token
        Token.type = ERROR;
        Token.lexeme[0] = currentChar;
        (*Lexer)->position++;
    }
    // Другие типы токенов могут быть добавлены сюда

    return Token;
}
