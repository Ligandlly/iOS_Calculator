//
//  Calculator.c
//  Calculator
//
//  Created by LLy on 2019/6/1.
//  Copyright © 2019 LLy. All rights reserved.
//

#include "Calculator.h"

void initStringStack(stringStack *stack) {
    stack->number = 0;
    stack->end = stack->charArray;
    for (size_t i = 0; i < MAX_SIZE; ++i) {
        stack->charArray[i] = NULL;
    }
}

void distroyStringStack(stringStack *stack) {
    for (size_t i = 0; i < stack->number; ++i) {
        free(stack->charArray[i]);
    }
}

void initDoubleStack(doubleStack *stack) {
    stack->number = 0;
    stack->end = stack->doubleArray;
}

void stringPush(stringStack *stack, char *str) {
    if (stack->number == MAX_SIZE) {
        return;
    } else if (strlen(str)){
        *(stack->end) = (char *)calloc(strlen(str) + 1, sizeof(char));
        strcpy(*(stack->end), str);
        ++ stack->end;
        ++ stack->number;
    }
}

doubleStack *doublePush(doubleStack *stack, double n) {
    if (stack->number == MAX_SIZE) {
        return NULL;
    } else {
        *(stack->end) = n;
        ++ stack->end;
        ++ stack->number;
        return stack;
    }
}

stringStack  *stringPop(stringStack *stack) {
    if (stack->number) {
        -- stack->end;
        -- stack->number;
        free(*(stack->end));
        *(stack->end) = NULL;
        return stack;
    } else {
        return NULL;
    }
}

doubleStack *doublePop(doubleStack *stack) {
    if (stack->number) {
        -- stack->end;
        -- stack->number;
        return stack;
    } else {
        return NULL;
    }
}

bool isOper(char c) {
    if ((c >= '0' && c <= '9') || c == '.') {
        return false;
    }
    return true;
}

unsigned char getLevel(char c) {
    switch (c) {
        case '+':
            return 1;
        case '-':
            return 1;
        case '*':
            return 2;
        case '/':
            return 2;
        case '^':
            return 3;
        default:
            return 0;
    }
}

void shuntingYard(const char *s, stringStack *output,stringStack *oper) {
    unsigned int lastOperIndex = 0;
    bool isLastOperRightParenthesis = false;
    size_t lengthOfs = strlen(s);
    for (unsigned int i = 1; i < lengthOfs + 1; ++i) {
        if (isOper(s[i]) || s[i] == '\0') {
            if (s[i] == '(') {
                stringPush(oper, "("); // push '(' into output directly
                lastOperIndex = i;
            } else {
                if(!isLastOperRightParenthesis) { // don't push anything if isLastOperRightParenthesis is true
                    char digit[DIGIT_SIZE];
                    strncpy(digit, s + lastOperIndex + 1, i - lastOperIndex - 1);
                    digit[i - lastOperIndex - 1] = '\0';
                    stringPush(output, digit);
                }
                lastOperIndex = i;
                if (s[i] == ')') {
                    isLastOperRightParenthesis = true;
                    while (oper->number != 0 && strcmp(*(oper->end - 1), "(")) {
                        stringPush(output, *(oper->end - 1));
                        stringPop(oper);
                    }
                    stringPop(oper); // pop '('
                } else {
                    isLastOperRightParenthesis = false;
                    while (oper->number != 0 && getLevel((*(oper->end - 1))[0]) >= getLevel(s[i])) {
                        stringPush(output, *(oper->end - 1));
                        stringPop(oper);
                    }
                    if (s[i] != '\0') {
                        char temp[2] = {s[i], '\0'};
                        stringPush(oper, temp);
                    }
                } // end if-else
            }
        }
    } // end for
    while (oper->number != 0) {
        stringPush(output, *(oper->end - 1));
        stringPop(oper);
    }
    //    distroyStringStack(oper);
}

double calculate(stringStack *output) {
    static doubleStack _result;
    doubleStack* result = &_result;
    initDoubleStack(result);
    for (size_t i = 0; i < output->number; ++i) {
        switch (output->charArray[i][0]) {
            case '+':
                *(result->end - 2) = *(result->end - 1) + *(result->end - 2);
                doublePop(result);
                break;
            case '-':
                *(result->end - 2) = *(result->end - 2) - *(result->end - 1);
                doublePop(result);
                break;
            case '*':
                *(result->end - 2) = *(result->end - 1) * *(result->end - 2);
                doublePop(result);
                break;
            case '/':
                *(result->end - 2) = *(result->end - 2) / *(result->end - 1);
                doublePop(result);
                break;
            case '^':
                *(result->end - 2) = pow(*(result->end - 2), *(result->end - 1));
                doublePop(result);
                break;
            default:
                doublePush(result, atof(output->charArray[i]));
                break;
        }
        }
    return result->doubleArray[0];
}

double wrapper(const char *s) {
    bool isPositive = true;
    if (s[0] == '-') {
        isPositive = false;
    }

    stringStack _output;
    stringStack *output = &_output;
    initStringStack(output);
    stringStack _oper;
    stringStack *oper = &_oper;
    initStringStack(oper);
    
    shuntingYard(s, output, oper);
    double result = calculate(output);
    
    distroyStringStack(output);
    distroyStringStack(oper);
    return isPositive ? result : -result;
}
