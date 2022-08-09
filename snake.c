/*
 *            DO YOU WHAT THE WANT TO PUBLIC LICENSE
 *
 * Everyone is permitted to copy and distribute verbatim or modified
 * copies of this license document, and changing it is allowed as long
 * as the name is changed.
 *
 *           DO YOU WHAT THE WANT TO PUBLIC LICENSE
 *  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
 *
 * 0. You just DO WHAT YOU WANT TO DO.
 */

#include <stdbool.h>
#include <SDL.h>
#include <SDL_timer.h>

/* 长宽比例 */
#define WIDTH_BLOCK_COUNT 50
#define HIGHT_BLOCK_COUNT 40

/* 尺寸大小 */
#define BLOCK_SIZE 20

/* 窗体尺寸 */
#define WIN_WIDTH (BLOCK_SIZE * WIDTH_BLOCK_COUNT)
#define WIN_HIGHT (BLOCK_SIZE * HIGHT_BLOCK_COUNT)

/* 固定刷新时间 */
#define FIXED_TIME 60

/* 蛇的方向 */
enum snake_dir
{
    DIR_DOWN,
    DIR_LEFT,
    DIR_RIGHT,
    DIR_UP
};

/* 当前方向 */
unsigned dir;

/* 
 *实体位置坐标 
 */

/* 蛇身实体(单一个体) */
typedef struct snk_body_entity
{
    /* 坐标 */
    int x;
    int y;

    /* 下一节身体 */
    struct snk_body_entity *next_body;

}snk_body_entity;

/* 食物实体 */
typedef struct food_entity
{
    /* 食物坐标 */
    int x;
    int y;

}food_entity;

/* 食物 */
food_entity *food = NULL;

/* 蛇头 */
snk_body_entity *snk_head = NULL;

/* 蛇体 */
snk_body_entity *snk_body = NULL;

/* 蛇体长度 */
unsigned snk_lenth;

/* 分数 */
unsigned score;

/* 绘制场景 */
void draw_scnen(SDL_Renderer *renderer);
/* 初始化实体 */
void init_entity(void);
/* 蛇体移动 */
void snake_move(void);
/* 吃食物事件 */
void snake_eat_food(void);

/* main函数 */
int main(int argc, char const *argv[])
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    /* 记录初始化后时间 */
    Uint32 timer;

    /* SDL 初始化 */
    SDL_Init(SDL_INIT_VIDEO);

    /* 创建窗体 */
    window = SDL_CreateWindow(
        "greedy snake",
        100, 100, 
        WIN_WIDTH, WIN_HIGHT, 
        SDL_WINDOW_SHOWN);

        /* 创建渲染器 */
    renderer = SDL_CreateRenderer(
        window, 
        -1, 
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    
    /* 获取初始化后的一次时间 */
    timer = SDL_GetTicks();

    init_entity();

    /* Main Loop */
    bool quit = false;
    SDL_Event event;
    while (!quit) 
    {
        while (SDL_PollEvent(&event)) 
        {
            switch (event.type)
            {
                /* 得到按下键盘 */
                #define KEY event.key.keysym.sym
                /* 键盘按键按下检测 */
                case SDL_KEYDOWN:
                    if (KEY == SDLK_w && dir != 0)
                    {
                        dir = 3;
                    }
                    else if (KEY == SDLK_s && dir != 3)
                    {
                        dir = 0;
                    }
                    else if (KEY == SDLK_a && dir != 2)
                    {
                        dir = 1;
                    }
                    else if (KEY == SDLK_d && dir != 1)
                    {
                        dir = 2;
                    }
                    
                    /* 取消定义 */
                    #undef KEY
                    break;

                /* 退出 */
                case SDL_QUIT:
                    quit = true;
    
                default:
                    break;
                }
        }
        /* 判断现在距离上次过了多久 */
        if (SDL_GetTicks() - timer > FIXED_TIME)/* 如果超过了 */
        {
            draw_scnen(renderer);
            snake_move();
            snake_eat_food();
            /* 重新计时 */
            timer = SDL_GetTicks();
        }
    }

    // 蛇和食物就不free了反正就这么用到程序结束(doge)
    
    /* SDL 清理 */
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}

void draw_scnen(SDL_Renderer *renderer)
{
    /*
     * 绘制背景
     */

    /* 背景颜色 */
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    /* 清屏 */
    SDL_RenderClear(renderer);
    
    /*
     * 绘制蛇
     */

    snk_body_entity *body = snk_head;

    for (int i = 0; i < snk_lenth; i++)
    {
        SDL_Rect rect = {body->x * BLOCK_SIZE, body->y * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE};
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        SDL_RenderDrawRect(renderer, &rect);
        /* 填充 */
        SDL_RenderFillRect(renderer, &rect);
        body = body->next_body;
    }

    /* 
     * 绘制食物
     */
    
    SDL_Rect rect = {food->x * BLOCK_SIZE, food->y * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE};
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &rect);
    /* 填充 */
    SDL_RenderFillRect(renderer, &rect);

    /* 显示 */
    SDL_RenderPresent(renderer);
}

