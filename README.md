# TreeVisualizer
A simple C++ utility to generate images of binary search trees using SFML 2.

##Files
-redblack.hpp -example RedBlack And Left Leaning Red Black Tree
-avl.hpp      -example AVL Tree
-bst.hpp      -unbalanced recursive Binary Search Tree
-treenode.hpp -node type used by above trees.
-TreeDraw.hpp -the visualizer itsself.
-treeviz.cpp  -an example of how to use TreeDraw

##Usage
  TreeDraw works by iterating over binary search trees once in-order to get each nodes x/y coordinates,
  and a second time breadth-first (level order) to plot the edges. The result is a visual representation
  of the tree, which is both displayed to the screen and also saved in the current working directory as
  tree.jpg
