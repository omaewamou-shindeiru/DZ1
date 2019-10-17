#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <locale.h>

typedef struct // создание структуры множества
{
    char * word;
    struct set *next;
} Element;

int compareStr(char s1[],char s2[]) // сравнение элементов
{
    int i = 0;
    while(s1[i] != '\0')            // пока не дойдём до конца элемента
    {
        if(s1[i] != s2[i])          // сравниваем его со вторым
        return 0;                   // возвращаем "0", если элементы разные
        i++;
    }
    i = 0;
    while(s2[i] != '\0')            // выполняем сравнение второй раз,
    {                               // так как один элемент может быть короче другого и не до конца сравниться
        if(s1[i] != s2[i])
        return 0;
        i++;
    }
    return 1;                       //если элементы одинаковы
}

char * enterstr()                   // ввод нового элемента
{
    int i=0;
    char c, str[100];
    while((c = getchar()) != '\n')      // заполнение элемента посимвольно до перехода на новую строку
    {
        str[i] = c;
        i++;
    }
    str[i] = '\0';
    for(i = 0 ; str[i] != '\0'; i++);
    char *prev = malloc(i*sizeof(char));
    for (int j = 0; j <= i; j++)
    prev[j] = str[j];
    return prev;
}

int searchSet(Element **set, char *str) // поиск элемента по его содержанию,
    {
    Element *tmp = (*set);
    int i = 0;
    while(tmp != NULL)
    {
        i++;
        if(compareStr(tmp -> word, str)) // если элемент одинаков с искомым, то возвращается его порядковый номер
        return i;
        tmp = tmp -> next;
    }
    return 0; // возвращает "0", если элементов не найдено
    }

void pushSet(Element **set) //вставка нового элемента
{
    Element *tmp = malloc(sizeof(set));
    char *str = enterstr(); // ввод нового элемента
    if(searchSet(set, str) == 0) // если новый элемент не входит во множество, то он вставляется в него
    {
        tmp -> word = str;
        tmp -> next = (*set);
        (*set) = tmp;
    }
    else printf("Such an element exists\n"); // в противном случае, этого не происходит
}

void printSet(Element **set) // вывод всех элементов множества последовательно
{
    Element *tmp = (*set);
    while(tmp != NULL)
    {
        printf("%s\n", tmp -> word);
        tmp = tmp -> next;
    }
}

void deleteSet(Element **set) // удаление элемента по содержанию
{
    char *str = enterstr();
    Element *tmp = (*set);
    if(tmp == NULL)
    {
        printf("Empty set \n");
        return;
    }
    int c = searchSet(set, str);
    if(c == 0)
    {
        printf("No matches found \n");
        return;
    }
    if(c == 1)
    {
        (*set) = tmp -> next;
        free(tmp);
        return;
    }
    for(int i = 1; i < c-1; i++)
    tmp = tmp -> next;
    Element *prev = tmp -> next;
    tmp -> next = prev -> next;
    free(prev);
}

int main()
{
    int menu,i;
    Element *set1=NULL,*set2=NULL;
    printf("\n-Create the first set-\n");
    while (1)
    {
        printf("Enter element: ");
        pushSet(&set1);
        printf("Continue?\n1-Yes\\2-No\n");
        scanf("%d",&i);
        getchar();
        if(i!=1)
        break;
    }
    printf("\n-Create the second set-\n");
    while (1)
    {
        printf("Enter element: ");
        pushSet(&set2);
        printf("Continue?\n1-Yes\\2-No\n");
        scanf("%d",&i);
        getchar();
        if(i!=1)
        break;
    }
    while(1)
    {
        i=0;
        printf("\n-Menu-\n1-First set\n2-Second set\n3-Exit\nEnter number: ");
        scanf("%d",&menu);
        switch(menu)        // menu передаёт номер множества
        {
            case 1:i=1;break;
            case 2:i=2;break;
            case 3:return 0;break;
            default: printf("Invalid number\n");
        }
        while(i!=0)
        {
            printf("\n-Menu %d set-\n1-Print elements of the set\n2-Add element of the set\n3-Delete element of the set\n4-Back\nEnter number: ",i);
            scanf("%d",&menu);
            getchar();
            switch(menu)
            {
                case 1:
                printf("\n-Print-\n");
                if(i==1)
                printSet(&set1);
                else printSet(&set2);
                break;
                case 2:
                printf("\n-Add-\nEnter element: ");
                if(i==1)
                pushSet(&set1);
                else pushSet(&set2);
                break;
                case 3:
                printf("\n-Remove-\nEnter element: ");
                if(i==1)
                deleteSet(&set1);
                else deleteSet(&set2);
                break;
                case 4: i=0;break;
                default: printf("Invalid number\n");
            }
        }
    }
    return 0;
}
