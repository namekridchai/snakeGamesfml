#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
using namespace sf;

int num = 1;
enum movement{Left,Right,Up,Down};
struct Snake{
int x = 0;
int y = 0;
movement dir = Down;
};
int main()
{

    Texture t1,t2,t3;
    t1.loadFromFile("white.png");
    t2.loadFromFile("green.png");
    t3.loadFromFile("red.png");
     Sprite s1(t1),s2(t2),s3(t3);
    Snake snake[100];
    int x = t1.getSize().x;
    int y = t1.getSize().y;

    int foodx = rand() % 30 * x;
    int foody = rand() % 20 * y;
    int frame = 0;
    sf::RenderWindow window(sf::VideoMode(x*30,y*20),"trrrrr");


    std::cout<<window.getSize().x<<std::endl;
    while(window.isOpen()){

    s3.setPosition(foodx,foody);
    if(frame % 300==0)
    {

    for(int i = 1;i<num;i++)
      {
          if(snake[0].x==snake[i].x && snake[0].y==snake[i].y)
          {
              num = i;
              break;
          }
      }

    if(snake[0].x==foodx && snake[0].y==foody)
    {
       foodx = rand() % 30 * x;
        foody = rand() % 20 * y;
       num++;
    }

    for(int i = num-1;i>0;i--)
    {
        snake[i].x = snake[i-1].x;
        snake[i].y = snake[i-1].y;
    }
       if(snake[0].x<0){
        if(snake[0].dir==Left)
            snake[0].x = window.getSize().x;
        else
            snake[0].x = window.getSize().x-t2.getSize().x;
       }

        else if(snake[0].x> window.getSize().x-t2.getSize().x)
        {
             if(snake[0].dir=Right)
                snake[0].x = 0 - x ;
            else
                 snake[0].x = 0 ;

        }

        else if(snake[0].y<0){
            if(snake[0].dir==Up)
                snake[0].y = window.getSize().y;
            else
                 snake[0].y = window.getSize().y-t2.getSize().y;
        }

        else if(snake[0].y >window.getSize().y-t2.getSize().y){
             if(snake[0].dir==Down)
                snake[0].y = 0-y;
            else
                 snake[0].y = 0;
        }
         if(snake[0].dir==Down)
            snake[0].y+=y;
        else if(snake[0].dir==Up)
            snake[0].y-=y;
        else if(snake[0].dir==Right)
            snake[0].x+=x;
        else if(snake[0].dir==Left)
            snake[0].x-=y;

        }




        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type ==sf::Event::Closed){
                window.close();
            }
        }
        if(Keyboard::isKeyPressed(Keyboard::Left))
           snake[0].dir = Left;
        if(Keyboard::isKeyPressed(Keyboard::Right))
           snake[0].dir = Right;
        if(Keyboard::isKeyPressed(Keyboard::Up))
           snake[0].dir = Up;
        if(Keyboard::isKeyPressed(Keyboard::Down))
           snake[0].dir= Down;





    for(int i = 0;i<window.getSize().y/t1.getSize().y;i++){

        for(int j = 0;j<window.getSize().x/t1.getSize().x;j++){
            s1.setPosition(Vector2f(j * x,i * y));
             window.draw(s1);
        }
    }

    for(int i =0;i<num;i++)
    {
        s2.setPosition(snake[i].x,snake[i].y);
     /* if(i==1)
        std::cout<<s2.getPosition().x<" "<<s2.getPosition.y<<std::endl;*/
    window.draw(s2);
    }
    window.draw(s3);
    window.display();
    window.clear();
    frame++;
    }

     return 0;
    }

