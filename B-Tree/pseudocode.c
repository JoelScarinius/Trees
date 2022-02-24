/*
search(TREE, KEY)
Step 1: IF TREE = NULL, then
            Return TREE

Step 2: FOR i <= TREE->KEY_COUNT 
            IF KEY = TREE->KEYS[i]
                Return TREE
            [END OF IF]
            IF KEY < TREE->KEYS[i]
                Return search(TREE->CHILDREN[i], KEY)
            [END OF IF]
            IF i = TREE->KEY_COUNT
                Return search(TREE->CHILDREN[i], KEY)
            [END OF IF]
        [END OF FOR]
        Return NULL
Step 3: END
*/