#include <stdio.h>
#include <Windows.h> //������� ��� Consolas
#include <string.h> // ������
#include <time.h> // ����������� ������� ����



#define N 25 //������������ ����� ������

struct date{
    int day; //���� ��������
    int month; //����� ��������
    int year; //��� ��������
};
struct studinfo{
    int id; //����� �������� � ����
    char fam[N]; //�������
    char name[N]; //���
    char group[N]; //������
    char studnum[N]; //����� �������������
    struct date data; //���� ��������
};
//���������� �������
void chan(char *fname);
void pri(char *fname, int id);
void fil(char *fname, int id);
void sort(char *fname, int id);
void diz();
void razr();

int main() {
    system("cls");
    system("color 3E");
    printf("\n                                  Attention! \n\n");
    printf("                     For correct operation of the program, \n");
    printf("          change the console font to 'Consolas' or 'Lucida Console'.\n");
    printf("                    To do this, right-click the console title\n");
    printf("                        and open the 'Properties' section.\n");
    printf("                                   Thank you!\n\n");
    system("pause");
    SetConsoleCP(1251); //����������� �� ��� ����������� �����
    SetConsoleOutputCP(1251); //� ������

    int id; //���������� ��������� � �����.
    diz(); //����� � ����� - ������
    printf("                        ����� ����������!\n\n");
    //����������� ����� �����
    printf("��� ������ � ����� ������ ");
    printf("������� � �������� (��� �����) � ����������� .bin\n");
    char fname[N];
    scanf("%s", &fname);
    //�������� �������������/������������ ����� �����
    int ot = 0; //���������� ��� ��������, ����� �� ��� ����� ������� �����
    FILE *file = NULL;
    while (ot != 1){
        if((file = fopen(fname, "rb")) == NULL) {
            fclose(file);
            printf("������� ����� �� ����������. ������� ����? 1 - ��, 2 - ���\n");
            scanf("%d", &ot);
            if (ot == 1) {
                printf("���� ������.\n\n");
                file = fopen(fname, "wb");
                ot = 1;
                id = 0;
                fclose(file);
            }
            else {
                printf("������� ������ ��� ����� � ����������� .bin \n");
                scanf("%s", &fname);
            }
        }
        else {
            printf("���� ������.\n\n");
            fclose(file);
            FILE *lastID = NULL; //lastID - ����, �������� ������ ���-�� ����������
            lastID = fopen("lastID.bin", "r+b"); //���������� ���-�� ���������� � ����
            fread(&id, sizeof(int), 1, lastID);
            fclose(lastID);
            ot = 1;
        }
    }

    system("pause");
    diz();
    //�������� �����!!
    int input = -1;
    while (input) {
        diz();

        printf("                        ����\n\n");
        printf("1 - �������� �������� \n");
        printf("2 - ������� �������� \n");
        printf("3 - �������� ������ � ��������  \n");
        printf("4 - ������� ������ ��������� \n");
        printf("5 - ������� ������ ��������� �� ������� \n");
        printf("6 - ������� ��������������� ������ ���������\n");
        printf("7 - �������� � �������������\n");
        printf("0 - ����� \n\n");
        printf("������� ����� ������������ ��������: ");
        scanf("%d", &input);
        switch (input) {
            case 1:
                id = zap(fname, id);
                break;
            case 2:
                id = del(fname, id);
                break;
            case 3:
                chan(fname);
                break;
            case 4:
                pri(fname, id);
                break;
            case 5:
                fil(fname, id);
                break;
            case 6:
                sort(fname, id);
                break;
            case 7:
                razr();
                break;
            case 0:
                diz();
                printf("                        ���������� ������. �� ��������!\n\n" );
                break;
        default:
            printf( "������������ ����.\n" );
            system("pause");
        }
    }
    return 0;
}

