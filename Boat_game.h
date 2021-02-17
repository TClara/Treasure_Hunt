#ifndef BOAT_GAME_H
#define BOAT_GAME_H
#include <iostream>
#include <string>
#include <vector>
#include <duels/treasure_hunt/msg.h>
#include <duels/local.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;
using duels::Player;
using namespace duels::treasure_hunt;


struct MsgSonar
{
    vector<int> xs;
    vector<int> ys;
    vector<bool> obstacle;
};


class Boat{
public:
    int x;
    int y;
    int t;
    bool treasure_found=false;
    bool hit_obstacle=false;
    MsgSonar Sonar_coordinates;
    Boat(){};
    Boat(int width, int height){
        srand (time(NULL));
        t=rand()%4;
        x=rand()%width;
        y=rand()%height;
        Sonar_coordinates.xs.push_back(-5);
        Sonar_coordinates.ys.push_back(-5);
        Sonar_coordinates.obstacle.push_back(false);
    };

    void Update_game(inputMsg input, int Xo[20], int Yo[20], int xt, int yt);
    void Move(int Xo[20], int Yo[20]);
    void Turn_l();
    void Turn_r();
    void Get_Sonar(int Xo[20], int Yo[20]);
    bool On_treasure(int xt, int yt);

};

bool Is_free(int x,int y, int X[20], int Y[20]);
bool Is_In(int x, int y, vector<int> X, vector<int> Y);

class Grid
{
public:
    int height, width;
    int x_treasure, y_treasure;
    int Xo[20];
    int Yo[20];
    Boat b1;
    Boat b2;


    Grid(){
        srand (time(NULL));
        height=20;
        width=20;

//        height=rand()%31+20;
//        width=rand()%31+20;
        x_treasure=rand()%width;
        y_treasure=rand()%height;
        b1=Boat(width, height);
        while (Is_free(b1.x, b1.y, Xo, Yo)==false){
            b1=Boat(width, height);
        }
        b2=Boat(width, height);
        while ((!Is_free(b2.x, b2.y, Xo, Yo))||(b1.x==b2.x)||(b1.y==b2.y)){
            b2=Boat(width, height);
        }
        Create_Obstacles();
    };
    void Create_Obstacles();
    feedbackMsg Create_feedback(Boat b);
};



#endif
