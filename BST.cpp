#include <iostream>
using namespace std;

struct node {
  int key;
  struct node *left, *right;
};

// Creating new node
node* newNode(int data)
{
    node* temp = new node;
    temp->key = data;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

//Finding minimum key value
struct node* minValueNode(struct node* node)
{
    struct node* current = node;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}

// Inorder traversal
void traverseInOrder(struct node *root) {
    if (root == NULL)
        return;
    else {
        traverseInOrder(root->left);
        cout << root->key << " ";
        traverseInOrder(root->right);
    }
}

// Insert a node
struct node *insertNode(struct node *node, int key) {
    //if the node is empty
    if(node == NULL)
        return newNode(key);

  if(node->key < key)
        node->right = insertNode(node->right,key);

  else if(node->key > key)
        node->left = insertNode(node->left,key);

  return node;
}

// Deleting a node
struct node *deleteNode(struct node *root, int key) {

    if (root == NULL)
        return root;

    // If key less left subtree
    if (key < root->key)
        root->left = deleteNode(root->left, key);

    // If key more left subtree
    else if (key > root->key)
        root->right = deleteNode(root->right, key);

    // if key is same
    else {
        // no child
        if (root->left == NULL and root->right == NULL)
            return NULL;

        // with only one child
        else if (root->left == NULL) {
            struct node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            struct node* temp = root->left;
            free(root);
            return temp;
        }

        //with two children
        struct node* temp = minValueNode(root->right);

        root->key = temp->key;

        root->right = deleteNode(root->right, temp->key);
    }
    return root;
}

// Driver code
int main() {
  struct node *root = NULL;

  int operation;
  int operand;
  cin >> operation;

  while (operation != -1) {
    switch(operation) {
      case 1: // insert
        cin >> operand;
        root = insertNode(root, operand);
        cin >> operation;
        break;
      case 2: // delete
        cin >> operand;
        root = deleteNode(root, operand);
        cin >> operation;
        break;
      default:
        cout << "Invalid Operator!\n";
        return 0;
    }
  }

  traverseInOrder(root);
}
