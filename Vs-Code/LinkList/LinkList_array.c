#include <stdio.h>
#include <stdlib.h>

struct Node {
    int mark;
    int roll;
    struct Node* next;
};

struct Node* new_node(int roll, int mark) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    if (node != NULL) {
        node->roll = roll;
        node->mark = mark;
        node->next = NULL;
    }
    return node;
}

void Linklisttravarsal(struct Node* head) {
    struct Node* p = head;
    while (p != NULL) {
        printf("%d %d\n", p->roll, p->mark);
        p = p->next;
    }
}

struct Node* Linklist_insert(struct Node* head, int data, int roll, int index) {
    struct Node* ptr = new_node(roll, data);
    if (ptr == NULL) {
        printf("Memory allocation failed.\n");
        return head;
    }

    if (index == 0) {
        ptr->next = head;
        return ptr;
    }

    struct Node* p = head;
    for (int i = 0; i < index - 1 && p != NULL; i++) {
        p = p->next;
    }

    if (p != NULL) {
        ptr->next = p->next;
        p->next = ptr;
    }

    return head;
}

struct Node* Linklist_delete(struct Node* head, int mark) {
    struct Node* p = head;
    struct Node* q = head->next;
    if (head->mark == mark) {
        free(head);
        return q;
    }

    while (q != NULL && q->mark != mark) {
        p = p->next;
        q = q->next;
    }

    if (q != NULL) {
        p->next = q->next;
        free(q);
    }
    return head;
}

void bubbleSort(struct Node* head) {
    int swapped;
    struct Node* p;
    struct Node* lptr = NULL;

    if (head == NULL)
        return;

    do {
        swapped = 0;
        p = head;

        while (p->next != lptr) {
            if (p->mark < p->next->mark) {
                int temp = p->mark;
                p->mark = p->next->mark;
                p->next->mark = temp;

                // Swap roll numbers as well
                temp = p->roll;
                p->roll = p->next->roll;
                p->next->roll = temp;

                swapped = 1;
            }
            p = p->next;
        }
        lptr = p;
    } while (swapped);
}


struct Node* search(struct Node* head, int roll) {
    struct Node* p = head;
    while (p != NULL) {
        if (p->roll == roll) {
            return p;
        }
        p = p->next;
    }
    return NULL;
}

struct Node* update(struct Node* head, int roll, int mark) {
    struct Node* p = search(head, roll);
    if (p != NULL) {
        p->mark = mark;
    }
    return head;
}

struct Node* reverse(struct Node* head) {
    struct Node* current = head;
    struct Node* prev = NULL, * next = NULL;

    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    head = prev;

    return head;
}

struct Node* getNodeAt(struct Node* head, int index) {
    struct Node* p = head;
    int i = 0;
    while (p != NULL && i < index) {
        p = p->next;
        i++;
    }
    return p;
}

int getCount(struct Node* head) {
    struct Node* p = head;
    int count = 0;
    while (p != NULL) {
        count++;
        p = p->next;
    }
    return count;
}

struct Node* removeLastNode(struct Node* head) {
    if (head == NULL || head->next == NULL) {
        free(head);
        return NULL;
    }

    struct Node* p = head;
    while (p->next->next != NULL) {
        p = p->next;
    }
    free(p->next);
    p->next = NULL;

    return head;
}

struct Node* insertAtEnd(struct Node* head, int roll, int mark) {
    struct Node* node = new_node(roll, mark);
    if (head == NULL) {
        return node;
    }

    struct Node* p = head;
    while (p->next != NULL) {
        p = p->next;
    }
    p->next = node;

    return head;
}

void bubbleSortRoll(struct Node* head) {
    int swapped;
    struct Node* p;
    struct Node* lptr = NULL;

    if (head == NULL)
        return;

    do {
        swapped = 0;
        p = head;

        while (p->next != lptr) {
            if (p->roll > p->next->roll) {
                int temp = p->roll;
                p->roll = p->next->roll;
                p->next->roll = temp;
                swapped = 1;
            }
            p = p->next;
        }
        lptr = p;
    } while (swapped);
}

void updateRolls(struct Node* head) {
    bubbleSort(head);  // make sure the list is sorted by marks

    struct Node* p = head;
    int roll = 1;
    while (p != NULL) {
        p->roll = roll++;
        p = p->next;
    }
}