void init_entity(void)
{
    /* 
     *初始化蛇体 
     */
    snk_lenth = 4;
    /* 方向 */
    dir = rand()%4;
    /* 分数 */
    score = 0;

    /* 当前开辟的位置 */
    snk_body_entity *temp;

    /* 初始化身体 */
    for (int i = 0; i < snk_lenth; i++)
    {
        temp = malloc(sizeof(snk_body_entity));
        /* 头部未初始化 */
        if (snk_head == NULL)
        {
            /* 蛇头初始化 */
            snk_head = temp;
            snk_head->x = rand() % WIDTH_BLOCK_COUNT;
            snk_head->y = rand() % HIGHT_BLOCK_COUNT;
        }
        else
        {
            /* 身体初始化 */
            snk_body->next_body = temp;
        }

        /* 给其赋值 */
        temp->next_body = NULL;

        temp->x = snk_head->x;
        temp->y = snk_head->y;

        /* 准备下一个 */
        snk_body = temp;
    }

    /* 
     * 初始化食物
     */

    food = malloc(sizeof(food_entity));

    food->x = rand() % WIDTH_BLOCK_COUNT;
    food->y = rand() % HIGHT_BLOCK_COUNT;
}

void snake_move(void)
{
    snk_body_entity *temp = snk_head;

    for (int i = snk_lenth-1; i > 0; i--)
    {
        /* 跳转到最后 */
        for (int j = 0; j < i - 1; j++)
        {
            temp = temp->next_body;
        }

        /* 每后一个的运动都是前者位置 */
        temp->next_body->x = temp->x;
        temp->next_body->y = temp->y;

        temp = snk_head;
    }

    
    /* 蛇体移动方向 */
    switch (dir)
    {
    case DIR_DOWN:
        snk_head->y += 1;
        break;
    case DIR_UP:
        snk_head->y -= 1;
        break;
    case DIR_LEFT:
        snk_head->x -= 1;
        break;
    case DIR_RIGHT:
        snk_head->x += 1;
    }

    /* 超过边界返回 */
    if (snk_head->x >= WIDTH_BLOCK_COUNT)
    {
        snk_head->x = 0;
    }
    else if (snk_head->x < 0)
    {
        snk_head->x = WIDTH_BLOCK_COUNT;
    }
    else if (snk_head->y >= HIGHT_BLOCK_COUNT)
    {
        snk_head->y = 0;
    }
    else if (snk_head->y < 0)
    {
        snk_head->y = HIGHT_BLOCK_COUNT;
    }

    /* 碰到身体判断 */
    temp = snk_head->next_body;

    for (int i = 1; i < snk_lenth; i++)
    {
        if (temp->x == snk_head->x && temp->y == snk_head->y)
        {
            printf("you died! your final score is: %d \n", score);
            /* 释放食物内存 */
            free(food);
            /* 释放蛇内存 */
            snk_body_entity *temp = snk_head;
            for(int i = 0; i < snk_lenth; i++)
            {
                temp = snk_head;
                snk_head = temp->next_body;

                free(temp);
            }
            /* 将头指向空 */
            snk_head = NULL;
            /* 重新生成 */
            init_entity();
    
            /* 生成新食物 */
            food->x = rand() % WIDTH_BLOCK_COUNT;
            food->y = rand() % HIGHT_BLOCK_COUNT;
            //snk_head->x = rand() % WIDTH_BLOCK_COUNT;
            //snk_head->y = rand() % HIGHT_BLOCK_COUNT;
            break;
        }

        temp = temp->next_body;
        
    }
}

void snake_eat_food(void)
{
    /* 吃食物判定 生成新食物 */
    if (snk_head->x == food->x && snk_head->y == food->y)
    {
        /* 生成新食物 */
        food->x = rand() % WIDTH_BLOCK_COUNT;
        food->y = rand() % HIGHT_BLOCK_COUNT;

        /* 
         * 生成新的身体
         */ 

        /* 最后生成新的蛇体 */ 
        snk_body->next_body = malloc(sizeof(snk_body_entity));
        snk_body->next_body->x = snk_body->x;
        snk_body->next_body->y = snk_body->y;
        /* 长度增加 */
        snk_lenth++;
        /* 为下一次增加准备 */
        snk_body = snk_body->next_body;
        /* 获得分数 */
        score += 100;

        printf("score: %d\n", score);
    }
}