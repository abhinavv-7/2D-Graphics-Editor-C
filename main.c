#include <stdio.h>
#include <stdlib.h>
#define ROWS 25
#define COLS 80

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
void drawLine(int r1, int c1, int r2, int c2)
{
    int dx = c2 - c1;
    int dy = r2 - r1;

    int steps = abs(dx);

    if(abs(dy) > steps)
        steps = abs(dy);

    for(int i = 0; i <= steps; i++)
    {
        int r = r1 + (dy * i) / steps;
        int c = c1 + (dx * i) / steps;

        if(r >= 0 && r < ROWS && c >= 0 && c < COLS)
            canvas[r][c] = '*';
    }
}
void drawTriangle(int r1, int c1,
                  int r2, int c2,
                  int r3, int c3)
{
    drawLine(r1, c1, r2, c2);
    drawLine(r2, c2, r3, c3);
    drawLine(r3, c3, r1, c1);
}
void drawCircle(int centerRow, int centerCol, int radius)
{
    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < COLS; j++)
        {
            int d = (i - centerRow) * (i - centerRow)
                  + (j - centerCol) * (j - centerCol);

            if(d >= radius * radius - radius &&
               d <= radius * radius + radius)
            {
                canvas[i][j] = '*';
            }
        }
    }
}
void menu()
{
    printf("\n--- 2D Graphics Editor ---\n");
    printf("1. Display Canvas\n");
    printf("2. Draw Rectangle\n");
    printf("3. Draw Line\n");
    printf("4. Draw Triangle\n");
    printf("5. Draw Circle\n");
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
            case 3:
            {
            int r1, c1, r2, c2;

             printf("Line (row1 col1 row2 col2): ");
             scanf("%d %d %d %d", &r1, &c1, &r2, &c2);

            drawLine(r1, c1, r2, c2);

            printf("Line drawn!\n");
            break;
            }
            case 4:
            {
             int r1, c1, r2, c2, r3, c3;

            printf("Enter row1 col1 row2 col2 row3 col3: ");
            scanf("%d %d %d %d %d %d",
            &r1, &c1, &r2, &c2, &r3, &c3);

            drawTriangle(r1, c1, r2, c2, r3, c3);

             printf("Triangle drawn!\n");
             break;
             }
             case 5:
           {
            int row, col, radius;

             printf("Enter center row center col radius: ");
            scanf("%d %d %d", &row, &col, &radius);

            drawCircle(row, col, radius);

            printf("Circle drawn!\n");
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