// ------------------------------ includes ------------------------------//
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
//#include <stdbool.h>
//#include <jmorecfg.h>
// ---------------------------------------------------------------------//

// -------------------------- const definitions -------------------------//
#define EXIT 'q'
#define BEST "best"
#define MERGE "merge"
#define QUICK "quick"
#define NUM_OF_ARGUMENT 2
#define ID 0
#define NAME 1
#define GRADE 2
#define AGE 3
#define COUNTRY 4
#define CITY 5
#define ARR_SIZE(x)  (sizeof(x) / sizeof(x[0]))
#define MAX_NUM_OF_STUDENTS 5001
#define OVER_MAX_NUM_OF_STUDENTS 5002
#define MAX_SIZE_OF_LINE 151


char bestStudent[MAX_SIZE_OF_LINE];
double bestStudentScore = -1.0;
int lineCounter = -1;
unsigned int studentCounter = 0;
const int ID_LENGTH = 10;
//const int MAX_GRADE_OR_AGE_LENGTH = 3;
const int MAX_GRADE = 100;
//const int OVER_MAX_NUM_OF_STUDENTS = 5002;
const int MAX_AGE = 120;
const int MIN_AGE = 18;
const int MIN_AGE_LENGTH = 2;
const int MIN_GRADE_LENGTH = 1;

/**
 * @brief the struct that define the Student in this program
 */
typedef struct Student
{

//    unsigned long id;
    char id[11], name[41], country[41], city[41];
    unsigned int age, grade;
//    unsigned long *p_id;
    unsigned int index;
    // todo maybe more pointers!!!
} Student;

Student studentsArr[MAX_NUM_OF_STUDENTS];

// -----------------------------------------------------------------------//

// -------------------------- functions ----------------------------------//

/**
 * @brief integer validation method
 * @param n - signifies what type this integer reprecents
 * @param str - string to check
 * @return - 0 if it integer -1 otherwise
 */
int integerValidation(int n, char str[])
{
    if ( n > 3 || n < 0 || n == 1)
    {
        return -1;
    }
    int i, value;
    int arrayLength = strlen(str);
//    printf("%d\n", arrayLength);
    for ( i = 0; i < arrayLength; i++)
    {
//        printf("%c\n", str[i]);
        if(!isdigit(str[i]))
        {
            printf("ERROR: The grade or age should include only digits\n");
            printf("in line %d\n", lineCounter);
            return -1;
        }
    }
//    value = atoi(str);
    char *p;
    value = (int) strtol(str,&p,10);
    if(n == ID)
    {
        if(str[0] == '0' || arrayLength != ID_LENGTH)
        {
            printf("ERROR: ID number must include 10 digits and doesn't starts with '0'\n");
            printf("in line %d\n", lineCounter);
            return -1;
        }
    }
    else if (n == GRADE)
    {
//        printf("%d\n", (MAX_GRADE-value));
//        int k = (MAX_GRADE-value);
        if((arrayLength > MIN_GRADE_LENGTH && str[0] == '0') || (int)(MAX_GRADE-value) < 0)
        {
            printf("ERROR: Grade should be an integer from 0 to 100\n");
            printf("in line %d\n", lineCounter);
            return -1;
        }
    }
    else if (n == AGE)
    {
        if((arrayLength >= MIN_AGE_LENGTH && str[0] == '0') || (int)(value - MIN_AGE) < 0 || (int)(MAX_AGE - value) < 0)
        {
            printf("ERROR: Age should be an integer from 18 to 120\n");
            printf("in line %d\n", lineCounter);
            return -1;
        }
    }

    return 0;
}

/**
 * @brief alphabetical validation method
 * @param n - signifies what type this word reprecents
 * @param str - string to check
 * @return - 0 if it integer -1 otherwise
 */
int stringValidation(int n, char str[])
{
    unsigned int i;
    unsigned int arrayLength = strlen(str);
    for ( i = 0; i < arrayLength; i++)
    {
        if(!(isalpha(str[i]) || str[i] == '-' || str[i] == ' '))
        {
            if (n == CITY)
            {
                printf("ERROR: city can only contain alphabetic characters or ’-’\n");
                printf("in line %d\n", lineCounter);
                return -1;
            }
            else if (n == COUNTRY)
            {
                printf("ERROR: country can only contain alphabetic characters or ’-’\n");
                printf("in line %d\n", lineCounter);
                return -1;
            }
            else
            {
                printf("ERROR: name can only contain alphabetic characters, spaces or ’-’\n");
                printf("in line %d\n", lineCounter);
                return -1;
            }
        }
    }
    return 0;
}

/**
 * @brief checking if there is any need to update best student - if yes update it
 * @param grade - grade of current student
 * @param age - age of current student
 * @param line - counter of lines amount
 */
void bestStudentCheck(unsigned int grade, unsigned int age, char line[])
{
    double studentScore = (double) grade / age;
    if (bestStudentScore < studentScore)
    {
        bestStudentScore = studentScore;
        strcpy(bestStudent, line);
    }
}

