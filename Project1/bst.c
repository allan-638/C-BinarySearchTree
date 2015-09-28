#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include "bst.h"

void bst_init( bst_t *tree ) {
    // Nullify root pointer
    tree -> root = NULL;
    // Reset size to zero
    tree -> size = 0;
}

void bst_destroy( bst_t *tree ) {
    // Initialize variable 
    S32 valToRemove = 0;
    
    while(tree -> size > 0) {
       // Get the largest value from the tree
       valToRemove = bst_max(tree);
       printf("%d\n", valToRemove);
       // Pop the largest value
       bst_erase(tree, valToRemove);
    }
    // Tree will be empty at this point
    free(tree);
}

size_t bst_size( bst_t *tree ) {
    // Return size property from tree
	return tree -> size;
}

bool bst_insert( bst_t *tree, S32 val ) {
	  // Initialize temporary node at root
    bsn_t *p_tempNode = tree -> root;
  	// Initialize blank node
    bsn_t *p_inputNode = (bsn_t *)malloc(sizeof(bsn_t));
    // Set left and right to NULL
    p_inputNode -> left = p_inputNode -> right = NULL;
    // Add value to the node
    p_inputNode -> val = val;

    // If the tree is empty, make root = node
    if(bst_size == 0 || tree -> root == NULL) {
         tree -> root = p_inputNode;
         tree -> size++;
         return true;
    }
    
    // Initialize Search Loop 
    while(p_tempNode != NULL) {
         // If there already exists input value
         if(p_tempNode -> val == val) {
              return false;
         } 
         // If the input value is smaller than current value
         else if(val < p_tempNode -> val) {
              // if left node is empty, insert val to left
              if(p_tempNode -> left == NULL) {
                   p_tempNode -> left = p_inputNode;
                   tree -> size++; // size increment
                   return __TRUE;
              }
              // if left node is not empty, traverse to left
              else {
                   p_tempNode = p_tempNode -> left;
              }
         }
         // If the input value is bigger than current value (last possible case)
         else {
              // if right node is empty, insert val to right
              if(p_tempNode -> right == NULL) {
                   p_tempNode -> right = p_inputNode;
                   tree -> size++; // size increment
                   return __TRUE;
              }
              // if right node is not empty, traverse to right
              else {
                   p_tempNode = p_tempNode -> right;
              }
         }
    }
		
    return false;
}

S32 bst_min( bst_t *tree ) {
    // Placeholder node at root
    bsn_t* p_visitorNode = tree -> root;

    // If tree isnt initialized or empty
    if (tree -> root == NULL || tree -> size == 0){
       return INT_MIN;
    }
    
    // Keep going left for smallest value
    while (p_visitorNode -> left != NULL) {
        p_visitorNode = p_visitorNode -> left;
    }
    
    // Return value
    return p_visitorNode -> val;
}

S32 bst_max( bst_t *tree ) {
    // Placeholder node at root
    bsn_t* p_visitorNode = tree -> root;
	
	// If tree isnt initialized or empty
    if (tree -> root == NULL || tree -> size == 0){
       return INT_MAX;
    }
    
    // Keep going right for largest value
    while (p_visitorNode -> right != NULL) {
        p_visitorNode = p_visitorNode -> right;
    }
    
    // Return value
    return p_visitorNode -> val;
}

bool bst_erase( bst_t *tree, S32 val ) {
     // Initialize double pointer for search value
     bsn_t **p_searchNode = &(tree -> root); 
     bool foundFlag = false;
	 
	 // Initialize left/right nodes
	 bsn_t *p_leftNode = NULL;
	 bsn_t *p_rightNode = (*p_searchNode) -> right;
     
     // If tree is invalid (i.e. empty or not initialized)
     if(tree -> size == 0 || tree -> root == NULL) {
         return false;
     }
     
     // Searching for value, if not found, return false
     while(!foundFlag) {
         if((*p_searchNode) == NULL) {
             return false; 
         } else if((*p_searchNode) -> val == val) {
             foundFlag = true;
         } else if(val < (*p_searchNode) -> val) {
             p_searchNode = &((*p_searchNode) -> left);
         } else {
             p_searchNode = &((*p_searchNode) -> right); 
         }
     }
     
     p_leftNode = (*p_searchNode) -> left;
     p_rightNode = (*p_searchNode) -> right;
     // Free the targeted value
     free((*p_searchNode));
     
     // Adjusting tree for removed value
     // Case 1: Leaf Node
     if(p_leftNode == NULL && p_rightNode == NULL) { 
         (*p_searchNode) = NULL;
     }
     // Case 2: If Left Node Doesn't Exist
     else if(p_leftNode == NULL && p_rightNode != NULL) {
         (*p_searchNode) = p_rightNode; 
     }
     // Case 3: If Right Node Doesn't Exist
     else if(p_leftNode != NULL && p_rightNode == NULL) {
         (*p_searchNode) = p_leftNode; 
     }
     // Case 4: If Both Nodes Exist 
     else {
         (*p_searchNode) = p_rightNode;
         // Find Minimum Node on Right-Side Tree   
         while(p_rightNode -> left != NULL) {
             p_rightNode = p_rightNode -> left; 
         }
         p_rightNode -> left = p_leftNode;
     }
     
     tree -> size--;
     return true;
}
