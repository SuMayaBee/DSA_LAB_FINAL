#include <stdio.h>
#include <stdlib.h>

struct student {
    int roll;
    int mark;
};

struct Node {
    int roll;
    int mark;
    struct Node* next;
};

struct Node* new_node(int roll, int mark) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    if (node == NULL) {
        return NULL;
    }
    node->roll = roll;
    node->mark = mark;
    node->next = NULL;
    return node;
}

void Linklisttravarsal(struct Node* head) {
    struct Node* p = head;
    while (p != NULL) {
        printf("Roll: %d, Marks: %d\n", p->roll, p->mark);
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

struct Node* Linklist_delete(struct Node* head, int roll) {
    struct Node* p = head;
    struct Node* q = head->next;
    if (head->roll == roll) {
        head = q;
        free(p);
        return head;
    }

    while (q != NULL && q->roll != roll) {
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

int main() {
    int n;
    printf("Enter the number of students: ");
    scanf("%d", &n);
    struct student arr[n];
    for(int i = 0; i < n; i++) {
        printf("Enter the roll & mark: ");
        scanf("%d %d", &arr[i].roll, &arr[i].mark);
    }

    struct Node* head = NULL;
    for(int i = 0; i < n; i++) {
        head = Linklist_insert(head, arr[i].mark, arr[i].roll, i);
    }

    bubbleSort(head);

    printf("\nSorted list by marks:\n");
    Linklisttravarsal(head);

    printf("\nDeleting a node (enter roll): ");
    int roll;
    scanf("%d", &roll);
    head = Linklist_delete(head, roll);

    printf("\nAfter deletion:\n");
    Linklisttravarsal(head);

    return 0;
}