/**
 * @brief according to task this method receives it does appropriated actions
 * @param task - task that we received to do
 * @param parsedLine - parsed line from user that we work with at that moment
 * @param inputLine - original line from the user
 */
void preTaskDoing(char task[], char parsedLine[7][41], char inputLine[MAX_SIZE_OF_LINE])
{
    //    studentCounter++;
//    unsigned int grade = atoi(parsedLine[GRADE]);
    char *p;
    unsigned int grade = (int)strtol(parsedLine[GRADE], &p, 10);;
//    printf("%d\n",grade);
//    int age = atoi(parsedLine[AGE]);
    int age = (int) strtol(parsedLine[AGE],&p,10);
//    printf("%d\n",age);

    if (strcmp(task, BEST) == 0)
    {
        bestStudentCheck(grade, age, inputLine);
    }
    else
    {
        /* char k[10];
    strcpy(k, separatedLine[ID]);*/
        Student currentStudent;
        /*= {separatedLine[ID], separatedLine[NAME], separatedLine[GRADE],
                    separatedLine[AGE], grade, age}*/
        strcpy(currentStudent.id, parsedLine[ID]);
        strcpy(currentStudent.name, parsedLine[NAME]);
        currentStudent.grade = grade;
        currentStudent.age = age;
        strcpy(currentStudent.country, parsedLine[COUNTRY]);
        strcpy(currentStudent.city, parsedLine[CITY]);
        currentStudent.index = studentCounter;

//        printf("%s  %s  %d  %d  %s  %s  %d\n", currentStudent.id,currentStudent.name,currentStudent.grade,
//                currentStudent.age,currentStudent.country, currentStudent.city, currentStudent.index);

        studentsArr[studentCounter] = currentStudent;
    }
}

/**
 * @brief - the parsing method that checks if it correct line from the user
 * @param inputLine - line from input
 * @param task - task from user
 * @return - 0  if this line fit the legal pattern, -1 otherwise (and prints what exactly was wrong)
 */
int parsing(char inputLine[], char task[])
{

    char separatedLine[7][41];
//    gets(inputLine);
//    printf(inputLine);

    /*char * tok = strtok(inputLine, "\t");
    while (tok != NULL) {
        printf("%s\n", tok);
        if()
        tok = strtok(NULL, "\t");
    }*/
    lineCounter++;
    unsigned int valueCounter = 0;
    unsigned int charIndex = 0;
    unsigned long i;
    int tabCounter = 0;
    /*printf("%lu\n",strlen(inputLine));
    inputLine[6] = 'g';
    printf("%c",inputLine[6]);*/

    for(i = 0; i < strlen(inputLine); i++)
    {
        if (inputLine[i] == '\0' )
        {
            separatedLine[i][0] = '\0';
            break;       //todo not sure about it
        }
        else if (inputLine[i] == '\t' )
        {
            /*if( i==0 )
            {
                tabCounter++;
            }*/
            separatedLine[valueCounter][charIndex] = '\0';
            tabCounter++;
            valueCounter++;
            charIndex = 0;
        }
        else
        {
            separatedLine[valueCounter][charIndex] = inputLine[i];
            charIndex++;
        }
    }
    if(valueCounter != 6 || tabCounter != 6)
    {
        printf("ERROR: illegal format of input -- number of words or tabs doesn't fit the pattern\n");
        printf("in line %d\n", lineCounter);
        return -1;
    }
    for( i = 0; i < valueCounter; i++ )
    {
        switch (i)
        {
            case ID:
            case GRADE:
            case AGE:
                if (integerValidation(i, separatedLine[i]) != 0)
                {
                    return -1;
                }
                break;
            case NAME:
            case COUNTRY:
            case CITY:
                if (stringValidation(i, separatedLine[i]) != 0)
                {
                    return -1;
                }
                break;
            default:
                return -1;
        }
    }

    preTaskDoing(task, separatedLine, inputLine);

    /* printf("\n Strings or words after split by space are :\n");
     for(i=0; i < valueCounter; i++)
     {printf(" %s\n",separatedLine[i]);}
     printf("%d\n", valueCounter);
     printf("%d", tabCounter);
     return 0;*/

    return 0;
}

/**
 * @brief this method part of merge algorithm implementation in this code
 * @param left
 * @param center
 * @param right
 * @param assistantArray - array that help us to sort the original one (the global one in this code)
 */
void doMerge(int left, int center, int right, Student assistantArray[])
{
    int i, j, k;

    for (j = left, k = center + 1, i = left; j <= center && k <= right; i++)
    {
        if(studentsArr[j].grade <= studentsArr[k].grade)
        {
            assistantArray[i] = studentsArr[j++];
        }
        else
        {
            assistantArray[i] = studentsArr[k++];
        }
    }
    while (j <= center)
    {
        assistantArray[i++] = studentsArr[j++];
    }
    while (k <= right)
    {
        assistantArray[i++] = studentsArr[k++];
    }
    for (i = left; i <= right; i++)
    {
        studentsArr[i] = assistantArray[i];
    }
}

