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
  TreeNode *Nodo = createTreeNode(key, value);
  TreeNode *Aux;
  
  searchTreeMap(tree, key);
  
  Aux = tree->current;
  Nodo->parent = Aux;
  
  if (tree->lower_than(Aux->pair->key, key) == 1) {
    Aux->right = Nodo;
  }else if (tree->lower_than(key, Aux->pair->key) == 1) {
    Aux->left = Nodo;
  }
  tree->current = Nodo;
}

TreeNode * minimum(TreeNode * x){
  if (x == NULL) return NULL;
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
    
  }else if ((node->left != NULL && node->right == NULL) || (node->left == NULL && node->right != NULL)) {
    if (node->left == NULL) {
      if (tree->lower_than(parentNode->pair->key, node->pair->key) == 1) {
        parentNode->right = node->right; 
      }else if (tree->lower_than(node->pair->key, parentNode->pair->key) == 1) {
        parentNode->left = node->right; 
      }
    node->right->parent = parentNode; 
    }
    
    if(node->right == NULL) {
      if (tree->lower_than(parentNode->pair->key, node->pair->key) == 1) {
        parentNode->right = node->left; 
      }else if (tree->lower_than(node->pair->key, parentNode->pair->key) == 1) {
        parentNode->left = node->left;
      }
    node->left->parent = parentNode;
    }
    free(node);
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
  TreeNode * nodo;
  tree -> current = tree -> root;
  nodo = NULL;
  
  while (tree -> current != NULL){
    if (tree-> lower_than(key,tree->current->pair->key) == 1 ){
      nodo = tree->current;
      if(tree -> current -> left == NULL){
        break;
      }tree -> current = tree -> current -> left;
    }else if (is_equal(tree, key,tree->current->pair->key) == 1){
      nodo = tree->current;
      break;
    }else{
    if(tree->current->right == NULL){
        break;
      }tree->current = tree->current->right;
    }
  }
  if (nodo == NULL){
    return NULL; 
  }
  return nodo -> pair;
}


Pair * firstTreeMap(TreeMap * tree) {
    TreeNode* nodo = (TreeNode*)calloc(1,sizeof(TreeNode));
    nodo = tree->root;
    if(tree == NULL || tree->root == NULL){
      return NULL;
    }
    while(nodo->left != NULL){
      nodo = nodo->left;
    }
    return nodo->pair;
}

Pair * nextTreeMap(TreeMap * tree) {
    TreeNode * aux = tree -> current;
    if(tree -> current == NULL){
         return NULL;
      
    }
    if (aux -> right == NULL){
    while (aux -> parent != NULL){
      if (aux == NULL) {
        return NULL; 
      }else if (tree->lower_than(aux -> parent -> pair -> key,tree -> current -> pair -> key) == 1){
        aux = aux -> parent;
      }else if (tree -> lower_than(tree -> current -> pair -> key, aux -> parent -> pair -> key) == 1){
        aux = aux -> parent;
        tree -> current = aux;
        return aux -> pair;
      }else return aux->pair;
    }
    }else {
      tree -> current = minimum(tree -> current -> right);
      return tree -> current -> pair;
    }   
    return NULL;
}
