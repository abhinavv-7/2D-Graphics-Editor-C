#include <stdio.h>

#define ROWS 20
#define COLS 40

char canvas[ROWS][COLS];

void initCanvas()
{
    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < COLS; j++)
        {
            canvas[i][j] = '_';
        }
    }
}

void displayCanvas()
{
    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < COLS; j++)
        {
            printf("%c", canvas[i][j]);
        }
        printf("\n");
    }
}

void menu()
{
    printf("\n--- 2D Graphics Editor ---\n");
    printf("1. Display Canvas\n");
    printf("0. Exit\n");
}

int main()
{
    int choice;

    initCanvas();

    do
    {
        menu();
        printf("Enter choice: ");
        scanf("%d", &choice);

        if(choice == 1)
        {
            displayCanvas();
        }

    } while(choice != 0);

    return 0;
}
