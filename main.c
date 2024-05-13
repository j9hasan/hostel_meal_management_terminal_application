#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
int i, date, main_exit, checkdate, checkid;
float totalmeal = 0;
struct
{
    char name[60];
    int id;
    char department[60];
    double phone;
    float amd;
    float total_deposit;
    float total_bazar;
    float total_khala_bill;
    float total_current_bill;
    float total_fuel_bill;
    float total_paper_bill;
    float total_others;
    float meal;
    float totalmeal;
} add, upd, check, rem, calc, input;

void menu(void)
{
    int choice;
    system("color B");
    printf("\n\n\t\tMEAL MANAGEMENT SYSTEM\n");
    printf("\n\n\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2 WELCOME TO THE MAIN MENU \xB2\xB2\xB2\xB2\xB2\xB2\xB2\n\n\n");
    printf("\t1.add new member\n\t2.removing existing member\n\t3.view member's list\n\t4.daily meal input\n\t5.view meal by date\n\t6.view total meal for each member\n\t7.make meal report\n\t0.caution and about\n\n\n\tenter your choice:");
    scanf("%d", &choice);
    system("cls");
    switch (choice)
    {
    case 1:
        add_new_member();
        break;
    case 2:
        delete_member();
        break;
    case 3:
        view_member_list();
        break;
    case 4:
        meal_input();
        break;
    case 5:
        view_meal();
        break;
    case 6:
        total_meal_per_person();
        break;
    case 7:
        make_meal_report();
        break;
    case 0:
        printf("\n\n!!!!DO NOT DELETE A MEMBER BEFORE MEAL CALCULATION!!!!\nit causes incorrect calculation.\n\nFor any advice or query feel free to contact us\njubaid.eee07@gmail.com\nthank you\n\n\nDeveloped by jubaid(Team Lead),Redoy,Rahaman and Nahid\nDept. of EEE,JUST");
    add_invalid:
        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nEnter 1 to go to the main menu and 0 to exit:");
        scanf("%d", &main_exit);
        system("cls");
        if (main_exit == 1)
            menu();
        else if (main_exit == 0)
            close();
        else
        {
            printf("\nInvalid!\a");
            goto add_invalid;
        }

        break;

    default:
        menu();
        break;
    }
}
int main()
{
    system("color B");
    menu();
    return 0;
}

