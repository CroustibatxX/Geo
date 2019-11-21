#include <SFML/Graphics.hpp>
#include <time.h>
#include <math.h>
#include <string.h>


#include "fonction.h"





#define GROUND_HEIGHT 3
#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 600
#define BLOCK_SIZE 50



#define HAUTEURFENETRE 600
#define LARGEURFENETRE 1000
#define HAUTEURBOUTON 100
#define LARGEURBOUTON 300
#define HAUTEURCREDIT 57
#define LARGEURCREDIT 100
#define POS_X_PERSO 100
#define PAS_PERSO 2
#define HAUTEURPERSO 200
#define LARGEURREGLE 150
#define HAUTEURREGLE 50
#define IMG_FOND "image/fond.png"
#define IMG_CIEL "image/new.png"


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

    srand(time(NULL));
    int a = 0, b = 0;


    char pseudo[20]; // Pseudo du jouer demande dans selection Pseudo
    int jouer = 1;

    Texture texFond, texBack;
    Sprite spFond, spBack;

    texBack.loadFromFile(IMG_CIEL);
    texFond.loadFromFile(IMG_FOND);

    spFond.setTexture(texFond);
    spBack.setTexture(texBack);

    spBack.setPosition(0,0);
    spFond.setPosition(0,0);

    RenderWindow app(VideoMode(LARGEURFENETRE,HAUTEURFENETRE), "GeometryPac");

    /////////////////////////////SON SAUT/////
    /*SoundBuffer buffMenu;
    buffMenu.loadFromFile("sound.wav");
    Sound soundMenu;
    soundMenu.setBuffer(buffmenu);*/
    //////////////////////////////////////

    /////////////////////////////////
    /*Sound musicMenu;
    musicMenu.load  ("Off Limits.wav");

    Music musicGame;
    musicGame.openFromFile("Blaizer Rail.wav");*/

    //////////////////////////////



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

    app.setFramerateLimit(30);






    do
    {
        bool jump = false, collisionDown = false, contactLeft = false, collisionUp= false;
        int index = 0;
        int explosRayon = 0,xEplos=0,yExplos=0, nbExplos=0, totalExplos = 0, jumpRank = 0, jumpGravity = 1, onlyDown = 0,upAccelere = -14,nbTurn = 0, nbColTurn = 0, OldnbColTurn = 0;
        int score = 0;
        int phase = 1;
        // Etape du code (menu/saisie/jeu...)



        //Initialisation player;
        Sprite listeMissile[20];
        Sprite listeShoot[10];
        Perso player;
        player.sprite.setTexture(imgPac);
        player.jump=false;
        player.sprite.setPosition(200,0);

        //Jump

        //Entity variables
        int nombreEnnemi=0,boucleEnnemi=0,boucleTir=0,boucleShootTimer=0,boucleTirEnnemi=0,shootBoucle=0,playerShootTime=0,shootOn=0,nbMissile=0,boucleMissile=0,vie=1;


        //Jump Variables
        int jumpBoucle=1,acceleration=-ACCELERATION,graviter=1,playerOldY=0;
        int jumpBoucle2=1,acceleration2=-ACCELERATION,graviter2=1,playerOldY2=0;
        bool jumpOn=false,jumpOn2=false;




        int moveB = 4;
        int drawLine =0, valueof=0;
        sf::Vertex line[] =
        {
            sf::Vertex(sf::Vector2f(10, 10)),
            sf::Vertex(sf::Vector2f(150, 150))
        };


        int nbCol = numColumn()-3;


        int hgCol = heightColumn()-heightColumn()/3;
        ColumnsGame columns[nbCol];
        ColumnsGame groundCol[nbCol];

        ColumnsGame columns2[nbCol];
        ColumnsGame groundCol2[nbCol];

        columnGroup(columns,nbCol,hgCol,2,&texture,0,0,false);
        columnGroup(groundCol,nbCol,GROUND_HEIGHT,2,&texture,0,(hgCol+1) * BLOCK_SIZE,true);

        columnGroup(columns2,nbCol,hgCol,2,&texture,(nbCol)*BLOCK_SIZE,0,false);
        columnGroup(groundCol2,nbCol,GROUND_HEIGHT,2,&texture,(nbCol)*BLOCK_SIZE,(hgCol+1) * BLOCK_SIZE,true);

        //musicMenu.play();
        // Lancement du menu
        afficheMenu(&app, spFond, spBack, &phase);

        // Lancement de la saisie de pseudo si le joueur appuie sur jouer
        selectionPseudo(&app, spFond, spBack, pseudo, &phase);
        RectangleShape inCollum(Vector2f(TAILLE_PLAYER,TAILLE_PLAYER));
        inCollum.setPosition(200,500);
        //musicMenu.play();




        //musicGame.play();
        do
        {
            app.clear();
            app.draw(spBack);





            if(OldnbColTurn<nbColTurn)
            {
                OldnbColTurn = nbColTurn;
                int plusd = 4;
                if(OldnbColTurn>=0)
                {
                    plusd=0;
                }
                if(nbColTurn%2 == 1)
                {

                    columnGroup(columns,nbCol,hgCol,2,&texture,(BLOCK_SIZE*(nbCol+plusd)),0,false);
                    columnGroup(groundCol,nbCol,GROUND_HEIGHT,2,&texture,(BLOCK_SIZE*(nbCol+plusd)),(hgCol+1) * BLOCK_SIZE,true);


                }
                else

                {
                    columnGroup(columns2,nbCol,hgCol,2,&texture,(nbCol+plusd)*BLOCK_SIZE,0,false);
                    columnGroup(groundCol2,nbCol,GROUND_HEIGHT,2,&texture,(nbCol+plusd)*BLOCK_SIZE,(hgCol+1) * BLOCK_SIZE,true);
                }
            }

            //colorChangeColumns(columns2,3,145,178,189);
            //colorChangeColumns(columns,3,145,178,189);


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
                            moveB = 4;
                            valueof=0;
                            colorBlocksOnLineAndDestroy(columns2,nbCol,line[0].position.x,line[0].position.y,line[1].position.x,line[1].position.x,123,234,244);
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

            moveGroup(&app,columns2,nbCol,-moveB,0);
            moveGroup(&app,groundCol2,nbCol,-moveB,0);
            //int g = columnGroup(nbCol,hgCol,3,texture,10)[1].block[3].sprite.getPosition().x;

            //colorChangeColumn(&columns[8],34,254,23);
            animLeftColumn(columns,nbCol,moveB,&texture);
            animLeftColumn(groundCol,nbCol,moveB,&texture);

            animLeftColumn(columns2,nbCol,moveB,&texture);
            animLeftColumn(groundCol2,nbCol,moveB,&texture);
            //colorBlocksOnLine(columns,nbCol,100,600,700, -100, 233, 123, 234);
            //moveGroup(&app,columns,nbCol,-1 - diff,0);
            drawColumns(&app,columns,nbCol);
            drawColumns(&app,groundCol,nbCol);

            drawColumns(&app,columns2,nbCol);
            drawColumns(&app,groundCol2,nbCol);

            //printf("Col %i\n",columns[1].block[1].x);
            //printf("Col2 %i\n",columns2[1].block[1].x);
            jumpPlayer(&player,&app,&acceleration,&graviter,&jumpBoucle,columns,groundCol,nbCol,&playerOldY);

            /*for (int i=0; i<16; i++)
            {
                for (int j=0; j<3; j++)
                {
                    if (groundCol[i].block[j].sprite.getGlobalBounds().intersects(inCollum.getGlobalBounds()))
                    {
                        //jumpPlayer(&player,&app,&acceleration,&graviter,&jumpBoucle,columns,groundCol,nbCol,&playerOldY);
                        //printf("Go");
                    }

                    /*if (groundCol2[i].block[j].sprite.getGlobalBounds().intersects(inCollum.getGlobalBounds()))
                    {
                        jumpPlayer(&player,&app,&acceleration2,&graviter2,&jumpBoucle2,columns2,groundCol2,nbCol,&playerOldY2,jumpOn2);
                        //printf("Starf");
                    }
                }

            }*/








            createMissile(listeMissile, &boucleMissile,&nbMissile,&imgMissile);
            drawPerso(&app,player);
            ShootUpdate(listeShoot,&app,10,VITESSE_SHOOT_PLAYER);
            ShootUpdate(listeMissile,&app,20,VITESSE_SHOOT_ENNEMI);



            playerShootTimer(&shootOn,&playerShootTime);
            scoreUpdate(&score);
            afficheOr(&app, &phase, &score);
            collisionShootPlayer(listeShoot,columns,nbCol);
            collisionShootPlayer(listeShoot,columns2,nbCol);

            vieVerif(&vie,player,listeMissile);

            app.display();
            nbTurn ++;
            nbColTurn = nbTurn/(((BLOCK_SIZE*(nbCol+2)))/moveB);





        }
        while(vie==1);

        phase++;
        vie=1;


        // Compare le score joueur aux 5 premiers, le remplace si necessaire et affiche les 5 premiers scores
        affiScore(&app, spFond, spBack, pseudo, score, &phase, &jouer);
        phase=1;
        //musicGame.stop();


    }
    while(jouer == 1);

    return 0;
}

