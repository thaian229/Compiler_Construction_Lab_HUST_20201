/* Scanner
 * @copyright (c) 2008, Hedspi, Hanoi University of Technology
 * @author Huu-Duc Nguyen
 * @version 1.0
 */

#include <stdio.h>
#include <stdlib.h>

#include "reader.h"
#include "charcode.h"
#include "token.h"
#include "error.h"

extern int lineNo;
extern int colNo;
extern int currentChar;

extern CharCode charCodes[];

int state = 0;

/***************************************************************/

Token *getToken(void)
{
    Token *token;
    int ln, cn;

    // Initialize DFA state:
    state = 0;
    ln = lineNo;
    cn = colNo;
    char ident[MAX_IDENT_LEN + 1];
    char number[MAX_NUMBER_LEN + 1];
    char constChar;
    int i = 0;

    // Run DFA
    while (1)
    {
        switch (state)
        {
        case 0:
            if (currentChar == EOF)
            {
                state = 37;
                break;
            }
            switch (charCodes[currentChar])
            {
            case CHAR_SPACE:
                state = 1;
                break;

            case CHAR_LPAR:
                state = 2;
                break;

            case CHAR_LETTER:
                state = 8;
                break;

            case CHAR_DIGIT:
                state = 10;
                break;

            case CHAR_PLUS:
                state = 12;
                break;

            case CHAR_MINUS:
                state = 13;
                break;

            case CHAR_TIMES:
                state = 14;
                break;

            case CHAR_SLASH:
                state = 15;
                break;

            case CHAR_EQ:
                state = 16;
                break;

            case CHAR_COMMA:
                state = 17;
                break;

            case CHAR_SEMICOLON:
                state = 18;
                break;

            case CHAR_PERIOD:
                state = 19;
                break;

            case CHAR_GT:
                state = 22;
                break;

            case CHAR_LT:
                state = 25;
                break;

            case CHAR_EXCLAIMATION:
                state = 28;
                break;

            case CHAR_COLON:
                state = 31;
                break;

            case CHAR_SINGLEQUOTE:
                state = 34;
                break;

            case CHAR_RPAR:
                state = 39;
                break;

            default:
                state = 38;
                break;
            }
            break;
        case 1:
            readChar();
            if ((currentChar != EOF) && (charCodes[currentChar] == CHAR_SPACE))
            {
                state = 1;
            }
            else
            {
                return getToken();
            }
            break;

        case 2:
            readChar();
            switch (charCodes[currentChar])
            {
            case CHAR_TIMES:
                state = 3;
                break;

            case CHAR_PERIOD:
                state = 6;
                break;

            default:
                state = 7;
                break;
            }
            break;

        case 3:
            readChar();
            if (charCodes[currentChar] == CHAR_TIMES)
            {
                state = 4;
            }
            else if (currentChar == EOF)
            {
                state = 40;
            }
            else
            {
                state = 3;
            }
            break;

        case 4:
            readChar();
            if (charCodes[currentChar] == CHAR_TIMES)
            {
                state = 4;
            }
            else if (currentChar == EOF)
            {
                state = 40;
            }
            else if (charCodes[currentChar] == CHAR_RPAR)
            {
                state = 5;
            }
            else
            {
                state = 3;
            }
            break;

        case 5:
            readChar();
            return getToken();
            break;

        case 6:
            readChar();
            return makeToken(SB_LSEL, ln, cn);
            break;

        case 7:
            return makeToken(SB_LPAR, ln, cn);
            break;

        case 8:
            ident[i] = currentChar;
            ++i;
            readChar();
            switch (charCodes[currentChar])
            {
            case CHAR_LETTER:
                state = 8;
                break;

            case CHAR_DIGIT:
                state = 8;
                break;

            default:
                state = 9;
                break;
            }
            break;

        case 9:
            if (i > MAX_IDENT_LEN)
            {
                error(ERR_IDENTTOOLONG, ln, cn);
            }
            else
            {
                if (checkKeyword(ident) == TK_NONE)
                {
                    token = makeToken(TK_IDENT, ln, cn);
                    for (int j = 0; j < i; j++)
                    {
                        token->string[j] = ident[j];
                    }
                    return token;
                }
                else
                {
                    return makeToken(checkKeyword(ident), ln, cn);
                }
            }
            break;

        case 10:
            number[i] = currentChar;
            i++;
            readChar();
            switch (charCodes[currentChar])
            {
            case CHAR_DIGIT:
                state = 10;
                break;

            default:
                state = 11;
                break;
            }
            break;

        case 11:
            token = makeToken(TK_NUMBER, ln, cn);
            if (i > MAX_NUMBER_LEN)
            {
                error(ERR_NUMBERTOOLONG, ln, cn);
            }
            else
            {
                for (int j = 0; j < i; j++)
                {
                    token->string[j] = number[j];
                }
                token->value = atoi(token->string);
                return token;
            }
            break;

        case 12:
            readChar();
            return makeToken(SB_PLUS, ln, cn);
            break;

        case 13:
            readChar();
            return makeToken(SB_MINUS, ln, cn);
            break;

        case 14:
            readChar();
            return makeToken(SB_TIMES, ln, cn);
            break;

        case 15:
            readChar();
            return makeToken(SB_SLASH, ln, cn);
            break;

        case 16:
            readChar();
            return makeToken(SB_EQ, ln, cn);
            break;

        case 17:
            readChar();
            return makeToken(SB_COMMA, ln, cn);
            break;

        case 18:
            readChar();
            return makeToken(SB_SEMICOLON, ln, cn);
            break;

        case 19:
            readChar();
            switch (charCodes[currentChar])
            {
            case CHAR_RPAR:
                state = 20;
                break;

            default:
                state = 21;
                break;
            }
            break;

        case 20:
            readChar();
            return makeToken(SB_RSEL, ln, cn);
            break;

        case 21:
            return makeToken(SB_PERIOD, ln, cn);
            break;

        case 22:
            readChar();
            switch (charCodes[currentChar])
            {
            case CHAR_EQ:
                state = 23;
                break;

            default:
                state = 24;
                break;
            }
            break;

        case 23:
            readChar();
            return makeToken(SB_GE, ln, cn);
            break;

        case 24:
            return makeToken(SB_GT, ln, cn);
            break;

        case 25:
            readChar();
            switch (charCodes[currentChar])
            {
            case CHAR_EQ:
                state = 26;
                break;

            default:
                state = 27;
                break;
            }
            break;

        case 26:
            readChar();
            return makeToken(SB_LE, ln, cn);
            break;

        case 27:
            return makeToken(SB_LT, ln, cn);
            break;

        case 28:
            readChar();
            switch (charCodes[currentChar])
            {
            case CHAR_EQ:
                state = 29;
                break;

            default:
                state = 30;
                break;
            }
            break;

        case 29:
            readChar();
            return makeToken(SB_NEQ, ln, cn);
            break;

        case 30:
            error(ERR_INVALIDSYMBOL, ln, cn);
            break;

        case 31:
            readChar();
            switch (charCodes[currentChar])
            {
            case CHAR_EQ:
                state = 32;
                break;

            default:
                state = 33;
                break;
            }
            break;

        case 32:
            readChar();
            return makeToken(SB_ASSIGN, ln, cn);
            break;

        case 33:
            return makeToken(SB_COLON, ln, cn);
            break;

        case 34:
            readChar();
            if (currentChar == EOF || charCodes[currentChar] == CHAR_UNKNOWN)
            {
                error(ERR_INVALIDCHARCONSTANT, ln, cn);
            }
            else if (charCodes[currentChar] == CHAR_SINGLEQUOTE)
            {
                state = 36;
            }
            else
            {
                state = 35;
            }
            break;

        case 35:
            constChar = currentChar;
            readChar();
            if (currentChar == EOF || charCodes[currentChar] == CHAR_UNKNOWN)
            {
                error(ERR_INVALIDCHARCONSTANT, ln, cn);
            }
            else if (charCodes[currentChar] == CHAR_SINGLEQUOTE)
            {
                state = 36;
            }
            else
            {
                error(ERR_INVALIDCHARCONSTANT, ln, cn);
            }
            break;

        case 36:
            readChar();
            token = makeToken(TK_CHAR, ln, cn);
            if (constChar)
            {
                token->string[0] = constChar;
            }
            return token;
            break;

        case 37:
            readChar();
            return makeToken(TK_EOF, ln, cn);
            break;

        case 38:
            error(ERR_INVALIDSYMBOL, ln, cn);
            break;

        case 39:
            readChar();
            return makeToken(SB_RPAR, ln, cn);
            break;

        case 40:
            error(ERR_INVALIDSYMBOL, ln, cn);
            break;

        default:
            token = makeToken(TK_NONE, lineNo, colNo);
            error(ERR_INVALIDSYMBOL, lineNo, colNo);
            readChar();
            return token;
            break;
        }
    }
}

