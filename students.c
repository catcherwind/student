#include <stdio.h>
#include <Windows.h> //русский для Consolas
#include <string.h> // строки
#include <time.h> // определение текущей даты



#define N 25 //максимальная длина строки

struct date{
    int day; //ДЕНЬ рождения
    int month; //МЕСЯЦ рождения
    int year; //ГОД рождения
};
struct studinfo{
    int id; //номер студента в базе
    char fam[N]; //фамилия
    char name[N]; //имя
    char group[N]; //группа
    char studnum[N]; //номер студенческого
    struct date data; //ДАТА рождения
};
//объявление функций
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
    SetConsoleCP(1251); //подключение РЯ для корректного ввода
    SetConsoleOutputCP(1251); //и вывода

    int id; //количество элементов в файле.
    diz(); //здесь и далее - дизайн
    printf("                        ДОБРО ПОЖАЛОВАТЬ!\n\n");
    //Определение имени файла
    printf("Для работы с базой данных ");
    printf("введите её название (имя файла) с расширением .bin\n");
    char fname[N];
    scanf("%s", &fname);
    //Проверка существования/правильности имени файла
    int ot = 0; //Переменная для проверки, точно ли имя файла введено верно
    FILE *file = NULL;
    while (ot != 1){
        if((file = fopen(fname, "rb")) == NULL) {
            fclose(file);
            printf("Данного файла не существует. Создать файл? 1 - да, 2 - нет\n");
            scanf("%d", &ot);
            if (ot == 1) {
                printf("Файл создан.\n\n");
                file = fopen(fname, "wb");
                ot = 1;
                id = 0;
                fclose(file);
            }
            else {
                printf("Введите верное имя файла с расширением .bin \n");
                scanf("%s", &fname);
            }
        }
        else {
            printf("Файл найден.\n\n");
            fclose(file);
            FILE *lastID = NULL; //lastID - файл, хранящий только кол-во переменных
            lastID = fopen("lastID.bin", "r+b"); //Считывание кол-ва переменных в базе
            fread(&id, sizeof(int), 1, lastID);
            fclose(lastID);
            ot = 1;
        }
    }

    system("pause");
    diz();
    //ОСНОВНАЯ ЧАСТЬ!!
    int input = -1;
    while (input) {
        diz();

        printf("                        МЕНЮ\n\n");
        printf("1 - Добавить студента \n");
        printf("2 - Удалить студента \n");
        printf("3 - Изменить данные о студенте  \n");
        printf("4 - Вывести список студентов \n");
        printf("5 - Вывести список студентов по фильтру \n");
        printf("6 - Вывести отсортированный список студентов\n");
        printf("7 - Сведения о разработчиках\n");
        printf("0 - Выход \n\n");
        printf("Введите номер выполняемого действия: ");
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
                printf("                        Завершение работы. До свидания!\n\n" );
                break;
        default:
            printf( "Неправильный ввод.\n" );
            system("pause");
        }
    }
    return 0;
}

