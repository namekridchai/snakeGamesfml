#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
using namespace sf;
enum movement{Right,Left,Up,Down};


Texture myTexture(std::string n)
{
    Texture t;
    if(!t.loadFromFile(n))
    {
        std::cout<<"Fail for load file"<<std::endl;
    }
    return t;
}
struct Behavior{
int x;
int y;
movement direction;

};

struct Snake{
int dx;
int dy;
Sprite s;
movement direction;
};



int main(){
RenderWindow window(VideoMode(500,400),"snake game");
Texture t1  = myTexture("white.png");
Texture t2 = myTexture("green.png");
Texture t3 = myTexture("red.png");
Vector2u wsize =   window.getSize();
Vector2u isize = t1.getSize();
Sprite table[(wsize.y / isize.y)][(wsize.x/isize.x)];
Snake head;
head.dx = isize.x;  head.dy = 0;    head.direction = Right;

std::vector<Snake> snakeList;
snakeList.push_back(head);  snakeList[0].s.setTexture(t2);

Sprite food;
food.setTexture(t3);


FloatRect snakeBox[100],foodBox;

int drx,dry;    int frame = 0;

int posFoodx =  (rand() %  (wsize.x/isize.x)) * isize.x;
int posFoody  = (rand() % (wsize.y/isize.y))  * isize.y;
food.setPosition(Vector2f(posFoodx,posFoody));

dry = 0;
Vector2f v1 = snakeList[0].s.getPosition();
Vector2f v;



for(int i = 0;i<(wsize.y/isize.y);i++){
        drx = 0;

        for(int j = 0;j<(wsize.x/isize.x);j++){
          table[i][j].setTexture(t1);
          table[i][j].setPosition(Vector2f(drx,dry));
          drx+=isize.x;
        }
        dry += isize.y;
   }

Vector2f isizef(isize);
Behavior behavior[100];

while(window.isOpen()){

    for(int i = 0;i<snakeList.size();i++)
        snakeBox[i] = snakeList[i].s.getGlobalBounds();
    foodBox = food.getGlobalBounds();


    Event event;
    while(window.pollEvent(event))
    {
        if(event.type == Event::Closed)
        {
            window.close();
        }

        if(event.type == Event::KeyPressed)
        {
            if(event.key.code == Keyboard::Right)
            {

                 snakeList[0].dx = isizef.x;
                 snakeList[0].dy = 0;
                snakeList[0].direction = Right;

            }
        }

        if(event.type == Event::KeyPressed)
        {
            if(event.key.code == Keyboard::Left)
            {
                 snakeList[0].dx = isizef.x * -1;
                 snakeList[0].dy = 0;
                 snakeList[0].direction = Left;

            }
        }

        if(event.type == Event::KeyPressed)
        {
            if(event.key.code == Keyboard::Up)
            {
                snakeList[0].dx = 0;
                snakeList[0].dy = isizef.y * -1;
                snakeList[0].direction = Up;
            }
        }

        if(event.type == Event::KeyPressed)
        {
            if(event.key.code == Keyboard::Down)
            {
                 snakeList[0].dx = 0;
                 snakeList[0].dy = isizef.y;
                snakeList[0].direction = Down;
            }
        }
    }

    window.clear();
   for(int i = 0;i<(wsize.y/isize.y);i++){

        for(int j = 0;j<(wsize.x/isize.x);j++){

              window.draw(table[i][j]);

        }
   }
    if(frame %175==0){

        for(int i = 0;i<snakeList.size();i++)
        {
                snakeList[i].s.move(Vector2f(snakeList[i].dx,snakeList[i].dy));
                behavior[i].x = snakeList[i].dx;
                behavior[i].y = snakeList[i].dy;
                behavior[i].direction = snakeList[i].direction;
        }


    if(foodBox.intersects(snakeBox[0])){
        posFoodx =  (rand() %  (wsize.x/isize.x)) * isize.x;
        posFoody  = (rand() % (wsize.y/isize.y))  * isize.y;
        food.setPosition(Vector2f(posFoodx,posFoody));
        Snake tail;
        tail.s.setTexture(t2);
        tail.dx = snakeList[snakeList.size()-1].dx;
        tail.dy = snakeList[snakeList.size()-1].dx;
        v = snakeList[snakeList.size()-1].s.getPosition();

        // switch for draw picture to expand snake's length
        switch(snakeList[snakeList.size()-1].direction){
        case Right:
            tail.s.setPosition(Vector2f(v.x-isizef.x,v.y));
            tail.direction = Right;
            break;
        case Left:
            tail.s.setPosition(Vector2f(v.x+isizef.x,v.y));
            tail.direction = Left;
            break;
        case Up:
            tail.s.setPosition(Vector2f(v.x,v.y+isizef.y));
            tail.direction = Up;
            break;
        case Down:
            tail.s.setPosition(Vector2f(v.x,v.y-isizef.y));
            tail.direction = Down;
            break;


        }
        snakeList.push_back(tail);
    }

             for(int i =1;i<snakeList.size();i++)
            {
                     snakeList[i].dx = behavior[i-1].x;
                    snakeList[i].dy = behavior[i-1].y;
                    snakeList[i].direction = behavior[i-1].direction;
            }
    }

    v1 = snakeList[0].s.getPosition();
    std::cout<<v1.x<<" "<<v1.y<<std::endl;
    for(int i = 0;i<snakeList.size();i++)
    {
         if(i==snakeList.size()-1)
            snakeList[i].s.setColor(Color::Yellow);
         else
            snakeList[i].s.setColor(Color::White);
         window.draw(snakeList[i].s);
    }
    window.draw(food);
    window.display();
    frame++;

}



}