void add_new_member()
{
    float Totalmeal = 0;
    int choice;
    FILE *old;
    FILE *ptr;
    ptr = fopen("record.txt", "a+");
    old = fopen("total meal per person.txt", "a+");
id_no:
    system("cls");
    printf("\n\t\t\t\xB2\xB2\xB2\ ADD RECORD \xB2\xB2\xB2\n\n\n\n\n");
    printf("enter ID:\n");
    scanf("%d", &check.id);
    while (fscanf(ptr, "%d %s %s %lf %f", &add.id, add.name, add.department, &add.phone, &add.amd) != EOF)
    {
        if (check.id == add.id)
        {
            printf("ID already in use!!!\a");
            goto id_no;
        }
    }
    add.id = check.id;
    printf("enter name:");
    fflush(stdin);
    gets(add.name);
    printf("enter department:");
    fflush(stdin);
    gets(add.department);
    printf("enter phone no:");
    scanf("%lf", &add.phone);
    printf("enter deposit amount(tk):");
    scanf("%f", &add.amd);
    fprintf(ptr, "%-17d %-18s %-17s 0%-22.0lf %-8.2f\n", add.id, add.name, add.department, add.phone, add.amd);
    fprintf(old, "%8s %8d %4.2f\n", add.name, add.id, Totalmeal);
    printf("member added successfully:");
    fclose(ptr);
    fclose(old);
add_invalid:
    printf("\n\n\nEnter 1 to go to the main menu and 0 to exit:");
    scanf("%d", &main_exit);
    system("cls");
    if (main_exit == 1)
        menu();
    else if (main_exit == 0)
        close();
    else
    {
        printf("\nInvalid!\a");
        goto add_invalid;
    }
}
void delete_member()
{
    system("cls");
    int check, c = 0;
    float Totalmeal = 0;
    FILE *ptr, *old, *temp1, *temp2;
    ptr = fopen("record.txt", "r");
    temp1 = fopen("newrec1.txt", "w");
    old = fopen("total meal per person.txt", "r");
    temp2 = fopen("newrec2.txt", "w");
    printf("enter id to delete member:");
    scanf("%d", &check);
    while ((fscanf(ptr, "%d %s %s %lf %f", &add.id, add.name, add.department, &add.phone, &add.amd) != EOF) && (fscanf(old, "%s %d %f", &add.name, &add.id, &add.totalmeal) != EOF))
    {
        if (check != add.id)
        {
            fprintf(temp1, "%-17d %-18s %-17s 0%-22.0lf %-8.2f\n", add.id, add.name, add.department, add.phone, add.amd);
            fprintf(temp2, "%8s %8d %4.2f\n", add.name, add.id, Totalmeal);
        }
        else
        {
            c++;
            printf("member deleted successfully!!!");
        }
    }

    fclose(ptr);
    fclose(old);
    fclose(temp1);
    fclose(temp2);
    remove("record.txt");
    remove("total meal per person.txt");
    rename("newrec1.txt", "record.txt");
    rename("newrec2.txt", "total meal per person.txt");

    if (c == 0)
    {
        printf("member not found!!!");
    }

add_invalid:
    printf("\n\n\nEnter 1 to go to the main menu and 0 to exit:");
    scanf("%d", &main_exit);
    system("cls");
    if (main_exit == 1)
        menu();
    else if (main_exit == 0)
        close();
    else
    {
        printf("\nInvalid!\a");
        goto add_invalid;
    }
}
void view_member_list()
{
    int test = 0;
    FILE *ptr;
    ptr = fopen("record.txt", "r");
id_no:
    rewind(ptr);
    system("cls");
    printf("\nID.NO             NAME               DEPARTMENT        PHONE                   DEPOSIT\n");
    printf("---------------------------------------------------------------------------------------\n");
    while (fscanf(ptr, "%d %s %s %lf %f", &add.id, add.name, add.department, &add.phone, &add.amd) != EOF)
    {
        printf("%-17d %-18s %-17s 0%-22.0lf %-8.2f\n", add.id, add.name, add.department, add.phone, add.amd);
        test++;
    }
    printf("%d records found", test);
    fclose(ptr);
add_invalid:
    printf("\n\n\nEnter 1 to go to the main menu and 0 to exit:");
    scanf("%d", &main_exit);
    system("cls");
    if (main_exit == 1)
        menu();
    else if (main_exit == 0)
        close();
    else
    {
        printf("\nInvalid!\a");
        goto add_invalid;
    }
}

void meal_input()
{
    FILE *old, *newrec;
    FILE *ptr;
    FILE *cnt;
    old = fopen("total meal per person.txt", "r");
    newrec = fopen("temp.txt", "w");
    cnt = fopen("daily meal input.txt", "a+");
    ptr = fopen("record.txt", "r");
    system("cls");
    printf("Enter today's date(DD/MM/YYYY):");
    scanf("%d", &date);
    while ((fscanf(ptr, "%d %s %s %lf %f", &add.id, &add.name, &add.department, &add.phone, &add.amd) != EOF) && (fscanf(old, "%s %d %f", &add.name, &add.id, &add.totalmeal) != EOF))
    {
        printf("Enter meal for %s:", add.name);
        fflush(stdin);
        scanf("%f", &input.meal);
        add.totalmeal += input.meal;
        fprintf(newrec, "%8s %8d %4.2f\n", add.name, add.id, add.totalmeal);
        fprintf(cnt, "%-4d %8s %8d %4.2f\n", date, add.name, add.id, input.meal);
    }
    fclose(ptr);
    fclose(cnt);
    fclose(old);
    fclose(newrec);
    remove("total meal per person.txt");
    rename("temp.txt", "total meal per person.txt");
    printf("meal added succesfully!!!!");
add_invalid:
    printf("\n\n\nEnter 1 to go to the main menu and 0 to exit:");
    scanf("%d", &main_exit);
    system("cls");
    if (main_exit == 1)
        menu();
    else if (main_exit == 0)
        close();
    else
    {
        printf("\nInvalid!\a");
        goto add_invalid;
    }
}
void view_meal()
{
    FILE *cnt;

    cnt = fopen("daily meal input.txt", "r");
    while (fscanf(cnt, "%d %s %d %f", &date, &add.name, &add.id, &input.meal) != EOF)

    {
        printf("%d/09/2018\t%-10s %-8d %.2f\n", date, add.name, add.id, input.meal);
    }

    fclose(cnt);
add_invalid:
    printf("\n\n\nEnter 1 to go to the main menu and 0 to exit:");
    scanf("%d", &main_exit);
    system("cls");
    if (main_exit == 1)
        menu();
    else if (main_exit == 0)
        close();
    else
    {
        printf("\nInvalid!\a");
        goto add_invalid;
    }
}

