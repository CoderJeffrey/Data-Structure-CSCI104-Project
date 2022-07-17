#include <exception>
#include <stdexcept>
#include <vector>

template<class T>
class MinHeap {
public:
    MinHeap(int d);

    ~MinHeap();

    void add(T item, int priority);

    const T& peek() const;
    /* returns the element with smallest priority.
           Break ties however you wish.
           Throws an exception if the heap is empty. */

    void remove();
    /* removes the element with smallest priority.
            Break ties however you wish.
    Throws an exception if the heap is empty. */

    bool isEmpty();
    /* returns true iff there are no elements on the heap. */

private:
    std::vector<T> node_list;
    std::vector<int> priority_list;
    int sub_node;
    void bubbleUp(int index);
    void trickleDown(int index);
};

template<class T>
MinHeap<T>::MinHeap(int d) {
    sub_node = d;
}

template<class T>
MinHeap<T>::~MinHeap() {}

template<class T>
const T& MinHeap<T>::peek() const {
    if (node_list.empty()) {
        throw std::logic_error("NO Elements");
    }
    return node_list[0];
}

template<class T>
bool MinHeap<T>::isEmpty() {
    if (node_list.empty()) {
        return true;
    } else {
        return false;
    }
}

template<class T>
void MinHeap<T>::bubbleUp(int index) {
    // Edge Case: when the index is 0
    // if(index > 0 && priority_list[index]<=priority_list[(index-1)/sub_node])
    if (index > 0 && priority_list[index] <= priority_list[(index - 1) / sub_node]) {
        // Switch and break ties
        if (priority_list[index] == priority_list[(index - 1) / sub_node]) {
            if (node_list[index] < node_list[(index - 1) / sub_node]) {
                // T item switch
                T temp = node_list[index];
                node_list[index] = node_list[(index - 1) / sub_node];
                node_list[(index - 1) / sub_node] = temp;
                // priority switch
                int temp_priority = priority_list[index];
                priority_list[index] = priority_list[(index - 1) / sub_node];
                priority_list[(index - 1) / sub_node] = temp_priority;
                bubbleUp((index - 1) / sub_node);
            }
        }

        if (priority_list[index] < priority_list[(index - 1) / sub_node]) {
            // T item switch
            T temp = node_list[index];
            node_list[index] = node_list[(index - 1) / sub_node];
            node_list[(index - 1) / sub_node] = temp;
            // priority switch
            int temp_priority = priority_list[index];
            priority_list[index] = priority_list[(index - 1) / sub_node];
            priority_list[(index - 1) / sub_node] = temp_priority;
            bubbleUp((index - 1) / sub_node);
        }
    }
}

template<class T>
void MinHeap<T>::trickleDown(int index) {
    int sub = index * sub_node + 1;
    // find the the subnode with least priority
    int smallest = sub;
    // judge whether there exist a complete next level
    if (sub < node_list.size()) {
        for (int i = 0; i < sub_node; i++) {
            // Break ties
            if (priority_list[sub + i] <= priority_list[smallest] && (sub + i) < node_list.size()) {
                if (priority_list[sub + i] == priority_list[smallest] && node_list[sub + i] < node_list[smallest]) {
                    smallest = sub + i;
                }

                if (priority_list[sub + i] < priority_list[smallest])
                    smallest = sub + i;
            }
        }

        if (priority_list[index] >= priority_list[smallest]) {
            if (priority_list[index] == priority_list[smallest] && node_list[index] > node_list[smallest]) {
                // switch the elements
                T temp = node_list[index];
                node_list[index] = node_list[smallest];
                node_list[smallest] = temp;

                // switch the priority
                int temp_priority = priority_list[index];
                priority_list[index] = priority_list[smallest];
                priority_list[smallest] = temp_priority;
                trickleDown(smallest);
            }

            if (priority_list[index] > priority_list[smallest]) {
                // switch the elements
                T temp = node_list[index];
                node_list[index] = node_list[smallest];
                node_list[smallest] = temp;

                // switch the priority
                int temp_priority = priority_list[index];
                priority_list[index] = priority_list[smallest];
                priority_list[smallest] = temp_priority;
                trickleDown(smallest);
            }
        }
    }
}

template<class T>
void MinHeap<T>::add(T item, int priority) {
    node_list.push_back(item);
    priority_list.push_back(priority);
    //
    bubbleUp(node_list.size() - 1);
}

template<class T>
void MinHeap<T>::remove() {
    if (node_list.empty()) {
        throw std::logic_error("NO ELEMENTS IN HEAP");
    }

    priority_list[0] = priority_list[priority_list.size() - 1];
    node_list[0] = node_list[node_list.size() - 1];
    priority_list.pop_back();
    node_list.pop_back();
    trickleDown(0);
}
