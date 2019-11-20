#include <SFML/Graphics.hpp>
#include <time.h>
#include <math.h>
#include <string.h>

#include "fonction.h"





#define GROUND_HEIGHT 3
#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 600
#define BLOCK_SIZE 50

using namespace sf;




void explosAsync(ColumnsGame col[],int nbColonne,int x,int y, int rayon)
{
    explosionFromPos(col,nbColonne,x,y,rayon);
}



int numColumn()
{
    return (WINDOW_WIDTH/BLOCK_SIZE)-1;
}
int heightColumn()
{
    return (WINDOW_HEIGHT/BLOCK_SIZE);
}
int main()
{
    int explosRayon = 0,xEplos=0,yExplos=0, nbExplos=0, totalExplos = 0, jumpRank = 0, jumpGravity = 1, onlyDown = 0,upAccelere = -14,playerOldY=0;
    srand(time(NULL));
    Sprite listeShoot[100];
    int a = 0, b = 0;
    // Create the main window
    sf::RenderWindow app(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "geometryPac");

    //Entity variable
    int jumpBoucle=1,nombreEnnemi=0,boucleEnnemi=0,boucleTir=0,boucleShootTimer=0,boucleTirEnnemi=0,acceleration=-ACCELERATION,graviter=1,shootBoucle=0,playerShootTime=0,shootOn=0;
    int score=0;
    // Load a sprite to display
    sf::Texture texture;
    if (!texture.loadFromFile("bloc.png"))
        return EXIT_FAILURE;
    //sf::Sprite sprite(texture);

    //Texture entity
    Texture imgPac,imgMissile,imgTir,imgMonstre;
    imgPac.loadFromFile("image_pacman.png");
    imgMissile.loadFromFile("missile.png");
    imgTir.loadFromFile("image_M1.png");
    imgMonstre.loadFromFile("image_M1.png");
    //Initialisation player;
    Perso player;
    player.jump=false;
    player.sprite.setTexture(imgPac);
    player.sprite.setPosition(200,415);







    app.setFramerateLimit(30);
    int nbCol = numColumn()+8;
    int hgCol = heightColumn()-heightColumn()/3-1;
    ColumnsGame columns[nbCol];
    ColumnsGame groundCol[nbCol];

    columnGroup(columns,nbCol,hgCol,2,&texture,10,0,false);
    columnGroup(groundCol,nbCol,GROUND_HEIGHT,2,&texture,10,(hgCol+2) * BLOCK_SIZE,true);
    //memcpy(savecolumns,columns,nbCol);
    int moveB = 4;
    int drawLine =0, valueof=0;
    sf::Vertex line[] =
    {
        sf::Vertex(sf::Vector2f(10, 10)),
        sf::Vertex(sf::Vector2f(150, 150))
    };

    //test
    RectangleShape rect(Vector2f(1000,10));
    rect.setPosition(0,450);

    while(app.isOpen())
    {
        app.clear();

        Event event;
        while(app.pollEvent(event))
        {
            if (event.type == sf::Event::MouseButtonPressed)
            {
                //printf("ok");
                if (event.mouseButton.button == sf::Mouse::Right)
                {
                    moveB = 0;
                    drawLine = 1;
                    if(valueof==0)
                    {
                        line[0] = Vertex(Vector2f(event.mouseButton.x,event.mouseButton.y));
                        valueof=1;
                    }
                    else
                    {
                        line[1]=Vertex(Vector2f(event.mouseButton.x,event.mouseButton.y));
                        app.draw(line, 2, sf::Lines);
                        app.display();
                        moveB = 4;
                        valueof=0;
                        colorBlocksOnLineAndDestroy(columns,nbCol,line[0].position.x,line[0].position.y,line[1].position.x,line[1].position.x,123,234,244);
                    }


                }
                else if(event.mouseButton.button == sf::Mouse::Left)
                {
                    nbExplos = 0;
                    totalExplos=5;
                    xEplos = event.mouseButton.x;
                    yExplos = event.mouseButton.y;
                    explosRayon= 5;
                }




            }
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == Keyboard::Space)
                {
                    if (player.jump==false)
                    {
                        player.jump=true;

                    }
                }
                if (event.key.code == Keyboard::Right)
                {
                    if (shootOn==0)
                    {
                        playerShoot(&player,&shootBoucle,listeShoot,&imgTir);
                        shootOn=1;
                    }



                }


            }

        }
        if(explosRayon>0)
        {
            //printf("IN %i  %i\n\n", xEplos, yExplos);
            explosAsync(columns,nbCol,xEplos-(nbExplos*moveB),yExplos,totalExplos-explosRayon+1);
            if(explosRayon==1)
            {
                nbExplos = 0;
                totalExplos=0;
                xEplos = 0;
                yExplos = 0;


            }
            nbExplos++;
            explosRayon--;
        }

        moveGroup(&app,columns,nbCol,-moveB,0);
        moveGroup(&app,groundCol,nbCol,-moveB,0);
        //int g = columnGroup(nbCol,hgCol,3,texture,10)[1].block[3].sprite.getPosition().x;
        //printf("%i\n",g);
        //colorChangeColumn(&columns[8],34,254,23);
        animLeftColumn(columns,nbCol,moveB,&texture);
        animLeftColumn(groundCol,nbCol,moveB,&texture);
        //colorBlocksOnLine(columns,nbCol,100,600,700, -100, 233, 123, 234);
        //moveGroup(&app,columns,nbCol,-1 - diff,0);
        drawColumns(&app,columns,nbCol);
        drawColumns(&app,groundCol,nbCol);

        jumpPlayer(&player,&app,&acceleration,&graviter,&jumpBoucle,columns,nbCol,&playerOldY);






        int collision= toucheCoule(columns,nbCol,player.sprite.getPosition().x,player.sprite.getPosition().y,35,35);
        //printf("%i",collisionBlockBottom(columns,nbCol,player.sprite.getPosition().x,player.sprite.getPosition().y,35,35));

        app.draw(rect);


        drawPerso(&app,player);
        playerShootUpdate(listeShoot,&app);
        playerShootTimer(&shootOn,&playerShootTime);
        scoreUpdate(&score);



        app.display();
    }












}
