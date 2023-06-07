#include <stdio.h>
#include <limits.h>
#include <malloc.h>

struct BstNode {
    int data;
    struct BstNode* left;
    struct BstNode* right;
};

struct BstNode* GetNewNode(int data) {
    struct BstNode* newNode = (struct BstNode*)malloc(sizeof(struct BstNode));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

struct BstNode* Insert(struct BstNode* root, int data) {
    if (root == NULL) {
        root = GetNewNode(data);
        return root;
    }
    else if (data <= root->data) {
        root->left = Insert(root->left, data);
    }
    else {
        root->right = Insert(root->right, data);
    }
    return root;
}

struct BstNode* FindMin(struct BstNode* root) {
    if (root == NULL) {
        return NULL;
    }
    else if (root->left == NULL) {
        return root;
    }
    return FindMin(root->left);
}

struct BstNode* FindMax(struct BstNode* root) {
    if (root == NULL) {
        return NULL;
    }
    else if (root->right == NULL) {
        return root;
    }
    return FindMax(root->right);
}

// Addition: Move the max and FindHeight function before IsBalanced function
int max(int a, int b) {
    return (a > b) ? a : b;
}

int FindHeight(struct BstNode* root) {
    if (root == NULL) {
        return -1;
    }
    return max(FindHeight(root->left), FindHeight(root->right)) + 1;
}

// Rest of your code follows...


struct BstNode* Delete(struct BstNode* root, int data) {
    if (root == NULL) {
        return root;
    }
    else if (data < root->data) {
        root->left = Delete(root->left, data);
    }
    else if (data > root->data) {
        root->right = Delete(root->right, data);
    }
    else {
        if (root->left == NULL && root->right == NULL) {
            free(root);
            root = NULL;
        }
        else if (root->left == NULL) {
            struct BstNode* temp = root;
            root = root->right;
            free(temp);
        }
        else if (root->right == NULL) {
            struct BstNode* temp = root;
            root = root->left;
            free(temp);
        }
        else {
            struct BstNode* temp = FindMin(root->right);
            root->data = temp->data;
            root->right = Delete(root->right, temp->data);
        }
    }
    return root;
}

struct BstNode* Search(struct BstNode* root, int data) {
    if (root == NULL || root->data == data) {
        return root;
    }
    else if (data < root->data) {
        return Search(root->left, data);
    }
    else {
        return Search(root->right, data);
    }
}

void InOrder(struct BstNode* root) {
    if (root == NULL) {
        return;
    }
    InOrder(root->left);
    printf("%d ", root->data);
    InOrder(root->right);
}

void PreOrder(struct BstNode* root) {
    if (root == NULL) {
        return;
    }
    printf("%d ", root->data);
    PreOrder(root->left);
    PreOrder(root->right);
}

void PostOrder(struct BstNode* root) {
    if (root == NULL) {
        return;
    }
    PostOrder(root->left);
    PostOrder(root->right);
    printf("%d ", root->data);
}

void LevelOrder(struct BstNode* root) {
    if (root == NULL) {
        return;
    }

    struct BstNode* queue[100];
    int front = 0;
    int rear = 0;
    int currentLevelNodes = 1;
    int nextLevelNodes = 0;

    queue[rear++] = root;

    while (front < rear) {
        struct BstNode* current = queue[front++];
        printf("%d ", current->data);
        currentLevelNodes--;

        if (current->left != NULL) {
            queue[rear++] = current->left;
            nextLevelNodes++;
        }

        if (current->right != NULL) {
            queue[rear++] = current->right;
            nextLevelNodes++;
        }

        if (currentLevelNodes == 0) {
            printf("\n");
            currentLevelNodes = nextLevelNodes;
            nextLevelNodes = 0;
        }
    }
}

int CountNodes(struct BstNode* root) {
    if (root == NULL) {
        return 0;
    }
    return CountNodes(root->left) + CountNodes(root->right) + 1;
}

struct BstNode* FindSuccessor(struct BstNode* root, int data) {
    struct BstNode* current = Search(root, data);
    if (current == NULL) {
        return NULL;
    }
    if (current->right != NULL) {
        return FindMin(current->right);
    }
    else {
        struct BstNode* successor = NULL;
        struct BstNode* ancestor = root;
        while (ancestor != current) {
            if (current->data < ancestor->data) {
                successor = ancestor;
                ancestor = ancestor->left;
            }
            else {
                ancestor = ancestor->right;
            }
        }
        return successor;
    }
}

struct BstNode* FindPredecessor(struct BstNode* root, int data) {
    struct BstNode* current = Search(root, data);
    if (current == NULL) {
        return NULL;
    }
    if (current->left != NULL) {
        return FindMax(current->left);
    }
    else {
        struct BstNode* predecessor = NULL;
        struct BstNode* ancestor = root;
        while (ancestor != current) {
            if (current->data > ancestor->data) {
                predecessor = ancestor;
                ancestor = ancestor->right;
            }
            else {
                ancestor = ancestor->left;
            }
        }
        return predecessor;
    }
}




int IsBalanced(struct BstNode* root) {
    if (root == NULL) {
        return 1;
    }
    int leftHeight = FindHeight(root->left);
    int rightHeight = FindHeight(root->right);
    int diff = abs(leftHeight - rightHeight);
    if (diff <= 1 && IsBalanced(root->left) && IsBalanced(root->right)) {
        return 1;
    }
    return 0;
}

struct BstNode* LowestCommonAncestor(struct BstNode* root, int value1, int value2) {
    if (root == NULL) {
        return NULL;
    }
    if (root->data > value1 && root->data > value2) {
        return LowestCommonAncestor(root->left, value1, value2);
    }
    else if (root->data < value1 && root->data < value2) {
        return LowestCommonAncestor(root->right, value1, value2);
    }
    return root;
}

void RangeSearch(struct BstNode* root, int low, int high) {
    if (root == NULL) {
        return;
    }
    if (root->data >= low) {
        RangeSearch(root->left, low, high);
    }
    if (root->data >= low && root->data <= high) {
        printf("%d ", root->data);
    }
    if (root->data <= high) {
        RangeSearch(root->right, low, high);
    }
}

void FreeTree(struct BstNode* root) {
    if (root == NULL) {
        return;
    }
    FreeTree(root->left);
    FreeTree(root->right);
    free(root);
}



int ValidateBST(struct BstNode* root, int min, int max) {
    if (root == NULL) {
        return 1;
    }
    if (root->data > min && root->data < max &&
        ValidateBST(root->left, min, root->data) &&
        ValidateBST(root->right, root->data, max)) {
        return 1;
    }
    return 0;
}

int main() {
    struct BstNode* root = NULL;
    int numNodes, data;

    printf("Enter the number of nodes: ");
    scanf("%d", &numNodes);

    printf("Enter the values of the nodes:\n");
    for (int i = 0; i < numNodes; i++) {
        scanf("%d", &data);
        root = Insert(root, data);
    }

    printf("In-order traversal: ");
    InOrder(root);
    printf("\n");

    printf("Pre-order traversal: ");
    PreOrder(root);
    printf("\n");

    printf("Post-order traversal: ");
    PostOrder(root);
    printf("\n");

    printf("Level-order traversal:\n");
    LevelOrder(root);
    printf("\n");

    // Minimum and Maximum
    struct BstNode* minNode = FindMin(root);
    struct BstNode* maxNode = FindMax(root);
    printf("Minimum value: %d\n", minNode->data);
    printf("Maximum value: %d\n", maxNode->data);

    // Count Nodes
    int totalNodes = CountNodes(root);
    printf("Total nodes in the BST: %d\n", totalNodes);

    // Deletion
    printf("Enter a value to delete: ");
    scanf("%d", &data);
    root = Delete(root, data);
    printf("In-order traversal after deleting %d: ", data);
    InOrder(root);
    printf("\n");

    // Searching
    printf("Enter a value to search: ");
    scanf("%d", &data);
    struct BstNode* searchResult = Search(root, data);
    if (searchResult != NULL) {
        printf("%d found in the tree.\n", data);
    }
    else {
        printf("%d not found in the tree.\n", data);
    }

    // Height
    int treeHeight = FindHeight(root);
    printf("Height of the tree: %d\n", treeHeight);

    // Validation
    int isValidBST = ValidateBST(root, INT_MIN, INT_MAX);
    if (isValidBST) {
        printf("The tree is a valid binary search tree.\n");
    }
    else {
        printf("The tree is not a valid binary search tree.\n");
    }

    // Successor
    printf("Enter a value to find its successor: ");
    scanf("%d", &data);
    struct BstNode* successor = FindSuccessor(root, data);
    if (successor != NULL) {
        printf("Successor of %d: %d\n", data, successor->data);
    }
    else {
        printf("No successor found for %d\n", data);
    }

    // Predecessor
    printf("Enter a value to find its predecessor: ");
    scanf("%d", &data);
    struct BstNode* predecessor = FindPredecessor(root, data);
    if (predecessor != NULL) {
        printf("Predecessor of %d: %d\n", data, predecessor->data);
    }
    else {
        printf("No predecessor found for %d\n", data);
    }

    // Check Balanced
    int isBalanced = IsBalanced(root);
    if (isBalanced) {
        printf("The tree is balanced.\n");
    }
    else {
        printf("The tree is not balanced.\n");
    }

    // Lowest Common Ancestor
    int value1, value2;
    printf("Enter two values to find their lowest common ancestor: ");
    scanf("%d%d", &value1, &value2);
    struct BstNode* lca = LowestCommonAncestor(root, value1, value2);
    if (lca != NULL) {
        printf("Lowest Common Ancestor of %d and %d: %d\n", value1, value2, lca->data);
    }
    else {
        printf("No Lowest Common Ancestor found for %d and %d\n", value1, value2);
    }

    // Range Search
    int low, high;
    printf("Enter the range (low and high) to perform range search: ");
    scanf("%d%d", &low, &high);
    printf("Nodes within the range %d and %d: ", low, high);
    RangeSearch(root, low, high);
    printf("\n");

    // Freeing memory
    FreeTree(root);

    return 0;
}


/*
Enter the number of nodes: 8
Enter the values of the nodes:
15
10
Enter a value to delete: 12
In-order traversal after deleting 12: 6 8 10 15 17 20 25
Enter a value to search: 20
20 found in the tree.
Height of the tree: 3
The tree is a valid binary search tree.
Enter a value to find its successor: 15
Successor of 15: 17
Enter a value to find its predecessor: 17
Predecessor of 17: 15
The tree is not balanced.
Enter two values to find their lowest common ancestor: 6 20
Lowest Common Ancestor of 6 and 20: 15
Enter the range (low and high) to perform range search: 10 20
Nodes within the range 10 and 20: 10 15 17 20
*/