In this project, I mainly achieve the avl tree/ bst tree/ and the backtracking.  

1. For BST Tree, the bst.h achieve the Binary Search Tree basic function like remove(), insert()  
2. For AVL Tree, the tree can achieve the self-balancing properties  
    * In the AVL Tree, we need to consider multiples cases in order to achieve balance
    * Specifically, there are 4 types cater to the zig-zig or zig-zag pattern
        * Left-Left Case
        * Right-Right Case
        * Right-Left Case
        * Left-Left Case
    * With these cases determined, we can know how many times to rotate as well as where to rotate
3. For the back tracing problem, the above two files help me to build the data structures needed
    * Back tracking problem involves trick to go down the steps to find available courses to add in each time slot , if the slot is not occupied, we can then go back, thus, it involves recursion

For the makefile incorporated, simply type 'make' can compile the `./scheduling` executable 