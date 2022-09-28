// treemap_funcs.c: Provides a small library of functions that operate on
// binary search trees mapping strings keys to string values.
#include <stdio.h>
#include "treemap.h"
#include <stdlib.h>
#include <string.h>
//Yiling Tan tan00250
//OH YEAH, Part 3 FINALLy 

void treemap_init(treemap_t *tree){
  tree->root = NULL;
  return;
}
// Initialize the given tree to have a null root making it size 0.

int treemap_add(treemap_t *tree, char key[], char val[]){

  node_t* cur = tree->root;
  int result = 1;
//if the tree doesn't even have a root (poor tree, but don't worry, we gonna make one for ya)
  if(cur == NULL){
    node_t* new_node = malloc(sizeof(node_t)); 
    //solve the valgrind error, ==2966274== Memcheck, a memory error detector
    memset(new_node,0,sizeof(node_t));
    strcpy(new_node->key, key); 
    strcpy(new_node->val, val);
    tree->root = new_node;
    return 1;
  }
  while(1){
    int diff =0;
    diff = strcmp(cur->key, key);
    //if the current node key is less than the key of the new node which we want to add
    if(diff<0){
      if(cur->right != NULL){
        cur = cur->right;
      }else{
        //there is no node on the right side of the current node, so we need to make a newnode and add to that tree        
        node_t* new_node = malloc(sizeof(node_t)); 
        //solve the valgrind error, ==2966274== Memcheck, a memory error detector
        memset(new_node,0,sizeof(node_t));
        strcpy(new_node->key, key); 
        strcpy(new_node->val, val);
        cur->right = new_node;
        result = 1;
        break;
      }
    }
    //if the current node key is the same as the key of the new node which we want to add
    if(diff == 0){
      //if the val is different, we gonna say "modified existing key" Yo!
    if(strcmp(cur->val,val) != 0){
      printf("modified existing key\n");
      strcpy(cur->val,val);
    }
    //if vals are different, then we just set result to 0 and we are good to go, BREAK
      result = 0;
      break;
    }      
    //okay, if the current node key is greater than the key of the new node which we want to add
    if(diff > 0){
      //there is no node on the left side of the current node, so we need to make a newnode and add to that tree  
      if(cur->left != NULL){
        cur = cur->left;
      }else{
        node_t* new_node = malloc(sizeof(node_t)); 
        //solve the valgrind error, ==2966274== Memcheck, a memory error detector
        memset(new_node,0,sizeof(node_t));
        strcpy(new_node->key, key); 
        strcpy(new_node->val, val);
        cur->left = new_node;
        result = 1;
        break;
      }
    }
  }
  
  return result;
}
// Inserts given key/value into a binary search tree. Uses an
// ITERATIVE (loopy) approach to insertion which starts a pointer at
// the root of the tree and changes its location until the correct
// insertion point is located. If the key given already exists in the
// tree, no new node is created; the existing value is changed to the
// parameter 'val' and 0 is returned.  If no node with the given key
// is found, a new node is created and with the given key/val, added
// to the tree, and 1 is returned. Makes use of strcpy() to ease
// copying characters between memory locations.


char *treemap_get(treemap_t *tree, char key[]){
  node_t* root = tree->root;
  if(root == NULL){
    return NULL;
  }
  //iterate through the tree to find the node
  while(root != NULL){
    int diff = 0;
    diff = strcmp(root->key, key);
    if(diff == 0){
      return root->val;
    }
    //recursing to the right
    if(diff < 0){
      root = root->right;
    }
    //recursing to the left
    if(diff > 0){
      root = root->left;
    }
  }
  return NULL;
}
// Searches the tree for given 'key' and returns its associated
// value. Uses an ITERATIVE (loopy) search approach which starts a
// pointer at the root of the tree and changes it until the search key
// is found or determined not to be in the tree. If a matching key is
// found, returns a pointer to its value. If no matching key is found,
// returns NULL.

void treemap_clear(treemap_t *tree){
  //using the node_t** cuz I want to access the tree root after I iterate through all those subtree of the tree
  node_t** root = &tree->root;
  node_remove_all(*root);
  *root = NULL;
}  
// Eliminate all nodes in the tree setting its contents empty. Uses
// recursive node_remove_all() function to free memory for all nodes.

void node_remove_all(node_t *cur){
  if(cur == NULL){
    return;
  }
  node_remove_all(cur->left);
  node_remove_all(cur->right);
  free(cur);
}
// Recursive helper function which visits all nodes rooted at node
// `cur` and frees the memory associated with them. This requires a
// post-order traversal: visit left sub-tree, visit right sub-tree,
// then free the `cur` node.

