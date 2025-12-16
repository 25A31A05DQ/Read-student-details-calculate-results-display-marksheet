#include <stdio.h>
#include <string.h>

#define MAX_SUBJECTS 10
#define MAX_NAME_LEN 50

/* Structure to hold student details */
struct Student {
    char name[50];
    int roll;
    int marks[10];
    int total;
    float percentage;
    char grade;
};

/* Function prototypes */
void inputStudent(struct Student *s, int n);
void calculateResult(struct Student *s, int n);
char findGrade(float percentage);
void displayMarksheet(const struct Student *s, int n);
void strip_newline(char *s);

int main(void) {
    struct Student s;
    int n;
    int ready = 0;

    printf("Enter number of subjects (1 to %d): ", MAX_SUBJECTS);
    if (scanf("%d", &n) != 1) {
        printf("Invalid input.\n");
        return 1;
    }

    /* basic validation */
    if (n < 1 || n > MAX_SUBJECTS) {
        printf("Number of subjects must be between 1 and %d.\n", MAX_SUBJECTS);
        return 1;
    }

    /* consume leftover newline from scanf */
    {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) { /* discard */ }
    }

    inputStudent(&s, n);
    calculateResult(&s, n);
    displayMarksheet(&s, n);

    return 0;
}

/* Helper to remove trailing newline from fgets */
void strip_newline(char *s) {
    size_t len = strlen(s);
    if (len > 0 && s[len - 1] == '\n') {
        s[len - 1] = '\0';
    }
}

/* Function to take student details */
void inputStudent(struct Student *s, int n) {
    int i;

    printf("\nEnter Student Name: ");
    if (fgets(s->name, sizeof(s->name), stdin) == NULL) {
        s->name[0] = '\0';
    }
    strip_newline(s->name);

    printf("Enter Roll Number : ");
    if (scanf("%d", &s->roll) != 1) {
        s->roll = 0;
    }

    /* consume leftover newline before next fgets/inputs */
    {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) { /* discard */ }
    }

    printf("\nEnter marks of %d subjects (0-100):\n", n);
    for (i = 0; i < n; i++) {
        printf("Subject %d: ", i + 1);
        if (scanf("%d", &s->marks[i]) != 1) {
            s->marks[i] = 0;
        }
        /* optional: validate range */
        if (s->marks[i] < 0) s->marks[i] = 0;
        if (s->marks[i] > 100) s->marks[i] = 100;
    }
}

/* Calculate total, percentage, grade */
void calculateResult(struct Student *s, int n) {
    int i;
    s->total = 0;
    for (i = 0; i < n; i++) {
        s->total += s->marks[i];
    }
    s->percentage = (float) s->total / n;
    s->grade = findGrade(s->percentage);
}

/* Grade logic */
char findGrade(float percentage) {
    if (percentage >= 90.0f) return 'A';
    else if (percentage >= 75.0f) return 'B';
    else if (percentage >= 60.0f) return 'C';
    else if (percentage >= 50.0f) return 'D';
    else return 'F';
}

/* Display the full marksheet */
void displayMarksheet(const struct Student *s, int n) {
    int i;
    printf("\n\n============= STUDENT MARKSHEET =============\n");
    printf("Name       : %s\n", s->name);
    printf("Roll No    : %d\n", s->roll);
    printf("----------------------------------------------\n");
    printf("Marks:\n");
    for (i = 0; i < n; i++) {
        printf("Subject %d : %d\n", i + 1, s->marks[i]);
    }
    printf("----------------------------------------------\n");
    printf("Total Marks   : %d\n", s->total);
    printf("Percentage    : %.2f%%\n", s->percentage);
    printf("Grade         : %c\n", s->grade);
    printf("----------------------------------------------\n");
}
