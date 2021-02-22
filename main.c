#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#define STR 60

typedef struct {
    int id;
    char first[STR];
    char second[STR];
} Student;

typedef struct SNode {
    struct SNode *next;
    Student data;
} Node, *NodeP;

Student createStudent (int id, char first[STR], char second[STR]);
Student readStudent();
NodeP createNode(Student data, NodeP next);
void printStudent(Student *student);
void printList(NodeP node);
void insertElement(NodeP *node, Student new, int index);
void deleteElement(NodeP *node, int index);
void deleteList(NodeP *node);
NodeP gotoIndex(NodeP *node, int index);
void insertSorted(NodeP *node, Student new);

void testFnHeader(char *, char*);

void testCreateReadPrint (NodeP *list);
void testInsertFront (NodeP *list);
void testInsertMiddle (NodeP *list);
void testInsertEnd (NodeP *list);
void testInsertSorted (NodeP *list);
void testDeleteElement (NodeP *list);
void testDeleteFirst (NodeP *list);
void testDeleteList (NodeP *list);

int main() {
    setbuf(stdout, 0); //debugger doesnt work else

    NodeP list = NULL;

    testCreateReadPrint(&list);
    testInsertFront(&list);
    testInsertMiddle(&list);
    testInsertEnd(&list);
    testInsertSorted(&list);
    testDeleteElement(&list);
    testDeleteFirst(&list);
    testDeleteList(&list);

    return 0;
}

Student createStudent (int id, char first[STR], char second[STR]) {
    Student new;

    new.id = id;
    strcpy(new.first, first);
    strcpy(new.second, second);

    return new;
}

Student readStudent() {
    Student new;

    printf("Enter id (65 for testing insertSorted): ");
    scanf("%d", &new.id);

    printf("Enter first name: ");
    scanf("%s", new.first);

    printf("Enter second name: ");
    scanf("%s", new.second);

    printf("\n");
    return new;
}

NodeP createNode(Student data, NodeP next) {
    NodeP new = (NodeP) malloc(sizeof(Node));
    new->next = next;
    new->data = data;
    return new;
}

void printStudent(Student *student) {
    printf("[%d: %s %s]", student->id, student->first, student->second);
}

void printList(NodeP node) {
    if (node == NULL) {
        printf("<empty list>\n");
        return;
    }

    while(node) {
        printStudent(&(node->data));
        if (node->next) printf(", ");

        node = node->next;
    }
    printf("\n");
}

void insertElement(NodeP *node, Student new, int index) {
    if (index < 0) {
        printf("\nCannot insert at index smaller than 0.");
        exit(1);
    }

    if (index == 0) {
        *node = createNode(new, *node);
        return;
    }

    NodeP target = gotoIndex(node, index);
    NodeP temp = target->next;
    target->next = createNode(new, temp);
}

void deleteElement(NodeP *node, int index) {
    if (index < 0) {
        printf("\nCannot delete at index smaller than 0.");
        exit(1);
    }

    if (index == 0) {
        NodeP toDelete = *node;
        *node = (*node)->next;
        free(toDelete);

        return;
    }

    NodeP target = gotoIndex(node, index);
    NodeP tempP = target->next;
    target->next = target->next != NULL ? target->next->next : NULL;
    free(tempP);
}

void deleteList(NodeP *node) {
    int *address = NULL;
    int size = 0;

    while (*node) {
        size++;
        address = (int *) realloc(address, sizeof (int) * size);
        address[size - 1] = (int) *node;

        *node = (*node)->next;
    }

    for (int i = 0; i < size; i++) {
        free(address + i);
    }
    free(address);
}

NodeP gotoIndex (NodeP *node, int index) {
    int loopIndex = 0;
    NodeP rp = *node;

    while (rp->next) {
        if (loopIndex >= index - 1) break;
        loopIndex++;

        rp = rp->next;
    }

    return rp;
}

void insertSorted (NodeP *node, Student new) {
    NodeP start = *node;

    while (*node) {
        if ((*node)->data.id < new.id && new.id < (*node)->next->data.id) {
            (*node)->next = createNode(new, (*node)->next);
            if (*node == start) return; else break;
        }

        *node = (*node)->next;
    }

    *node = start;
}

//-------------- tests

void testFnHeader(char *testName, char *expected) {
    printf("Test: %s\n", testName);
    printf("\tExpected: %s\n", expected);
    printf("\tGot: ");
}

void testCreateReadPrint (NodeP *list) {
    printf("Test element data: \n");
    Student test = readStudent();

    testFnHeader("Create list, read user data, print list", "[<id>, <first>, <last>]");

    *list = createNode(test, NULL);
    printList(*list);

    printf("\n\n");
}

void testInsertFront (NodeP *list) {
    testFnHeader("Insert into list (front)", "[60, first second], ...");

    insertElement(list, createStudent(60, "first", "second"), 0);
    printList(*list);

    printf("\n\n");
}

void testInsertMiddle (NodeP *list) {
    testFnHeader("Insert into list (middle)", "..., [61, middle list], ...");

    insertElement(list, createStudent(61, "middle", "list"), 1);
    printList(*list);

    printf("\n\n");
}

void testInsertEnd (NodeP *list) {
    testFnHeader("Insert into list (end)", "..., [62, end list]");

    insertElement(list, createStudent(70, "end", "list"), INT_MAX);
    printList(*list);

    printf("\n\n");
}

void testDeleteElement (NodeP *list) {
    printf("List before: ");
    printList(*list);
    testFnHeader("Delete list element", "..., (second element missing), ...");

    deleteElement(list, 1);
    printList(*list);

    printf("\n\n");
}

void testDeleteFirst (NodeP *list) {
    printf("List before: ");
    printList(*list);
    testFnHeader("Delete first list element", "(list shifted right)");

    deleteElement(list, 0);
    printList(*list);

    printf("\n\n");
}

void testDeleteList (NodeP *list) {
    testFnHeader("Delete whole list", "<empty list>");

    deleteList(list);
    printList(*list);

    printf("\n\n");
}

void testInsertSorted (NodeP *list) {
    testFnHeader("Insert sorted into list", "..., (id sorted) [69, sorted element], ...");

    insertSorted(list, createStudent(69, "sorted", "element"));
    printList(*list);

    printf("\n\n");
}