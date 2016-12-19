#include"avl.h"
#include"getkey.h"
#include"dlinklist.h"
int main(){
	AVLTree<int,int> a;
	a.Insert(5);
	a.print();
	a.Insert(4);
	a.print();
	a.Insert(2);
	a.print();
	a.Insert(8);
	a.print();
	a.Insert(6);
	a.print();
	a.Insert(9);
	a.print();
	return 0;
}