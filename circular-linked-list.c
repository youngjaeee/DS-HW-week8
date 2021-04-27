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

	if (h->rlink == h && h->llink == h) // h->first = NULL인 경우, 즉 리스트에 노드가 존재하지 않을 경우
	{
		printf("입력된 node가 없습니다.\n"); // 메시지 출력 및 복귀
		return 0;
	}

	listNode* temp = h->rlink; // 노드 포인터 temp를 선언후 헤더 노드가 가리키는 첫 번째 노드 주소 대입
	h->rlink = h->rlink->rlink; // 헤더 노드가 두 번째 노드(첫 번째 노드의 rlink를 통해)를 가리키게 하여 첫 번째 노드의 연결고리 끊음
	h->rlink->llink = h; // 새롭게 첫 번째로 된 노드의 llink를 헤드 포인터를 가리키게 함
	free(temp); // 기존 첫 번째 노드의 주소를 가지고 있는 temp에 대한 할당을 해제하여 첫 번째 노드를 삭제


	return 0;

	return 1;

}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(listNode* h) {

	listNode* lead = h->rlink;  // 역순 재배치를 위한 노드 포인터 lead 선언, 첫 번째 노드 가리키게 함
	listNode* temp = NULL; // lead의 우측 노드를 가리키는 포인터 temp 선언
	lead->llink = h;

	while (lead != h) // lead가 모든 노드에 대해 한 번씩 탐색을 완료할 때까지
	{
		temp = lead->rlink; // temp가 기존 lead 노드의 우측 노드를 가리키게 함
		lead->rlink = lead->llink; // lead의 rlink를 lead의 llink로 대입하여 순서 바꿈
		lead->llink = temp; // lead의 llink를 기존 우측 노드인 temp를 가리키게 하여 순서 바꿈
		if (temp == h) // 마지막 노드까지 탐색을 완료하였을 때
		{
			h->rlink = lead; // 순서를 모두 바꾼 후 h->rlink가 lead를 가리키게 하여 첫 번째 노드로 함
			lead -> llink = h; // lead 노드(순서 변경 후의 첫번째 노드)의 llink가 h를 가리키게 함
		}
		lead = temp; // lead에 기존 우측 노드 포인터인 temp 대입하여 다음 노드 탐색 실행

	}
	return 0;

	return 0;
}



/**
 *  리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 
 **/
