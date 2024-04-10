
#include "sintaxAnalizer.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ASTNode *createASTNode(tokenType type, const char *lexeme)
{
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    if (node == NULL)
    {
        fprintf(stderr, "ERROR MEMORY ALLOC");
        exit(EXIT_FAILURE);
    }
    node->type = type;
    strncpy(node->lexeme, lexeme, 100 - 1);
    node->lexeme[100 - 1] = '\0';
    node->numChildren = 0;
    return node;
}

void freeAST(ASTNode **root)
{
    if (*root == NULL)
        return;
    for (int i = 0; i < (*root)->numChildren; i++)
        freeAST(&(*root)->children[i]);
    free(*root);
}

ASTNode *parse(token *tokenList, int numTokens)
{

    // AST root
    ASTNode *root = createASTNode(QUERY, "query");
    int currentTokenIndex = 0;

    // Parce main structure
    while (currentTokenIndex < numTokens)
    {
        token currentToken = tokenList[currentTokenIndex];

        if (currentToken.type == SEMICOLON)
        {
            break;
        }
        else if (currentToken.type == COMMENT)
        {
            currentTokenIndex++;
            continue;
        }
        // If SELECT
        else if (currentToken.type == SELECT)
        {
            ASTNode *selectNode = createASTNode(SELECT, "SELECT");

            currentTokenIndex++;

            if (tokenList[currentTokenIndex].type == DISTINCT)
            {
                ASTNode *distinctNode = createASTNode(DISTINCT, tokenList[currentTokenIndex].lexeme);
                selectNode->children[selectNode->numChildren++] = distinctNode;
                currentTokenIndex++;
            }

            // Column list
            while (currentTokenIndex < numTokens && tokenList[currentTokenIndex].type != FROM)
            {
                if (tokenList[currentTokenIndex].type == COMMA)
                {
                    currentTokenIndex++;
                    continue;
                }
                ASTNode *columnNode = createASTNode(COLUMN, tokenList[currentTokenIndex].lexeme);
                selectNode->children[selectNode->numChildren++] = columnNode;
                currentTokenIndex++;
            }
            root->children[root->numChildren++] = selectNode;
            continue;

            // If FROM
        }
        else if (currentToken.type == FROM)
        {
            ASTNode *fromNode = createASTNode(FROM, "FROM");

            currentTokenIndex++;

            // Table list
            while (currentTokenIndex < numTokens && tokenList[currentTokenIndex].type != WHERE)
            {

                if (tokenList[currentTokenIndex].type == SEMICOLON)
                {
                    break;
                }
                ASTNode *tableNode = createASTNode(TABLE, tokenList[currentTokenIndex].lexeme);
                fromNode->children[fromNode->numChildren++] = tableNode;

                currentTokenIndex++;
            }
            root->children[root->numChildren++] = fromNode;
            continue;

            // If Where
        }
        else if (currentToken.type == WHERE)
        {
            ASTNode *whereNode = createASTNode(WHERE, "WHERE");

            currentTokenIndex++;

            while (currentTokenIndex < numTokens)
            {
                token currentToken = tokenList[currentTokenIndex];
                int flag = 0;

                // If operator (<, == , != i t. d.)
                for (int i = 0; i < NUM_OPERATORS; i++)
                {
                    if (currentToken.type == operatorsList[i].type)
                    {

                        ASTNode *compressionNode = createASTNode(operatorsList[i].type, currentToken.lexeme);
                        whereNode->children[whereNode->numChildren++] = compressionNode;
                        flag = 1;

                        currentTokenIndex++;
                    }
                }

                // If logical operator (AND, OR, NOT)
                if (currentToken.type == AND || currentToken.type == OR || currentToken.type == NOT)
                {

                    ASTNode *logicalNode = createASTNode(currentToken.type, currentToken.lexeme);
                    whereNode->children[whereNode->numChildren++] = logicalNode;

                    currentTokenIndex++;
                }

                // If identifier or value
                else if (currentToken.type == IDENTIFIER || currentToken.type == NUMBER || currentToken.type == STRING)
                {

                    ASTNode *wtfNode = createASTNode(currentToken.type, currentToken.lexeme);
                    whereNode->children[whereNode->numChildren++] = wtfNode;

                    currentTokenIndex++;
                }
                else
                {
                    if (flag == 0)
                        break;
                }
            }
            root->children[root->numChildren++] = whereNode;
            continue;
        }
        else if (currentToken.type == INSERT)
        {
            ASTNode *insertNode = createASTNode(INSERT, "INSERT");

            currentTokenIndex++;

            if (tokenList[currentTokenIndex].type != INTO)
            {
                fprintf(stderr, "Ошибка: Ожидалось ключевое слово INTO после INSERT\n");
                exit(EXIT_FAILURE);
            }

            currentTokenIndex++;

            if (tokenList[currentTokenIndex].type != IDENTIFIER)
            {
                fprintf(stderr, "Ошибка: Ожидалось имя таблицы после INTO\n");
                exit(EXIT_FAILURE);
            }

            ASTNode *tableNode = createASTNode(TABLE, tokenList[currentTokenIndex].lexeme);
            insertNode->children[insertNode->numChildren++] = tableNode;

            currentTokenIndex++;

            if (tokenList[currentTokenIndex].type == LEFT_PARENTHESIS)
            {
                ASTNode *columnsListNode = createASTNode(COLUMN_LIST, "COLUMN_LIST");

                (currentTokenIndex)++;

                while (currentTokenIndex < numTokens)
                {

                    if (tokenList[currentTokenIndex].type == RIGHT_PARENTHESIS)
                    {

                        break;
                    }
                    else if (tokenList[currentTokenIndex].type == COMMA)
                    {

                        currentTokenIndex++;
                    }
                    else
                    {

                        ASTNode *columnNode = createASTNode(tokenList[currentTokenIndex].type, tokenList[currentTokenIndex].lexeme);
                        columnsListNode->children[columnsListNode->numChildren++] = columnNode;

                        currentTokenIndex++;
                    }
                }

                insertNode->children[insertNode->numChildren++] = columnsListNode;

                if (tokenList[currentTokenIndex].type != RIGHT_PARENTHESIS)
                {
                    fprintf(stderr, "Ошибка: Ожидалась закрывающая скобка после списка значений\n");
                    exit(EXIT_FAILURE);
                }

                currentTokenIndex++;
            }

            if (tokenList[currentTokenIndex].type != VALUES)
            {
                fprintf(stderr, "Ошибка: Ожидалось ключевое слово VALUES после имени таблицы\n");
                exit(EXIT_FAILURE);
            }

            currentTokenIndex++;

            if (tokenList[currentTokenIndex].type != LEFT_PARENTHESIS)
            {
                fprintf(stderr, "Ошибка: Ожидалась открывающая скобка перед списком значений\n");
                exit(EXIT_FAILURE);
            }

            ASTNode *valuesListNode = createASTNode(VALUES_LIST, "VALUES_LIST");

            (currentTokenIndex)++;

            while (currentTokenIndex < numTokens)
            {

                if (tokenList[currentTokenIndex].type == RIGHT_PARENTHESIS)
                {

                    break;
                }
                else if (tokenList[currentTokenIndex].type == COMMA)
                {

                    currentTokenIndex++;
                }
                else
                {

                    ASTNode *valueNode = createASTNode(tokenList[currentTokenIndex].type, tokenList[currentTokenIndex].lexeme);
                    valuesListNode->children[valuesListNode->numChildren++] = valueNode;

                    currentTokenIndex++;
                }
            }

            if (tokenList[currentTokenIndex].type != RIGHT_PARENTHESIS)
            {
                fprintf(stderr, "Ошибка: Ожидалась закрывающая скобка после списка значений\n");
                exit(EXIT_FAILURE);
            }

            insertNode->children[insertNode->numChildren++] = valuesListNode;
            root->children[root->numChildren++] = insertNode;
            currentTokenIndex++;
            continue;
        }
        else if (currentToken.type == UPDATE)
        {

            ASTNode *updateNode = createASTNode(UPDATE, "UPDATE");

            currentTokenIndex++;

            if (tokenList[currentTokenIndex].type != IDENTIFIER)
            {
                fprintf(stderr, "Ошибка: Ожидалось имя таблицы после UPDATE\n");
                exit(EXIT_FAILURE);
            }

            ASTNode *tableNode = createASTNode(TABLE, tokenList[currentTokenIndex].lexeme);
            updateNode->children[updateNode->numChildren++] = tableNode;

            currentTokenIndex++;

            if (tokenList[currentTokenIndex].type != SET)
            {
                fprintf(stderr, "Ошибка: Ожидалось ключевое слово SET после имени таблицы\n");
                exit(EXIT_FAILURE);
            }

            ASTNode *setNode = createASTNode(SET, "SET");

            currentTokenIndex++;

            while (currentTokenIndex < numTokens)
            {

                if (tokenList[currentTokenIndex].type == IDENTIFIER)
                {

                    ASTNode *columnNode = createASTNode(COLUMN, tokenList[currentTokenIndex].lexeme);
                    setNode->children[setNode->numChildren++] = columnNode;

                    currentTokenIndex++;
                    if (tokenList[currentTokenIndex].type != EQUAL)
                    {
                        fprintf(stderr, "Ошибка: Ожидался оператор присваивания после имени столбца\n");
                        exit(EXIT_FAILURE);
                    }

                    currentTokenIndex++;

                    if (tokenList[currentTokenIndex].type != STRING && tokenList[currentTokenIndex].type != NUMBER)
                    {
                        fprintf(stderr, "Ошибка: Ожидалось значение после оператора присваивания\n");
                        exit(EXIT_FAILURE);
                    }

                    ASTNode *valueNode = createASTNode(tokenList[currentTokenIndex].type, tokenList[currentTokenIndex].lexeme);
                    setNode->children[setNode->numChildren++] = valueNode;
                }
                else if (tokenList[currentTokenIndex].type == WHERE)
                {
                    currentTokenIndex--;
                    break;
                }
                else if (tokenList[currentTokenIndex].type == COMMA)
                {

                    (currentTokenIndex)++;
                }
                else
                {
                    fprintf(stderr, "Ошибка: Ожидалось имя столбца или ключевое слово WHERE\n");
                    exit(EXIT_FAILURE);
                }

                currentTokenIndex++;
            }
            updateNode->children[updateNode->numChildren++] = setNode;
            root->children[root->numChildren++] = updateNode;
            currentTokenIndex++;
            continue;
        }

        // if DELETE
        else if (currentToken.type == DELETE)
        {

            ASTNode *deleteNode = createASTNode(DELETE, "DELETE");

            currentTokenIndex++;

            if (tokenList[currentTokenIndex].type != FROM)
            {
                fprintf(stderr, "ERROR: NEED FROM after DELETE");
                exit(EXIT_FAILURE);
            }

            currentTokenIndex++;

            if (tokenList[currentTokenIndex].type != IDENTIFIER)
            {
                fprintf(stderr, "ERROR: NEED TAbLE NAME AFTER FROM");
                exit(EXIT_FAILURE);
            }

            ASTNode *tableNode = createASTNode(TABLE, tokenList[currentTokenIndex].lexeme);
            deleteNode->children[deleteNode->numChildren++] = tableNode;

            root->children[root->numChildren++] = deleteNode;
            currentTokenIndex++;

            // if create
        }
        else if (currentToken.type == CREATE)
        {

            ASTNode *createNode = createASTNode(CREATE, "CREATE");
            currentTokenIndex++;

            if (tokenList[currentTokenIndex].type != INDEX && tokenList[currentTokenIndex].type != TABLE_DDL && tokenList[currentTokenIndex].type != COLUMN_DDL && tokenList[currentTokenIndex].type != VIEW)
            {
                fprintf(stderr, "ERROR: NEED STRUCTURE AFTER CREATE\n");
                exit(EXIT_FAILURE);
            }

            ASTNode *createObjectBig = createASTNode(tokenList[currentTokenIndex].type, tokenList[currentTokenIndex].lexeme);
            currentTokenIndex++;

            ASTNode *createObject = createASTNode(tokenList[currentTokenIndex].type, tokenList[currentTokenIndex].lexeme);
            currentTokenIndex++;

            if (tokenList[currentTokenIndex].type != LEFT_PARENTHESIS)
            {
                fprintf(stderr, "Ошибка: Ожидалась открывающая скобка перед списком значений\n");
                exit(EXIT_FAILURE);
            }
            currentTokenIndex++;

            ASTNode *valuesListNode = createASTNode(VALUES_LIST, "VALUES_LIST");

            while (currentTokenIndex < numTokens)
            {

                if (tokenList[currentTokenIndex].type == RIGHT_PARENTHESIS)
                {

                    break;
                }
                else if (tokenList[currentTokenIndex].type == COMMA)
                {

                    currentTokenIndex++;
                }
                else
                {

                    if (strcmp(tokenList[currentTokenIndex].lexeme, "INT") == 0)
                    {
                        tokenList[currentTokenIndex].type = INT;
                    }
                    else if (strcmp(tokenList[currentTokenIndex].lexeme, "CHAR") == 0)
                    {
                        tokenList[currentTokenIndex].type = CHAR;
                    }
                    else if (strcmp(tokenList[currentTokenIndex].lexeme, "FLOAT") == 0)
                    {
                        tokenList[currentTokenIndex].type = FLOAT;
                    }
                    ASTNode *valueNode = createASTNode(tokenList[currentTokenIndex].type, tokenList[currentTokenIndex].lexeme);
                    valuesListNode->children[valuesListNode->numChildren++] = valueNode;

                    currentTokenIndex++;
                }
            }

            createObjectBig->children[createObjectBig->numChildren++] = valuesListNode;
            createObjectBig->children[createObjectBig->numChildren++] = createObject;
            createNode->children[createNode->numChildren++] = createObjectBig;
            if (tokenList[currentTokenIndex].type != RIGHT_PARENTHESIS)
            {
                fprintf(stderr, "Ошибка: Ожидалась закрывающая скобка после списка значений\n");
                exit(EXIT_FAILURE);
            }
            root->children[root->numChildren++] = createNode;
            currentTokenIndex++;
        }
        else if (currentToken.type == ORDERBY)
        {
            ASTNode *orderBy = createASTNode(ORDERBY, "ORDERBY");
            currentTokenIndex++;

            while ((tokenList[currentTokenIndex].type != DESC || tokenList[currentTokenIndex].type != ASC) && currentTokenIndex < numTokens)
            {
                if (tokenList[currentTokenIndex].type == SEMICOLON)
                {
                    break;
                }
                else if (tokenList[currentTokenIndex].type == COMMA)
                {
                    currentTokenIndex++;
                    continue;
                }
                else
                {
                    ASTNode *columnNode = createASTNode(COLUMN, tokenList[currentTokenIndex].lexeme);
                    orderBy->children[orderBy->numChildren++] = columnNode;
                    currentTokenIndex++;
                }
            }

            root->children[root->numChildren++] = orderBy;
        }
        else
        {
            // Errors
            fprintf(stderr, "ERROR: WRONG TOKEN: %s\n", currentToken.lexeme);
            exit(EXIT_FAILURE);
        }
    }
    return root;
}

void printASTNode(ASTNode *node, int depth)
{
    for (int i = 0; i < depth; ++i)
    {
        printf("  ");
    }

    printf("Type: %d, Lexeme: %s\n", node->type, node->lexeme);

    for (int i = 0; i < node->numChildren; ++i)
    {
        printASTNode(node->children[i], depth + 1);
    }
}
