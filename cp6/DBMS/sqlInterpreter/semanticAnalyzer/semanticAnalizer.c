
#include "semanticAnalizer.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


lexer* createLexer(char *input) {
    lexer *Lexer = malloc(sizeof(lexer));
    Lexer->input = input;
    Lexer->position = 0;
    return Lexer;
}

void destroyLexer(lexer **Lexer) {
    free(*Lexer);
}

token getNextToken(lexer **Lexer) {
    token Token;
    char currentChar = (*Lexer)->input[(*Lexer)->position];

    // Пропустить пробелы и символы новой строки
    while (currentChar == ' ' || currentChar == '\n') {
        (*Lexer)->position++;
        currentChar = (*Lexer)->input[(*Lexer)->position];
    }
    if (currentChar == ',') {
        // Токен является символом ","
        Token.type = SYMBOL;
        Token.lexeme[0] = currentChar;
        Token.lexeme[1] = '\0';
        (*Lexer)->position++;
        


    } else if (currentChar == ';') {
        // Токен является символом ","
        Token.type = SYMBOL;
        Token.lexeme[0] = currentChar;
        Token.lexeme[1] = '\0';
        (*Lexer)->position++;


    }

    // Определить тип токена на основе текущего символа
    else if (isalpha(currentChar) || currentChar == '_') {
        // Токен является идентификатором (именем таблицы, столбца и т. д.)
        Token.type = IDENTIFIER;
        int i = 0;
        while (isalnum(currentChar) || currentChar == '_') {
            Token.lexeme[i++] = currentChar;
            (*Lexer)->position++;
            currentChar = (*Lexer)->input[(*Lexer)->position];
        }
        Token.lexeme[i] = '\0';

        // Udalenie probelov i proverka na keyword
        int j = 0;
        for (i = 0; Token.lexeme[i] != '\0'; i++) {
            if (!isspace(Token.lexeme[i])) {
                Token.lexeme[j++] = Token.lexeme[i];
            }
        }
        Token.lexeme[i] = '\0';

        for (int k = 0; k < NUM_KEYWORDS; k++) {
            if (strcmp(Token.lexeme, keyWords[k]) == 0) {
                Token.type = KEYWORD;
                break;
            }
        }

        for (int k = 0; k < NUM_DATATYPES; k++) {
            if (strcmp(Token.lexeme, dataTypes[k]) == 0) {
                Token.type = DATATYPE;
                break;
            }
        }

        for (int k = 0; k < NUM_KEYPHRASES; k++) {
            if (strcmp(Token.lexeme, keyPhrases[k]) == 0) {
                Token.type = KEYPHRASE;
                break;
            }
        }

    } else if (currentChar == '-' && (*Lexer)->input[(*Lexer)->position + 1] == '-') {
        // Proverka na odnostrochniy comment
        int i = -1;
        (*Lexer)->position++;
        while (1)
        {
            if (currentChar == '\n') break;
            Token.lexeme[i++] = currentChar;
            (*Lexer)->position++;
            currentChar = (*Lexer)->input[(*Lexer)->position];
        } 
        Token.type = COMMENT;
        Token.lexeme[i] = '\0';


    } else if (currentChar == '/' && (*Lexer)->input[(*Lexer)->position + 1] == '*') {
        // Proverka na mnogostrochniy comment
        char *endComment = strstr((*Lexer)->input, "*/");
        if (endComment) {
            Token.type = COMMENT;
            strncpy(Token.lexeme, (*Lexer)->input, endComment - (*Lexer)->input + 2);
            Token.lexeme[endComment - (*Lexer)->input + 2] = '\0';

            (*Lexer)->position = endComment - (*Lexer)->input + 2;
            
        } else {
            Token.type = ERROR;
            strcpy(Token.lexeme, "Wrong comment");
            (*Lexer)->position = strlen((*Lexer)->input);
        }
    } else if (isdigit(currentChar)) {
        // Токен является числовым литералом
        Token.type = LITERAL;
        int i = 0;
        while (isdigit(currentChar) || currentChar == '.') {
            Token.lexeme[i++] = currentChar;
            (*Lexer)->position++;
            currentChar = (*Lexer)->input[(*Lexer)->position];
        }
        Token.lexeme[i] = '\0';


    } else if (currentChar == '\'' || currentChar == '"') {
        // Токен является строковым литералом
        Token.type = LITERAL;
        int i = 0;
        char quoteChar = currentChar;
        Token.lexeme[i++] = currentChar;
        (*Lexer)->position++;
        currentChar = (*Lexer)->input[(*Lexer)->position];
        while (currentChar != '\0' && currentChar != quoteChar) {
            Token.lexeme[i++] = currentChar;
            (*Lexer)->position++;
            currentChar = (*Lexer)->input[(*Lexer)->position];
        }
        if (currentChar == quoteChar) {
            Token.lexeme[i++] = currentChar;
            (*Lexer)->position++;
        }
        Token.lexeme[i] = '\0';


    }  else if (currentChar == '=' || currentChar == '<' || currentChar == '>' || currentChar == '!') {
        // Token yavlyetsya operatorom
        int i = 0;
        Token.type = OPERATOR;
        Token.lexeme[i++] = currentChar;
        (*Lexer)->position++;
        currentChar = (*Lexer)->input[(*Lexer)->position];
        if ((currentChar == '=' && (Token.lexeme[0] == '=' || Token.lexeme[0] == '<' || Token.lexeme[0] == '>' || Token.lexeme[0] == '!'))) {
            Token.lexeme[i++] = currentChar;
            (*Lexer)->position++;
        }
        Token.lexeme[i] = '\0';


    }  else {
        // ERROR huy znaet chto token
        Token.type = ERROR;
        Token.lexeme[0] = currentChar;
        (*Lexer)->position++;
    }
    // Другие типы токенов могут быть добавлены сюда

    return Token;
}



int main() {
    // Test Lexer
    token* tokenList = malloc(sizeof(token) * 20);
    char *input = 
    "/*DELETE FROM table_name\n"
    "WHERE i < b;";
    lexer *Lexer = createLexer(input);
    int i = 0;
    while (Lexer->position < strlen(Lexer->input)) {
        tokenList[i] = getNextToken(&Lexer);
        if (tokenList[i].type == ERROR) printf("ERROR\n");
        printf("%s - value\n", tokenList[i].lexeme);
        i++;
    }
    destroyLexer(&Lexer);
}