//1 - �������� ��������
int zap(char *fname, int id) {
    diz();
    struct studinfo stud;
    FILE *file = NULL;
    file = fopen(fname, "r+b");
    id++;
    stud.id = id;
    int isize = sizeof(stud);
    fseek(file, isize * (id - 1), SEEK_SET);
    printf("                        ���������� ��������\n\n");
    printf("������� ���\n");
    scanf("%s", &stud.name);
    printf("������� �������\n");
    scanf("%s", &stud.fam);
    printf("������� ������\n");
    scanf("%s", &stud.group);
    printf("������� ����� �������������\n");
    scanf("%s", &stud.studnum);
    printf("������� ���� �������� �������� (������� ����� ������, ����. '21 12 1999')\n");
    scanf("%d%d%d", &stud.data.day, &stud.data.month, &stud.data.year);
    fwrite(&stud, sizeof(stud), 1, file);

    fclose(file);
    FILE *lastID = NULL;
    lastID = fopen("lastID.bin", "wb");
    fwrite(&stud.id, sizeof(int), 1, lastID);
    fclose(lastID);

    printf("\n");
    printf("������� ��������!\n\n");
    system("pause");
    return id;
}
//2 - �������� ��������
int del(char *fname, int id) {
    struct studinfo stud;
    FILE *file = NULL;
    file = fopen(fname, "r+b");

    printf("\n������� ����� ��������, �������� ���������� �������: ");
    int temp_id;
    scanf("%d", &temp_id);

    int isize = sizeof(stud);
    int qq;
    for (temp_id; temp_id < id; temp_id++){
         fseek(file, isize * temp_id, SEEK_SET);
         qq = fread(&stud, sizeof(stud), 1, file);
         stud.id--;
         fseek(file, isize * (temp_id - 1), SEEK_SET);
         fwrite(&stud, sizeof(stud), 1, file);
    }

    fseek(file, 0, SEEK_SET);
    fclose(file);
    id--;

    FILE *lastID = NULL;
    lastID = fopen("lastID.bin", "wb");
    fwrite(&id, sizeof(int), 1, lastID);
    fclose(lastID);

    system("pause");
    return id;
}
//3 - �������� ������ � ��������
void chan(char *fname) {
    struct studinfo stud;
    FILE *file = NULL;
    file = fopen(fname, "r+b");

    printf("\n������� ����� ��������, ���������� � ������� ����� ��������: ");
    int temp_id;
    scanf("%d", &temp_id);
    diz();
    printf("                        ��������� ���������� � �������� � %d\n\n", temp_id);

    int isize = sizeof(stud);
    fseek(file, isize * (temp_id - 1), SEEK_SET);
    int qq;
    qq = fread(&stud, sizeof(stud), 1, file);
    printf("%d. %s %s. \n   ������: %s. ����� �������������: %s. ���� ��������: %d.%d.%d \n", stud.id, stud.name, stud.fam, stud.group, stud.studnum, stud.data.day, stud.data.month, stud.data.year);

    printf("\n����� �������� �� ������ ��������?\n");
    printf("1 - ���, 2 - �������, 3 - ������, 4 - ����� �������������, 5 - ���� ��������\n");
    int input;
    scanf("%d", &input);
        switch (input) {
            case 1:
                printf("������� ����� ���\n");
                scanf("%s", &stud.name);
                break;
            case 2:
                printf("������� ����� �������\n");
                scanf("%s", &stud.fam);
                break;
            case 3:
                printf("������� ����� ������\n");
                scanf("%s", &stud.group);
                break;
            case 4:
                printf("������� ����� ����� �������������\n");
                scanf("%s", &stud.studnum);
                break;
            case 5:
                printf("������� ���� �������� �������� (������� ����� ������, ����. '11 12 1999')\n\n");
                scanf("%d%d%d", &stud.data.day,&stud.data.month,&stud.data.year);
                break;
        default:
            printf("������������ ����.\n" );
        }
    fseek(file, isize * (temp_id - 1), SEEK_SET);
    fwrite(&stud, sizeof(stud), 1, file);
    fseek(file, 0, SEEK_SET);
    fclose(file);
    printf("���������� ������� ��������.\n\n" );
    system("pause");
}
//4 - ������� ������ ���������
void pri(char *fname, int id) {
    diz();
    struct studinfo stud;
    FILE *file = NULL;
    file = fopen(fname, "r+b");
    rewind(file); //������� � ������ ������

    printf("                        ������ ��������� \n\n");
    int i = 1, qq;
    for (i; i <= id; i++){
        qq = fread(&stud, sizeof(stud), 1, file);
        printf("%d. %s %s. \n   ������: %s. ����� �������������: %s. ���� ��������: %d.%d.%d \n", stud.id, stud.name, stud.fam, stud.group, stud.studnum, stud.data.day, stud.data.month, stud.data.year);
    }

    fclose(file);
    system("pause");
}
//5 - ������� ������ ��������� �� �������
void fil(char *fname, int id) {
    diz();
    struct studinfo stud;
    FILE *file = NULL;
    file = fopen(fname, "r+b");
    rewind(file); //������� � ������ ������
    int input = 0;

    printf("�������:\n\n");
    printf("1 - ������� ��������� �� ������... \n");
    printf("2 - ������� ���������, �������� � ����... \n");
    printf("3 - ������� ���������, �������� � ������... \n");
    printf("4 - ������� ���������, ������ ... ���\n\n");

    printf("������� ����� ������� �������: ");

    scanf("%d", &input);
    if (input == 1){
        struct studinfo gro;
        printf("\n������� ������: ");
        scanf("%s", &gro.group);
        diz();
        printf("                        �������� �� ������ %s \n\n", gro.group);
        int i = 1, qq;
        for (i; i <= id; i++){
            qq = fread(&stud, sizeof(stud), 1, file);
            if (strcmp(stud.group, gro.group) == 0) {
                 printf("%d. %s %s. ����� �������������: %s. ���� ��������: %d.%d.%d \n", stud.id, stud.name, stud.fam, stud.studnum, stud.data.day, stud.data.month, stud.data.year);
            }
        }
    }
    else if (input == 2){
        int ye;
        printf("\n������� ���: ");
        scanf("%d", &ye);
        diz();
        printf("                        ��������, ��������� � %d ����\n\n", ye);
        int i = 1, qq;
        for (i; i <= id; i++){
            qq = fread(&stud, sizeof(stud), 1, file);
            if (stud.data.year == ye){
                 printf("%d. %s %s. \n ������: %s. ����� �������������: %s. ���� ��������: %d.%d.%d \n", stud.id, stud.name, stud.fam, stud.group, stud.studnum, stud.data.day, stud.data.month, stud.data.year);
            }
        }
    }
    else if (input == 3){
        int mo;
        printf("\n������� ����� (������): ");
        scanf("%d", &mo);
        diz();
        printf("                        ��������, ���Ĩ���� � ������ %d:\n\n", mo);
        int i = 1, qq;
        for (i; i <= id; i++){
            qq = fread(&stud, sizeof(stud), 1, file);
            if (stud.data.month == mo){
                 printf("%d. %s %s. \n ������: %s. ����� �������������: %s. ���� ��������: %d.%d.%d \n", stud.id, stud.name, stud.fam, stud.group, stud.studnum, stud.data.day, stud.data.month, stud.data.year);
            }
        }
    }
    else if (input == 4){
        time_t t;
        struct tm *ti;
        time(&t);
        ti = localtime(&t);
        int now_year = (ti->tm_year)+1900;
        int now_mon = (ti->tm_mon);

        int age;
        printf("\n������ ������� ��� ����� ���� ��������? ");
        scanf("%d", &age);
        diz();
        printf("                        �������� ������ %d ���\n", age);
        printf("                          (������� ���: %d)\n\n", now_year);
        int i = 1, qq;
        for (i; i <= id; i++){
            qq = fread(&stud, sizeof(stud), 1, file);
            if ((now_year - stud.data.year) > age) {
                 printf("%d. %s %s. \n ������: %s. ����� �������������: %s. ���� ��������: %d.%d.%d \n", stud.id, stud.name, stud.fam, stud.group, stud.studnum, stud.data.day, stud.data.month, stud.data.year);
            }
        }

    }
    else
        printf( "�������������� ������.\n" );

    fclose(file);
    system("pause");
}
//6 - ������� ���������������� ������ ���������
void sort(char *fname, int id) {
    diz();
    struct studinfo stud[N];
    struct studinfo temp;
    FILE *file = NULL;
    file = fopen(fname, "r+b");
    int input = 0;
    rewind(file); //������� � ������ ������

    printf("����������:\n\n");
    printf("1 - ���������� �� ���� ��������\n");
    printf("2 - ���������� �� �����\n\n");

    printf("������� ����� ������ ����������: ");

    int i, j, qq;
    for (i = 1; i <= id; i++){
        qq = fread(&stud[i], sizeof(stud), 1, file);
    }

    scanf("%d", &input);
    diz();
    if (input == 1){
        printf("              ������ ���������, ��������������� �� ���� ��������\n\n");
        for (i = 1; i <= (id - 1); i++){
            for (j = 1; j <= (id - 1); j++){
                if (stud[j].data.year > stud[j+1].data.year){
                    temp = stud[j];
                    stud[j] = stud[j+1];
                    stud[j+1] = temp;
                }
            }
        }
    }
    else if (input == 2){
        printf("              ������ ���������, ��������������� �� �����:\n\n");
        for (i = 1; i <= (id - 1); i++){
            for (j = 1; j <= (id - 1); j++){
                if (strcmp(stud[j].name,stud[j+1].name) > 0){
                    temp = stud[j];
                    stud[j] = stud[j+1];
                    stud[j+1] = temp;
                }
            }
        }
    }
    else
        printf( "�������������� ����������.\n" );


    for (i = 1; i <= id; i++){
        printf("%d. %s %s. \n   ������: %s. ����� �������������: %s. ���� ��������: %d.%d.%d \n", stud[i].id, stud[i].name, stud[i].fam, stud[i].group, stud[i].studnum, stud[i].data.day, stud[i].data.month, stud[i].data.year);
    }

    fclose(file);
    system("pause");
}
//7 - �������� � �������������
void razr() {
    diz();
    printf("������ ������ ��� �������� �����������\n");
    printf("�������� ������������ �������������� � ����������\n");
    printf("������������ �� ������������� 09.02.03 - \n���������������� � ������������ ��������\n");
    printf("� ������ �1-15\n");
    printf("���������� �.�. � ��������� �.�.\n\n");
    printf("�������� ������������ - ��������� �.�.\n");
    printf("������, 2017.\n\n");
    system("pause");
}

//������
void diz() {
    system("cls");
    system("color 3B");
}

