![37-fibonacci-AVL-RB](https://github.com/maxgoren/TreeVisualizer/assets/65133477/2e2f9956-3037-4cdf-bebe-2cacef2d9b67)
![35-random-BST-LLRB](https://github.com/maxgoren/TreeVisualizer/assets/65133477/a7c618e9-0b2f-4edb-b291-736ca452673d)
# TreeVisualizer
A simple C++ utility to generate images of binary search trees using SFML 2.

## Files
```
 -TreeDraw.hpp -the tree visualizer.
 -treeviz.cpp  - an example of how to use TreeDraw with the trees listed below.
 -redblack.hpp - example RedBlack And Left Leaning Red Black Tree.
 -avl.hpp      - example AVL Tree.
 -bst.hpp      - unbalanced recursive Binary Search Tree
 -treenode.hpp - node type used by above trees.
```

## The Basic Idea
  TreeDraw works by iterating over a binry tree in two ways. The first pass is an in-order traversal which
  calculated each nodes x/y coordinates. A second, breadth-first (level order) traversal is then performed 
  to calculate the end point coordinates for the edges which connect the vertices. The result is a visual 
  representation of the tree, which is both displayed to the screen and also saved in the current working 
  directory as tree.jpg
