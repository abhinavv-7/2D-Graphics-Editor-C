#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ROWS 24
#define COLS 80
#define MAX 100

int shapeType[MAX];
int px1[MAX], py1[MAX];
int px2[MAX], py2[MAX];
int px3[MAX], py3[MAX];

int count = 0;

char canvas[ROWS][COLS];

// ---------------- CANVAS ----------------
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

// ---------------- DRAW LINE ----------------
// x = col, y = row
void drawLine(int ax1, int ay1, int ax2, int ay2)
{
    int dx = ax2 - ax1;
    int dy = ay2 - ay1;

    int steps = abs(dx);
    if(abs(dy) > steps) steps = abs(dy);
    if(steps == 0)
    {
        if(ay1 >= 0 && ay1 < ROWS && ax1 >= 0 && ax1 < COLS)
            canvas[ay1][ax1] = '*';
        return;
    }

    for(int i = 0; i <= steps; i++)
    {
        int c = ax1 + (dx * i) / steps;
        int r = ay1 + (dy * i) / steps;

        if(r >= 0 && r < ROWS && c >= 0 && c < COLS)
            canvas[r][c] = '*';
    }
}

// ---------------- DRAW RECTANGLE ----------------
void drawRectangle(int ax1, int ay1, int ax2, int ay2)
{
    for(int r = ay1; r <= ay2; r++)
        for(int c = ax1; c <= ax2; c++)
            if(r >= 0 && r < ROWS && c >= 0 && c < COLS)
                if(r == ay1 || r == ay2 || c == ax1 || c == ax2)
                    canvas[r][c] = '*';
}

// ---------------- DRAW TRIANGLE ----------------
void drawTriangle(int ax1, int ay1, int ax2, int ay2, int ax3, int ay3)
{
    drawLine(ax1, ay1, ax2, ay2);
    drawLine(ax2, ay2, ax3, ay3);
    drawLine(ax3, ay3, ax1, ay1);
}

// ---------------- DRAW CIRCLE (OUTLINE) ----------------
void drawCircle(int cx, int cy, int radius)
{
    for(int r = 0; r < ROWS; r++)
    {
        for(int c = 0; c < COLS; c++)
        {
            double dx = (c - cx) * 0.5;
            double dy = (r - cy);
            double dist = sqrt(dx*dx + dy*dy);

            if(fabs(dist - radius) < 0.6)
                canvas[r][c] = '*';

    }
}

// ---------------- RENDER ----------------
void render()
{
    createCanvas();

    for(int i = 0; i < count; i++)
    {
        if(shapeType[i] == 1)
            drawLine(px1[i], py1[i], px2[i], py2[i]);
        else if(shapeType[i] == 2)
            drawRectangle(px1[i], py1[i], px2[i], py2[i]);
        else if(shapeType[i] == 3)
            drawCircle(px1[i], py1[i], px2[i]);
        else if(shapeType[i] == 4)
            drawTriangle(px1[i], py1[i], px2[i], py2[i], px3[i], py3[i]);
    }
}

// ---------------- MENU ----------------
void menu()
{
    printf("\n2D Graphics Editor\n");
    printf("Canvas size: %d x %d\n", COLS, ROWS);
    printf("1. Add object\n");
    printf("2. Delete object\n");
    printf("3. Modify object\n");
    printf("4. Display picture\n");
    printf("5. List objects\n");
    printf("0. Exit\n");
    printf("Enter choice: \n");
}

// ---------------- MAIN LOOP ----------------
void runMenu()
{
    int choice;

    do
    {
        menu();
        fflush(stdout);
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
            {
                int t;
                printf("Choose shape type:\n");
                printf("1. Line\n");
                printf("2. Rectangle\n");
                printf("3. Circle\n");
                printf("4. Triangle\n");
                printf("Enter shape type: ");
                fflush(stdout);
                scanf("%d", &t);

                shapeType[count] = t;

                if(t == 1)
                {
                    printf("Enter x1 y1 x2 y2: ");
                    fflush(stdout);
                    scanf("%d %d %d %d",
                          &px1[count], &py1[count],
                          &px2[count], &py2[count]);
                }
                else if(t == 2)
                {
                    printf("Enter top-left x y and bottom-right x y: ");
                    fflush(stdout);
                    scanf("%d %d %d %d",
                          &px1[count], &py1[count],
                          &px2[count], &py2[count]);
                }
                else if(t == 3)
                {
                    printf("Enter center x y and radius: ");
                    fflush(stdout);
                    scanf("%d %d %d",
                          &px1[count], &py1[count], &px2[count]);
                }
                else if(t == 4)
                {
                    printf("Enter x1 y1 x2 y2 x3 y3: ");
                    fflush(stdout);
                    scanf("%d %d %d %d %d %d",
                          &px1[count], &py1[count],
                          &px2[count], &py2[count],
                          &px3[count], &py3[count]);
                }

                printf("Object added with index %d.\n", count);
                count++;
                render();
                break;
            }

            case 2:
            {
                int idx;
                printf("Enter index to delete: ");
                fflush(stdout);
                scanf("%d", &idx);
                if(idx >= 0 && idx < count)
                {
                    for(int i = idx; i < count - 1; i++)
                    {
                        shapeType[i] = shapeType[i+1];
                        px1[i] = px1[i+1]; py1[i] = py1[i+1];
                        px2[i] = px2[i+1]; py2[i] = py2[i+1];
                        px3[i] = px3[i+1]; py3[i] = py3[i+1];
                    }
                    count--;
                    render();
                    printf("Deleted.\n");
                }
                else
                    printf("Invalid index.\n");
                break;
            }

            case 3:
                printf("Modify not required.\n");
                break;

            case 4:
                render();
                displayCanvas();
                break;

            case 5:
                for(int i = 0; i < count; i++)
                    printf("Index %d Type %d\n", i, shapeType[i]);
                break;

            case 0:
                printf("Goodbye.\n");
                break;
        }

    } while(choice != 0);
}

// ---------------- MAIN ----------------
int main()
{
    createCanvas();
    runMenu();
    return 0;
}