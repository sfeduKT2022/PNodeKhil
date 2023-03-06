#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

struct Node {
	char word[80];
	int count;
	Node* next;
};

typedef Node* PNode;
PNode Head = NULL;

PNode CreateNode(char NewWord[]) {
	PNode NewNode = new Node;
	strcpy(NewNode->word, NewWord);
	NewNode->count = 1;
	NewNode->next = NULL;
	return NewNode;
}

void AddFirst(PNode& Head, PNode NewNode) {
	NewNode->next = Head;
	Head = NewNode;
}

void AddAfter(PNode p, PNode NewNode) {
	NewNode->next = p->next;
	p->next = NewNode; 
}

void AddLast(PNode &Head, PNode NewNode) {
	PNode q = Head;
	if (Head == NULL)
	{
		AddFirst(Head, NewNode);
		return;
	}
	while (q->next)
		q = q->next;
	AddAfter(q, NewNode);
}

void AddBefore(PNode& Head, PNode p, PNode NewNode) {
	PNode q = Head;
	if (Head == p)
	{
		AddFirst(Head, NewNode);
		return;
	}
	while (q && q->next != p)
		q = q->next;
	if (q)
		AddAfter(q, NewNode);
}

void AddBeforeTwo(PNode p, PNode NewNode)
{
	Node temp;
	temp = *p;
	*p = *NewNode;
	*NewNode = temp;
	p->next = NewNode;
}

PNode Find(PNode Head, char NewWord[])
{
	PNode q = Head;
	while (q && strcmp(q->word, NewWord))
		q = q->next;
	return q;
}

PNode FindPlace(PNode Head, char NewWord[])
{
	PNode q = Head;
	while (q && strcmp(NewWord, q->word) > 0)
		q = q->next;
	return q;
}

void DeleteNode(PNode& Head, PNode p)
{
	PNode q = Head;
	if (Head == p)
		Head = p->next;
	else {
		while (q && q->next != p)
			q = q->next;
		if (q == NULL) return;
		q->next = p->next;
	}
	delete p;
}

int main()
{
	FILE* in = fopen("input.txt", "r");
	FILE* out = fopen("output.txt", "w");
	char word[80];
	PNode q;
	int n = fscanf(in, "%s", word);
	while (n == 1) {
		q = Find(Head, word);
		if (q != NULL) q->count++;
		else AddBefore(Head, FindPlace(Head, word), CreateNode(word));
		n = fscanf(in, "%s", word);
	}
	q = Head;
	while (q != NULL) {
		fprintf(out, "%s %d\n", q->word, q->count);
		q = q->next;
	}
	return 0;
}
