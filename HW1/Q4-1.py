from cProfile import label
import matplotlib.pyplot as plt
import numpy as np

def func1(n) :
    return 100 * n + 2

def func2(n):
    return 10 * (n ** 2) + 4 * n + 2

def func3(n):
    return 6 * (2 ** n) + (n ** 2)


x = np.arange(0, 12, 0.1)
y1 = []
y2 = []
y3 = []


for i in x:
    y1.append(func1(i))
    y2.append(func2(i))
    y3.append(func3(i))


plt.ylim(0, 2000)
plt.plot(x, y1, label = '100n + 2')
plt.plot(x, y2, label = '10(n ^ 2) + 4n + 2')
plt.plot(x, y3, label = '6(2 ^ n) + (n ^ 2)')
plt.legend()
plt.xlabel('n')
plt.ylabel('y')
plt.savefig('func')

