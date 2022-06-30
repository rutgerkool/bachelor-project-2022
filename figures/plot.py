import matplotlib.pyplot as plt
import numpy as np
import matplotlib.ticker as ticker

plt.style.use(['science'])

x = [] 
x1 = []
y = [] 
y1 = []
# for line in open('results.txt', 'r'):
#     lines = [i for i in line.split()]
#     x.append(int(lines[0]))
#     y.append(int(lines[1]))
      
# plt.title("findSmallestMissingNumber()")
# plt.xlabel('Number of invocations')
# plt.ylabel('Accuracy')
# plt.autoscale(tight=True)
# plt.plot(x, y, marker='o')
# plt.ylim([0,100])
# plt.savefig('figures/fig1.jpg', dpi=300)

for line in open('results-3.txt', 'r'):
    lines = [i for i in line.split()]
    x1.append(int(lines[0]))
    y1.append(int(lines[1]))

plt.title("BST::inOrder()")
plt.xlabel('Number of invocations')
plt.ylabel('Accuracy')
plt.autoscale(tight=True)
plt.plot(x1, y1, marker='o')
plt.ylim([0,100])
plt.savefig('figures/fig2.jpg', dpi=300)