#include <stdio.h>
#include <stdlib.h>

struct node{
	int val; // 5 digits / MOD 100000
	struct node *next;
};

typedef struct node NODE;

void print_val(NODE *head){
	NODE *temp;
	temp = head->next;

	//head has no value
	while(temp != NULL){
		printf("%d", temp->val);
		temp = temp->next;
	}

	printf("\n");
}

int main(){
	NODE *head;
	NODE *newnode;

	/*
	STRUCT
	head
		v next
		most significant bit
			v next
			......
				v next
				least significant bit
					v next
					NULL
	*/
	head = (NODE*)(malloc(sizeof(NODE)));

	/*
		SAMPLE
		repunit 19-digit 1's
	*/
	newnode = (NODE*)(malloc(sizeof(NODE)));
	newnode->val = 1111;
	head->next = newnode;

	newnode = (NODE*)(malloc(sizeof(NODE)));
	newnode->val = 11111;
	head->next->next = newnode;

	newnode = (NODE*)(malloc(sizeof(NODE)));
	newnode->val = 11111;
	head->next->next->next = newnode;

	newnode = (NODE*)(malloc(sizeof(NODE)));
	newnode->val = 11111;
	newnode->next = NULL;
	head->next->next->next->next = newnode;

	print_val(head);
}
