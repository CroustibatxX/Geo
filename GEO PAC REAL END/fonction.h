#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <fstream>
#include <SFML/Audio.hpp>

using namespace sf;


#define FPS 30
#define TAILLE_PLAYER 35
#define JUMP_FRAME_NUM 16
#define HEIGHT_JUMP 200
#define ACCELERATION 16



#define TAILLE_NOMBRE_ENNEMI 10
#define TAILE_NOMBRE_SHOOT_ENNEMI 20
#define TAILE_NOMBRE_SHOOT_MISSILE 20
#define TAILLE_NOMBRE_SHOOT_PLAYER 10
#define VITESSE_SHOOT_PLAYER 20
#define VITESSE_SHOOT_ENNEMI -20
#define TAILLE_EXPLO 3
#define SPAWN_MISSILE_Y 1000
#define TAILLE_LISTE_SHOOT 10


#define PLAYER_SHOOT_INTERVAL 16




#define COLONNE_MAX 100
#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 600
#define BLOCK_SIZE 50
#define BLOCKSET 1
#define NOTBLOCKSET 0

#define GRAVITE 14
#define MOVE 4


typedef struct{
    int x, y, width, height;
    sf::Sprite sprite;
    bool destroyed = false;
    bool ground = false;
    int type =0;
} Block;

typedef struct
{
    Sprite sprite;
    bool jump;
    int x,y;
} Perso;

typedef struct
{
    int columns[COLONNE_MAX];
    Block block[COLONNE_MAX];
    int nbBlock=0;

} ColumnsGame;

typedef struct
{
    int x;
    int y;

}PointBox;

typedef struct
{
    PointBox a;
    PointBox b;
    PointBox c;
    PointBox d;
}BlockPoints;





Font chargeFont(char nom[ ]);
void afficheMenu(RenderWindow *fenetre, Sprite spFond, Sprite spBack, int *phase);
void selectionPseudo ( RenderWindow *fenetre, Sprite spFond, Sprite spBack, char pseudo[ ], int *phase);
void affiScore( RenderWindow *fenetre, Sprite spFond, Sprite spBack, char pseudoX[ ], int scoreX, int *phase, int *jouer);
void afficheOr( RenderWindow *fenetre, int *phase, int *score );


void gravity(Sprite * spr, int forceUp, int rankOf, bool * collisionBottom, bool * contactLeft, bool * contactUp);
void drawPerso(RenderWindow * fen,Perso player);
void animLeftColumn(ColumnsGame col[],int nbCol, int moveB, Texture * txt);
void drawMob(RenderWindow * fen,Sprite liste[],int taille);
void gravityVerif(Perso * player,int *acceleration,ColumnsGame col[],int nbColonne);
void jumpPlayer(Perso *player,RenderWindow *fenetre,int *acceleration,int *graviter,int *r,ColumnsGame col[],ColumnsGame col2[],int nbColonne,int *oldY);
void mobSpawn(RenderWindow *fenetre,Sprite listeEnnemi[],int *boucleEnnemi,Texture *imgMonstre,int x, int y,Sprite listeTirEnnemi[TAILLE_NOMBRE_ENNEMI][TAILE_NOMBRE_SHOOT_ENNEMI],int *nombreEnnemi);
void playerShoot(Perso *player,int *i,Sprite listeS[],Texture *imgTir);
void ShootUpdate(Sprite liste[],RenderWindow *fenetre, int taille,int x);
void ennemiShootTimer(int *shootTimer,Texture *imgTir,Sprite listeEnnemi[],Sprite listeTirEnnemi[TAILLE_NOMBRE_ENNEMI][20],int *boucleTirEnnemi);
void playerShootTimer(int *shootON,int *playerShootTime);
void scoreUpdate(int *score);
void collisionShootPlayer(Sprite listeShoot[],ColumnsGame col[],int nbCol);
void vieVerif(int *vie,Perso player,Sprite listeMissile[]);
void createMissile(Sprite listeMissile[],int *boucleMissile,int *nbMissile,Texture *imgMissile);


void blockAnimate(Sprite allSprites[],Block spr, Texture allTexture[]);
void blockResize(Block * spr,int width, int height,int blocksize);
void blockArrayRotateAnimate(Block spr[], float finalRotation);
void moveBlock(Block * a, int x, int y);
void FlipBlockHorizontal(Block & spr);
void FlipBlockVertical(Block & spr);
void opacityBlock(Block * spr,float opacite);

void opacityBlock(Block * spr,float opacite);
void drawColumns(RenderWindow * fen,ColumnsGame col[], int nbColonne);
void colorChangeColumns(ColumnsGame col[], int nbColonne,int r,int g, int b);
void colorChangeColumn(ColumnsGame * col,int r,int g, int b);
BlockPoints getBlockBox(Block a);
bool PosInBlock(Block a,int x,int y);
void colorBlocksOnLine(ColumnsGame col[],int nbColonne,int x1,int y1,int x2, int y2, int r, int g, int b);
void removeBlock(Block blcy[], int rankB, int nbBlock);
void breakBlock(ColumnsGame * col,int rankC);
void colorBlocksOnLineAndDestroy(ColumnsGame col[],int nbColonne,int x1,int y1,int x2, int y2, int r, int g, int b);
int collisionBlock(ColumnsGame col[],int nbColonne,int x,int y,int width,int height);
int collisionBlockLeft(ColumnsGame col[],int nbColonne,int x,int y,int width,int height);
int collisionBlockRight(ColumnsGame col[],int nbColonne,int x,int y,int width,int height);
int collisionBlockTop(ColumnsGame col[],int nbColonne,int x,int y,int width,int height);
int collisionBlockBottom(ColumnsGame col[],int nbColonne,int x,int y,int width,int height);
int sommeCube(int rayon);
bool blockInRange(Block a,int x,int y,int width, int height);
void explosionFromPos(ColumnsGame col[],int nbColonne,int x,int y, int rayon);
void getRandomColumn(int columns[],int height, int probaBlock);
void columnGroup(ColumnsGame col[],int nbCol, int height, int probaBlock, Texture * txt, int x, int y, bool ground);
void moveGroup(RenderWindow * fen,ColumnsGame col[], int nbColonne,int x, int y);
ColumnsGame randColumn(int height, int probaBlock, Texture * txt, int x, int y, bool ground);
ColumnsGame columnGroupR(ColumnsGame col[],int nbCol, int height, int probaBlock, Texture txt, int x);
int toucheCoule(ColumnsGame col[],int nbColonne,int x,int y,int width,int height);




int distanceBloc(ColumnsGame col[],int nbColonne,/*int x,int y,int width,int height*/Perso * player);







