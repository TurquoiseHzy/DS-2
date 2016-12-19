#ifndef GETKEY_H
#define GETKEY_H

void getKey(int elem, int& key){
	key = elem;
}

template<class ElemType, class KeyType>
void getKey(const ElemType &elem, KeyType& key,int){
	getKey(elem,key);
}

#endif