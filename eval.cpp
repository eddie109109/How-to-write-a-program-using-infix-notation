
#include <iostream>
#include <stack>
using namespace std;

int precedence(char op) { // this is the function that determines the precedence of the operator
    if(op == '+' || op == '-') {
        return 1;
    } else if (op == '*' || op == '/') {
        return 2;
    } else {
        return 0;
    }
}

int applyOp(int a, int b, char op) {
    int result = 0;
    switch(op) {
        case '+':
        result = a+b;
        break;
        case '-':
        result = a-b;
        break;
        case '*':
        result = a*b;
        break;
        case '/':
        result = a/b;
        break;
    }
    return result;
}

//you need to use space to seperate each operand and operator 

int evaluate(string tokens) { // the user is going to put in a whole expression like "103 + 7 * 6"
    stack <int> values;
    stack <char> ops;
    int i;
    for (i = 0; i< tokens.length(); i++) {
        if (tokens[i] == ' ') {
            cout << "hi" <<endl;
            continue;
        }

        else if (tokens[i] == '(') {
            ops.push(tokens[i]);
        } 

        else if (isdigit(tokens[i])) {
            int total = 0;
            while(i < tokens.length() && isdigit(tokens[i])) {
                total = total*10 + (tokens[i]-'0');
                i++;
            }
            values.push(total);
        } 

        // when the second operator appears, there must be two numbers in the ops already

        else if (tokens[i] == '+' ||  tokens[i] == '-' ||  tokens[i] == '*' ||  tokens[i] == '/' ) {
            while (!ops.empty() &&  precedence(ops.top()) >= precedence(tokens[i])) {
                char op = ops.top();
                ops.pop();
                int val2 = values.top(); 
                values.pop();
                int val1 = values.top();
                values.pop();

                values.push(applyOp(val1, val2, op));
            }
                ops.push(tokens[i]); // after calculating the previous arithemetics, then we add the current operator
        }

        else if (tokens[i] == ')') { // in this case, when there are more than two operators with the same precedence
            int val2;
            int val1;
            char op;
            // while (!ops.empty()) {
                 op = ops.top();
                 ops.pop();
                 val2 = values.top();
                 values.pop();
                 val1 = values.top();
                 values.pop();

            // }
            

            values.push(applyOp(val1,val2,op));
            ops.pop();
        }


    }

    

    while (!ops.empty()) {
        int val2;
        int val1;
        char op;
            
                 op = ops.top();
                 ops.pop();
                 val2 = values.top();
                 values.pop();
                 val1 = values.top();
                 values.pop();
                 values.push(applyOp(val1,val2,op));
    }

    return values.top();

}




int main() {
    int result = 0;
    string tokens = "( 5 + 11 ) * 2 ";  // you will get the number 32

    result = evaluate(tokens);
    cout << "the final value is " << result;
    return 0;
}



