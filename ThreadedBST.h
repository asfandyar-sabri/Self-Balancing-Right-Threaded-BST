#pragma once

#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>

using namespace std;

template<typename keyType, typename valueType>  // tempaltizing the  class
// making mymap class 
class mymap { 
	private:
        struct NODE {  // creating NODE structure 
            keyType key;  
            valueType value;  
            NODE* left;  
            NODE* right;  
            int nL;  
            int nR;  
            bool isThreaded;
        };
        NODE* root;  // node to keep record of the root of the tree 
        int size;  
        int sizer = 0;
        bool decider = true;
	// creating iterator 
    struct iterator {
        private:
            NODE* curr;  
            
        public:
            iterator(NODE* node) {
                curr = node;
            }
	    //*operator overloading
            keyType operator *() { 
                return curr -> key;
            }
            //+ operator overloading
            valueType operator +() { 
                return curr -> value;
            }
	    // == operator overloading 
            bool operator ==(const iterator& rhs) { 
                return curr == rhs.curr;
            }
	    // != operator overloading	
            bool operator !=(const iterator& rhs) {  
                return curr != rhs.curr;
            }
            bool isDefault() { 
                return !curr;
            }
            NODE* get_current() {  // func to get the current node 
                return curr;
            }
            // get the left most node
            NODE* left_most_node(NODE* node) {  //gets the left most node
                if (node == NULL) {
                    return NULL;
                } else {
                    while(node->left != NULL) {
                        node = node->left;
                    }
                    return node;
                }
            }
	    // ++ operator overloading to get next inorder node
            void operator++() { 
                if (curr->isThreaded)
                    curr = curr->right;
                else
                    curr = left_most_node(curr->right);
            }
        };

 public:
    mymap() { // deault constructor 
        root = NULL;
        size = 0;
    }
    NODE*& get_root() { // get root function
        return this->root;
    }
    void reset_size() { // reset size function 
        this->size = 0;
    }
    void reset_sizer() { // reset_sizer function to reset sizer member 
            sizer = 0;
    }
    mymap(const mymap& other) { // copy constructor
        this->root = NULL;
        this->size = 0;
        this->root = other.root;
    }
    mymap& operator=(const mymap& other) { // operator= overlaoding 
        this->root = other.root;
        return *this; 
    }
    void clear() {
        root = NULL;
    }
    ~mymap() {
        //DestroyRecursive(root);
        //delete root;
    }
    
