#include "fonction.h"




void drawPerso(RenderWindow * fen,Perso player)
{
    fen->draw(player.sprite);
}

void drawMob(RenderWindow * fen,Sprite liste[],int taille)
{
    for(int i=0; i<taille; i++)
    {
        fen->draw(liste[i]);
    }

}
void collisionShootPlayer(Sprite listeShoot[],ColumnsGame col[],int nbCol)
{
    for (int i=0; i<TAILLE_LISTE_SHOOT; i++)
    {
        int collision= toucheCoule(col,nbCol,listeShoot[i].getPosition().x,listeShoot[i].getPosition().y,TAILLE_PLAYER,TAILLE_PLAYER);
        if (collision==1)
        {
            explosionFromPos(col,nbCol,listeShoot[i].getPosition().x,listeShoot[i].getPosition().y, TAILLE_EXPLO);
            listeShoot[i].setPosition(listeShoot[i].getPosition().x,listeShoot[i].getPosition().y+SPAWN_MISSILE_Y);
        }


    }

}


void vieVerif(int *vie,Perso player,Sprite listeMisille[])
{
    if (player.sprite.getPosition().x<0-TAILLE_PLAYER)
        *vie=0;
    if (player.sprite.getPosition().y>WINDOW_HEIGHT)
        *vie=0;
    for (int i=0; i<TAILE_NOMBRE_SHOOT_MISSILE; i++)
    {
        if (player.sprite.getGlobalBounds().intersects(listeMisille[i].getGlobalBounds())==true)

            *vie=0;
    }
}



void jumpPlayer(Perso *player,RenderWindow *fenetre,int *acceleration,int *graviter,int *boucleJump,ColumnsGame col[],ColumnsGame colGround[],int nbColonne,int *oldY)
{
    int collisionBot=collisionBlockBottom(col,nbColonne,player->sprite.getPosition().x,player->sprite.getPosition().y,35,35);
    int collisionTop=collisionBlockTop(col,nbColonne,player->sprite.getPosition().x,player->sprite.getPosition().y,35,35);
    int collisionTopGround=collisionBlockTop(colGround,nbColonne,player->sprite.getPosition().x,player->sprite.getPosition().y,35,35);
    int collisionLeft=collisionBlockLeft(col,nbColonne,player->sprite.getPosition().x,player->sprite.getPosition().y,35,35);
    //printf("Bas : %i , Haut : %i, Left : %i\n",collisionBot,collisionTop, collisionLeft);
    int x=0,y=0;

    if (player->jump==true)
    {

        if (collisionLeft==0)
        {
            x=0;
            if (collisionTop==1 || collisionTopGround==1)
            {
                player->sprite.move(0,-10);
                y=0;
                *graviter=1;
                *acceleration=-ACCELERATION;
                player->jump=false;
                *boucleJump=1;

                printf("2");


            }
            else if (collisionTop==0 || collisionTopGround==0)
            {
                if (*graviter>6)
                    *graviter=5;
                y=*graviter;
                *graviter+=1;
                printf("1");
            }

        }

        else if (collisionLeft==1)
        {
             if (collisionTop==1 || collisionTopGround==1)
            {
                player->jump=false;
                x-=4;
                y=0;
                *boucleJump=1;
                *acceleration=-ACCELERATION;
                *graviter=1;
                printf("4");
            }
            else if (collisionTop==0 || collisionTopGround==0)
            {
                if (*graviter>6)
                    *graviter=5;
                x=-4;
                y=*graviter;
                *graviter+=1;
                printf("3");
            }

        }



        if (collisionBot==1)
        {
            *boucleJump=JUMP_FRAME_NUM+1;
            *graviter=1;
            //player->sprite.setPosition(player->sprite.getPosition().x,*oldY);
        }
        if (*boucleJump<JUMP_FRAME_NUM)
        {

            (*boucleJump)++;
            *acceleration+=1;
            y=*acceleration;
            printf("5");
        }



    }

    else if (player->jump==false)
    {
        *graviter=4;

        if (collisionLeft==0)
        {
            x=0;

            if (collisionTop==1 || collisionTopGround==1)
            {
                y=0;
                *graviter=1;
                //player->sprite.setPosition(player->sprite.getPosition().x,*oldY);
                //printf("6");
            }

            else if (collisionTop==0 || collisionTopGround==0)
            {
                if (*graviter>6)
                    *graviter=5;

                y=*graviter;
                *graviter+=1;
                //printf("7");

            }
        }

        if (collisionLeft==1)
        {
            if (collisionTop==1 || collisionTopGround==1)
            {
                x=-4;
                *graviter=1;
                //printf("5");
            }
            else if (collisionTop==0 || collisionTopGround==0)
            {
                x-=4;
                if (*graviter>6)
                    *graviter=5;
                y=*graviter;
                *graviter+=1;
                //printf("4");
            }



        }

    }
    *oldY=player->sprite.getPosition().y;
    player->sprite.move(x,y);


}












