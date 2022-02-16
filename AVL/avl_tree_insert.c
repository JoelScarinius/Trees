// This source codeis from the texbook Data Structures Using C, 2nd edition, by Reema Thareja, Oxford University Press, 2014.
// The detailed comments and references to the lecture slides are added by Vladimir Tarasov
// Data Structures, 7.5 credits, Spring 2022.

#include <stdio.h>
#include <stdlib.h>

#define SIZE 8

typedef enum
{
    FALSE,
    TRUE
} bool;

struct node
{
    int data;
    int balance;
    struct node *left;
    struct node *right;
};

struct node* insertingNodes(int data, struct node *tree, bool *ht_inc)
{   
    // ht_inc is a tricky variable. It is set to TRUE after a new node is inserted
    // as a leaf, which means that a re-balancing might be needed at a hihger
    // level of a tree, where the critical node resides. When re-balancing is  
    // done or will not be needed at a hihger level, ht_inc is set to FALSE.
    struct node *aptr, *bptr;
    if (tree == NULL)
    {
        tree = (struct node *)malloc(sizeof(struct node));
        tree->data = data;
        tree->left = NULL;
        tree->right = NULL;
        tree->balance = 0;
        *ht_inc = TRUE; // a new node is a added
        return (tree);
    }
    // A new node is inserted as a leaf.
    // First find where to add it by following the BST order
    // Then check the balance factor
    // Finally perform a rebalancing rotation
    if (data < tree->data)
    {
        // Insert in the left sub-tree
        tree->left = insertingNodes(data, tree->left, ht_inc);
        if (*ht_inc == TRUE) // a re-balancing might be needed
        {
            // Check the balance factor after the insertion
            switch (tree->balance)
            {
            case -1: /* Right heavy */
                // the node was right heavy and after insertion has become balanced.
                tree->balance = 0;
                *ht_inc = FALSE; // re-balancing will not be needed at a hihger level
                break;
            case 0: /* Balanced */
                // the node was balanced and after insertion has become left heavy.
                tree->balance = 1;
                break;
            case 1: /* Left heavy */
                // the node was left heavy and after insertion has become an unbalanced sub-tree.
                // Rebalancing rotation is needed - determine the type of rotation
                // Check the left sub-tree
                aptr = tree->left; // "tree" is A and "aptr" is B (see slides 46 and 48)
                if (aptr->balance == 1)
                {
                    // LL rotation: the new node is inserted in the left sub-tree of
                    // the left sub-tree of the critical node
                    printf("Left to Left Rotation\n");
                    tree->left = aptr->right; // T2 is made left sub-tree of A (see slide 46)
                    aptr->right = tree;             // A is made right sub-tree of B (see slide 46)
                    tree->balance = 0;
                    aptr->balance = 0;
                    tree = aptr; // B is moved up to the A-place (see slide 46)
                }
                else
                {
                    // LR rotation: the new node is inserted in the right sub-tree of
                    // the left sub-tree of the critical node
                    printf("Left to Right rotation\n");
                    bptr = aptr->right;             // "bptr" is C (see slide 48)
                    aptr->right = bptr->left; // T2 is made right sub-tree of B (see slide 48)
                    bptr->left = aptr;              // B is made left sub-tree of C (see slide 48)
                    tree->left = bptr->right;  // T3 is made left sub-tree of A (see slide 48)
                    bptr->right = tree;              // A is made right sub-tree of C (see slide 48)
                    if (bptr->balance == 1)
                        tree->balance = -1;
                    else
                        tree->balance = 0;
                    if (bptr->balance == -1)
                        aptr->balance = 1;
                    else
                        aptr->balance = 0;
                    bptr->balance = 0;
                    tree = bptr; // C moved up to the A-place (see slide 48)
                }
                *ht_inc = FALSE; //re-balancing is done
            }
        }
    }
    else if (data > tree->data)
    {
        // Insert in the right sub-tree
        tree->right = insertingNodes(data, tree->right, ht_inc);
        if (*ht_inc == TRUE) // a re-balancing might be needed
        {
            // Check the balance factor after the insertion
            switch (tree->balance)
            {
            case 1: /* Left heavy */
                // the node was left heavy and after insertion has become balanced.
                tree->balance = 0;
                *ht_inc = FALSE; // re-balancing will not be needed at a hihger level
                break;
            case 0: /* Balanced */
                // the node was balanced and after insertion has become right heavy.
                tree->balance = -1;
                break;
            case -1: /* Right heavy */
                // the node was right heavy and after insertion has become an unbalanced sub-tree.
                // Rebalancing rotation is needed - determine the type of rotation
                aptr = tree->right; // "tree" is A and "aptr" is B (see slides 47 and 49)
                if (aptr->balance == -1)
                {
                    printf("Right to Right Rotation\n");
                    tree->right = aptr->left; // T2 is made right sub-tree of A (see slide 47)
                    aptr->left = tree;              // A is made left sub-tree of B (see slide 47)
                    tree->balance = 0;
                    aptr->balance = 0;
                    tree = aptr; // B is moved up to A-palce (see slide 47)
                }
                else
                {
                    printf("Right to Left Rotation\n");
                    bptr = aptr->left;              //  "bptr" is C (see slide 49)
                    aptr->left = bptr->right; // T3 is made left sub-tree of B (see slide 49)
                    bptr->right = aptr;             // B is made right sub-tree of C (see slide 49)
                    tree->right = bptr->left;  // T2 is made right sub-tree of A (see slide 49)
                    bptr->left = tree;
                    if (bptr->balance == -1)
                        tree->balance = 1;
                    else
                        tree->balance = 0;
                    if (bptr->balance == 1)
                        aptr->balance = -1;
                    else
                        aptr->balance = 0;
                    bptr->balance = 0;
                    tree = bptr; // C is moved up to A-palce (see slide 49)
                }               /*End of else*/
                *ht_inc = FALSE; // re-balancing is done
            }
        }
    }
    return (tree);
}