/**
 * @brief this reduction method part of merge algorithm implementation in this code
 * @param left
 * @param right
 * @param assistantArray - array that help us to sort the original one (the global one in this code)
 */
void mergeSort(int left, int right, Student assistantArray[])
{
    int center;
    if(left < right)
    {
        center = ((right + left) / 2);
        mergeSort(left, center, assistantArray);
        mergeSort(center + 1, right, assistantArray);
        doMerge(left, center, right, assistantArray);
    }
    else
    {
        return;
    }
}

/**
 * @brief the quick sort algorithm implementation in this code
 * @param start
 * @param finish
 */
void quickSort(int start, int finish)
{
    int i, j, pivIndex;
    Student tempStudent;

    if(start < finish)
    {
        pivIndex = start;
        i = start;
        j = finish;

        while (i < j)
        {
            while ( strcmp(studentsArr[i].name, studentsArr[pivIndex].name) <= 0 && i < finish) /*studentsArr[i]<=studentsArr[pivot]*/
            {
                i++;
            }
            while (strcmp(studentsArr[j].name, studentsArr[pivIndex].name) > 0)  /*studentsArr[j]>studentsArr[pivIndex]*/
            {
                j--;
            }
            if (i < j)
            {
                tempStudent = studentsArr[i];
                studentsArr[i] = studentsArr[j];
                studentsArr[j] = tempStudent;
            }
        }

        tempStudent = studentsArr[pivIndex];
        studentsArr[pivIndex] = studentsArr[j];
        studentsArr[j] = tempStudent;
        quickSort(start, j - 1);
        quickSort(j + 1, finish);
    }
}

void deleteEnding(/*char str[]*/)
{
    char *ending;
    ending = strchr(bestStudent,'\r');
    if(ending)
    {
        ending[0] = 0;
    }
    ending = strchr(bestStudent,'\n');
    if (ending)
    {
        ending[0] = 0;
    }
}

/**
 * @brief the main method of the program - first of all checks if the task order from the user were legal,
 *                                         then receives input from user and at final this method do it
 * @param argc - num of arguments from user
 * @param argv - "task" from user
 * @return - o if task was completed, -1 otherwise;
 */
int main(int argc, char *argv[] )
{
    if (argc == NUM_OF_ARGUMENT && (strcmp(argv[1], BEST) == 0 || strcmp(argv[1], QUICK) == 0
                || strcmp(argv[1], MERGE) == 0))
    {
        unsigned int toContinue = 0;
        while (toContinue == 0)
        {
            char inputLine[MAX_SIZE_OF_LINE];
            printf("Enter student info. To exit press q, then enter\n");
            fgets(inputLine, sizeof inputLine, stdin);
//            printf("%lu\n", strlen(inputLine));
//            printf("%c\n",inputLine[6]);
//            if (inputLine[0] == EXIT && inputLine[1] == '\n')
            if (strcmp(inputLine, "q\n") == 0 || strcmp(inputLine, "q\r\n") == 0)
            {
                toContinue = 1;
                Student student;
                // two next lines help us to determinate on what size of array we should do
                // merge or quick sort;
                student.index = OVER_MAX_NUM_OF_STUDENTS;
                studentsArr[studentCounter] = student;
                continue;
            }
            if (parsing(inputLine, argv[1]) == 0)
            {
                studentCounter++;
            }
        }
        if (studentCounter == 0)
        {
            return 0;
        }
        if (strcmp(argv[1], BEST) == 0)
        {
            deleteEnding(/*bestStudent*/);
            printf("best student info is: %s\n", bestStudent);
            return 0;
        }
        else /*if (strcmp(argv, MERGE) == 0)*/
        {
            /*printf("%lu\n", ARR_SIZE(studentsArr));
            printf("%d\n", studentsArr[0].index);
            printf("%d\n", studentsArr[1].index);*/
//            printf("%lu\n", ARR_SIZE(mergeArr));
            unsigned int i;
            for (i = 0; i < ARR_SIZE(studentsArr); i++)
            {
                if (studentsArr[i].index == OVER_MAX_NUM_OF_STUDENTS)
                {
                    break;
                }
            }
            // amount of students > 1
            if (i > 0)
            {
                i--;
                Student mergeArr[MAX_NUM_OF_STUDENTS];
                if (strcmp(argv[1], MERGE) == 0)
                {
                    mergeSort(0, i, mergeArr);
                }
                else
                {
                    quickSort(0, i);
                }
                for (unsigned int j = 0; j <= i; j++)
                {
                    printf("%s\t%s\t%d\t%d\t%s\t%s\t\n", studentsArr[j].id, studentsArr[j].name,
                           studentsArr[j].grade, studentsArr[j].age, studentsArr[j].country,
                           studentsArr[j].city); /*, studentsArr[j].index*/
                }
            }
                // if i=0 and it's mean that we have only one student to do with this task
            else
            {
                printf("%s\t%s\t%d\t%d\t%s\t%s\t\n", studentsArr[i].id, studentsArr[i].name,
                       studentsArr[i].grade, studentsArr[i].age, studentsArr[i].country,
                       studentsArr[i].city);
            }
            return 0;
        }
    }
}
