# TreeVisualizer
A simple C++ utility to generate images of binary search trees using SFML 2.

## Examples
![145-rand-RB](https://github.com/maxgoren/TreeVisualizer/assets/65133477/173c372e-8aae-460a-8337-57c59712b340)
A Larege Red Black Tree.
![130-random-splay](https://github.com/maxgoren/TreeVisualizer/assets/65133477/b0bbcd19-f8f5-4ace-8501-ab937d515cc3)
A Large Splay Tree
![35-random-BST-LLRB](https://github.com/maxgoren/TreeVisualizer/assets/65133477/a7c618e9-0b2f-4edb-b291-736ca452673d)
An unbalanced BST and Left Leaning Red Black Tree
![Insertion-Sequence](https://github.com/maxgoren/TreeVisualizer/assets/65133477/27cd8564-b16f-4f80-aa6a-615596f43146)
UPDATE: As of 1/2024 node labeling, and tiling have been aded, so capturing sequences of insertions, etc is much easier.

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
  TreeDraw works by performing two traversals of a binry tree in. The first pass is an in-order traversal which
  calculated each nodes x/y coordinates. A second, breadth-first (level order) traversal is then performed 
  to pair up the nodes point coordinates for the edges which connect the vertices to its children. 
  The result is a graphical representation of the tree, which is both displayed to the screen and also saved in the current working 
  directory as tree.jpg

## How to use
   Right now the code depends on you using the supplied treenode.hpp as the node for the binary tree you're building. In the future I plan
   to remove this dependency, possibly with the visitor pattern. Instantiate a TreeDraw object, and when you have the tree you wish to depict,
   you use the mark(root, nullmarker, treetype) method to perform a traversal of the tree, and then invoke drawTree().
   ```
       int main() {
           TreeDraw<int,int> td;
           RedBlackTree<int,int> bst;
           for (int i = 0; i < 10; i++) {
              bst.insert(rand() % 50, i);
              td.mark(bst.rootNode(), nullptr, REDBLACK)
           }
           td.drawTree();
       }
   ```

  
