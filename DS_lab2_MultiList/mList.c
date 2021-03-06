//
// Created by 이재현 on 2017. 9. 18..
//

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mList.h"


void Init(studentListType *Lptr){
    Lptr->studentCnt = 0;
    Lptr->student_Head = NULL;
}
bool IsEmpty(studentListType *Lptr){
    return (Lptr->studentCnt == 0);
}

void readCSVfile_And_MakeMultiList(studentListType *Lptr, char *filePath){
    char line [256];
    char delimiter [] = ",\n";
    /* Use " \n" as a delimiter if the contents are separated with black.
     * In this case, contents are separated with comma (CSV file, comma separated file)
     * */
    char *token;
    int s_flag = 0;
    int m_flag = 0;
    int index = 0;

    FILE *filePtr;

    filePtr = fopen(filePath,"r");
    if (filePtr == NULL){
        printf("File i/o exception ! ");
    }
    else{
        Init(Lptr);

        students_Nptr s_prev = (students_node *)malloc(sizeof(students_node));

        major_Nptr m_prev = (major_node *)malloc(sizeof(major_node));

        while( fgets(line, 255, filePtr) != NULL ){

            token = strtok(line, delimiter);

            Lptr->studentCnt++;

            /* new student */

            students_Nptr s_nptr = (students_node *)malloc(sizeof(students_node));

            majorListType* mlType = (majorListType *)malloc(sizeof(majorListType));

            s_nptr->avg = 0;

            s_nptr->majorList = mlType;

            strcpy(s_nptr->studentName,token);

            if(s_flag == 0) {
                /* new major.
                 * s_flag == 0일 때 ( 맨 처음으로 학생노드가 만들어질 때,
                 * studentHead에 새로 들어온 학생노드를 연결
                 * */
                s_flag++;
                Lptr->student_Head = s_nptr;
                s_prev = s_nptr;
            }
            else {

                /*  이전 학생 노드의 다음 노드를 가르키는 포인터에 현재 노드를 연결시켜줌
                 */
                s_prev->next_student = s_nptr;
                s_prev = s_nptr;
            }
            s_nptr->majorList->majorCnt = 0;

            while (token != NULL){
                token = strtok(NULL,delimiter);

                if(token != NULL){
                    s_nptr->majorList->majorCnt++;

                    major_Nptr m_temp_ptr = (major_node *)malloc(sizeof(major_node));

                    strcpy(m_temp_ptr->major,token);

                    m_prev -> score = 0;

                    if(m_flag == 0){

                        m_flag++;

                        s_nptr->majorList->major_Head = m_temp_ptr;

                        m_prev = m_temp_ptr;

                    }
                    else{
                        m_prev->next_mnode = m_temp_ptr;

                        m_prev = m_temp_ptr;
                    }
                }
            }
            m_flag--;
        }
        s_flag--;
        fclose(filePtr);
    }
}

void setScore(studentListType *Lptr, char *name, char *majorName, int score){
    int isNotFound = true; // used for a while loop condition.
    int i = 0;
    int check_student_Cnt = 0;

    students_Nptr sNptr = (students_node *)malloc(sizeof(students_node));

    major_Nptr mNptr = (major_node *)malloc(sizeof(major_node));

    sNptr = Lptr -> student_Head;

    while(isNotFound && (check_student_Cnt < Lptr->studentCnt)){

        check_student_Cnt++;

        if( strcmp(sNptr->studentName,name) == 0 ){ // if equal to current pointer`s name field.

            mNptr = sNptr->majorList->major_Head;

            for( i = 0 ; i < sNptr->majorList->majorCnt ; i++ ){

                if( strcmp(mNptr->major,majorName) == 0){

                    mNptr->score = score;

                    isNotFound = false;

                    printf("Successfully set score!\n");

                    break;
                }

                else {
                    mNptr = mNptr->next_mnode;
                }
            }

            if(isNotFound == true) {

                printf("Major Name doesn`t match to any data in the list\n");

                sNptr = sNptr->next_student;
            }


        }
        else { // if not equal to current pointer`s name field.

            sNptr = sNptr->next_student;
            if(isNotFound && (check_student_Cnt == Lptr->studentCnt))
                printf("Student Name doesn`t match to any data in the list\n");
            continue;
        }
    }

}









