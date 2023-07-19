# Multi-variable branching data
The code generate_instance.cpp is used to generate the knapsack problem instances used in the paper [Multi-Variable Branching: A 0-1 Knapsack Problem Case Study](https://pubsonline.informs.org/doi/abs/10.1287/ijoc.2020.1052) by [Yu Yang](https://sites.google.com/view/yu-yang), Natashia Boland, and Martin Savelsbergh. A detailed description of the instances can be found in [Where are the hard knapsack problems?](https://reader.elsevier.com/reader/sd/pii/S030505480400036X?token=4C179054129651AF55FBE796262E3E7F591702CA18E7F3188D007C05F2A2061C4C313EA68C029682645641ED9BC86FD3). The source code can be compiled by "g++ generate_instance.cpp -std=c++11 -o generator". The compiled executable will generate instances in the folder named "data" in the current directory. 

Each generated instance file is named as "InstanceType_n_R_k.txt", where "InstanceType" can be "Uncorrelated", "Weak", and "Strong", "n" is the number of items of the knapsack problem, "R" is the data range, and "k" is the instance index. The first number in each file is the # of items, which is followed by the prices and the weights of the items (all prices and then all weights). The last number is the capacity of the knapsack.

