#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int x_line=105,y_line=30;
int host_x,host_y;
int food_x,food_y;
int tmp_x,tmp_y;
int point = 0;
int died = 0;
struct snake *head;

void snake_add(void);
void snake_del(void);
struct snake* creat_snake(void);

struct snake{
    int x;
    int y;
    struct snake *next;
};

void print_map (int x,int y)
{    
    int z,w;
    for(w=0;w <= y;w++)
    {
        printf("|");
        for(z=0;z <= x;z++)
        {  
            if(w == 0 || w == y) 
                printf("-");
            else if(w == food_y && z == food_x)
                printf("$");
            //else if(w == host_y && z == host_x)
            else if(host_local(z,w) == 1)
                printf("@");
            else
                printf(" ");

        }
        printf("|\n");
    }
}

int host_local(int x,int y)
{
    struct snake *now;

    now = head;
    while(now != NULL)
    {
        if(now->x == x && now->y == y)
            return 1;
        now=now->next;
    }
    return 0;
}    

void set_host(int x,int y)
{
    
    if( x > 0 && x < x_line)
        host_x = x;
    else if (x > x_line)
        host_x = 1;
    else if (x < 1)
        host_x = x_line - 1;

    if( y > 0 && y < y_line)
        host_y = y;
    else if (y > y_line )
        host_y = 1;
    else if (y < 1)
        host_y = y_line - 1;

    snake_add();

}

void snake_del(void)
{
    struct snake *now,*below;
    now = head;
    while(now != NULL)
    {
        if(now->next == NULL)
        {
            below->next = NULL;
            free(now->next);
            break;    
        }
        below=now;
        now=now->next;
    }
}

void snake_add(void)
{
    struct snake *new;
    new = creat_snake();
    new->x = host_x;
    new->y = host_y;
    new->next = head;
    head = new;
}

struct snake * creat_snake(void)
{
   struct snake *new = (struct snake*)malloc(sizeof(struct snake));
   
   new->x = 0;
   new->x = 0;
   new->next = NULL;

   return new;
}

void set_food(void)
{
    food_x=(rand()%(x_line-1)+1);
    food_y=(rand()%(y_line-1)+1);
}

void eating(void)
{
    if (host_x == food_x && host_y == food_y){
        set_food();
        point++;
    }else{
        snake_del();
    }
}

void delay(int x)
{
    do{
        volatile int count = x * 5000; 
        while (count--); 
    }while(0);
}

void go_ahead(void)
{
    int x = host_x - tmp_x;
    int y = host_y - tmp_y;

    if(x > 0 )
    { 
        if(y > 0)   
           host_y--;
        else if(y < 0) 
            host_y++;
        else if (y == 0)
            host_x--;
    } else if(x < 0 )
    { 
        if(y > 0)   
            host_y--;
        else if(y < 0) 
            host_y++;
        else if (y == 0)
            host_x++;
    }
}

void snake_died(void)
    {
    int try = 0;
    while(host_local(host_x,host_y) == 1)
    {
        if(host_x - head->x > 0){
            if (try == 0)
                tmp_x = 0;
            if (try == 1)
                tmp_x = 1000;
            if (try == 2)
                tmp_y = 0;
            if (try == 3)
                tmp_y = 10000;
        }else if(host_x - head->x < 0){
            if (try == 0)
                tmp_x = 0;
            if (try == 1)
                tmp_x = 1000;
            if (try == 2)
                tmp_y = 0;
            if (try == 3)
                tmp_y = 10000;
        }

        if(host_y - head->y > 0){
            if (try == 0)
                tmp_x = 0;
            if (try == 1)
                tmp_x = 1000;
            if (try == 2)
                tmp_y = 0;
            if (try == 3)
                tmp_y = 10000;
        }else if(host_y - head->y < 0){
            if (try == 0)
                tmp_x = 0;
            if (try == 1)
                tmp_x = 1000;
            if (try == 2)
                tmp_y = 0;
            if (try == 3)
                tmp_y = 10000;
        }
        if(try == 4){   
            died = 1;
            break;
        }
        host_x = head->x;
        host_y = head->y;

        try++;

        go_ahead();
    }
    }

    void main(void)
    {
        char input;
    head = creat_snake();
    set_host(x_line/2,y_line/2);
    head->x = host_x;
    head->y = host_y;
    set_food();
    print_map(x_line,y_line);
    srand(time(NULL));

    while(1)
    {
        printf("%d,%d,%p\t",head->x,head->y,head->next);
        printf("point : %d \t",point);
        printf("died : %d \t",died);
        printf("food : %d,%d\t",food_x,food_y);    
        //printf("head : %d,%d\t",head->x,head->y);    
        printf("host : %d,%d\n",host_x,host_y);    

        tmp_x = food_x;
        tmp_y = food_y;
        go_ahead();
        snake_died();
        
        if(!died)
        {    
            set_host(host_x,host_y);
            eating();
        }
        print_map(x_line,y_line);
        delay(3000);
        //sleep(1);
    }
}