void setAverageScorePerStu(studentListType *Lptr){
    int i=0,j=0,sum=0;
    double avg = 0;

    students_Nptr sNptr = (students_node *)malloc(sizeof(students_node));
    major_Nptr mNptr = (major_node *)malloc(sizeof(major_node));

    sNptr = Lptr -> student_Head;
    for( i = 0 ; i < Lptr->studentCnt ; i++ ){
        sum = 0;
        avg = 0;
        mNptr = sNptr->majorList->major_Head;
        for( j = 0 ; j < sNptr->majorList->majorCnt ; j++ ){
            sum += mNptr->score;
            mNptr = mNptr->next_mnode;
        }
        avg = sum / sNptr->majorList->majorCnt;
        sNptr->avg = avg;

        sNptr = sNptr->next_student;
    }
}

void dispList(studentListType *Lptr){
    dispAvgPerStudent(Lptr);
    dispAvgPerMajor(Lptr);
}
void dispAvgPerStudent(studentListType *Lptr){

    int i=0,j=0;
    size_t len = 0;
    printf("--------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("Student Name        |       Major Information\n");
    printf("--------------------------------------------------------------------------------------------------------------------------------------\n");
    students_Nptr sNptr = (students_node *)malloc(sizeof(students_node));
    major_Nptr mNptr = (major_node *)malloc(sizeof(major_node));
    sNptr = Lptr -> student_Head;
    for( i = 0 ; i < Lptr->studentCnt ; i++ ){
        len = strlen(sNptr->studentName);
        printf("%s",sNptr->studentName);
        for(j = 0 ; j < 20-len ; j++){
            printf(" ");
        }
        printf("| ");

        mNptr = sNptr->majorList->major_Head;
        for( j = 0 ; j < sNptr->majorList->majorCnt ; j++ ){
            printf("%s ",mNptr->major);
            printf("(%d) -> ",mNptr->score);
            mNptr = mNptr->next_mnode;
        }
        printf("Average (%.1lf)\n",sNptr->avg);
        sNptr = sNptr->next_student;
    }
    printf("--------------------------------------------------------------------------------------------------------------------------------------\n");

}

void dispAvgPerMajor(studentListType *Lptr) {

    int i = 0, j = 0, k = 0;
    int index = 0;
    double avg_temp = 0;
    bool flag = true;
    char lookUpTable[20][30] = {' ',};

    size_t len = 0;

    students_Nptr sNptr = (students_node *) malloc(sizeof(students_node));
    major_Nptr mNptr = (major_node *) malloc(sizeof(major_node));
    sNptr = Lptr->student_Head;
    for (i = 0; i < Lptr->studentCnt; i++) {
        mNptr = sNptr->majorList->major_Head;
        for (j = 0; j < sNptr->majorList->majorCnt; j++) {
            for (k = 0; k < 20; k++) {
                if (strcmp(mNptr->major, lookUpTable[k]) == 0) {
                    flag = false;
                    break;
                }
            }
            if (flag == true) {
                strcpy(lookUpTable[index], mNptr->major);
                index++;
            }
            mNptr = mNptr->next_mnode;
            flag = true;
        }
        sNptr = sNptr->next_student;
    }
    printf("Major               |  Average Score\n");
    printf("--------------------------------------------------------------------------------------------------------------------------------------\n");
    int *sumArray = (int *) malloc(sizeof(int) * index);
    int *cntArray = (int *) malloc(sizeof(int) * index);

    for (i = 0; i < index; i++) {
        sumArray[i] = 0;
        cntArray[i] = 0;
    }

    sNptr = Lptr -> student_Head;
    for( i = 0 ; i < Lptr->studentCnt ; i++ ){
        mNptr = sNptr->majorList->major_Head;
        for( j = 0 ; j < sNptr->majorList->majorCnt ; j++ ){
            for( k=0 ; k < index ; k++ ){
                if(strcmp(mNptr->major,lookUpTable[k])==0){
                    sumArray[k] += mNptr->score;
                    cntArray[k] += 1;
                }

            }
            mNptr = mNptr->next_mnode;
        }
        sNptr = sNptr->next_student;
    }


    for( i = 0 ; i < index ; i++ ){
        printf("%s",lookUpTable[i]);
        len = strlen(lookUpTable[i]);
        for(j = 0 ; j < 20-len ; j++){
            printf(" ");
        }
        avg_temp = sumArray[i]/cntArray[i];
        printf("| %.1lf\n",avg_temp);
    }
    printf("--------------------------------------------------------------------------------------------------------------------------------------\n");



}