void freeList(struct Node* head) {
    struct Node* p = head;
    while (p != NULL) {
        struct Node* temp = p;
        p = p->next;
        free(temp);
    }
}

int main() {

    int num_nodes, roll, mark;
    printf("Enter the number of students: ");
    scanf("%d", &num_nodes);

    printf("Enter roll number and mark for student 1: ");
    scanf("%d%d", &roll, &mark);
    struct Node* head = new_node(roll, mark);

    struct Node* current = head;
    for (int i = 1; i < num_nodes; i++) {
        printf("Enter roll number and mark for student %d: ", i + 1);
        scanf("%d%d", &roll, &mark);
        current->next = new_node(roll, mark);
        current = current->next;
    }

    bubbleSort(head);
    Linklisttravarsal(head);
    printf("\n");

    printf("Enter the mark of the student to be deleted: ");
    scanf("%d", &mark);
    head = Linklist_delete(head, mark);
    Linklisttravarsal(head);
    printf("\n");

    printf("Enter roll number, mark, and index to insert a new student: ");
    int index;
    scanf("%d%d%d", &roll, &mark, &index);
    head = Linklist_insert(head, mark, roll, index);
    Linklisttravarsal(head);

    printf("\n");
    printf("Enter roll number of the student to be searched: ");
    scanf("%d", &roll);
    struct Node* node = search(head, roll);
    if (node != NULL) {
        printf("Found student: roll = %d, mark = %d\n", node->roll, node->mark);
    } else {
        printf("No student with roll number %d\n", roll);
    }

    printf("\n");
    printf("Enter roll number and new mark to update a student: ");
    scanf("%d%d", &roll, &mark);
    head = update(head, roll, mark);
    Linklisttravarsal(head);

    printf("\n");
    head = reverse(head);
    printf("Reversed linked list:\n");
    Linklisttravarsal(head);

    printf("\n");
    printf("Enter index to get node at: ");
    scanf("%d", &index);
    node = getNodeAt(head, index);
    if (node != NULL) {
        printf("Node at index %d: roll = %d, mark = %d\n", index, node->roll, node->mark);
    } else {
        printf("No node at index %d\n", index);
    }

    printf("\n");
    printf("Count of nodes: %d\n", getCount(head));

    printf("\n");
    head = removeLastNode(head);
    printf("Linked list after removing last node:\n");
    Linklisttravarsal(head);

    printf("\n");
    printf("Enter roll number and mark to insert at the end: ");
    scanf("%d%d", &roll, &mark);
    head = insertAtEnd(head, roll, mark);
    Linklisttravarsal(head);

    printf("\n");
    bubbleSortRoll(head);
    printf("Linked list sorted by roll:\n");
    Linklisttravarsal(head);

    printf("\n");
    bubbleSortRoll(head);
    printf("Linked list sorted by roll:\n");
    Linklisttravarsal(head);

    printf("\n");
    updateRolls(head);
    printf("Linked list after updating rolls by marks:\n");
    Linklisttravarsal(head);

    freeList(head);

    return 0;
}

/*
Enter the number of students: 5
Enter roll number and mark for student 1: 1 50
Enter roll number and mark for student 2: 2 30
Enter roll number and mark for student 3: 3 80
Enter roll number and mark for student 4: 4 60
Enter roll number and mark for student 5: 5 70
Enter the mark of the student to be deleted: 30
Enter roll number, mark and index to insert a new student: 6 20 2
Enter roll number of the student to be searched: 4
Enter roll number and new mark to update a student: 1 90
Enter index to get node at: 3
Enter roll number and mark to insert at end: 7 10

*/
  
  /*
  Sorted list by marks:
3 80
5 70
4 60
1 50
2 30

Linked list after deleting the student with mark 30:
3 80
5 70
4 60
1 50

Linked list after inserting new student:
3 80
5 70
6 20
4 60
1 50

Found student: roll = 4, mark = 60

Linked list after updating mark of student with roll number 1:
3 80
5 70
6 20
4 60
1 90

Reversed linked list:
1 90
4 60
6 20
5 70
3 80

Node at index 3: roll = 5, mark = 70

Count of nodes: 5

Linked list after removing last node:
1 90
4 60
6 20
5 70

Linked list after inserting at end:
1 90
4 60
6 20
5 70
7 10

Linked list sorted by roll:
1 90
4 60
5 70
6 20
7 10

Linked list after updating rolls by marks:
1 90
2 70
3 60
4 20
5 10

  */