//1 - Добавить студента
int zap(char *fname, int id) {
    diz();
    struct studinfo stud;
    FILE *file = NULL;
    file = fopen(fname, "r+b");
    id++;
    stud.id = id;
    int isize = sizeof(stud);
    fseek(file, isize * (id - 1), SEEK_SET);
    printf("                        ДОБАВЛЕНИЕ СТУДЕНТА\n\n");
    printf("Введите имя\n");
    scanf("%s", &stud.name);
    printf("Введите фамилию\n");
    scanf("%s", &stud.fam);
    printf("Введите группу\n");
    scanf("%s", &stud.group);
    printf("Введите номер студенческого\n");
    scanf("%s", &stud.studnum);
    printf("Введите дату рождения студента (цифрами через пробел, напр. '21 12 1999')\n");
    scanf("%d%d%d", &stud.data.day, &stud.data.month, &stud.data.year);
    fwrite(&stud, sizeof(stud), 1, file);

    fclose(file);
    FILE *lastID = NULL;
    lastID = fopen("lastID.bin", "wb");
    fwrite(&stud.id, sizeof(int), 1, lastID);
    fclose(lastID);

    printf("\n");
    printf("Студент добавлен!\n\n");
    system("pause");
    return id;
}
//2 - Удаление студента
int del(char *fname, int id) {
    struct studinfo stud;
    FILE *file = NULL;
    file = fopen(fname, "r+b");

    printf("\nВведите номер студента, которого необходимо удалить: ");
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
//3 - Изменить данные о студенте
void chan(char *fname) {
    struct studinfo stud;
    FILE *file = NULL;
    file = fopen(fname, "r+b");

    printf("\nВведите номер студента, информация о котором будет изменена: ");
    int temp_id;
    scanf("%d", &temp_id);
    diz();
    printf("                        ИЗМЕНЕНИЕ ИНФОРМАЦИИ О СТУДЕНТЕ № %d\n\n", temp_id);

    int isize = sizeof(stud);
    fseek(file, isize * (temp_id - 1), SEEK_SET);
    int qq;
    qq = fread(&stud, sizeof(stud), 1, file);
    printf("%d. %s %s. \n   Группа: %s. Номер студенческого: %s. Дата рождения: %d.%d.%d \n", stud.id, stud.name, stud.fam, stud.group, stud.studnum, stud.data.day, stud.data.month, stud.data.year);

    printf("\nКакой параметр вы хотите изменить?\n");
    printf("1 - Имя, 2 - Фамилия, 3 - Группа, 4 - Номер студенческого, 5 - дата рождения\n");
    int input;
    scanf("%d", &input);
        switch (input) {
            case 1:
                printf("Введите новое имя\n");
                scanf("%s", &stud.name);
                break;
            case 2:
                printf("Введите новую фамилию\n");
                scanf("%s", &stud.fam);
                break;
            case 3:
                printf("Введите новую группу\n");
                scanf("%s", &stud.group);
                break;
            case 4:
                printf("Введите новый номер студенческого\n");
                scanf("%s", &stud.studnum);
                break;
            case 5:
                printf("Введите дату рождения студента (цифрами через пробел, напр. '11 12 1999')\n\n");
                scanf("%d%d%d", &stud.data.day,&stud.data.month,&stud.data.year);
                break;
        default:
            printf("Неправильный ввод.\n" );
        }
    fseek(file, isize * (temp_id - 1), SEEK_SET);
    fwrite(&stud, sizeof(stud), 1, file);
    fseek(file, 0, SEEK_SET);
    fclose(file);
    printf("Информация успешно изменена.\n\n" );
    system("pause");
}
//4 - Вывести список студентов
void pri(char *fname, int id) {
    diz();
    struct studinfo stud;
    FILE *file = NULL;
    file = fopen(fname, "r+b");
    rewind(file); //Переход в начало строки

    printf("                        СПИСОК СТУДЕНТОВ \n\n");
    int i = 1, qq;
    for (i; i <= id; i++){
        qq = fread(&stud, sizeof(stud), 1, file);
        printf("%d. %s %s. \n   Группа: %s. Номер студенческого: %s. Дата рождения: %d.%d.%d \n", stud.id, stud.name, stud.fam, stud.group, stud.studnum, stud.data.day, stud.data.month, stud.data.year);
    }

    fclose(file);
    system("pause");
}
//5 - Вывести список студентов по фильтру
void fil(char *fname, int id) {
    diz();
    struct studinfo stud;
    FILE *file = NULL;
    file = fopen(fname, "r+b");
    rewind(file); //Переход в начало строки
    int input = 0;

    printf("ФИЛЬТРЫ:\n\n");
    printf("1 - Вывести студентов из группы... \n");
    printf("2 - Вывести студентов, рождённых в году... \n");
    printf("3 - Вывести студентов, рождённых в месяце... \n");
    printf("4 - Вывести студентов, старше ... лет\n\n");

    printf("Введите номер нужного фильтра: ");

    scanf("%d", &input);
    if (input == 1){
        struct studinfo gro;
        printf("\nВведите группу: ");
        scanf("%s", &gro.group);
        diz();
        printf("                        СТУДЕНТЫ ИЗ ГРУППЫ %s \n\n", gro.group);
        int i = 1, qq;
        for (i; i <= id; i++){
            qq = fread(&stud, sizeof(stud), 1, file);
            if (strcmp(stud.group, gro.group) == 0) {
                 printf("%d. %s %s. Номер студенческого: %s. Дата рождения: %d.%d.%d \n", stud.id, stud.name, stud.fam, stud.studnum, stud.data.day, stud.data.month, stud.data.year);
            }
        }
    }
    else if (input == 2){
        int ye;
        printf("\nВведите год: ");
        scanf("%d", &ye);
        diz();
        printf("                        СТУДЕНТЫ, РОЖДЕННЫЕ В %d ГОДУ\n\n", ye);
        int i = 1, qq;
        for (i; i <= id; i++){
            qq = fread(&stud, sizeof(stud), 1, file);
            if (stud.data.year == ye){
                 printf("%d. %s %s. \n Группа: %s. Номер студенческого: %s. Дата рождения: %d.%d.%d \n", stud.id, stud.name, stud.fam, stud.group, stud.studnum, stud.data.day, stud.data.month, stud.data.year);
            }
        }
    }
    else if (input == 3){
        int mo;
        printf("\nВведите месяц (цифрой): ");
        scanf("%d", &mo);
        diz();
        printf("                        СТУДЕНТЫ, РОЖДЁННЫЕ В МЕСЯЦЕ %d:\n\n", mo);
        int i = 1, qq;
        for (i; i <= id; i++){
            qq = fread(&stud, sizeof(stud), 1, file);
            if (stud.data.month == mo){
                 printf("%d. %s %s. \n Группа: %s. Номер студенческого: %s. Дата рождения: %d.%d.%d \n", stud.id, stud.name, stud.fam, stud.group, stud.studnum, stud.data.day, stud.data.month, stud.data.year);
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
        printf("\nСтарше скольки лет должы быть студенты? ");
        scanf("%d", &age);
        diz();
        printf("                        СТУДЕНТЫ СТАРШЕ %d ЛЕТ\n", age);
        printf("                          (Текущий год: %d)\n\n", now_year);
        int i = 1, qq;
        for (i; i <= id; i++){
            qq = fread(&stud, sizeof(stud), 1, file);
            if ((now_year - stud.data.year) > age) {
                 printf("%d. %s %s. \n Группа: %s. Номер студенческого: %s. Дата рождения: %d.%d.%d \n", stud.id, stud.name, stud.fam, stud.group, stud.studnum, stud.data.day, stud.data.month, stud.data.year);
            }
        }

    }
    else
        printf( "Несуществующий фильтр.\n" );

    fclose(file);
    system("pause");
}
//6 - Вывести отстортированный список студентов
void sort(char *fname, int id) {
    diz();
    struct studinfo stud[N];
    struct studinfo temp;
    FILE *file = NULL;
    file = fopen(fname, "r+b");
    int input = 0;
    rewind(file); //Переход в начало строки

    printf("СОРТИРОВКИ:\n\n");
    printf("1 - Сортировка по году рождения\n");
    printf("2 - Сортировка по имени\n\n");

    printf("Введите номер нужной сортировки: ");

    int i, j, qq;
    for (i = 1; i <= id; i++){
        qq = fread(&stud[i], sizeof(stud), 1, file);
    }

    scanf("%d", &input);
    diz();
    if (input == 1){
        printf("              СПИСОК СТУДЕНТОВ, ОТСТОРИРОВАННЫЙ ПО ГОДУ РОЖДЕНИЯ\n\n");
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
        printf("              СПИСОК СТУДЕНТОВ, ОТСТОРИРОВАННЫЙ ПО ИМЕНИ:\n\n");
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
        printf( "Несуществующая сортировка.\n" );


    for (i = 1; i <= id; i++){
        printf("%d. %s %s. \n   Группа: %s. Номер студенческого: %s. Дата рождения: %d.%d.%d \n", stud[i].id, stud[i].name, stud[i].fam, stud[i].group, stud[i].studnum, stud[i].data.day, stud[i].data.month, stud[i].data.year);
    }

    fclose(file);
    system("pause");
}
//7 - Сведения о разработчиках
void razr() {
    diz();
    printf("Данный проект был выполнен студентками\n");
    printf("Колледжа Космического Машиностроения и Технологий\n");
    printf("Обучающимися по специальности 09.02.03 - \nПрограммирование в компьютерных системах\n");
    printf("В группе П1-15\n");
    printf("Лемешкиной К.А. и Романовой Е.В.\n\n");
    printf("Классный руководитель - Гусятинер Л.Б.\n");
    printf("Королёв, 2017.\n\n");
    system("pause");
}

//Дизайн
void diz() {
    system("cls");
    system("color 3B");
}