    void DestroyRecursive(NODE* node) {
        if (node == NULL)
            delete (node);
        else if (node->left) {
            DestroyRecursive(node->left);
            delete (node);
        }
        else if (node->right && !node->isThreaded){
            DestroyRecursive(node->right);
            delete (node);
        }
    }  
    // put function for adding nodes to the tree  
    void put(keyType key, valueType value) {
        NODE* new_node = new NODE; // creating new node and setting default values
        new_node->key = key;
        new_node->value = value;
        new_node->isThreaded = false;
        new_node->left = NULL;
        new_node->right = NULL;
        new_node -> nL = 0;
        new_node -> nR = 0;
        if (root == NULL) {
            // inserting at root and returning
            root = new_node;
            lets_balance(this->get_root());
            //delete new_node;
            return;
        }
        NODE* current = root;
        NODE* temp = NULL;
        while(true) {
            temp = current;
            if(temp->key == key) { // same value
               temp->value = value;
               //delete new_node;
               return;
            }
            if (key < current->key) { // to left
                current = current->left;
                if (current == NULL){
                    temp->left = new_node;
                    new_node->right = temp;
                    new_node->isThreaded = true;
                    lets_balance(get_root());
                    //delete new_node;
                    return;
                }
            } else {
                if(!current->isThreaded) { // to right
                    current = current -> right;

                    if (current == NULL) {
                        temp->right = new_node;
                        lets_balance(get_root());
                        //delete new_node;
                        return;
                    }
                } else { // to right
                    NODE* temp = current->right;
                    current->right = new_node;
                    current->isThreaded = false;
                    new_node->right = temp;
                    new_node->isThreaded = true;
                    lets_balance(get_root());
                    //delete new_node;
                    return;
                }
            }
        }
    }
    // put function for adding nodes to the newly created subtree 
    void put_2(keyType key, valueType value) {
        NODE* new_node = new NODE;
        new_node->key = key;
        new_node->value = value;
        new_node->isThreaded = false;
        new_node->left = NULL;
        new_node->right = NULL;
        new_node -> nL = 0;
        new_node -> nR = 0;
        if (root == NULL) {
            // inserting at root and returning
            root = new_node;
            //delete new_node;
            return;
        }
        NODE* current = root;
        NODE* temp = NULL;
        while(true) {
            temp = current;
            if (key < current->key) {     // to left
                current = current->left;
                if (current == NULL) {
                    temp->left = new_node;
                    new_node->right = temp;
                    new_node->isThreaded = true;
                    //delete new_node;
                    return;
                }
            } else {   // to right
                if(!current->isThreaded) {
                    current = current -> right;
                    if (current == NULL) {
                        temp->right = new_node;
                        //delete new_node;
                        return;
                    }
                } else {   // to right
                    NODE* temp = current->right;
                    current->right = new_node;
                    current->isThreaded = false;
                    new_node->right = temp;
                    new_node->isThreaded = true;
                    //delete new_node;
                    return;
                }
            }
        }
    }
    // funtion for inorder traversal 
    void in_order(NODE* root) {
        NODE* current = left_most_node(root);
        while (current != NULL) {
            if (current != NULL) {
                cout << current->key << " " << current->value << " " << current->isThreaded << "\n";
            }
            if (current->isThreaded)
                current = current->right;
            else
                current = left_most_node(current->right);
        }
        cout << endl;
    }
    // function for finding left most node
    NODE* left_most_node(NODE* node) {
        if (node == NULL) {
            return NULL;
        }
        else {
            while(node->left != NULL) {
                node = node->left;
            }
            return node;
        }
    }
    // search function to search a node exists in tree or not it responds in yes or no 
    bool search(keyType key) {
        iterator start = begin();
        iterator end = this->end();
        for (start; start != end ; start.operator++()) {
           if(key == start.operator*()){
                return true;
           } 
        }
        return false;
    }
    // to check wether a specific node is present in the tree or not and if it exists it returns 
    bool contains(keyType key){
        return this->search(key);
    }
    NODE* new_search(keyType key){
        iterator start = begin();
        iterator end = this->end();
        for (start; start != end ; start.operator++()) {
           if(key == start.operator*())
                return start.get_current();
        }
        return NULL;
    }
    // returns the value of the given key 
    valueType get(keyType key) {
        // valueType temp = NULL;
        NODE* n1 = new_search(key);
        if(n1) 
            return n1->value;
        else
            return NULL;
    }
    // operator[] overloading 
    valueType operator[](keyType key) {
        // valueType temp = NULL;
        NODE* node = new_search(key);
        if(node) {
            return node->value;
        } else {
            this->put(key, NULL);
            return NULL;
        }
    }
    // returns the sizer function 
    int get_sizer() {
        int temp = sizer;
        decider = true;
        sizer = 0;
        return temp;
    }
    // resets the decider to true
    void reset_decider() {
        this->decider = true;
    }
    // returns number of left and right childs of the subtree 
    void no_of_childs(NODE* node) {
        if (node == NULL)
            return;
        if (node->left) {    // calculating left child
            this->new_size(node->left);
            node->nL = this->get_sizer();
            no_of_childs(node->left);
        }
        if(node->right && !node->isThreaded) {  // calculating right child
            this->new_size(node->right);
            node->nR = this->get_sizer();
            no_of_childs(node->right);
        }
    }   
    // checks wether the the given node is balanced or not 
    bool calculate_balance(NODE* node) {
        this->new_size(node->left);
        node->nL = get_sizer();   // calculating left child
        this->reset_sizer();
        this->reset_decider();
        if (node->right && !node->isThreaded) {
            this->new_size(node->right);
        }
        node->nR = get_sizer();  // calcualting right child
        this->reset_sizer();
        this->reset_decider();
        return max(node->nL, node->nR) <= (2 * min(node->nL, node->nR) + 1);
    }
    // returns the size of the given tree
    void new_size(NODE* node){
        if (node == NULL) {
            return;
        }
        if (decider) {
            sizer++;
            decider = false;
        }

        if (node->left) { 
            sizer++;
            new_size(node->left);
        }
        if (node->right && !(node->isThreaded)) {
            sizer++;
            new_size(node->right);
        }
        return;
    }
    // calculates the size of the given tree 
    int Size() {
        NODE* cur = left_most_node(root);   // getting start node of tree
        while (cur != NULL) {
            this->size++;
            if (cur->isThreaded)
                cur = cur->right;
            else
                cur = left_most_node(cur->right);
        }
        int temp = this->size;
        size = 0;
        return temp;
    }
    // creates a balanced sub tree from vector
    NODE* balanced_subtree(vector<pair<keyType,valueType>> victor, int first, int last) {
        int new_size = last - first + 1;
        if (new_size <= 0)
            return NULL;
        int middle = (first + last)/2; // getting middle
        NODE * subtreeRoot = new NODE();
        subtreeRoot->key = victor[middle].first;
        subtreeRoot->value = victor[middle].second;
        subtreeRoot -> left = balanced_subtree(victor, first, middle - 1);  // recursive call to left
        subtreeRoot -> right = balanced_subtree(victor, middle + 1, last);  // recursive call to right
        //NODE *&new_subtree = subtreeRoot;
        //delete subtreeRoot;
        return subtreeRoot;
    }

