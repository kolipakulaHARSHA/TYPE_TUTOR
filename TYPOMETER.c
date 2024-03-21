#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LEN 1000

typedef struct Node {
    char data[MAX_LEN];
    struct Node* next;
} Node;

Node* createNode(const char* data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    strncpy(newNode->data, data, MAX_LEN - 1);
    newNode->data[MAX_LEN - 1] = '\0';
    newNode->next = NULL;
    return newNode;
}

Node* createSentenceList() {
    Node* head = NULL;
    Node* current = NULL;

    const char* sentences[] = {
        "The quick brown fox jumps over the lazy dog.",
        "She sells seashells by the seashore.",
        "How much wood would a woodchuck chuck if a woodchuck could chuck wood?",
        "Peter Piper picked a peck of pickled peppers.",
        "The five boxing wizards jump quickly.",
        "A quick brown fox jumps over the lazy dog.",
        "The quick onyx goblin jumps over the lazy dwarf.",
        "Pack my box with five dozen liquor jugs.",
        "Jackdaws love my big sphinx of quartz.",
        "Jinxed wizards pluck ivy from the big quilt.",
        "Blowzy night-frumps vex'd Jack Q.",
        // Add more sentences as needed
    };

    for (int i = 0; i < sizeof(sentences) / sizeof(sentences[0]); ++i) {
        Node* newNode = createNode(sentences[i]);
        if (head == NULL) {
            head = newNode;
            current = newNode;
        } else {
            current->next = newNode;
            current = newNode;
        }
    }
    return head;
}

void displaySentence(Node* node) {
    printf("%s\n", node->data);
}

void displaySentenceList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        displaySentence(current);
        current = current->next;
    }
}

void freeSentenceList(Node* head) {
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    Node* sentenceList = createSentenceList();

    printf("Test Sentences for Typing Test:\n");
    displaySentenceList(sentenceList);

    srand((unsigned int)time(NULL)); // Seed for random sentence selection
    Node* randomSentence = sentenceList;
    int randomIndex = rand() % 11; // Adjust the number if more sentences are added

    // Move to the randomly selected sentence
    for (int i = 0; i < randomIndex; ++i) {
        randomSentence = randomSentence->next;
    }

    printf("\nType the following sentence:\n");
    displaySentence(randomSentence);

    time_t startTime = time(NULL);
    char input[MAX_LEN];
    fgets(input, MAX_LEN, stdin);

    time_t endTime = time(NULL);
    double timeTaken = difftime(endTime, startTime);

    int correct = 0;
    int total = strlen(randomSentence->data) - 1; // excluding the newline character

    for (int i = 0; input[i] != '\0'; ++i) {
        if (input[i] == randomSentence->data[i]) {
            correct++;
        }
        else{
            printf("The incorrect letter:%c\n",input[i]);
            printf("The letter to be typed:%c\n",randomSentence->data[i]);
        }
    }

    printf("\nAccuracy: %.2f%%\n", ((double)correct / total) * 100);
    printf("Typing speed: %.2f characters per minute\n", (total / timeTaken) * 60);

    freeSentenceList(sentenceList); // Free allocated memory
    return 0;
}