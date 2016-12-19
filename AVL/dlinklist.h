#ifndef DLINKLIST_H
#define DLINKLIST_H

class DLinkListNode{
public:
	int TermID;
	int DocID;
	int Times;
	DLinkListNode *next;
public:
	DLinkListNode(int TID,int DID,int T):
		TermID(TID),
		DocID(DID),
		Times(T),
		next(NULL)
	{
	}
};

class DLinkList{
public:
	DLinkListNode *head,*tail;
	unsigned int size;

public:
	DLinkList():
		head(NULL),
		tail(NULL),
		size(0)
	{
	}

public:
	void Add(int TermID,int DocID,int Times){
		DLinkListNode *newNode = new DLinkListNode(TermID,DocID,Times);
		if(size == 0){
			head = newNode;
			tail = newNode;
		}
		else{
			DLinkListNode *now = head;
			while(now->next != NULL && now->next->Times > Times){
				now = now -> next;
			}
			if(now->next != NULL){
				newNode -> next = now -> next;
				now -> next = newNode;
			}
			else{
				tail->next = newNode;
				tail = newNode;
			}
		}
		size ++;
	}

	DLinkListNode* Search(int DocID){
		DLinkListNode *searchNode = head;
		while(searchNode != NULL)
		{
			if(searchNode->DocID == DocID){
				return searchNode;
			}
			searchNode = searchNode -> next;
		}
		return NULL;
	}

	void Edit(int DocID,int Times){
		
	}
};
#endif