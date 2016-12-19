#ifndef AVL_H
#define AVL_H

#include<stdio.h>
#include<iostream>

#define Node AVLNode<ElemType,KeyType>
#define MAX(a,b) (a > b ? a : b)
#define LHEIGHT(a) (a->lchild ? a->lchild->subtreeHeight : 0)
#define RHEIGHT(a) (a->rchild ? a->rchild->subtreeHeight : 0)
template<class ElemType, class KeyType>
extern void getKey(const ElemType &elem, KeyType *key,int);

template<class ElemType, class KeyType>
class AVLNode{
public:
	int bFactor;
	KeyType key;
	ElemType *data;
	AVLNode *lchild,*rchild;
	AVLNode *father;
	unsigned int subtreeHeight; 

public:
	AVLNode(const ElemType& elem):
		bFactor(0),
		lchild(NULL),
		rchild(NULL),
		father(NULL),
		subtreeHeight(1)
	{
		data = new ElemType(elem);
		getKey<ElemType,KeyType>(elem,key,0);
	}
};


template<class ElemType, class KeyType>
class AVLTree{
public:
	Node *root;
	unsigned int size;

public:
	AVLTree():
		root(NULL),
		size(0)
	{
	}

public:
	void Insert(const ElemType &elem){
		Node *newNode = new Node(elem);
		if(!size){
			root = newNode;
		}
		else{
			Node *now = root ;
			while( true ){
				if( now->key > newNode->key ){
					if(now->lchild != NULL){
						now = now->lchild;
					}
					else{
						now->lchild = newNode;
						newNode->father = now;
						break;
					}
				}
				else{
					if(now->rchild != NULL){
						now = now->rchild;
					}
					else{
						now->rchild = newNode;
						newNode->father = now;
						break;
					}
				}
			}
			while(now != NULL){
				Adjust_height(now);
				if(now->bFactor > 1 || now->bFactor < -1){
					Adjust(now);
				}
				now = now -> father;
			}
		}
		size ++;
	}

	void Adjust_height(Node *adjustNode){
		adjustNode->subtreeHeight = MAX(LHEIGHT(adjustNode) , RHEIGHT(adjustNode)) + 1;
		adjustNode->bFactor = LHEIGHT(adjustNode) - RHEIGHT(adjustNode);
	}
	void Adjust_right(Node *adjustNode){
		Node* lchild = adjustNode->lchild;
		if(adjustNode->father != NULL){
			if(adjustNode->father->lchild == adjustNode){
				adjustNode->father->lchild = lchild;
			}
			else{
				adjustNode->father->rchild = lchild;
			}
		}
		else{
			root = lchild;
		}
		lchild->father = adjustNode->father;
		adjustNode->lchild = lchild->rchild;
		if(adjustNode->lchild != NULL){
			adjustNode->lchild->father = adjustNode;
		}
		lchild->rchild = adjustNode;
		adjustNode->father = lchild;
		Adjust_height(adjustNode);
		Adjust_height(lchild);
	}
	
	void Adjust_left(Node *adjustNode){
		Node* rchild = adjustNode->rchild;
		if(adjustNode->father != NULL){
			if(adjustNode->father->lchild == adjustNode){
				adjustNode->father->lchild = rchild;
			}
			else{
				adjustNode->father->rchild = rchild;
			}
		}
		else{
			root = rchild;
		}
		rchild->father = adjustNode->father;
		adjustNode->rchild = rchild->lchild;
		if(adjustNode->rchild != NULL){
			adjustNode->rchild->father = adjustNode;
		}
		rchild->lchild = adjustNode;
		adjustNode->father = rchild;
		Adjust_height(adjustNode);
		Adjust_height(rchild);
	}

	void Adjust(Node *adjustNode){
		if(adjustNode->bFactor == 2){
			if(adjustNode->lchild->bFactor == 1){
				Adjust_right(adjustNode);
			}
			else{
				Adjust_left(adjustNode->lchild);
				Adjust_right(adjustNode);
			}
		}
		else{
			if(adjustNode->rchild->bFactor == -1){
				Adjust_left(adjustNode);
			}
			else{
				Adjust_right(adjustNode->rchild);
				Adjust_left(adjustNode);
			}
		}
	}


	Node* Search(const ElemType &elem){
		KeyType key ;
		getKey<ElemType,KeyType>(elem,key,0);
		Node *now = root;
		while(now != NULL){
			if(key == now->key){
				return now;
			}
			else if(key < now->key){
				now = now->lchild;
			}
			else{
				now = now->rchild;
			}
		}
		return NULL;
	}

	void print(){
		print(root);
		std::cout << std::endl;
	}

	void print(Node* printNode){
		if(printNode == NULL){
			return ;
		}
		std::cout << *printNode->data;
		if(printNode->subtreeHeight > 1){
			std::cout << "(";
			print(printNode->lchild);
			std::cout << ",";
			print(printNode->rchild);
			std::cout << ")";
		}
	}
};


#endif