void mobSpawn(RenderWindow *fenetre,Sprite listeEnnemi[],int *boucleEnnemi,Texture *imgMonstre,int x, int y,Sprite listeTirEnnemi[TAILLE_NOMBRE_ENNEMI][TAILE_NOMBRE_SHOOT_ENNEMI],int *nombreEnnemi)
{

    Perso monstre;
    monstre.sprite.setTexture(*imgMonstre);
    monstre.sprite.setPosition(x,y);
    listeEnnemi[*boucleEnnemi]=monstre.sprite;
    if (*boucleEnnemi==TAILLE_NOMBRE_ENNEMI-1)
        *boucleEnnemi=0;
    (*boucleEnnemi)++;
    (*nombreEnnemi)++;

}

void playerShoot(Perso *player,int *i,Sprite listeS[],Texture *imgTir)
{

    Perso tir;
    tir.sprite.setTexture(*imgTir);
    tir.sprite.setPosition(player->sprite.getPosition().x,player->sprite.getPosition().y);
    listeS[*i]=tir.sprite;
    if (*i==TAILLE_NOMBRE_SHOOT_PLAYER-1)
        *i=0;
    (*i)++;

}


void ShootUpdate(Sprite liste[],RenderWindow *fenetre, int taille,int x)
{
    for(int i=0; i<taille; i++)
    {
        liste[i].move(x,0);
        fenetre->draw(liste[i]);
    }
}

void createMissile(Sprite listeMissile[],int *boucleMissile,int *nbMissile,Texture *imgMissile)
{

    int nb=rand()%8+(-1);
    int y=nb*50;
    if (*boucleMissile==FPS*2)
    {
        Perso missile;
        missile.sprite.setTexture(*imgMissile);
        missile.sprite.setPosition(SPAWN_MISSILE_Y,y);
        listeMissile[*nbMissile]=missile.sprite;
        *boucleMissile=0;
        (*nbMissile)++;
        if(*nbMissile==TAILE_NOMBRE_SHOOT_MISSILE-1)
            *nbMissile=0;


    }
    (*boucleMissile)++;

}

void ennemiShootTimer(int *shootTimer,Texture *imgTir,Sprite listeEnnemi[],Sprite listeTirEnnemi[TAILLE_NOMBRE_ENNEMI][20],int *boucleTirEnnemi)
{

    if (*shootTimer==(FPS*2))
    {

        for (int i=0; i<TAILLE_NOMBRE_ENNEMI; i++)
        {

            printf("%i\n",i);
            Sprite tir;
            tir.setTexture(*imgTir);
            tir.setPosition(listeEnnemi[i].getPosition().x,listeEnnemi[i].getPosition().y);
            listeTirEnnemi[i][*boucleTirEnnemi]=tir;
            if (*boucleTirEnnemi==TAILE_NOMBRE_SHOOT_ENNEMI-1)
                *boucleTirEnnemi=0;
            (*boucleTirEnnemi)++;

        }
        *shootTimer=0;
    }
    (*shootTimer)++;
}

void ennemiShootUpdate(Sprite listeTirEnnemi[TAILLE_NOMBRE_ENNEMI][TAILE_NOMBRE_SHOOT_ENNEMI],RenderWindow *fenetre,int nombreEnnemi)
{
    for (int i=0; i<nombreEnnemi; i++)
    {
        for(int j=0; j<TAILE_NOMBRE_SHOOT_ENNEMI; j++)
        {
            listeTirEnnemi[i][j].move(-VITESSE_SHOOT_ENNEMI,0);
            fenetre->draw(listeTirEnnemi[i][j]);
        }
    }
}




void playerShootTimer(int *shootON,int *playerShootTime)
{
    if (*shootON==1)
    {
        if (*playerShootTime==PLAYER_SHOOT_INTERVAL)
        {
            *shootON=0;
            *playerShootTime=0;
        }
        else
        {
            (*playerShootTime)++;
        }

    }
}

void scoreUpdate(int *score)
{
    (*score)++;
}


