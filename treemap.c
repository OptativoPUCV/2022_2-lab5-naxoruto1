#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)){
  TreeMap * arbol = (TreeMap*)malloc(sizeof(TreeMap));
  if(arbol == NULL){
    exit(-1);
  }
  arbol->current = NULL;
  arbol->root = NULL;
  arbol->lower_than = lower_than;
  return arbol;
}


void insertTreeMap(TreeMap * tree, void* key, void * value) {

}

TreeNode * minimum(TreeNode * x){
  while (x->left != NULL) {
    x = x->left;
  }
  return x;
}


void removeNode(TreeMap * tree, TreeNode* node) {
  TreeNode * parentNode = node->parent;
  
  if (node->right == NULL && node->left == NULL) {
    if (tree->lower_than(parentNode->pair->key, node->pair->key) == 1) {
      parentNode->right = NULL; 
    }else if (tree->lower_than(node->pair->key, parentNode->pair->key) == 1) {
      parentNode->left = NULL; 
    }
    
  }
    
  else {
    TreeNode *min = minimum(node->right);
    node->pair->key = min->pair->key;
    node->pair->value = min->pair->value;
    removeNode(tree, min);
  }
}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);
}




Pair * searchTreeMap(TreeMap * tree, void* key){
  
  if(tree == NULL){ // si es nulo
    return NULL;
  }
  
  TreeNode * Aux = tree->root;
  
  while(Aux != NULL){
    tree->current = Aux;
    
    if(is_equal(tree,tree->current->pair->key,key)){
      return tree->current->pair;
    }
    if(tree->lower_than(Aux->pair->key, key)){
      Aux = Aux->right;
    }
    else{
      Aux = Aux->left;
    }
  }
  
  return NULL;
}


Pair * upperBound(TreeMap * tree, void* key) {
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
    return NULL;
}

Pair * nextTreeMap(TreeMap * tree) {
    return NULL;
}
