#include "../semanticAnalizer/semanticAnalizer.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
{
    // Test Lexer
    //-------------
    // Test Sintaxer
    //-------------
    // Test sematic analizer
    token *tokenList = malloc(sizeof(token) * 20);
    char *input =
        "CREATE TABLE table_name (column1 INT, column2 CHAR);";

    lexer *Lexer = createLexer(input);
    int i = 0;
    while (Lexer->position < strlen(Lexer->input))
    {
        tokenList[i] = getNextToken(&Lexer);
        printf("%s - value, %d - type\n", tokenList[i].lexeme, tokenList[i].type);
        i++;
    }
    printf("-----------------------\n");
    int tokenLen = i;
    // Test parser
    ASTNode *root = parse(tokenList, tokenLen);
    printASTNode(root, 0);
    printf("---------------------------\n");
    nodeQueue *queue = makeQueue(root);
    printQueue(queue);
    destroyLexer(&Lexer);
    freeAST(&root);
    free(queue);
}