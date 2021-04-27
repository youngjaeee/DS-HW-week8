/*
 *  doubly circular linked list
 *
 *  Data Structures
 *
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

/* 함수 리스트 */
int initialize(listNode** h);
int freeList(listNode* h);
int insertLast(listNode* h, int key);
int deleteLast(listNode* h);
int insertFirst(listNode* h, int key);
int deleteFirst(listNode* h);
int invertList(listNode* h);

int insertNode(listNode* h, int key);
int deleteNode(listNode* h, int key);

void printList(listNode* h);



int main()
{
	char command;
	int key;
	listNode* headnode=NULL;

	do{
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}


int initialize(listNode** h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(*h != NULL)
		freeList(*h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}

/* 메모리 해제 */
int freeList(listNode* h){

	listNode* p = h; // 노드 포인터 p를 선언해 h->first 대입
	listNode* temp; // free()함수를 실행하기 위한 임시 포인터 선언
	while (p != NULL) { // 모든 노드에 대한 공간 할당 해제를 완료할 때까지
		temp = p; // temp를 p로 설정
		p = p->rlink; // p를 p->rlink로 설정
		free(temp); // prev가 가리키는 노드 공간에 대한 할당 해제
	}
	free(h); // headNode 뒷부분의 노드 할당 해제 완료 후 headNode도 할당 해제

	return 0;
}



void printList(listNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink;

	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}
	printf("  items = %d\n", i);


	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

	i = 0;
	p = h->rlink;
	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink;
		i++;
	}

}



/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(listNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); // 추가할 노드의 정보를 저장할 node 선언 및 공간 할당
	node->key = key; // node의 key를 사용자가 입력한 key 값으로 설정

	if (h->rlink == h && h->llink == h) // 리스트에 노드가 없는 경우
	{
		node->rlink = h; // 첫 번째이자 유일한 노드로 추가하므로 node->rlink를 h로 설정
		node->llink = h; // 첫 번째이자 유일한 노드로 추가하므로 node->llink를 h로 설정
		h->rlink = node; // h의 rlink가 새로 추가한 node를 가리키게 함
		h->llink = node; // h의 llink가 새로 추가한 node를 가리키게 함
		return 0;
	}
	// 기존 리스트에 노드가 있는 경우
	listNode* listPoint; // 마지막 노드를 가리키는 포인터인 listPoint 선언
	for (listPoint = h; (listPoint->rlink) != h; )
		listPoint = listPoint->rlink; // for문을 통해 listPoint가 리스트의 마지막 노드를 가리킴


	listPoint->rlink = node; // listPoint가 가리키는 리스트의 마지막 노드의 rlink를 새로 추가하는 node로 설정
	node->llink = listPoint; // 새로 추가하는 마지막 node의 llink를 좌측 노드 포인터인 listPoint로 설정
	node->rlink = h; // node가 리스트의 새로운 마지막 노드이므로 node->rlink를 h로 설정
	h->llink = node; // node가 마지막 노드이므로 h->llink를 노드로 설정

	return 1;
}


/**
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode* h) {

	if (h->rlink == h && h->llink == h) // h->first = NULL, 즉 입력된 노드가 없는 경우
	{
		printf("입력된 노드가 없습니다.\n"); // 메시지 출력 및 복귀
		return 0;
	}
	else if (h->rlink != NULL && h->rlink->rlink == h) // 리스트에 노드가 1개 있는 경우
	{
		listNode* temp = h->rlink; // 노드 포인터 temp를 선언하여 헤드 포인터 값 대입
		h->rlink = h; // 모든 노드를 삭제하므로 h->rlink, llink = h
		h->llink = h;
		free(temp); // temp, 즉 첫 번째 노드에 대한 공간 할당을 해제하여 노드 삭제함
		return 0;
	}

	// 노드가 2개 이상 있는 경우
	listNode* temp; // 마지막 노드 탐색을 위한 노드 포인터 temp 선언
	for (temp = h; ; temp = temp->rlink)
	{
		if (temp->rlink == h) // for문 반복을 통해 temp가 리스트의 마지막 노드를 가리킬 경우
		{
			h->llink = temp->llink; // temp의 좌측 노드가 새로운 마지막 노드가 되므로 h의 llink = temp->llink
			temp->llink->rlink = h; // temp의 좌측 노드가 새로운 마지막 노드가 되므로 좌측 노드의 rlink = h
			free(temp); // 마지막 노드 삭제를 위한 free() 함수 실행
			break;
		}
	}

	return 1;
}


/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(listNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); // 추가할 노드에 대한 공간을 할당에 node에 저장
	node->key = key; // node의 key를 사용자가 입력한 값으로 설정


	if (h->rlink == h && h->llink == h) // 리스트에 노드가 존재하지 않을 경우
	{
		h->rlink = node; // h->rlink, llink를 node로 설정하고
		node->rlink = h; // node가 리스트의 첫번째 노드이므로 node->rlink = h
		node->llink = h; // node가 리스트의 첫번째 노드이므로 node->rlink = h
		h->llink = node;
		return 0;
	}
	// 기존 리스트에 노드가 존재하는 경우
	h->rlink->llink = node; // 기존 첫 번째 노드의 llink를 새로 추가하는 node를 가리키게 하고
	node->rlink = h->rlink; // 새로 추가하는 node의 node->rlink가 기존 첫 번째 노드를 가리키게 하고
	h->rlink = node; // h가 가리키는 위치를 추가한 node로 새로 지정
	node->llink = h; // node의 llink가 h를 가리키게 함


	return 1;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode* h) {


	return 1;

}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(listNode* h) {


	return 0;
}



/**
 *  리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 
 **/
int insertNode(listNode* h, int key) {

	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(listNode* h, int key) {

	return 0;
}


