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

//true if a>=b
int compare(NODE *a, NODE *b){
	NODE *tempa;
	NODE *tempb;
	int result = 0;

	tempa = a;
	tempb = b;

	while(tempa != NULL && tempb != NULL){
		if(tempa->val >= tempb->val){
			result = 1;
		}
		else{
			result = 0;
		}
		tempa = tempa->next;
		tempb = tempb->next;
	}

	if(tempa==NULL && tempb==NULL){
		return result;
	}
	//a>=b
	else if(tempa==NULL){
		return 0; 
	}
	//a<b
	else{
		return 1;
	}
}

int main(){
	NODE *head;
	NODE *newnode;
	NODE *a;
	NODE *b;

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


	//TEST COMPARISON
	/*
	a = (NODE*)(malloc(sizeof(NODE)));
	b = (NODE*)(malloc(sizeof(NODE)));

	newnode = (NODE*)(malloc(sizeof(NODE)));
	newnode->val = 111;
	a->next = newnode;

	newnode = (NODE*)(malloc(sizeof(NODE)));
	newnode->val = 11111;
	newnode->next = NULL;
	a->next->next = newnode;

	newnode = (NODE*)(malloc(sizeof(NODE)));
	newnode->val = 111;
	b->next = newnode;

	printf("a value: ");
	print_val(a);
	printf("b value: ");
	print_val(b);

	printf("compare: %d\n", compare(b,a));
	*/
}
