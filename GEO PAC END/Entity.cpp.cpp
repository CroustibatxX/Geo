#include "fonction.h"


using namespace sf;


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


void jumpPlayer(Perso *player,RenderWindow *fenetre,int *acceleration,int *graviter,int *r,ColumnsGame col[],int nbColonne,int *oldY)
{
    int collisionBot=collisionBlockBottom(col,nbColonne,player->sprite.getPosition().x,player->sprite.getPosition().y,35,35);
    int collisionTop=collisionBlockTop(col,nbColonne,player->sprite.getPosition().x,player->sprite.getPosition().y,35,35);
    int collisionRight=collisionBlockRight(col,nbColonne,player->sprite.getPosition().x,player->sprite.getPosition().y,35,35);
    //printf("%i",collisionRight);
    int x=0,y=0;
    if (player->jump==true)
    {
        if (collisionBot==1)
        {
            *r=17;
            *acceleration=0;
            player->sprite.setPosition(player->sprite.getPosition().x,*oldY);

        }
        else if (*r>0 && *r<JUMP_FRAME_NUM)
        {
            (*r)++;
            *acceleration+=1;
            y=*acceleration;
        }
        else if (/*collisionTop==1*/player->sprite.getPosition().y>=450-*acceleration-1-35)
        {
            y=0;
            player->sprite.setPosition(player->sprite.getPosition().x,450-35);
            *acceleration=-ACCELERATION;
            player->jump=false;
            *r=1;
        }
        else
        {
            y=*acceleration;
            *acceleration+=1;
        }


    }

    if (player->jump==false)
    {
        if (/*collisionTop==1*/player->sprite.getPosition().y>400-35)
        {
            y=0;
            *graviter=1;
        }
        else
        {
            y=*graviter;
            *graviter+=1;
        }


    }

    *oldY=player->sprite.getPosition().y;
    player->sprite.move(x,y);




}


void affichageTexteVariable(Font police,RenderWindow *fenetre,char textEcrire[TAILLE_CHAINE_CARACTERE],int x,int y,int taille)
{
    char text[TAILLE_CHAINE_CARACTERE];
    Text texte;
    texte.setFont(police);
    texte.setString(textEcrire);
    texte.setCharacterSize(taille);
    texte.setPosition(x,y);
    texte.setColor(Color::White);
    fenetre->draw(texte);

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


void playerShootUpdate(Sprite liste[],RenderWindow *fenetre)
{
    for(int i=0; i<50; i++)
    {
        liste[i].move(VITESSE_SHOOT_PLAYER,0);
        fenetre->draw(liste[i]);
    }
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
        if (*playerShootTime==32)
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
    printf("%i\n",*score);
}
