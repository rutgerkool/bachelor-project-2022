

#include <iostream>
#include<string>
#include<vector>
#include<math.h>
#include<algorithm>
#include<iomanip>
#include<queue>
#include<climits>
using namespace std;
//Node class for each individual pointer node in a BST
class Node
{
public:
    int val;
    Node* left;
    Node* right;
    //Consteructor for Node class
    Node(int val)
    {
        this->val = val;
        this->left = nullptr;
        this->right = nullptr;
    }
};
class BST {
    Node* root;
public:
    BST() {
        root = nullptr;
    }
    //Insert key function which  has a helper recursive function
    void insertKey(int newKey) {
        root = insertRec(newKey, root);
    }
    //Check key function which has a heper recursive function
    bool hasKey(int searchKey) {
        return  recurhasKey(searchKey, root);
    }
    //Function for creating inordr epresentation in vector
    std::vector<int> inOrder() {
        vector<int> v;
        //Passing vector as reference
        recurInorder(root, v);
        return v;
    }
    //Function to get height of the tree which also has a helper
    int getHeight() {
        return recurgetHeight(root);
    }
    //Overidding destructor for BST call and we need helper recursive function as we need to delete all the nodes recursively using delete keyword
    ~BST() {
        recurDelete(root);
        root = nullptr;
    }
    
private:
    //This is recursive implementation of insertKey  because it takes root as the parameter which keeps changeing
    Node* insertRec(int newKey, Node* root)
    {
        if (root == nullptr) {
            Node* curr = new Node(newKey);
            return curr;
        }
        if (root->val < newKey) {
            root->right = insertRec(newKey, root->right);
        }
        else {
            root->left = insertRec(newKey, root->left);
        }
        return root;
    }
    //This is recursive implementation of checkKey  because it takes root as the parameter which keeps changeing
    bool recurhasKey(int searchKey, Node* root)
    {
        if (root == nullptr)
            return false;;
        if (root->val < searchKey)
            return recurhasKey(searchKey, root->right);
        else if (root->val == searchKey)
            return true;
        else
            return recurhasKey(searchKey, root->left);
    }
    //This is recursive implementation of inOrder  because it takes root as the parameter which keeps changeing nad vector is passed as reference
    void recurInorder(Node* root, vector<int>& v)
    {
        if (root == nullptr)
            return;
        recurInorder(root->left, v);
        v.push_back(root->val);
        recurInorder(root->right, v);
    }
    //This is recursive implementation of getHeight  because it takes root as the parameter which keeps changeing
    int recurgetHeight(Node* root)
    {
        if (root == nullptr)
            return 0;
        return 1 + max(recurgetHeight(root->left), recurgetHeight(root->right));
    }
    //delete all allocated data
    void recurDelete(Node* root) {
        if (root == nullptr)
            return;
        recurDelete(root->left);
        recurDelete(root->right);
        delete(root);
        root = nullptr;
    }
    //counting nodes
    unsigned int nodeCount(const Node* node)
    {
        if (node == nullptr) {
            return 0;
        }
        else {
            return 1 + nodeCount(node->left) + nodeCount(node->right);
        }
    }
};
//check if given string is integer or not
bool isInteger(string str)
{
    for (int i = 0; i < str.size(); i++)
    {
        if (str.at(i) == '-') {
            i++;
        }
        if (!isdigit(str.at(i))) {
            return false;
        }
    }
    return true;
}
int main()
{
    BST* tree = new BST();
    string str;
    //Taking user input till the user inputs a q or Q
    cout << "Enter the numbers to be stored (end with a letter): ";
    while (cin >> str)
    {
        //Calling helper function to check if input is integer or not
        if (!isInteger(str)) {
            break;
        }
        int v = stoi(str);
        tree->insertKey(v);
    }
    cout << endl;
    cout << "Which number do you want to look up? ";
    int keyToSearch;
    cin >> keyToSearch;
    cout << endl;
    cout << keyToSearch << " is in the tree: ";
    if (tree->hasKey(keyToSearch)) {
        cout << "yes" << endl;
    }
    else {
        cout << "no" << endl;;
    }
    vector<int> v = tree->inOrder();
    //Printing vector
    cout << "The numbers in sorted order: ";
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }
    cout << endl;
    cout << "Height of the tree: " << tree->getHeight() << endl;
    delete(tree);
    return 0;
}

