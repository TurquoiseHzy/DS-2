#ifndef DLINKLIST_H
#define DLINKLIST_H

class DLinkListNode{
public:
	int TermID;
	int DocID;
	int Times;
	DLinkListNode *next,*pre;
public:
	DLinkListNode(int TID,int DID,int T):
		TermID(TID),
		DocID(DID),
		Times(T),
		next(NULL),
		pre(NULL)
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
				now -> next -> pre = newNode;
				newNode -> next = now -> next;
				newNode -> pre =now;
				now -> next = newNode;
			}
			else{
				newNode->pre = tail;
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
		DLinkListNode *editNode = Search(DocID);
		if(editNode -> pre != NULL){
			editNode -> pre -> next = editNode -> next;
		}
		if(editNode -> next != NULL){
			editNode -> next -> pre = editNode -> pre;
		}
		Add(editNode->TermID,DocID,Times);
	}
};
#endif