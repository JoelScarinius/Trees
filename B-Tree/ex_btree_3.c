// Exercise: Trees-2 (TDRK12 Spring 2022)
// Task 2. Write an algorithm in pseudocode to traverse the tree using "inorder"
//
// Task 3. Extend the program specified in (1) to traverse the B-tree.
// Implement the  algorithm from (2) and
// add function to traverse the tree using "inorder"
// void traverse(struct node *tree, int level)

#include <stdio.h>
#include <stdlib.h>

// Order of the B-tree
#define MAX 4

struct node
{
    struct node *children[MAX]; // M sub-trees
    int keys[MAX - 1];          // M-1 keys
    int key_count;              // number of keys, number of children is key_count+1
};

struct node *root;

// Creates a node with given keys, number of them and pointer to children
struct node *createNode(int keys[], int count, struct node *children[])
{
    struct node *newNode;
    newNode = (struct node *)malloc(sizeof(struct node));
    newNode->key_count = count;
    for (size_t i = 0; i < count; i++)
    {
        newNode->keys[i] = keys[i];
        newNode->children[i] = children[i];
    }
    newNode->children[count] = children[count];
    return newNode;
}

// Traverse the tree using "inorder"
void traverse(struct node *tree, int level)
{
    if (tree == NULL)
    {
        return;
    }
    for (size_t i = 0; i < tree->key_count; i++)
    {
        traverse(tree->children[i], level + 1);
        printf("\n");
        for (size_t i = 0; i < level; i++)
        {
            printf("  ");
            //fflush(stdout);
        }
        printf("%d ", tree->keys[i]);
    }
    traverse(tree->children[tree->key_count], level + 1);
}

struct node *search(struct node *tree, int key) // Algorimth for searching for any value in the given tree.
{
    if (tree == NULL) return tree; // If the tree is empty or if the value searched for doesn't exists return NULL.
    for (size_t i = 0; i <= tree->key_count; i++) // Loops until all values at a certain node is compare to key.
    {
        if (key == tree->keys[i]) return tree; // Returns the node with the found key.
        if (key < tree->keys[i]) return search(tree->children[i], key); // Recursivly calls the function to search the left subtree.
        if (i == tree->key_count) return search(tree->children[i], key); // Recursivly calls the function to search the right subtree.
    }
    return NULL;
}

int main()
{   
    // Max amount of children for all nodes is 4
    struct node *leaf_children[4] = {NULL, NULL, NULL, NULL};

    // Create the left sub-tree
    int leaf1_keys[2] = {18, 27};
    struct node *leaf1 = createNode(leaf1_keys, 2, leaf_children);

    int leaf2_keys[2] = {30, 31};
    struct node *leaf2 = createNode(leaf2_keys, 2, leaf_children);

    int leaf3_keys[2] = {36, 39};
    struct node *leaf3 = createNode(leaf3_keys, 2, leaf_children);

    int inter1_keys[2] = {29, 32};
    struct node *inter1_children[3] = {leaf1, leaf2, leaf3};
    struct node *inter1 = createNode(inter1_keys, 2, inter1_children);

    // Create the right sub-tree
    int leaf4_keys[2] = {46, 47};
    struct node *leaf4 = createNode(leaf4_keys, 2, leaf_children);

    int leaf5_keys[3] = {54, 59, 61};
    struct node *leaf5 = createNode(leaf5_keys, 3, leaf_children);

    int leaf6_keys[2] = {67, 72};
    struct node *leaf6 = createNode(leaf6_keys, 2, leaf_children);

    int inter2_keys[2] = {49, 63};
    struct node *inter2_children[3] = {leaf4, leaf5, leaf6};
    struct node *inter2 = createNode(inter2_keys, 2, inter2_children);

    // Create the root
    int root_keys[1] = {45};
    struct node *root_children[2] = {inter1, inter2};
    root = createNode(root_keys, 1, root_children);

    // Traverse the tree
    traverse(root, 0);
    printf("\n");

    char input;
    int key;
    while (input != 'N' && input != 'n') // Loops until user enters the letter n in lower or uppercase form.
    {
        fflush(stdin);
        printf("\nEnter the value you want to search for : "); 
        scanf("%d", &key);
        struct node *foundKey = search(root, key); // Searches for the value entered and returns the node containing the value or NULL.
        (foundKey != NULL) ? puts("The value was found!") : puts("The value wasn't found!"); 
        do
        {
            fflush(stdin);
            printf("\nDo you want to search for antoher value? Press \"Y\" for \"Yes\" and \"N\" for \"No\" : ");
            scanf("%c", &input);
            if (input != 'N' && input != 'n' && input != 'Y' && input != 'y') puts("Invalid input, please try again!");
        } while (input != 'N' && input != 'n' && input != 'Y' && input != 'y'); // Loops until user enters a valid character.
    }
    puts("Have a good one!");
}