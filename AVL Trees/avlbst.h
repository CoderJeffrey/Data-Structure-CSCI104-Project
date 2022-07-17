#ifndef RBBST_H
#define RBBST_H

#include "bst.h"
#include <algorithm>
#include <cstdlib>
#include <exception>
#include <iostream>

struct KeyError {};

/**
 * A special kind of node for an AVL tree, which adds the height as a data member, plus
 * other additional helper functions. You do NOT need to implement any functionality or
 * add additional data members or helper functions.
 */
template<typename Key, typename Value>
class AVLNode : public Node<Key, Value> {
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int getHeight() const;
    void setHeight(int height);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int height_;
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
 * An explicit constructor to initialize the elements by calling the base class constructor and setting
 * the color to red since every new node will be red when it is first inserted.
 */
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent)
        : Node<Key, Value>(key, value, parent), height_(1) {}

/**
 * A destructor which does nothing.
 */
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode() {}

/**
 * A getter for the height of a AVLNode.
 */
template<class Key, class Value>
int AVLNode<Key, Value>::getHeight() const {
    return height_;
}

/**
 * A setter for the height of a AVLNode.
 */
template<class Key, class Value>
void AVLNode<Key, Value>::setHeight(int height) {
    height_ = height;
}

/**
 * An overridden function for getting the parent since a static_cast is necessary to make sure
 * that our node is a AVLNode.
 */