struct node *search(struct node *ptr, int data)
{
    if (ptr != NULL)
        if (data < ptr->data)
            ptr = search(ptr->left, data);
        else if (data > ptr->data)
            ptr = search(ptr->right, data);
    return (ptr);
}

void display(struct node *ptr, int level)
{
    int i;
    if (ptr != NULL)
    {
        display(ptr->right, level + 1);
        printf("\n");
        for (i = 0; i < level; i++)
            printf(" ");
        printf("%d", ptr->data);
        display(ptr->left, level + 1);
    }
}

struct node *findLargestElement(struct node *tree)
{
    if ((tree == NULL) || (tree->right == NULL))
        return tree;
    else
        return findLargestElement(tree->right);
}

struct node *deleteElement(struct node *tree, int val, bool *ht_inc)
{
    struct node *ptr;

    if (tree == NULL)
    {
        printf("\n VAL not found in the tree \n");
        *ht_inc = TRUE;
    }
    else if (val < tree->data)
    {
        *ht_inc = TRUE;
        tree->left = deleteElement(tree->left, val, ht_inc);
    }
    else if (val > tree->data)
    {
        *ht_inc = TRUE;
        tree->right = deleteElement(tree->right, val, ht_inc);
    }
    else // val == tree->data
    {
        if (tree->left && tree->right)
        {
            // Find the in-order predecessor
            ptr = findLargestElement(tree->left);
            tree->data = ptr->data;
            // Delete the node of the in-order predecessor
            tree->left = deleteElement(tree->left, ptr->data, ht_inc);
        }
        else // at least one child is absent
        {
            ptr = tree;
            // no children - return NULL
            if (tree->left == NULL && tree->right == NULL)
                tree = NULL;
            // if the node has a child (but not both)
            // it is replaced by the child, which is returned
            else if (tree->left != NULL)
                tree = tree->left;
            else
                tree = tree->right;
            // Delete the initial node
            free(ptr);
        }
    }
    return tree;
}

struct node* balanceTree (struct node *tree, bool *ht_inc) 
{
    struct node *aptr, *bptr;

