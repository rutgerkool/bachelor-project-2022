

    #include <iostream>
    #include <cmath>
    #include <vector>
    #include <string>
    using namespace std;
    class BST{
        public:
            BST();
            ~BST();
            void insertKey(int newKey);
            bool hasKey(int searchKey);
            std::vector<int> inOrder();
            int getHeight();
        private:
            class Node {
                public:
                    int data; // Node Object
                    Node* left;
                    Node* right;
                    Node(int addData);
                    ~Node();
                private:
                    Node* nodePtr;
            };
            Node* rootPtr;
            void addData(int newKey, Node* &rootPtr);
            bool checkKey(int data, Node* &rootPtr);
            vector<int> sortedVector;
            void sortVector(Node* &rootPtr);
            int checkHeight(Node* rootPtr);
    };
    BST::BST()  {
        rootPtr = nullptr; // Creating an empty tree!
    }
    BST::~BST()  {
        if(rootPtr != nullptr) {
            delete rootPtr;
        }
    }
    BST::Node::Node(int addData) {
        left = nullptr;
        right = nullptr;
        this->data = addData;
    }
    BST::Node::~Node() {
        if(right != nullptr) {
            delete right;
        }
        if(left != nullptr) {
            delete left;
        }
    }
    void BST::insertKey(int newKey) {
        addData(newKey, rootPtr);
    }
    void BST::addData(int newKey, Node* &rootPtr) {
        if(rootPtr == nullptr) {
            rootPtr = new Node(newKey);
            // cout << rootPtr->data << endl;
        }
        else if(rootPtr->data > newKey){
            addData(newKey, rootPtr->left);
        }
        else if(rootPtr->data < newKey) {
            addData(newKey, rootPtr->right);
        }
    }
    bool BST::hasKey(int searchKey) {
        return checkKey(searchKey, rootPtr);
    }
    bool BST::checkKey(int data, Node* &rootPtr) {
        if(rootPtr == nullptr) {
            return false;
        }
        else if(rootPtr->data == data){
            return true;
        }
        else if(data < rootPtr->data) {
            return checkKey(data, rootPtr->left);
        }
        else {
            return checkKey(data, rootPtr->right);
        }
    }
    vector<int> BST::inOrder() {
        sortVector(rootPtr);
        return sortedVector;
    }
    void BST::sortVector(Node* &rootPtr) {
        if(rootPtr != nullptr) {
            sortVector(rootPtr->left);
            sortedVector.push_back(rootPtr->data);
            sortVector(rootPtr->right);
        }
    }
    int BST::getHeight() {
        return checkHeight(rootPtr);
    }
    int BST::checkHeight(Node* rootPtr) {
        if(rootPtr == nullptr) {
            return 0;
        }
        else {
            int heightRight = checkHeight(rootPtr->right);
            int heightLeft = checkHeight(rootPtr->left);
            if(heightRight > heightLeft){
                return (heightRight + 1);
            }
            else {
                return (heightLeft +1);
            }
        }
    }
    int main() {
        int userInput, findNumber;
        string result;
        vector<int> sortedTree;
        BST tree;
        BST* binarySearchTree = new BST;
        cout << "Enter the numbers to be stored (end with a letter): ";
        
        while(!cin.fail()){
            cin >> userInput;
            if(!cin.fail()){
                binarySearchTree->insertKey(userInput);
            }
        }
        
        cin.clear();
        cin.ignore();
        cout << "Which number do you want to look up? ";
        cin >> findNumber;
        if(binarySearchTree->hasKey(findNumber) == true) {
            result = "yes";
        }
        else {
            result = "no";
        }
        cout << findNumber << " is in the tree: " << result << endl;
        cout << "The numbers in sorted order: ";
        sortedTree = binarySearchTree->inOrder();
        for(int j = 0; j < sortedTree.size(); j++) {
            cout << sortedTree.at(j) << " ";
        }
        cout << endl;
        cout << "Height of the tree: " << binarySearchTree->getHeight() << endl;
        delete binarySearchTree;
        return 0;
    }