int treemap_size(treemap_t *tree){
  node_t* root = tree->root;
  int result = node_count_all(root);
  return result;
}
// Returns the number of nodes currently in the tree. Uses
// node_count_all() to recursively count all nodes.

int node_count_all(node_t *cur){
  if(cur == NULL){
    return 0;
  }
  return 1 + node_count_all(cur->left) + node_count_all(cur->right);
}
// Counts all nodes in the tree rooted at `cur`. Uses recursion to
// descend to the left and right branch if present and count nodes
// there, adding 1 for the `cur` if non-null. Returns 0 if `cur` is
// NULL.

void treemap_print_revorder(treemap_t *tree){
  node_t* root = tree->root;
  int indent = 0;
  node_print_revorder(root, indent);
}
// Prints the key/val pairs of the tree in reverse order at differing
// levels of indentation which shows all elements and their structure
// in the tree. Visually the tree can be rotated clockwise to see its
// structure. See the related node_print_revorder() for additional
// detals.

void node_print_revorder(node_t *cur, int indent){
  if(cur == NULL){
    return;
  }
  node_print_revorder(cur->right, indent + 1);
  //https://stackoverflow.com/questions/42044341/inserting-n-tabs-in-printf-statement googled how to print multiple " "
  printf("%*s%s -> %s \n",indent * 2, "",cur->key, cur->val);
  node_print_revorder(cur->left, indent + 1);
}
// Recursive helper function which prints all key/val pairs in the
// tree rooted at node 'cur' in reverse order. Traverses right
// subtree, prints cur node's key/val, then traverses left tree.
// Parameter 'indent' indicates how far to indent (2 spaces per indent
// level).
//
// For example: a if the root node "El" is passed into the function
// and it has the following structure:
// 
//         ___El->strange_____     
//        |                   |   
// Dustin->corny       ___Mike->stoic
//                    |              
//               Lucas->brash     
// 
// the recursive calls will print the following output:
// 
//   Mike -> stoic                 # root->right
//     Lucas -> brash              # root->right->left
// El -> strange                   # root
//   Dustin -> corny               # root->left

void treemap_print_preorder(treemap_t *tree){
  node_t* root = tree->root;
  node_write_preorder(root, NULL, 0);
}

// Print all the data in the tree in pre-order with indentation
// corresponding to the depth of the tree. Makes use of
// node_write_preorder() for this.

void node_write_preorder(node_t *cur, FILE *out, int depth){
  if(cur == NULL){
    return;
  }
  //for printing in preorder
  if(out == NULL){
    printf("%*s%s %s\n",depth*2,"",cur->key, cur->val);
    node_write_preorder(cur->left, NULL, ++depth);
    node_write_preorder(cur->right, NULL, depth);
  }
  //for write in preorder
  else{
    fprintf(out, "%*s%s %s\n",depth *2,"",cur->key, cur->val);
    node_write_preorder(cur->left, out, ++depth);
    node_write_preorder(cur->right, out, depth);
  }

}

// Recursive helper function which writes/prints the tree in pre-order
// to the given open file handle. The parameter depth gives how far to
// indent node data, 2 spaces per unit depth. Depth increases by 1 on
// each recursive call. The function prints the cur node data,
// traverses the left tree, then traverses the right tree.

void treemap_save(treemap_t *tree, char *fname){
  FILE *file = fopen(fname, "w");
  if(file == NULL){
    printf("ERROR: could not open file '%s'\n", fname);
    return;
  }
  node_t* root = tree->root;
  node_write_preorder(root, file, 0);
  fclose(file);
}
// Saves the tree by opening the named file, writing the tree to it in
// pre-order with node_write_preorder(), then closing the file.

int treemap_load(treemap_t *tree, char *fname ){
  
  FILE *file = fopen(fname, "r");
  if(file == NULL){
    printf("ERROR: could not open file '%s'\n", fname);
    return 0;
  }

  treemap_clear(tree);
  while(1){
    //declare and initializing key and val, to avoid the stack smashing error, which is super annoying!
    char key[64] = {0};
    char val[64] = {0};
    if(fscanf(file, " %s %s", key, val) == EOF){
      break;
    }
    treemap_add(tree, key,val);
  }
  fclose(file);
  return 1;
}
// Clears the given tree then loads new elements to it from the
// named. Repeated calls to treemap_add() are used to add strings read
// from the file.  If the tree is stored in pre-order in the file, its
// exact structure will be restored.  Returns 1 if the tree is loaded
// successfully and 0 if opening the named file fails in which case no
// changes are made to the tree.
 