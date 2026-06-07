#include <stdio.h>

#define ROWS 20
#define COLS 40

char canvas[ROWS][COLS];

void createCanvas()
{
    for(int i = 0; i < ROWS; i++)
        for(int j = 0; j < COLS; j++)
            canvas[i][j] = '_';
}

void displayCanvas()
{
    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < COLS; j++)
            printf("%c", canvas[i][j]);
        printf("\n");
    }
}
void drawRectangle(int r1, int c1, int r2, int c2)
{
    for(int i = r1; i <= r2; i++)
    {
        for(int j = c1; j <= c2; j++)
        {
            if(i == r1 || i == r2 || j == c1 || j == c2)
                canvas[i][j] = '*';
        }
    }
}

void menu()
{
    printf("\n--- 2D Graphics Editor ---\n");
    printf("1. Display Canvas\n");
    printf("2. Draw Rectangle\n");
    printf("0. Exit\n");
}

void runMenu()
{
    int choice;

    do
    {
        menu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                displayCanvas();
                break;

            case 2:
            {
                int x, y, w, h;

                printf("Enter Rectangle (x y width height): ");
                scanf("%d %d %d %d", &x, &y, &w, &h);

                drawRectangle(x, y, x + h - 1, y + w - 1);
                printf("Rectangle drawn!\n");
                break;
            }

            case 0:
                printf("Exiting program...\n");
                break;

            default:
                printf("Invalid choice\n");
        }

    } while(choice != 0);
}


int main()
{
    createCanvas();
    runMenu();
    return 0;
}