#include<stdio.h>
#include<malloc.h>

#define N 1000
int arr[N];

void swap(int *a, int *b) {
    int temp= *b;
    *b = *a;
    *a = temp;

}

void heapify(int a[], int n, int i) {

    if(n == 1) {
        printf("Single Elements in the array");
    }

    int largest =i;
    int l= 2*i+1;
    int r= 2*i+2;

    if(l<n && a[largest]< a[l]) {
        largest =l;
    }

    if(r<n && a[largest]< a[r] ) {
        largest = r;
    }
    if(i!= largest) {
        swap(&a[i], &a[largest]);
        heapify(a, n, largest);
    }
}

void insert(int a[], int n, int newnum) {
    if(n ==0) {
        a[0] = newnum;
        n++;
    }

    a[n]= newnum;
    n++;
    for(int i=n/2-1; i>=0; i--) {
        heapify(a, n, i);
    }
}

void deleteroot(int a[], int n, int deletenum) {
    if(n==0) {
        printf("This heap is empty");
    }
    
    int i;
    for(i=0; i<n; i++) {
        if(a[i]== deletenum) {
            break;
        }
    }

    swap(&a[i], &a[n-1]);
    n--;
    for(int i= n/2-1; i>=0; i--) {
        heapify(a, n, i);
    }
}

void heapsort(int a[], int n) {
    for(int i=n-1; i>0; i--) {
        swap(&a[i], &a[0]);
        heapify(arr, --n, 0);
    }
}

void searchHeap(int a[], int n, int key) {
    for (int i = 0; i < n; i++) {
        if (a[i] == key) {
            printf("Key %d found at index %d.\n", key, i);
            return;
        }
    }
    printf("Key %d not found in heap.\n", key);
}


int main() {

    int n;
    printf("Insert the number of nodes in the array: ");
    scanf("%d", &n);

    for(int i=0; i<n; i++) {
        scanf("%d", &arr[i]);
    }

    for(int a=n/2; a>=0; a--) {
        heapify(arr, n, a);
    }

    for(int i=0; i<n; i++) {
        printf("%d ", arr[i]);
    }

   /* insert(arr, n++, 8);
    
    printf("\n");
     for(int i=0; i<n; i++) {
        printf("%d ", arr[i]);
    }  */
   /* printf("\n");
    deleteroot(arr, n--, 6);
    */

    heapsort(arr, n);

    printf("\n");

     for(int i=0; i<n; i++) {
        printf("%d ", arr[i]);
    }

    printf("\n");

    searchHeap(arr, n, 5);


   return 0;

}