    if (*ht_inc == TRUE) // a re-balancing might be needed
    {
        // Check the balance factor after the deletion
        switch (tree->balance)
        {
        case -1: /* Right heavy */
            // the node was right heavy and after deletion has become balanced.
            tree->balance = 0;
            break;
        case 0: /* Balanced */
            // the node was balanced and after deletion has become left heavy.
            tree->balance = 1;
            break;
        case 1: /* Left heavy */
            // the node was left heavy and after deletion has become an unbalanced sub-tree.
            // Rebalancing rotation is needed - determine the type of rotation
            // Check the left sub-tree
            aptr = tree->left; // "tree" is A and "aptr" is B (see slides 46 and 48)
            if (aptr->balance == 1 || aptr->balance == 0)
            {
                // R0 or R1 rotation: the new node is deleted in the left sub-tree of
                // the left sub-tree of the critical node
                puts("R0 Rotation");
                tree->left = aptr->right; // T2 is made left sub-tree of A (see slide 46)
                aptr->right = tree;             // A is made right sub-tree of B (see slide 46)
                tree->balance = 0;
                aptr->balance = 0;
                tree = aptr; // B is moved up to the A-place (see slide 46)
            }
            else
            {
                // R-1 rotation: the new node is deleted in the right sub-tree of
                // the left sub-tree of the critical node
                puts("R-1 rotation");
                bptr = aptr->right;             // "bptr" is C (see slide 48)
                aptr->right = bptr->left; // T2 is made right sub-tree of B (see slide 48)
                bptr->left = aptr;              // B is made left sub-tree of C (see slide 48)
                tree->left = bptr->right;  // T3 is made left sub-tree of A (see slide 48)
                bptr->right = tree;              // A is made right sub-tree of C (see slide 48)
                if (bptr->balance == 1)
                    tree->balance = -1;
                else
                    tree->balance = 0;
                if (bptr->balance == -1)
                    aptr->balance = 1;
                else
                    aptr->balance = 0;
                bptr->balance = 0;
                tree = bptr; // C moved up to the A-place (see slide 48)
            }
            *ht_inc = FALSE; //re-balancing is done
        }
    }
    return tree;
}


int main()
{
    bool ht_inc;
    int data, num = 0, start = 0;
    struct node *root = NULL;

    while (1)
    {
        if (num == 0 || num == 3)
        {
            for (size_t i = 0; i < SIZE; i++)
            {   
                if (start == 0)
                {
                    int firstArr[SIZE] = {45,36,63,27,39,72,37,41};
                    root = insertingNodes(firstArr[i], root, &ht_inc);
                }
                else 
                {
                    if (start == 1) root = NULL;
                    int secondArr[SIZE] = {54,63,45,65,39,51,18,47};
                    root = insertingNodes(secondArr[i], root, &ht_inc);
                    start++;
                }
            }
        }
        if (num != -1 && num != 2)
        {
            printf("\tThe output of the %s test case:\n", (start == 0) ? "first" : "second");
            printf("\nRunning %s test\n", (start == 0) ? "first" : "second");
            printf("The %s AVL tree is:\n", (start == 0) ? "first" : "second");
            display(root, 1);
        }
        puts("\n\n1.Delete");
        puts("2.Display");
        printf("%s\n", (start == 0) ? "3.Second test" : "3.Quit");
        printf("Enter your option : ");
        fflush(stdin);
        scanf("%d", &num);
        switch (num)
        {
        case 1:
            printf("Enter the value to be deleted : ");
            fflush(stdin);
            scanf("%d", &data);
            if (search(root, data) != NULL) {
                root = deleteElement(root, data, &ht_inc);
                root = balanceTree(root, &ht_inc);
                num = -1;
            }
            else puts("Deletion failed, tree is empty!");
            break;
        case 2:
            if (root == NULL)
            {
                printf("Tree is empty\n");
            }
            else 
            {   
                printf("Tree is :\n");
                display(root, 1);
            }
            break;
        case 3:
            if (start == 0)
            {   
                start++;
                break;
            }
            exit(1);
        default:
            printf("Wrong option\n");
        }
    }
    fflush(stdin);
    getchar();
}
