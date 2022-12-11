# Data Sutructure Programing HW3

## 41047025S 王重鈞

### Introduction:

lang: cpp14  
environment: linux or mac

Using `make` to compile the program, the excutable file will be `calculate`.

After excute the program, please input the infix expression string without `=` and space, such as `1+2+3`, `4*5*6`. If input escape key(screen will show `^[`) and press enter, the program will stop.

### Time complexity

Suppose the infix expression string's length is N.

#### Build binary tree

It will screen the infix, and each char will only push and pop from stack, then the stack operation is O(1). So, building binary tree time complexity is O(N)

#### prefix traversal and postfix traversal and counting

Both traversal the visit each node, so the time complexity is O(n). Counting is visit each node and return child node calculate result, so it time compelxity is also O(N).
