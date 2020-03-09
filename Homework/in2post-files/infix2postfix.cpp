#include "infix2postfix.h"
#include <iostream>
#include <stack>
#include <string>

struct Operator
{
    Operator(char op, int precedence) : op(op), precedence(precedence)
    {}
    char op;
    int precedence;
    int prioritycompare(const Operator & other)
    {
        return precedence - other.precedence;
    }
};

static bool isNumber(char token)
{
    return token >= '0' && token <= '9';
}

static bool isOperator(char token)
{
    return token == '+' || token == '-' || token == '*' || token == '/';
}

static Operator convertChartoOperator(char op)
{
    if(op == '+' || op == '-')
        return Operator(op, 3);
    else if(op == '*' || op == '/')
        return Operator(op, 2);
    else
    {
        std::cout << "?Unknown operator yet " << op << std::endl;
        return Operator(op, 0);
    }
}

// Positive means stack lower precedance. Negative means stack has higher precedance
static int comparePrecedance(char stackToken, char token)
{
    Operator stackOp = convertChartoOperator(stackToken);
    Operator tokenOp = convertChartoOperator(token);
    return stackOp.prioritycompare(tokenOp);
}

static bool isHigherPrecedance(char firstToken, char secondToken)
{
    return comparePrecedance(firstToken, secondToken) <= 0;
}

int Evaluate( std::string const& postfix )
{
    std::stack<char> stack; //( postfix.length() );

    for ( std::string::const_iterator it = postfix.begin(); it != postfix.end(); ++it)
    {
        char token = *it;

        if (isNumber(token))
        {
            stack.push(token - '0');
        }
        else
            {
            int arg2 = stack.top();
            stack.pop();
            int arg1 = stack.top();
            stack.pop();

            switch(token)
            {
                case '+':
                    stack.push( arg1 + arg2);
                    break;
                case '*':
                    stack.push(arg1 * arg2);
                    break;
                case '-':
                    stack.push(arg1 - arg2);
                    break;
                case '/':
                    stack.push(arg1 / arg2);
                    break;
                default:
                    std::cout << "Unknown operator" << std::endl;
                    return 0;
            }
        }
    }
    return stack.top();
}

std::string Infix2postfix(std::string const &postfix)
{
    std::string result ="";
    std::stack<char> stack;
    for ( std::string::const_iterator it = postfix.begin(); it != postfix.end(); ++it)
    {
        char token = *it;

        if(token == ' ' || token == ',') continue;

        if(isNumber(token))
        {
            result += token;
        }
        else if(token == '(')
        {
            stack.push(token);
        }
        else if(token == ')')
        {
            char stackToken;
            while((stackToken = stack.top()) != '(')
            {
                result += stackToken;
                stack.pop();
            }
            stack.pop();
        }
        else if(isOperator(token))
        {
            while(!stack.empty() && stack.top() != '(' && isHigherPrecedance(stack.top(),token))
            {
                result += stack.top();
                stack.pop();
            }
            stack.push(token);
        }
    }

    // Pop all the stack onto the string
    while(!stack.empty())
    {
        result += stack.top();
        stack.pop();
    }
    return result;
}