int insertNode(listNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); // 추가할 노드에 대한 공간을 할당에 node에 저장
	node->key = key; // node의 key를 사용자가 입력한 값으로 설정


	listNode* temp = h->rlink; // 값을 비교하기 위한 노드 포인터 temp, prevtemp 선언
	listNode* prevtemp = NULL; // 각각 h->rlink, NULL로 초기화

	if (temp == h) // temp가 h일때, 즉 리스트에 노드가 존재하지 않는 경우
	{
		printf("연결리스트 상 첫 번째로 입력하는 key로 비교대상 node가 없습니다.\n");
		node->rlink = h; // 첫 번째이자 유일한 노드로 추가하므로 node->rlink를 h로 설정
		h->rlink = node; // h->rlink가 새로 추가한 node를 가리키게 함
		h->llink = node; // h->llink가 새로 추가한 node를 가리키게 함
		node->llink = h; // 새롭게 첫 번째로 된 노드의 llink를 h를 가리키게 함

		return 0;
	}
	else if (temp != h) // temp가 NULL이 아닐 때, 즉 노드가 1개 이상 존재하는 경우
	{
		for (temp = h->rlink; ; ) // temp가 리스트의 모든 노드를 한 번씩 가리킬 때까지 반복
		{
			if (key < (temp->key)) // 사용자가 추가하고자 하는 노드 key값 보다 큰 key를 가진 기존 노드를 발견한 경우
			{
				if (prevtemp == NULL) // prevtemp == NULL, 즉 첫 번째 노드가 되는 경우
				{
					h->rlink = node; // 새로 추가하는 node를 기존 노드보다 앞선 위치에 추가해야 하므로
					node->rlink = temp; // 헤드 포인터가 node를 가리키게 하고 node->rlink가 기존 노드를 가리키게 함
					node->llink = h; // 새로 추가한 노드의 llink가 헤드 포인터를 가리키게 함
					temp->llink = node; // 기존 노드의 llink가 새로 추가된 노드 가리키게 함
					return 0;
				}
				else
				{ // 기존 노드가 2개 이상 있는 경우 (두 번째 이후의 노드가 되는 경우)

					node->rlink = temp;  // 새로 추가하는 node->rlink를 값이 큰 뒤쪽 노드를 가리키게 하고
					node->llink = temp->llink; // 새로 추가하는 node의 llink가 좌측 노드를 가리키게 하고
					temp->llink->rlink = node; // 새로 추가하는 node의 좌측 노드의 rlink가 node를 가리키게 하며
					temp->llink = node; // 새로 추가하는 node보다 값이 큰 우측 노드의 llink가 node를 가리키게 한다.

					return 0;
				}
			}

			if ((temp->rlink) == h)
			{
				break; // temp->rlink가 hL일 때, 즉 모든 노드에 대한 값 탐색을 완료한 경우 for문 탈출
			}

			prevtemp = temp; // 하나의 노드에 대한 탐색을 완료한 경우
			temp = temp->rlink; // prevtemp, temp가 가리키는 노드 + 1

		}


		if ((temp->rlink) == h) // 모든 노드에 대한 탐색을 마쳤을 때 입력한 key보다 큰값 가지는 node 없는 경우
		{
			//			printf("입력한 key보다 큰값을 가지는 노드가 없어 마지막 노드로 추가합니다.\n");
			temp->rlink = node; // temp가 가리키는 리스트의 마지막 노드의 rlink를 새로 추가하는 node로 설정
			node->llink = temp; // 새로 추가하는 마지막 node의 llink를 좌측 노드인 temp로 설정
			node->rlink = h; // node가 리스트의 새로운 마지막 노드이므로 node->rlink를 h로 설정
			h->llink = node; // node가 리스트의 새로운 마지막 노드이므로 h->llink를 node로 설정
		}
		return 0;
	}


	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(listNode* h, int key) {

	if (h->rlink == h && h->llink == h) // h->first = NULL인 경우, 즉 리스트에 노드가 존재하지 않을 경우
	{
		printf("입력된 노드가 없습니다.\n"); // 메시지 출력 및 복귀
		return 0;
	}

	listNode* temp = h->rlink; // 값을 비교하기 위한 노드 포인터 temp 선언

	for (temp = h->rlink; ; temp = temp->rlink) // for문을 통해 리스트의 모든 노드를 탐색하여
	{
		if (h->rlink != h && temp->rlink == h) // 탐색 완료 후에도 값이 일치하는 노드가 없을 경우
		{
			printf("입력한 key와 같은 값을 가지는 노드가 없어 삭제하지 않습니다.\n"); // 메시지 출력 및 복귀
			break;
		}

		if (key == (temp->key)) // 입력한 key와 같은 값을 가지는 노드를 찾은 경우
		{
			if (h->rlink->rlink == h) // 리스트의 노드가 1개인 경우
			{
				h->rlink = h; // 리스트의 노드를 모두 없애므로 h->rlink, h->llink = NULL
				h->llink = h;
				free(temp); // 값이 같은 리스트의 노드에 대한 공간 할당 해제
				return 0;
			}
			// 리스트의 노드가 2개 이상일 경우
			temp->llink->rlink = temp->rlink; // temp 노드 좌측 노드의 rlink를 temp 노드 우측 노드를 가리키게 함
			temp->rlink->llink = temp->llink; // temp 노드 우측 노드의 llink를 temp 노드 좌측 노드를 가리키게 함
			free(temp); // 지울 노드(temp)에 대한 공간 할당 해제
			break; // for문 빠져나옴
		}
	}


	return 0;
}