/******************************************************************/

void printToken(Token *token)
{

    printf("%d-%d:", token->lineNo, token->colNo);

    switch (token->tokenType)
    {
    case TK_NONE:
        printf("TK_NONE\n");
        break;
    case TK_IDENT:
        printf("TK_IDENT(%s)\n", token->string);
        break;
    case TK_NUMBER:
        printf("TK_NUMBER(%s)\n", token->string);
        break;
    case TK_CHAR:
        printf("TK_CHAR(\'%s\')\n", token->string);
        break;
    case TK_EOF:
        printf("TK_EOF\n");
        break;

    case KW_PROGRAM:
        printf("KW_PROGRAM\n");
        break;
    case KW_CONST:
        printf("KW_CONST\n");
        break;
    case KW_TYPE:
        printf("KW_TYPE\n");
        break;
    case KW_VAR:
        printf("KW_VAR\n");
        break;
    case KW_INTEGER:
        printf("KW_INTEGER\n");
        break;
    case KW_CHAR:
        printf("KW_CHAR\n");
        break;
    case KW_ARRAY:
        printf("KW_ARRAY\n");
        break;
    case KW_OF:
        printf("KW_OF\n");
        break;
    case KW_FUNCTION:
        printf("KW_FUNCTION\n");
        break;
    case KW_PROCEDURE:
        printf("KW_PROCEDURE\n");
        break;
    case KW_BEGIN:
        printf("KW_BEGIN\n");
        break;
    case KW_END:
        printf("KW_END\n");
        break;
    case KW_CALL:
        printf("KW_CALL\n");
        break;
    case KW_IF:
        printf("KW_IF\n");
        break;
    case KW_THEN:
        printf("KW_THEN\n");
        break;
    case KW_ELSE:
        printf("KW_ELSE\n");
        break;
    case KW_WHILE:
        printf("KW_WHILE\n");
        break;
    case KW_DO:
        printf("KW_DO\n");
        break;
    case KW_FOR:
        printf("KW_FOR\n");
        break;
    case KW_TO:
        printf("KW_TO\n");
        break;

    case SB_SEMICOLON:
        printf("SB_SEMICOLON\n");
        break;
    case SB_COLON:
        printf("SB_COLON\n");
        break;
    case SB_PERIOD:
        printf("SB_PERIOD\n");
        break;
    case SB_COMMA:
        printf("SB_COMMA\n");
        break;
    case SB_ASSIGN:
        printf("SB_ASSIGN\n");
        break;
    case SB_EQ:
        printf("SB_EQ\n");
        break;
    case SB_NEQ:
        printf("SB_NEQ\n");
        break;
    case SB_LT:
        printf("SB_LT\n");
        break;
    case SB_LE:
        printf("SB_LE\n");
        break;
    case SB_GT:
        printf("SB_GT\n");
        break;
    case SB_GE:
        printf("SB_GE\n");
        break;
    case SB_PLUS:
        printf("SB_PLUS\n");
        break;
    case SB_MINUS:
        printf("SB_MINUS\n");
        break;
    case SB_TIMES:
        printf("SB_TIMES\n");
        break;
    case SB_SLASH:
        printf("SB_SLASH\n");
        break;
    case SB_LPAR:
        printf("SB_LPAR\n");
        break;
    case SB_RPAR:
        printf("SB_RPAR\n");
        break;
    case SB_LSEL:
        printf("SB_LSEL\n");
        break;
    case SB_RSEL:
        printf("SB_RSEL\n");
        break;
    }
}

int scan(char *fileName)
{
    Token *token;

    if (openInputStream(fileName) == IO_ERROR)
        return IO_ERROR;

    token = getToken();
    while (token->tokenType != TK_EOF)
    {
        printToken(token);
        free(token);
        token = getToken();
    }

    free(token);
    closeInputStream();
    return IO_SUCCESS;
}

/******************************************************************/

int main(int argc, char *argv[])
{
    if (argc <= 1)
    {
        printf("scanner: no input file.\n");
        return -1;
    }

    if (scan(argv[1]) == IO_ERROR)
    {
        printf("Can\'t read input file!\n");
        return -1;
    }

    return 0;
}
