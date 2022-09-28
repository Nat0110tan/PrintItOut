// main function for a linked list manager, student version
//Yiling Tan tan00250
//OMG I don't even know I need to write the main at the very begining....
//but anyway, yo, I'm done.
#include <stdio.h>
#include <string.h>
#include "treemap.h"

int main(int argc, char *argv[]){
  int echo = 0;                                // controls echoing, 0: echo off, 1: echo on
  if(argc > 1 && strcmp("-echo",argv[1])==0) { // turn echoing on via -echo command line option
    echo=1;
  }

  printf("TreeMap Editor\n");
  printf("Commands:\n");
  printf("  quit:            exit the program\n");
  printf("  print:           shows contents of the tree in reverse sorted order\n");
  printf("  add <key> <val>: inserts the given key/val into the tree, duplicate keys are ignored\n");
  printf("  get <key>:       prints FOUND if the name is in the tree, NOT FOUND otherwise\n");  
  printf("  clear:           eliminates all key/vals from the tree\n");
  printf("  size:            prints the total number of nodes in the tree\n");
  printf("  preorder:        prints contents of the tree in pre-order which is how it will be saved\n");
  printf("  save <file>:     writes the contents of the tree in pre-order to the given file\n");
  printf("  load <file>:     clears the current tree and loads the one in the given file\n");

  
  char cmd[128];
  treemap_t treemap;
  int success;
  treemap_init(&treemap);

  while(1){
    printf("TM> ");                 // print prompt
    success = fscanf(stdin,"%s",cmd); // read a command
    if(success==EOF){                 // check for end of input
      printf("\n");                   // found end of input
      break;                          // break from loop
    }

//quit

    if(strcmp("quit", cmd)==0 ){     // check for exit command
      if(echo){
        printf("quit\n");
      }
      break;                          // break from loop
    }

//print
    else if( strcmp("print", cmd)==0 ){   // print command
      if(echo){
        printf("print\n");
      }
      treemap_print_revorder(&treemap);
    }

//add

    else if( strcmp("add", cmd)==0 ){ // insertion
    //declare the key and val
      char key[64];
      char val[64];
      fscanf(stdin,"%s", key);  
      fscanf(stdin, "%s", val);
       
      if(echo){
        printf("add %s %s\n", key, val);

      }

      treemap_add(&treemap, key, val); 
    }
    
//get

    else if( strcmp("get", cmd)==0 ){     // get command
      char key[64];
      fscanf(stdin,"%s",key);          // read a string
      if(echo){
        printf("get %s\n",key);
      }

      char *value = treemap_get(&treemap, key); // call get function
      if(value == NULL){                    // check for success
        printf("NOT FOUND\n");
      }
      else {
        printf("FOUND: %s\n",value);
      }
    }

//clear

    else if( strcmp("clear", cmd)==0 ){   // clear command
      if(echo){
        printf("clear\n");
      }
      treemap_clear(&treemap);
    }
//size
    else if( strcmp("size", cmd)==0 ){   // clear command
          if(echo){
            printf("size\n");
          }
          int size = treemap_size(&treemap);
          printf("%d nodes\n", size);
        }
  //preorder  

    else if(strcmp("preorder", cmd)==0){                                 
      if(echo){
        printf("preorder\n");
      }
      treemap_print_preorder(&treemap);
    }

//load

    else if(strcmp("load", cmd) == 0){    
      fscanf(stdin,"%s", cmd);        
              
      if(echo){
        printf("load %s\n", cmd);
      }
      int success = treemap_load(&treemap, cmd);
      if(!success){                      // check for success 
        printf("load failed\n");
      }
    } 
//save     
    else if(strcmp("save", cmd) == 0){                                 
      fscanf(stdin, "%s", cmd);
      if(echo){
        printf("save %s\n", cmd);
      }
      treemap_save(&treemap, cmd);
    }
  }
  treemap_clear(&treemap);
  return 0;
}