void total_meal_per_person()
{
    FILE *old;
    old = fopen("total meal per person.txt", "r");
    while (fscanf(old, "%s %d %f", &add.name, &add.id, &add.totalmeal) != EOF)

    {
        printf("total meal of %-8s %4.2f\n", add.name, add.totalmeal);
    }
    fclose(old);
add_invalid:
    printf("\n\n\nEnter 1 to go to the main menu and 0 to exit:");
    scanf("%d", &main_exit);
    system("cls");
    if (main_exit == 1)
        menu();
    else if (main_exit == 0)
        close();
    else
    {
        printf("\nInvalid!\a");
        goto add_invalid;
    }
}

void make_meal_report()
{
    system("cls");
    float totalmeal = 0, mealrate = 0, othercost;
    FILE *ptr, *cnt, *old;
    ptr = fopen("record.txt", "r");
    // calculation of total deposit
    while (fscanf(ptr, "%d %s %s %lf %f", &add.id, &add.name, &add.department, &add.phone, &add.amd) != EOF)
    {
        calc.total_deposit = calc.total_deposit + add.amd;
    }
    fclose(ptr);
    // calculation of total meal
    cnt = fopen("daily meal input.txt", "r");
    while (fscanf(cnt, "%d %s %d %f", &date, &add.name, &add.id, &input.meal) != EOF)

    {
        totalmeal += input.meal;
    }
    fclose(cnt);
    // calculation of total member
    int test = 0;
    ptr = fopen("record.txt", "r");
    while (fscanf(ptr, "%d %s %s %lf %f", &add.id, &add.name, &add.department, &add.phone, &add.amd) != EOF)
    {
        test++;
    }
    fclose(ptr);
    printf("enter total bazar cost:");
    scanf("%f", &calc.total_bazar);
    printf("khala bill:");
    scanf("%f", &calc.total_khala_bill);
    printf("total current bill:");
    scanf("%f", &calc.total_current_bill);
    printf("total fuel bill:");
    scanf("%f", &calc.total_fuel_bill);
    printf("total paper bill:");
    scanf("%f", &calc.total_paper_bill);

    // calculation of mealrate
    mealrate = (calc.total_bazar + calc.total_fuel_bill) / totalmeal;
    // calculation of other cost
    othercost = (calc.total_current_bill + calc.total_paper_bill) / test;
    // final report
    ptr = fopen("record.txt", "r");
    old = fopen("total meal per person.txt", "r");
    printf("\n\n\n\t\t\t\t\t\t\t\t\tFINAL MEAL REPORT\n\n\n");
    printf("\tNAME\tTOTAL MEAL\tTOTAL MEAL COST(tk)\tKHALA BILL(tk)\tOTHER COST(tk)\tTOTAL COST(tk)\tDEPOSIT MONEY(tk)\tAMOUNT PAYABLE/RECEIVABLE(tk)\n");
    printf("\t-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
    while ((fscanf(ptr, "%d %s %s %lf %f", &add.id, &add.name, &add.department, &add.phone, &add.amd) != EOF) && (fscanf(old, "%s %d %f", &add.name, &add.id, &add.totalmeal) != EOF))

    {
        printf("\t%-10s %-18.2f %-20.2f %-15.2f %-15.2f %-15.2f %-30.2f %-.2f\n", add.name, add.totalmeal, (add.totalmeal * mealrate), calc.total_khala_bill, othercost, ((add.totalmeal * mealrate) + calc.total_khala_bill + othercost), add.amd, add.amd - ((add.totalmeal * mealrate) + calc.total_khala_bill + othercost));
    }
    fclose(ptr);
    printf("\n\n\n\tTotal diposit %8.1f tk\n", calc.total_deposit);
    printf("\ttotal meal %.2f\n", totalmeal);
    printf("\tmeal rate %.2f tk\n", mealrate);

add_invalid:
    printf("\n\n\nEnter 1 to go to the main menu and 0 to exit:");
    scanf("%d", &main_exit);
    system("cls");
    if (main_exit == 1)
        menu();
    else if (main_exit == 0)
        close();
    else
    {
        printf("\nInvalid!\a");
        goto add_invalid;
    }
}
