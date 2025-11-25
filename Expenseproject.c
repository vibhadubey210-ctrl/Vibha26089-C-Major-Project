#include <stdio.h>
#include <string.h>
#define MAX 100
struct expenses 
{
    char date[20], group[100], description[200];
    int price;
};
struct expenses ex;
void addexpense();
void viewexpense();
void editexpense();
void delexpense();
void filterexpense();
void summary();
int main()
{
    int ch;
    while(1)
    {
        printf("\nEXPENSE TRACKER\n");
        printf("1. Add Expense\n");
        printf("2. View Expense\n");
        printf("3. Edit Expense\n");
        printf("4. Delete Expense\n");
        printf("5. Filter Expense\n");
        printf("6. Summary\n");
        printf("7. Exit\n");
        printf("Choice");
        scanf("%d",&ch);
        switch(ch)
        {
            case 1: addexpense(); break;
            case 2: viewexpense(); break;
            case 3: editexpense(); break;
            case 4: delexpense(); break;
            case 5: filterexpense(); break;
            case 6: summary(); break;
            case 7: printf("Exited\n"); return 0;
            default: printf("Invalid choice\n");
        }
    }
}
void addexpense()
{
    FILE *fp = fopen("expenses.txt","a");
    if (!fp)
    {
        printf("Error opening file\n");
        return;
    }
    printf("Enter date(DD/MM/YYYY), category, amount, description\n");
    scanf("%s %s %d %s", ex.date, ex.group, &ex.price, ex.description);
    fprintf(fp,"%s %s %d %s\n", ex.date, ex.group, ex.price, ex.description);
    fclose(fp);
    printf("Expense added\n");
}
void viewexpense()
{
    FILE *fp = fopen("expenses.txt","r");
    if (!fp)
    {
        printf("No expenses found\n");
        return;
    }
    printf("\nDate     Category    Amount   Description\n");
    while (fscanf(fp,"%s %s %d %s", ex.date, ex.group, &ex.price, ex.description)!=EOF)
    {
        printf("%s %s %d %s\n", ex.date, ex.group, ex.price, ex.description);
    }
    fclose(fp);
}
void editexpense()
{
    struct expenses arr[MAX];
    char search[100];
    int c=0, i, found=0;
    FILE *fp = fopen("expenses.txt","r");
    if (!fp)
    {
        printf("No expenses found\n");
        return;
    }
    while (fscanf(fp,"%s %s %d %s", ex.date, ex.group, &ex.price, ex.description)!=EOF)
    {
        arr[c++]=ex;
    }
    fclose(fp);
    printf("Enter category to edit");
    scanf("%s", search);
    for(i=0; i<c;i++)
    {
        if(strcmp(arr[i].group,search)==0)
        {
            found = 1;
            printf("New date");
            scanf("%s", arr[i].date);
            printf("New category");
            scanf("%s", arr[i].group);
            printf("New amount");
            scanf("%d", &arr[i].price);
            printf("New description");
            scanf("%s", arr[i].description);
            break;
        }
    }
    if (!found)
    {
        printf("Category not found\n");
        return;
    }
    fp=fopen("expenses.txt","w");
    for(i = 0; i < c; i++)
    {
        fprintf(fp,"%s %s %d %s\n", arr[i].date, arr[i].group, arr[i].price, arr[i].description);
    }
    fclose(fp);
    printf("Expense edited\n");
}
void delexpense()
{
    struct expenses arr[MAX];
    char search[20];
    int c=0, i, j, found=0;
    FILE *fp = fopen("expenses.txt","r");
    if (!fp)
    {
        printf("No expenses found\n");
        return;
    }
    while (fscanf(fp,"%s %s %d %s", ex.date, ex.group, &ex.price, ex.description) != EOF)
    {
        arr[c++] = ex;
    }
    fclose(fp);
    printf("Enter date to delete(DD/MM/YYYY)");
    scanf("%s", search);
    for(i=0; i<c; i++)
    {
        if(strcmp(arr[i].date, search) == 0)
        {
            for(j=i; j<c-1; j++)
            {
                arr[j] = arr[j+1];
            }
            c--;
            found = 1;
            i--;
        }
    }
    if (!found)
    {
        printf("No expense found\n");
        return;
    }
    fp = fopen("expenses.txt","w");
    for(i=0; i<c; i++)
    {
        fprintf(fp,"%s %s %d %s\n", arr[i].date, arr[i].group, arr[i].price, arr[i].description);
    }
    fclose(fp);
    printf("Expense deleted\n");
}
void filterexpense()
{
    FILE *fp = fopen("expenses.txt","r");
    char target[100];
    int found = 0;
    if (!fp)
    {
        printf("No expenses found\n");
        return;
    }
    printf("Enter category to filter");
    scanf("%s", target);
    printf("\nDate   Category   Amount   Description\n");
    while (fscanf(fp,"%s %s %d %s", ex.date, ex.group, &ex.price, ex.description) != EOF)
    {
        if(strcmp(ex.group,target) == 0)
        {
            printf("%s %s %d %s\n", ex.date, ex.group, ex.price, ex.description);
            found = 1;
        }
    }
    if(!found)
    {
        printf("No expenses in this category\n");
    }
    fclose(fp);
}
void summary()
{
    FILE *fp = fopen("expenses.txt","r");
    if (!fp)
    {
        printf("No expenses found\n");
        return;
    }
    float total = 0;
    while (fscanf(fp,"%s %s %d %s", ex.date, ex.group, &ex.price, ex.description) != EOF)
    {
        total = total+ ex.price;
    }
    printf("Total expenses: %.2f\n", total);
    fclose(fp);
} 