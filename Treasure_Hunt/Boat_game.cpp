#include <iostream>
#include "Boat_game.h"
#include <vector>
#include <math.h>

using namespace std;


bool Is_free(int x, int y, int X[20], int Y[20]){
    int i;
    bool res=true;
    if (x>=19||y>=19||x<0||y<0){res=false;}
    else {
        for (i=0;i<20;i++){
            if ((X[i]==x)&&(Y[i]==y)){
                res=false;
            }
        }
    }
    return res;
};


bool Is_In(int x, int y, vector<int> X, vector<int> Y){
    bool res=false;
    for (int i=0; i<X.size(); i++){
        if ((x==X[i])&&(y==Y[i])){
                res=true;
        }
    }
    return res;
}



void Boat::Move(int Xo[20], int Yo[20]){
    int t=Boat::t;

    if (t==0){
        Boat::x++;
    }
    if (t==1){
        Boat::y--;
    }
    if (t==2){
        Boat::x--;
    }
    if (t==3){
        Boat::y++;
    }
};


void Boat::Turn_l(){
    if (Boat::t==3){Boat::t=0;}
    else {Boat::t=Boat::t+1;}
};

void Boat::Turn_r(){
    if (Boat::t==0){Boat::t=3;}
    else {Boat::t=Boat::t-1;}
};

void Boat::Get_Sonar(int Xo[20], int Yo[20]){
    Boat::Sonar_coordinates.xs.clear();
    Boat::Sonar_coordinates.ys.clear();
    Boat::Sonar_coordinates.obstacle.clear();
    float lower= -Boat::t*(3.14/2) - (3.14/4);
    float upper= -Boat::t*(3.14/2) + (3.14/4);
    float alpha=lower;
    for (int i = 0; i<1000; i++){
        alpha=lower+i*(upper-lower)/1000;
        float inc_a=cos(alpha);
        float inc_b=sin(alpha);

        float a = Boat::x + 0.5;
        float b = Boat::y + 0.5;
        while (Is_free(int(floor(a)), int(floor(b)), Xo, Yo)){
            if (!Is_In(int(a), int(b), Boat::Sonar_coordinates.xs, Boat::Sonar_coordinates.ys)){
                Boat::Sonar_coordinates.xs.push_back(int(floor(a)));
                Boat::Sonar_coordinates.ys.push_back(int(floor(b)));
                Boat::Sonar_coordinates.obstacle.push_back(false);

            }
            a = a+inc_a;
            b = b+inc_b;

        }
        if (!Is_In(int(a), int(b), Boat::Sonar_coordinates.xs, Boat::Sonar_coordinates.ys)){
            Boat::Sonar_coordinates.xs.push_back(int(a));
            Boat::Sonar_coordinates.ys.push_back(int(b));
            Boat::Sonar_coordinates.obstacle.push_back(true);
        }
    }
};




void Boat::Update_game(inputMsg input, int Xo[20], int Yo[20], int xt, int yt){
    string A=input.action;
    if (A=="move"){

        cout<<Boat::x<<" ; "<<Boat::y<<endl;

        Boat::Move(Xo, Yo);

        cout<<Boat::x<<" ; "<<Boat::y<<endl;
        cout<<"**********************"<<endl;

        if (Boat::On_treasure(xt, yt)){Boat::treasure_found=true;}
        if (!Is_free(Boat::x,Boat::y,Xo,Yo)){
            cout<<"dead"<<endl;
            Boat::hit_obstacle=true;}
    }
    if (A=="turn_l"){Boat::Turn_l();}
    if (A=="turn_r"){Boat::Turn_r();}
    if (A=="sonar"){Boat::Get_Sonar(Xo, Yo);}
};

bool Boat::On_treasure(int xt, int yt){
    return ((Boat::x==xt)&&(Boat::y==yt));
}

void Grid::Create_Obstacles(){
    srand (time(NULL));
    for (int i=0; i<20; i++){
        Xo[i]=x_treasure;
        Yo[i]=y_treasure;
        while ((Xo[i]==x_treasure)&&(Yo[i]==y_treasure)){
           Xo[i]=rand()%width;
           Yo[i]=rand()%height;
        }
        if (i>0){
            for (int j=0;j<i;j++){
                if ((Xo[i]==Xo[j])&&(Yo[i]==Yo[j])){
                    Xo[i]=rand()%width;
                    Yo[i]=rand()%height;
                }
            }
        }
    }
};

void Grid::Create_Controlled_Obstacles()
{

    for (int i = 0; i<5; i++)
    {
        Xo[i] = 10;
        Yo[i] = 8+i;
    }

    for (int i = 5; i<20; i++)
    {
        Xo[i] = -5;
        Yo[i] = -5;
    }

}


feedbackMsg Grid::Create_feedback(Boat b){
    feedbackMsg fb;
    fb.x=b.x;
    fb.y=b.y;
    fb.t=b.t;
    fb.Xs=b.Sonar_coordinates.xs;
    fb.Ys=b.Sonar_coordinates.ys;
    fb.Os=b.Sonar_coordinates.obstacle;
    fb.dist=abs(Grid::x_treasure-b.x)+abs(Grid::y_treasure-b.y);
    return fb;
};
