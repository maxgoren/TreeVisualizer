# TreeVisualizer
A simple C++ utility to generate images of binary search trees using SFML 2.

## Examples
![145-rand-RB](https://github.com/maxgoren/TreeVisualizer/assets/65133477/173c372e-8aae-460a-8337-57c59712b340)
A Larege Red Black Tree.
![130-random-splay](https://github.com/maxgoren/TreeVisualizer/assets/65133477/b0bbcd19-f8f5-4ace-8501-ab937d515cc3)
A Large Splay Tree
![35-random-BST-LLRB](https://github.com/maxgoren/TreeVisualizer/assets/65133477/a7c618e9-0b2f-4edb-b291-736ca452673d)
An unbalanced BST and Left Leaning Red Black Tree


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
  to pair up the nodes point coordinates for the edges which connect the vertices to its children. Future plan
  is to remove the breadth first step and draw edges and nodes at the same time. The result is a visual 
  representation of the tree, which is both displayed to the screen and also saved in the current working 
  directory as tree.jpg
