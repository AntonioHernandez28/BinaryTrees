 //
//  main.cpp
//  Arboles
//
//  Created by Antonio Hernández Ruiz on 10/8/19.
//  Copyright © 2019 Antonio Hernández Ruiz. All rights reserved.
//

#include <iostream>
#include <unordered_map>
#include <queue>
#include <stack>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* Left;
    TreeNode* Right;
};


TreeNode* root = NULL;
TreeNode* root2 = NULL;

//Creamos un nodo sin hijos sin conexiones ni nada
TreeNode* CrearNodo(int n) {
    TreeNode* nuevoNodo = new TreeNode();
    nuevoNodo -> val = n;
    nuevoNodo -> Left = NULL;
    nuevoNodo -> Right = NULL;
    
    return nuevoNodo;
}

void InsertarNodo(TreeNode* &root, int val) {
    // Si el arbol esta vacio
    if(root == NULL){
        TreeNode* nuevoNodo = CrearNodo(val);
        root = nuevoNodo;
    }
    else {
        int valorRaiz = root -> val;
        if(val < valorRaiz) InsertarNodo(root -> Left, val);
        else InsertarNodo(root -> Right, val);
    }
}


void MostrarArbol(TreeNode* root, int iContador) {
    if(root == NULL) return;
    else {
        MostrarArbol(root->Right, iContador + 1);
        for(int i = 0; i < iContador; i ++) cout << "  ";
        cout << root -> val << endl;
        MostrarArbol(root->Left, iContador + 1);
    }
}

bool BuscarNodo(TreeNode* root, int val) {
    if(root == NULL) return false;
    if(root -> val == val) return true;
    else if(root -> val < val) return BuscarNodo(root->Right, val);
    else return BuscarNodo(root->Left, val);
}


void PreOrden(TreeNode* root) {
    if(root == NULL) return;
    cout << root->val << " ";
    PreOrden(root->Left);
    PreOrden(root->Right);
}

void InOrden(TreeNode* root) {
    if(root == NULL) return;
    InOrden(root->Left);
    cout << root->val << " ";
    InOrden(root->Right);
}

void PostOrden(TreeNode* root) {
    if(root == NULL) return;
    PostOrden(root -> Left);
    PostOrden(root -> Right);
    cout << root -> val << " ";
}

void PreOrdenParaWidth(TreeNode* root, int Level, unordered_map<int, int> &map){
    if(root == NULL) return;
    map[Level] += 1;
    PreOrdenParaWidth(root->Left, Level + 1, map);
    PreOrdenParaWidth(root->Right, Level + 1, map);
}

int maxWidht(TreeNode* root) {
    if(root == NULL) return 0;
    unordered_map<int, int> map;
    PreOrdenParaWidth(root, 1, map);
    int res = 0;
    for(auto x: map)
        res = max(res, x.second);
    return res;
}

int LCA(TreeNode* root, int a, int b) {
    if(a == b) return a;
    if(a < root->val && b < root->val) return LCA(root->Left, a, b);
    else if(a > root->val && b > root->val) return LCA(root->Right, a, b);
    else return root->val;
}

bool SonIguales(TreeNode* root1, TreeNode* root2) {
    if(root1 == NULL && root2 == NULL) return true;
    if(root1 == NULL || root2 == NULL) return false;
    if(root1 -> val == root2 -> val && SonIguales(root1->Left, root2->Left) && SonIguales(root1->Right, root2->Right))
        return true;
    else return false;
}

stack<int> myStack;
void InOrderToQueue(TreeNode* root) {
    if(root == NULL) return;
    InOrderToQueue(root->Left);
    myStack.push(root->val);
    InOrderToQueue(root->Right);
}

queue<int> toQueue(TreeNode* root) {
    queue<int> result;
    InOrderToQueue(root);
    while(!myStack.empty()){
        result.push(myStack.top());
        myStack.pop();
    }
    
    return result;
}

void ancestros(TreeNode* root, int val, vector<int> &vec) {
    if(root->val == val) return;
    else vec.push_back(root->val);
    if(root->val < val) ancestros(root->Right, val, vec);
    else ancestros(root->Left, val, vec);
}
vector<int> ancestrosDeNodo(int val){
    vector<int> Result;
    ancestros(root, val, Result);
    return Result;
}

int Height(TreeNode* root){
    if(!root) return 0;
    return max(Height(root->Right), Height(root->Left)) + 1;
}


int NivelNodo(TreeNode* root, int val) {
    int Level = 0;
    while(root){
        if(root -> val == val) return Level;
        else Level ++;
        root -> val < val ? root = root -> Right : root = root -> Left;
    }
    return -1;
}

void PostOrder(TreeNode* root, vector<int> &r){
    if(!root) return;
    PostOrder(root->Left, r);
    PostOrder(root->Right, r);
    if(root->Left)
        if(!root->Left->Left && !root->Left->Right) {
            r.push_back(root->val);
            return;
        }
    if(root->Right)
        if(!root->Right->Left && !root->Right->Right) {
            r.push_back(root->val);
            return;
        }
    
}
vector<int> ParentOfLeafs(TreeNode* root){
    vector<int> result;
    PostOrder(root, result);
    return result;
}

int main() {
    
    // Menu();
    for(int i = 0; i < 9; i++){
        int temp;
        cin>>temp;
        InsertarNodo(root, temp);
    }
    
    vector<int> r = ParentOfLeafs(root);
    for(auto x:r) cout << x << " ";
    
    cout << endl;
    
    return 0;
}

/*
8
3
1
6
4
7
10
14
13
*/

 /*
  void Menu() {
  int dato, opcion;
  do {
  cout << endl;
  cout << "Menu" << endl;
  cout << "1. Insertar un nuevo Nodo" << endl;
  cout << "2. Mostrar Arbol" << endl;
  cout << "3. Buscar Nodo" << endl;
  cout << "4. Recorrido PreOrden" << endl;
  cout << "5. Recorrido InOrden" << endl;
  cout << "6. Recorrido PostOrden" << endl;
  cout << "7. Salir" << endl;
  cout << "Opcion" << endl;
  cin >> opcion;
  
  switch(opcion){
  case 1:
  cout << "De numero" << endl;
  cin >> dato;
  InsertarNodo(root, dato);
  cout << endl;
  break;
  
  case 2:
  MostrarArbol(root, 0);
  break;
  
  case 3:{
  int val;
  cout << "De valor a buscar" << endl;
  cin >> val;
  bool flag = BuscarNodo(root, val);
  if(flag) cout << "TRUE" << endl;
  else{ cout << "FALSE" << endl;}
  break;
  }
  
  case 4:
  PreOrden(root);
  break;
  
  case 5:
  InOrden(root);
  break;
  
  case 6:
  PostOrden(root);
  break;
  }
  }while(opcion != 7);
  }
  
  */