    // traverses the tree in inorder manner
    void pre_order(NODE* node) {
        if (node == NULL)
            return;
        cout << "Key: " << node->key << " Value: " << node->value << " Threaded: " << node->isThreaded;
        cout << " Lchild: " << node->nL << " Rchild: " << node->nR << endl; 
        if (node->left) {   // to left
            pre_order(node->left);
        }
        if (node->right && !node->isThreaded) {   // to right
            pre_order(node->right);
        }
    }
    // balancing the tree
    void lets_balance(NODE*& node) {
        if (node == NULL)
            return;
        while(node != NULL) {
            bool flag = calculate_balance(node);  // calculating balance of node
            if(!flag) {
                NODE* new_tree;
                vector<pair<keyType,valueType>> temp_vector = toVector_NEW(node);  // creating in order vector
                int first = 0;
                int last = temp_vector.size() - 1;               
                new_tree = balanced_subtree(temp_vector, first, last);  // creating new subtree
                //temp_vector.clear();
                node->left = node->right = NULL;
                node = NULL;
                balance_main_tree(new_tree);  // finalizing main tree
                //DestroyRecursive(new_tree);
                return;
            }
            if (node->left) {
                lets_balance(node->left);
            }
            if(node->right && !node->isThreaded) {
                lets_balance(node->right);
            }
            return;
        }       
    }
    // traverse the whole tree
    void traverser() {
        iterator start = begin();
        iterator end = this->end();
        for (start; start != end ; start.operator++())
            start.operator*(); 
    }
    // gets start node of subtree
    iterator new_begin(NODE* node) {
        return left_most_node(node);
    }
    // gets start node of tree
    iterator begin() {
        iterator start(left_most_node(this->root));
        return start;
    }
    iterator end() {
        return iterator(nullptr);
    }
    // returns max
    int max(int a, int b) {
        return a > b ? a : b;
    }
    // returns min
    int min(int a, int b) {
        return a < b ? a : b;
    }
    // converts the tree in to a string
    string toString() {
        stringstream ss;  // string stream to convert to string
        string holder = "";
        NODE* cur = left_most_node(root);
        while (cur != NULL) {
            ss << "key: ";
            ss << cur->key;
            ss << " value: ";
            ss << cur->value;
            ss << "\n";
            if (cur->isThreaded)  // traversing to right
                cur = cur->right;
            else
                cur = left_most_node(cur->right);  // traversing to left
        }
        holder = ss.str();
        return holder;
    }
    // retuns a vector containg inorder(sorted) keys of unbalanced tree
    vector<pair<keyType, valueType> > toVector_NEW(NODE* node) {
        new_size(node);
        int size = get_sizer();
        vector <pair<keyType, valueType>> my_vector;
        iterator start = new_begin(node);  // getting start of tree
        int i = 0;
        for(start; i<size ; start.operator++()) {  // iterating through the subtree
            pair<keyType, valueType> temp;
            temp.first = start.operator*();
            temp.second = start.operator+();
            my_vector.push_back(temp);
            i++;
        }
        return my_vector;
    }
    // retuns a vector containg inorder(sorted) keys of whole tree
    vector<pair<keyType, valueType> > toVector() {
        vector <pair<keyType, valueType>> my_vector;
        iterator i1 = begin();  // getting start
        iterator i2 = end();
        for(i1; i1 != i2; i1.operator++()){  // iterating through tree
            pair<keyType, valueType> temp;
            temp.first = i1.operator*();
            temp.second = i1.operator+();
            my_vector.push_back(temp);
        }
        return my_vector;
    }
    // balancing main tree again
    void balance_main_tree(NODE* node) {
        if (node == NULL)
            return;
        this->put_2(node->key, node->value);
        if (node->left) {  // traversing to left
            balance_main_tree(node->left);
        }
        if(node->right) {
            balance_main_tree(node->right);  // traversing to right
        }
        return;
    }
    // pre order traversal 
    void pre_order_2(NODE* node, stringstream &ss) {
        if (node == NULL)
            return;
        ss << "key: ";
        ss << node->key;  // adding key in the 
        ss << ", nL: ";
        ss << node->nL;
        ss << ", nR: ";
        ss << node->nR;
        ss << "\n";
        if (node->left) {  // traversing to left
            pre_order_2(node->left, ss);
        }
        if(node->right && !node->isThreaded) {  // traversing to right
            pre_order_2(node->right, ss);
        }
    }
    // checks the balnce 
    string checkBalance() {
        stringstream ss;  // creating a string stream object
        string temp = "";
        no_of_childs(this->get_root());  // calculating childs
        pre_order_2(this->get_root(), ss);  // traversing in preorder to get final result
        temp = ss.str();
        return temp;
    }
};