template<class Key, class Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getParent() const {
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
 * Overridden for the same reasons as above.
 */
template<class Key, class Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getLeft() const {
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
 * Overridden for the same reasons as above.
 */
template<class Key, class Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getRight() const {
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}

/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/

template<class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value> {
public:
    virtual void insert(const std::pair<const Key, Value>& new_item);  // TODO
    virtual void remove(const Key& key);                               // TODO
protected:
    virtual void nodeSwap(AVLNode<Key, Value>* n1, AVLNode<Key, Value>* n2);

    // Add helper functions here

    // left rotates around a node current
    void left_rotate(AVLNode<Key, Value>* current);
    // right rotates around a node current
    void right_rotate(AVLNode<Key, Value>* current);
    // find the three nodes to form zig-zig or zig-zag pattern
    int xyz_pattern(AVLNode<Key, Value>** current);

    // update the height of the current node and all its parent node, up to the root
    void updateHeight(AVLNode<Key, Value>* current);
    // find the node that is unbalanced
    int unbalanced_place(AVLNode<Key, Value>** current, AVLNode<Key, Value>** prev, AVLNode<Key, Value>** grand_prev);
    // find the height of a node
    int height_find(AVLNode<Key, Value>* current);
    int
    remove_unbalanced_find(AVLNode<Key, Value>** current, AVLNode<Key, Value>** prev, AVLNode<Key, Value>** grand_prev);
    AVLNode<Key, Value>* parent_remove(const Key& key);
    AVLNode<Key, Value>* insert_node(const std::pair<const Key, Value>& keyValuePair);
    int remove_xyz_pattern(AVLNode<Key, Value>** current);
};

// helper function return the height of a node
template<class Key, class Value>
int AVLTree<Key, Value>::height_find(AVLNode<Key, Value>* current) {
    // Edge Case: current is the nullptr then the height is 0
    if (current == nullptr)
        return 0;
    else {
        return current->getHeight();
    }
}

// helper function that find the node is unbalanced
template<class Key, class Value>
int AVLTree<Key, Value>::unbalanced_place(
        AVLNode<Key, Value>** current, AVLNode<Key, Value>** prev, AVLNode<Key, Value>** grand_prev) {
    if ((*current) == nullptr)
        return 0;
    while ((*current)->getParent() != nullptr) {
        *grand_prev = *prev;
        *prev = *current;
        *current = (*current)->getParent();
        // Find whether the current node is unbalanced
        if (abs(height_find((*current)->getLeft()) - height_find((*current)->getRight())) > 1) {
            return 1;
        }
    }
    return 0;
}

template<class Key, class Value>
void AVLTree<Key, Value>::left_rotate(AVLNode<Key, Value>* current) {
    // If the current have parents, then the parent have to change their child
    if (current->getParent() != nullptr && current->getParent()->getLeft() == current)
        current->getParent()->setLeft(current->getRight());
    if (current->getParent() != nullptr && current->getParent()->getRight() == current)
        current->getParent()->setRight(current->getRight());

    // Use a node to store the right node of the left child
    AVLNode<Key, Value>* left_temp = current->getRight()->getLeft();
    // Set the right child node of current left child as current

    current->getRight()->setLeft(current);

    // set the parent of the current->getRight()
    current->getRight()->setParent(current->getParent());

    // Set Current node's parent now as the current left subnode
    current->setParent(current->getRight());

    // set the parent of the current->getRight()
    // left the left child node of current now as the original node of current lef child
    current->setRight(left_temp);
    if (left_temp != nullptr)
        left_temp->setParent(current);

    // if current is at first the root then we need to reset the root
    if (this->root_ == current) {
        this->root_ = current->getParent();
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::right_rotate(AVLNode<Key, Value>* current) {
    // Change current's parent node's child node
    if (current->getParent() != nullptr && current->getParent()->getLeft() == current)
        current->getParent()->setLeft(current->getLeft());
    if (current->getParent() != nullptr && current->getParent()->getRight() == current)
        current->getParent()->setRight(current->getLeft());

    // Use a node to store the right node of the left child
    AVLNode<Key, Value>* right_temp = current->getLeft()->getRight();
    // Set the right child node of current left child as current
    current->getLeft()->setRight(current);
    current->getLeft()->setParent(current->getParent());

    // Set Current parent now as the current left subnode
    current->setParent(current->getLeft());
    current->setLeft(right_temp);
    if (right_temp != nullptr)
        right_temp->setParent(current);

    // if current is at first the root then we need to reset the root
    if (current == this->root_) {
        this->root_ = current->getParent();
    }
}

template<class Key, class Value>
int AVLTree<Key, Value>::xyz_pattern(AVLNode<Key, Value>** current) {
    int case_num = 0;
    AVLNode<Key, Value>* prev = nullptr;
    AVLNode<Key, Value>* grand_prev = nullptr;

    // 4 Cases
    // 1. Left-Left 2. Left-Right 3. Right-Right 4. Right-Left 5. is balanced no need for x-y-z pattern
    // Starting from w, travel up and find the first unbalanced node. Let z be the first unbalanced node, y be the child
    // of z that comes on the path from w to z and x be the grandchild of z that comes on the path from w to z.

    // find the node where the node is unbalanced
    int balanced_judge = unbalanced_place(current, &prev, &grand_prev);

    // can't find the x y z or the tree is balanced
    if (balanced_judge == 0)
        return 5;

    else {
        if ((*current)->getLeft() == prev && prev->getLeft() == grand_prev) {
            case_num = 1;
        } else if ((*current)->getLeft() == prev && prev->getRight() == grand_prev) {
            case_num = 2;
        } else if ((*current)->getRight() == prev && prev->getRight() == grand_prev)
            case_num = 3;
        else if ((*current)->getRight() == prev && prev->getLeft() == grand_prev)
            case_num = 4;
    }
    return case_num;
}

template<class Key, class Value>
int AVLTree<Key, Value>::remove_xyz_pattern(AVLNode<Key, Value>** current) {
    int case_num = 0;
    AVLNode<Key, Value>* prev = nullptr;
    AVLNode<Key, Value>* grand_prev = nullptr;

    if (current == nullptr)
        return 5;

    // There are 4 Cases 1. Left-Left 2. Left-Right 3. Right-Right 4. Right-Left 5. is balanced no need for x-y-z
    // pattern
    // find the node where the node is unbalanced
    int balanced_judge = remove_unbalanced_find(current, &prev, &grand_prev);

    // can't find the x y z or the tree is balanced
    if (balanced_judge == 0)
        return 5;

    else {
        if ((*current)->getLeft() == prev && prev->getLeft() == grand_prev) {
            case_num = 1;
        } else if ((*current)->getLeft() == prev && prev->getRight() == grand_prev) {
            case_num = 2;
        } else if ((*current)->getRight() == prev && prev->getRight() == grand_prev)
            case_num = 3;
        else if ((*current)->getRight() == prev && prev->getLeft() == grand_prev)
            case_num = 4;
    }
    return case_num;
}

// helper function that updats the height for all the nodes
template<class Key, class Value>
void AVLTree<Key, Value>::updateHeight(AVLNode<Key, Value>* current) {
    // every father/grandfather/grand-grand-father node's height changed
    while (current->getParent() != nullptr) {
        current->setHeight(1 + std::max(height_find(current->getLeft()), height_find(current->getRight())));
        current = current->getParent();
    }
    // Then we reach the root
    current->setHeight(1 + std::max(height_find(current->getLeft()), height_find(current->getRight())));
}

// BST insert for here
template<class Key, class Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::insert_node(const std::pair<const Key, Value>& keyValuePair) {
    // TODO
    // find a place to insert the node
    AVLNode<Key, Value>* temp = static_cast<AVLNode<Key, Value>*>(this->root_);
    AVLNode<Key, Value>* prev = nullptr;
    // for the int left_right used to indicate whether the subnode is on the left side of the parent node or the right
    // side 1 left 2 right
    int left_right = 0;

    // the BST is empty
    if (temp == nullptr) {
        AVLNode<Key, Value>* n_pointer = new AVLNode<Key, Value>(keyValuePair.first, keyValuePair.second, nullptr);
        this->root_ = n_pointer;
        return n_pointer;
    }

    // as long as temp is not the leaf node find a place to insert the keyValue Pair
    while (temp != nullptr) {
        prev = temp;

        if (keyValuePair.first == temp->getKey()) {
            temp->setValue(keyValuePair.second);
            return temp;
        }
        // case where the key is smaller than or equal to the temp node??
        else if (keyValuePair.first < temp->getKey()) {
            temp = temp->getLeft();
            left_right = 1;
        }
        // case where the key is bigger than the temp node
        else if (keyValuePair.first > temp->getKey()) {
            temp = temp->getRight();
            left_right = 2;
        }
    }

    // now the temp is null and find the place where
    temp = new AVLNode<Key, Value>(keyValuePair.first, keyValuePair.second, prev);
    // based on the left_right to determine the position of the subnode
    if (left_right == 1)
        prev->setLeft(temp);
    else if (left_right == 2)
        prev->setRight(temp);
    return temp;
}

template<class Key, class Value>
void AVLTree<Key, Value>::insert(const std::pair<const Key, Value>& new_item) {
    // TODO
    // first use the BST Tree insertion to insert the node
    AVLNode<Key, Value>* trans = insert_node(new_item);
    updateHeight(trans);
    int patt = xyz_pattern(&trans);

    if (patt != 5) {
        // Case 1: left-left case
        if (patt == 1) {
            right_rotate(trans);
            updateHeight(trans);
        }

        // Case 2: left-right case
        else if (patt == 2) {
            left_rotate(trans->getLeft());
            right_rotate(trans);
            updateHeight(trans);
            updateHeight(trans->getParent()->getLeft());
        }

        // Case 3: Right-Right Case
        else if (patt == 3) {
            left_rotate(trans);
            updateHeight(trans);
        }
        // Case 4: Right-Left Case
        else if (patt == 4) {
            right_rotate(trans->getRight());
            left_rotate(trans);
            updateHeight(trans);
            updateHeight(trans->getParent()->getRight());
        }
    }
}

// helper function for remove that returns the parent of the remove pointer
template<class Key, class Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::parent_remove(const Key& key) {
    // If the key is not already in the tree, this function will do nothing.
    if (BinarySearchTree<Key, Value>::internalFind(key) == nullptr)
        return nullptr;
    AVLNode<Key, Value>* temp = static_cast<AVLNode<Key, Value>*>(BinarySearchTree<Key, Value>::internalFind(key));
    AVLNode<Key, Value>* parent = nullptr;

    // if the node has no child
    if ((temp->getLeft() == nullptr) && (temp->getRight() == nullptr)) {
        if (temp->getParent() != nullptr) {
            parent = temp->getParent();
            if (temp->getParent()->getLeft() == temp)
                temp->getParent()->setLeft(nullptr);
            if (temp->getParent()->getRight() == temp)
                temp->getParent()->setRight(nullptr);
        }

        // edge case if the temp is the root
        if (this->root_ == temp) {
            this->root_ = nullptr;
        }

        delete temp;
        return parent;
    }

    // If the node to be removed has exactly one child, promote the child
    // first case left child exist, right child is NULL
    if ((temp->getLeft() != nullptr) && (temp->getRight() == nullptr)) {
        temp->getLeft()->setParent(temp->getParent());

        // replace the value of the node 30
        if (temp->getParent() != nullptr) {
            parent = temp->getParent();
            if (temp->getParent()->getLeft() == temp)
                temp->getParent()->setLeft(temp->getLeft());
            if (temp->getParent()->getRight() == temp)
                temp->getParent()->setRight(temp->getLeft());
        }
        // edge case if the temp is the root
        if (this->root_ == temp) {
            this->root_ = temp->getLeft();
        }
        delete temp;
        return parent;
    }

    else if ((temp->getRight() != nullptr) && (temp->getLeft() == nullptr)) {
        temp->getRight()->setParent(temp->getParent());
        // replace the value of the node 30
        if (temp->getParent() != nullptr) {
            parent = temp->getParent();
            if (temp->getParent()->getLeft() == temp)
                temp->getParent()->setLeft(temp->getRight());
            if (temp->getParent()->getRight() == temp)
                temp->getParent()->setRight(temp->getRight());
        }

        // edge case if the temp is the root
        if (this->root_ == temp) {
            this->root_ = temp->getRight();
        }
        delete temp;
        return parent;
    }

    // If the node to be removed has two children,swap with its predecessor (not its successor) in the BST removal
    // algorithm.
    if ((temp->getRight() != nullptr) && (temp->getLeft() != nullptr)) {
        AVLNode<Key, Value>* pred = static_cast<AVLNode<Key, Value>*>(this->predecessor(temp));
        nodeSwap(pred, temp);

        // if the node has no child
        if ((temp->getLeft() == nullptr) && (temp->getRight() == nullptr)) {
            if (temp->getParent() != nullptr) {
                parent = temp->getParent();
                if (temp->getParent()->getLeft() == temp)
                    temp->getParent()->setLeft(nullptr);
                if (temp->getParent()->getRight() == temp)
                    temp->getParent()->setRight(nullptr);
            }
            delete temp;
            return parent;
        }

        // If the node to be removed has exactly one child, promote the child
        // first case left child exist, right child is NULL
        if ((temp->getLeft() != nullptr) && (temp->getRight() == nullptr)) {
            temp->getLeft()->setParent(temp->getParent());

            // replace the value of the node 30
            if (temp->getParent() != nullptr) {
                parent = temp->getParent();
                if (temp->getParent()->getLeft() == temp)
                    temp->getParent()->setLeft(temp->getLeft());
                if (temp->getParent()->getRight() == temp)
                    temp->getParent()->setRight(temp->getLeft());
            }

            delete temp;
            return parent;
        }

        else if ((temp->getRight() != nullptr) && (temp->getLeft() == nullptr)) {
            temp->getRight()->setParent(temp->getParent());
            if (temp->getParent() != nullptr) {
                parent = temp->getParent();
                if (temp->getParent()->getLeft() == temp)
                    temp->getParent()->setLeft(temp->getRight());
                if (temp->getParent()->getRight() == temp)
                    temp->getParent()->setRight(temp->getRight());
            }
            delete temp;
            return parent;
        }
    }
    return nullptr;
}

// helper function for xyz to find out the three node to zig-zig or zigzag
template<class Key, class Value>
int AVLTree<Key, Value>::remove_unbalanced_find(
        AVLNode<Key, Value>** current, AVLNode<Key, Value>** next, AVLNode<Key, Value>** grand_next) {
    int balance = 0;
    if ((*current) == nullptr)
        return balance;
    // 0 means balanced while 1 means unbalanced here
    while ((*current) != nullptr) {
        if (abs(height_find((*current)->getLeft()) - height_find((*current)->getRight())) > 1) {
            balance = 1;
            break;
        }
        *current = (*current)->getParent();
    }

    // thus the case for unbalanced
    if (balance == 1) {
        // set the next node
        if (height_find((*current)->getLeft()) > height_find((*current)->getRight())) {
            *next = (*current)->getLeft();
        } else if (height_find((*current)->getLeft()) < height_find((*current)->getRight())) {
            *next = (*current)->getRight();
        }

        // set the grand next node
        // Consider if getLeft() is nullptr
        if (height_find((*next)->getLeft()) > height_find((*next)->getRight()))
            *grand_next = (*next)->getLeft();
        else if (height_find((*next)->getLeft()) < height_find((*next)->getRight()))
            *grand_next = (*next)->getRight();
        else if (height_find((*next)->getLeft()) == height_find((*next)->getRight())) {
            // break ties by zig-zig
            if (*next == (*current)->getLeft())
                *grand_next = (*next)->getLeft();  // forming left-left zig-zig
            if (*next == (*current)->getRight())
                *grand_next = (*next)->getRight();  // forming right right zig-zig
        }
    }
    return balance;
}

// Recursive Remove
template<class Key, class Value>
void AVLTree<Key, Value>::remove(const Key& key) {
    // TODO
    // first perform BST Basic remove, and the Node
    AVLNode<Key, Value>* temp = parent_remove(key);

    // Edge Case if the p is nullptr then
    if (temp == nullptr)
        return;
    else {
        updateHeight(temp);
        int patt = remove_xyz_pattern(&temp);

        while (patt != 5) {
            AVLNode<Key, Value>* temp_father = temp->getParent();
            // Case 1: left-left case
            if (patt == 1) {
                right_rotate(temp);
                // right
                updateHeight(temp);
                // update the heights of the nodes
            }

            // Case 2: left-right case
            else if (patt == 2) {
                left_rotate(temp->getLeft());
                right_rotate(temp);
                updateHeight(temp);
                updateHeight(temp->getParent()->getLeft());
            }

            // Case 3: Right-Right Case
            else if (patt == 3) {
                left_rotate(temp);
                updateHeight(temp);
            }
            // Case 4: Right-Left Case
            else if (patt == 4) {
                right_rotate(temp->getRight());
                left_rotate(temp);
                updateHeight(temp);
                updateHeight(temp->getParent()->getRight());
            }
            patt = remove_xyz_pattern(&temp_father);
            if (temp_father == nullptr)
                break;
            else
                temp = temp_father;
        }
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap(AVLNode<Key, Value>* n1, AVLNode<Key, Value>* n2) {
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int tempH = n1->getHeight();
    n1->setHeight(n2->getHeight());
    n2->setHeight(tempH);
}

#endif