#include "stdio.h"
#include "stdlib.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL2_gfxPrimitives.h"
#include "time.h"
#include "formulas.h"
#include "wall.h"
#include "robot.h"

int done = 0;


int main(int argc, char *argv[]) {
    SDL_Window *window;
    SDL_Renderer *renderer;

    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        return 1;
    }

    window = SDL_CreateWindow("Robot Maze", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, OVERALL_WINDOW_WIDTH, OVERALL_WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
    window = SDL_CreateWindow("Robot Maze", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, OVERALL_WINDOW_WIDTH, OVERALL_WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
    renderer = SDL_CreateRenderer(window, -1, 0);

    struct Robot robot;
    struct Wall_collection *head = NULL;
    int front_centre_sensor, left_sensor, right_sensor=0;
    clock_t start_time, end_time;
    int msec;
    int crashed = 0;

    // SETUP MAZE
    // You can create your own maze here. line of code is adding a wall.
    // You describe position of top left corner of wall (x, y), then width and height going down/to right
    // Relative positions are used (OVERALL_WINDOW_WIDTH and OVERALL_WINDOW_HEIGHT)
    // But you can use absolute positions. 10 is used as the width, but you can change this.

    // === Default maze ===
    // insertAndSetFirstWall(&head, 1,  OVERALL_WINDOW_WIDTH/2, OVERALL_WINDOW_HEIGHT/2, 10, OVERALL_WINDOW_HEIGHT/2);
    // insertAndSetFirstWall(&head, 2,  OVERALL_WINDOW_WIDTH/2-100, OVERALL_WINDOW_HEIGHT/2+100, 10, OVERALL_WINDOW_HEIGHT/2-100);
    // insertAndSetFirstWall(&head, 3,  OVERALL_WINDOW_WIDTH/2-250, OVERALL_WINDOW_HEIGHT/2+100, 150, 10);
    // insertAndSetFirstWall(&head, 4,  OVERALL_WINDOW_WIDTH/2-150, OVERALL_WINDOW_HEIGHT/2, 150, 10);
    // insertAndSetFirstWall(&head, 5,  OVERALL_WINDOW_WIDTH/2-250, OVERALL_WINDOW_HEIGHT/2-200, 10, 300);
    // insertAndSetFirstWall(&head, 6,  OVERALL_WINDOW_WIDTH/2-150, OVERALL_WINDOW_HEIGHT/2-100, 10, 100);
    // insertAndSetFirstWall(&head, 7,  OVERALL_WINDOW_WIDTH/2-250, OVERALL_WINDOW_HEIGHT/2-200, 450, 10);
    // insertAndSetFirstWall(&head, 8,  OVERALL_WINDOW_WIDTH/2-150, OVERALL_WINDOW_HEIGHT/2-100, 250, 10);
    // insertAndSetFirstWall(&head, 9,  OVERALL_WINDOW_WIDTH/2+200, OVERALL_WINDOW_HEIGHT/2-200, 10, 300);
    // insertAndSetFirstWall(&head, 10,  OVERALL_WINDOW_WIDTH/2+100, OVERALL_WINDOW_HEIGHT/2-100, 10, 300);
    // insertAndSetFirstWall(&head, 11,  OVERALL_WINDOW_WIDTH/2+100, OVERALL_WINDOW_HEIGHT/2+200, OVERALL_WINDOW_WIDTH/2-100, 10);
    // insertAndSetFirstWall(&head, 12,  OVERALL_WINDOW_WIDTH/2+200, OVERALL_WINDOW_HEIGHT/2+100, OVERALL_WINDOW_WIDTH/2-100, 10);
    


    // === My maze ===
    insertAndSetFirstWall(&head, 1, 170, 410, 10, 250);
    insertAndSetFirstWall(&head, 1, 170, 410, 270, 10);
    insertAndSetFirstWall(&head, 1, 410, 410, 10, 50);
    insertAndSetFirstWall(&head, 1, 410, 460, 30, 10);
    insertAndSetFirstWall(&head, 1, 440, 260, 10, 200);
    insertAndSetFirstWall(&head, 1, 190, 260, 250, 10);

    insertAndSetFirstWall(&head, 1, 270, 510, 10, 150);
    insertAndSetFirstWall(&head, 1, 270, 510, 40, 10);
    insertAndSetFirstWall(&head, 1, 310, 510, 10, 50);
    insertAndSetFirstWall(&head, 1, 310, 560, 200, 10);
    insertAndSetFirstWall(&head, 1, 510, 110, 10, 450);
    insertAndSetFirstWall(&head, 1, 110, 110, 400, 10);
    insertAndSetFirstWall(&head, 1, 110, 110, 10, 230);
    insertAndSetFirstWall(&head, 1, 110, 340, 200, 10);
    insertAndSetFirstWall(&head, 1, 10, 440, 160, 10);
    insertAndSetFirstWall(&head, 1, 10, 10, 10, 430);
    insertAndSetFirstWall(&head, 1, 10, 10, 450, 10);


    /// === Ed maze ===
    // insertAndSetFirstWall(&head, 1, 128, OVERALL_WINDOW_HEIGHT / 2, 10, 320);
    // insertAndSetFirstWall(&head, 2, 256, OVERALL_WINDOW_HEIGHT / 2, 10, 320);
    // insertAndSetFirstWall(&head, 3, OVERALL_WINDOW_WIDTH / 2 - 350, 320, 160,
    //                       10);
    // insertAndSetFirstWall(&head, 4, OVERALL_WINDOW_WIDTH / 2 - 350, 192, 510,
    //                       10);
    // insertAndSetFirstWall(&head, 5, 0, 192, 10, 128);
    // insertAndSetFirstWall(&head, 6, 256, OVERALL_WINDOW_HEIGHT / 2, 50, 10);
    // insertAndSetFirstWall(&head, 7, 306, OVERALL_WINDOW_HEIGHT / 2, 10, 200);
    // insertAndSetFirstWall(&head, 8, 428, 192, 10, 260);
    // insertAndSetFirstWall(&head, 12, 477, 192, 10, 260);
    // insertAndSetFirstWall(&head, 11, 599, -20, 10, 520);

    // insertAndSetFirstWall(&head, 13, 0, 0, 600, 10);

    // // Large Curved Wall
    // int radius = 147;
    // int centerX = 453;
    // int centerY = 490;
    // int numSegments = 1000;
    // double angleIncrement = M_PI / numSegments;

    // for (int i = 0; i < numSegments; i++) {
    //     int startX = centerX - radius * cos(i * angleIncrement);
    //     int startY = centerY + radius * sin(i * angleIncrement);
    //     int endX = centerX - radius * cos((i + 1) * angleIncrement);
    //     int endY = centerY + radius * sin((i + 1) * angleIncrement);

    //     insertAndSetFirstWall(&head, i + 14, startX, startY, 10, 10);
    // }

    // // Small Curved Wall
    // int radius2 = 25;
    // int centerX2 = 453;
    // int centerY2 = 450;
    // int numSegments2 = 500;
    // double angleIncrement2 = M_PI / numSegments2;

    // for (int i = 0; i < numSegments2; i++) {
    //     int startX2 = centerX2 - radius2 * cos(i * angleIncrement2);
    //     int startY2 = centerY2 + radius2 * sin(i * angleIncrement2);
    //     int endX2 = centerX2 - radius2 * cos((i + 1) * angleIncrement2);
    //     int endY2 = centerY2 + radius2 * sin((i + 1) * angleIncrement2);

    //     insertAndSetFirstWall(&head, i + 14, startX2, startY2, 10, 10);
    // }

    // === Second Ed Maze ===
    // insertAndSetFirstWall(&head, 0, 110, 360, 10, 100);
    // insertAndSetFirstWall(&head, 1, 110, 460, 510, 10);
    // insertAndSetFirstWall(&head, 2, 210, 270, 10, 100);
    // insertAndSetFirstWall(&head, 3, 390, 360, 10, 100);
    // insertAndSetFirstWall(&head, 4, 310, 360, 80, 10);
    // insertAndSetFirstWall(&head, 5, 500, 270, 10, 100);
    // insertAndSetFirstWall(&head, 6, 20, 170, 10, 300);
    // insertAndSetFirstWall(&head, 7, 20, 170, 95, 10);
    // insertAndSetFirstWall(&head, 8, 110, 170, 10, 100);
    // insertAndSetFirstWall(&head, 9, 110, 170, 285, 10);
    // insertAndSetFirstWall(&head, 10, 310, 270, 85, 10);
    // insertAndSetFirstWall(&head, 11, 390, 170, 10, 100);
    // insertAndSetFirstWall(&head, 12, 390, 270, 115, 10);
    // insertAndSetFirstWall(&head, 14, 610, 10, 10, 455);
    // insertAndSetFirstWall(&head, 15, 300, 90, 200, 10);
    // insertAndSetFirstWall(&head, 16, 300, 90, 10, 85);
    // insertAndSetFirstWall(&head, 17, 210, 10, 10, 85);
    // insertAndSetFirstWall(&head, 18, 110, 10, 500, 10);
    // insertAndSetFirstWall(&head, 19, 110, 90, 10, 85);
    // insertAndSetFirstWall(&head, 20, 20, 10, 10, 165);
    // insertAndSetFirstWall(&head, 21, 500, 90, 10, 100);

    // // Ed Maze 4
    // insertAndSetFirstWall(&head, 1, 15, 25, 10, 430);
    // insertAndSetFirstWall(&head, 1, 75, 145, 10, 60);
    // insertAndSetFirstWall(&head, 1, 75, 325, 10, 120);
    // insertAndSetFirstWall(&head, 1, 135, 85, 10, 60);
    // insertAndSetFirstWall(&head, 1, 135, 325, 10, 60);
    // insertAndSetFirstWall(&head, 1, 195, 145, 10, 300);
    // insertAndSetFirstWall(&head, 1, 255, 145, 10, 120);
    // insertAndSetFirstWall(&head, 1, 315, 25, 10, 60);
    // insertAndSetFirstWall(&head, 1, 315, 265, 10, 130);
    // insertAndSetFirstWall(&head, 1, 375, 85, 10, 70);
    // insertAndSetFirstWall(&head, 1, 375, 265, 10, 120);
    // insertAndSetFirstWall(&head, 1, 435, 85, 10, 60);
    // insertAndSetFirstWall(&head, 1, 435, 325, 10, 130);
    // insertAndSetFirstWall(&head, 1, 495, 145, 10, 180);
    // insertAndSetFirstWall(&head, 1, 555, 25, 10, 130);
    // insertAndSetFirstWall(&head, 1, 555, 205, 10, 190);
    // insertAndSetFirstWall(&head, 1, 615, 25, 10, 430);

    // insertAndSetFirstWall(&head, 1, 15, 25, 540, 10);
    // insertAndSetFirstWall(&head, 1, 75, 85, 190, 10);
    // insertAndSetFirstWall(&head, 1, 435, 85, 60, 10);
    // insertAndSetFirstWall(&head, 1, 315, 145, 60, 10);
    // insertAndSetFirstWall(&head, 1, 495, 145, 60, 10);
    // insertAndSetFirstWall(&head, 1, 75, 205, 60, 10);
    // insertAndSetFirstWall(&head, 1, 315, 205, 180, 10);
    // insertAndSetFirstWall(&head, 1, 15, 265, 120, 10);
    // insertAndSetFirstWall(&head, 1, 255, 265, 60, 10);
    // insertAndSetFirstWall(&head, 1, 375, 265, 60, 10);
    // insertAndSetFirstWall(&head, 1, 195, 325, 60, 10);
    // insertAndSetFirstWall(&head, 1, 255, 385, 60, 10);
    // insertAndSetFirstWall(&head, 1, 495, 385, 60, 10);
    // insertAndSetFirstWall(&head, 1, 75, 445, 540, 10);

    // // Spiral Ed maze
    // for (float i = 0; i < 25; i += 0.01){
    // insertAndSetFirstWall(&head, 0, OVERALL_WINDOW_WIDTH/2 + 15 * i * cos(i), OVERALL_WINDOW_HEIGHT/2 + 10 * i * sin(i), 10, 10);
    // }

    // for (int i = 0; i <= 10; i++){
    //     insertAndSetFirstWall(&head, 0, OVERALL_WINDOW_WIDTH - 5 * i, OVERALL_WINDOW_HEIGHT/4 + 5 * i, 10, 10);
    // }



    // === End of mazes ===

    setup_robot(&robot);
    updateAllWalls(head, renderer);

    SDL_Event event;
    while(!done){
        SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
        SDL_RenderClear(renderer);

        // This if statement is here to introduce a pause feature in order to debug our program. 
        // It does not affect the simulation.
        if (robot.paused == false || robot.next_frame == true) {
            //Move robot based on user input commands/auto commands
            if (robot.auto_mode == 1)
                robotAutoMotorMove(&robot, front_centre_sensor, left_sensor, right_sensor);
            printf("Left, front, right = (%d, %d, %d). Step %c %d. Speed: %d.\n", left_sensor, front_centre_sensor, right_sensor, robot.context, robot.count, robot.currentSpeed);
        robotMotorMove(&robot, crashed);
        }

        //Check if robot reaches endpoint. and check sensor values
        if (checkRobotReachedEnd(&robot, OVERALL_WINDOW_WIDTH, OVERALL_WINDOW_HEIGHT/2+100, 10, 100)){
            end_time = clock();
            msec = (end_time-start_time) * 1000 / CLOCKS_PER_SEC;
            robotSuccess(&robot, msec);
        }
        else if(crashed == 1 || checkRobotHitWalls(&robot, head)){
            robotCrash(&robot);
            crashed = 1;
        }
        //Otherwise compute sensor information
        else {
            front_centre_sensor = checkRobotSensorFrontCentreAllWalls(&robot, head);
            // if (front_centre_sensor>0)
            //     printf("Getting close on the centre. Score = %d\n", front_centre_sensor);

            left_sensor = checkRobotSensorLeftAllWalls(&robot, head);
            // if (left_sensor>0)
            //     printf("Getting close on the left. Score = %d\n", left_sensor);

            right_sensor = checkRobotSensorRightAllWalls(&robot, head);
            // if (right_sensor>0)
            //     printf("Getting close on the right. Score = %d\n", right_sensor);
        }
        robotUpdate(renderer, &robot);
        updateAllWalls(head, renderer);

        // Check for user input
        SDL_RenderPresent(renderer);
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                done = 1;
            }
            const Uint8 *state = SDL_GetKeyboardState(NULL);
            if(state[SDL_SCANCODE_UP] && robot.direction != DOWN){
                robot.direction = UP;
            }
            if(state[SDL_SCANCODE_DOWN] && robot.direction != UP){
                robot.direction = DOWN;
            }
            if(state[SDL_SCANCODE_LEFT] && robot.direction != RIGHT){
                robot.direction = LEFT;
            }
            if(state[SDL_SCANCODE_RIGHT] && robot.direction != LEFT){
                robot.direction = RIGHT;
            }
            if(state[SDL_SCANCODE_SPACE]){
                setup_robot(&robot);
                crashed = 0;
            }
            if(state[SDL_SCANCODE_RETURN]){
                robot.auto_mode = 1;
                start_time = clock();
            }
            if (state[SDL_SCANCODE_P] && robot.counter < 0) {
                robot.paused = !robot.paused;
                robot.counter = 1;
            } else {
                robot.counter--;
            }
            if (state[SDL_SCANCODE_C]) {
                robot.next_frame = true;
            } else {
                robot.next_frame = false;
            }
        }

        SDL_Delay(120);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    printf("DEAD\n");
}
