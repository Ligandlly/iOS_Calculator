//
//  Calculator.h
//  Calculator
//
//  Created by  on 2019/6/3.
//  Copyright © 2019 GTEGZGX-BXBWRCF. All rights reserved.
//

#ifndef Calculator_h
#define Calculator_h

#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100
#define DIGIT_SIZE 20

typedef struct _stringStack {
    char *charArray[MAX_SIZE];
    char **end;  /* pointer to the first empty address, as same as the end iterator in cpp */
    size_t number;  /* the number of items */
} stringStack;

typedef struct _doubleStack {
    double doubleArray[MAX_SIZE];
    double *end;
    size_t number;
} doubleStack;

void initStringStack(stringStack *stack);
void distroyStringStack(stringStack *stack);
void initDoubleStack(doubleStack *stack);
void stringPush(stringStack *stack, char *str);
doubleStack *doublePush(doubleStack *stack, double n);
stringStack  *stringPop(stringStack *stack);
doubleStack *doublePop(doubleStack *stack);
bool isOper(char c);
unsigned char getLevel(char c);
void shuntingYard(const char *  s, stringStack *output,stringStack *oper);
double calculate(stringStack *output);
double wrapper(const char *s);
#endif /* Calculator_h */
