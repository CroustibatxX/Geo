#include "fonction.h"

#define PAS_BLOCK 15

using namespace sf;

void animLeftColumn(ColumnsGame col[],int nbCol, int moveB, Texture * txt)
{
    int d=0, e=0;
    for(d=0;d<nbCol;d++)
    {
        for(e=0;e<col[d].nbBlock;e++)
        {
            int prop = WINDOW_WIDTH - (WINDOW_WIDTH/10);
            int diff = WINDOW_WIDTH - prop;
            int wt = 0;
            if(col[d].block[e].sprite.getPosition().x>prop)
            {
                //blockResize(&col[d].block[e],10,10);
                int iu = (int)(((float)(diff-(col[d].block[e].sprite.getPosition().x-prop))/(float)diff)*BLOCK_SIZE);
                int iuu = (int)(((float)(diff-(col[d].block[e].sprite.getPosition().x-prop))/(float)diff)*BLOCK_SIZE);
                //printf("%i : %i\n", prop, diff);
                blockResize(&col[d].block[e],iu,iuu,BLOCK_SIZE);
                wt = iu;
                if(col[d].block[e].sprite.getPosition().x>prop&&col[d].block[e].sprite.getPosition().x<=prop+moveB)
                {
                    Sprite spr;
                    spr.setTexture(*txt);





                    spr.setRotation(col[d].block[e].sprite.getRotation());
                    spr.setPosition(col[d].block[e].sprite.getPosition());
                    col[d].block[e].sprite = spr;
                    //col[d].block[e].sprite.setScale(0.95f/(float)col[d].block[e].sprite.getScale().x,0.95f/(float)col[d].block[e].sprite.getScale().y);
                    //printf("seen");
                }
            }

        }

    }

}

void drawColumns(RenderWindow * fen,ColumnsGame col[], int nbColonne)
{
    int j = 0, k=0, l=0;
    int total = 0;
    //printf("%i  %i\n",nbColonne,col[1].nbBlock);
    for(j=0;j<nbColonne;j++)
    {
        for(k=0;k<col[j].nbBlock;k++)
        {
            fen->draw(col[j].block[k].sprite);
        }
    }
}

void colorChangeColumns(ColumnsGame col[], int nbColonne,int r,int g, int b)
{
    int j = 0, k=0, l=0;
    int total = 0;
    //printf("%i  %i\n",nbColonne,col[1].nbBlock);
    for(j=0;j<nbColonne;j++)
    {
        for(k=0;k<col[j].nbBlock;k++)
        {
            col[j].block[k].sprite.setColor(Color(r,g,b,col[j].block[k].sprite.getColor().a));
        }
    }
}

void colorChangeColumn(ColumnsGame * col,int r,int g, int b)
{
    int j = 0, k=0, l=0;
    int total = 0;
    //printf("%i  %i\n",nbColonne,col[1].nbBlock);

        for(k=0;k<col->nbBlock;k++)
        {
            col->block[k].sprite.setColor(Color(r,g,b));
        }

}

/*Block getBlockByPosition(ColumnsGame col[],int nbColonne,int x1,int y1)
{
    int j = 0, k=0, l=0;
    Block gt;
    int total = 0;
    //printf("%i  %i\n",nbColonne,col[1].nbBlock);
    for(j=0;j<nbColonne;j++)
    {
        for(k=0;k<col[j].nbBlock;k++)
        {
            col[j].block[k].sprite.setColor(Color(r,g,b));
        }
    }
}*/



BlockPoints getBlockBox(Block a)
{
    BlockPoints bp;
    int posX = a.sprite.getPosition().x;
    int posY = a.sprite.getPosition().y;
    if(posX==0||posX<-10000)
    {
        posX = a.x;
        posY = a.y;
    }
    bp.a.x=posX;
    bp.a.y=posY;

    bp.b.x=posX + a.sprite.getTexture()->getSize().x;
    bp.b.y=posY;

    bp.c.x=posX+ a.sprite.getTexture()->getSize().x;
    bp.c.y=posY+ a.sprite.getTexture()->getSize().y;

    bp.d.x=posX;
    bp.d.y=posY+ a.sprite.getTexture()->getSize().y;
    return bp;

}

bool PosInBlock(Block a,int x,int y)
{
    bool is = false;
    BlockPoints bp = getBlockBox(a);
    if(x>=bp.a.x&&x<=bp.b.x&&y>=bp.a.y&&y<=bp.c.y)
    {
        is = true;
    }
    return is;
}
void colorBlocksOnLine(ColumnsGame col[],int nbColonne,int x1,int y1,int x2, int y2, int r, int g, int b)
{
    int j = 0, k=0, l=0;
    int a = 0;
    int total = 0;
    //printf("%i  %i\n",nbColonne,col[1].nbBlock);
    for(j=0;j<nbColonne;j++)
    {

        for(k=0;k<col[j].nbBlock;k++)
        {
            a=0;
            float distance = sqrt(pow(x2-x1,2)+pow(y2-y1,2));
            float val = distance;
            float coef = ((float)y2-(float)y1)/((float)x2-(float)x1);
            if(coef<0)
            {
                coef = -coef;
            }
            if(coef==0)
            {
                coef=0.1f;
            }
            float facteur = 5.0f;


            while(val>facteur*3)
            {

                float x=((float)x1+(facteur*(float)a));
                if(PosInBlock(col[j].block[k],x,(float)y1 - (facteur*(float)a)*coef))
                {
                    col[j].block[k].sprite.setColor(Color(r,g,b));



                }

                //printf("%i\n", a);

                //printf("%i",a);
                /*float posd = x;
                float posr = (float)y1 - (facteur*(float)a)*coef;
                //printf("%lf",sqrt((double)pow((double)(x2-posd),2)+(double)pow((double)(y2-posr),2)))
                float a1 = ((float)abs(x2-(int)posd))*((float)abs(x2-(int)posd));
                float a2 = ((float)abs(y2-(int)posr))*((float)abs(y2-(int)posr));*/


                //val=sqrt(a1+a2);
                //printf("%f\n",val);
                val = val -col[0].block[0].sprite.getTexture()->getSize().y/4;
                a++;




            }
        }
    }
}

void removeBlock(Block blcy[], int rankB, int nbBlock)
{

    int h = 0;
    int remov = 0;
    //printf("nb block : %i\n",nbBlock);
    for(h=0;h<nbBlock;h++)
    {
        if(h!=rankB)
        {

        }
        else
        {

            opacityBlock(&blcy[h],0.0f);
           //blcy[h].sprite = t;
        }
    }
}


void breakBlock(ColumnsGame * col,int rankC)
{
    int data[sizeof(col->columns)+1];
    memcpy(data, col->columns, sizeof(col->columns)+1);
    if(rankC<sizeof(col->columns)+1)
    {
        col->columns[rankC] = 0;
        removeBlock(col->block,rankC,col->nbBlock);

    }
}


void colorBlocksOnLineAndDestroy(ColumnsGame col[],int nbColonne,int x1,int y1,int x2, int y2, int r, int g, int b)
{
    int j = 0, k=0, l=0;
    int a = 0;
    int total = 0;
    //printf("%i  %i\n",nbColonne,col[1].nbBlock);
    for(j=0;j<nbColonne;j++)
    {

        for(k=0;k<col[j].nbBlock;k++)
        {
            a=0;
            float distance = sqrt(pow(x2-x1,2)+pow(y2-y1,2));
            float val = distance;
            float coef = ((float)y2-(float)y1)/((float)x2-(float)x1);
            if(coef<0)
            {
                coef = -coef;
            }
            if(coef==0)
            {
                coef=0.1f;
            }
            float facteur = 5.0f;


            while(val>facteur*3)
            {

                float x=((float)x1+(facteur*(float)a));
                if(PosInBlock(col[j].block[k],x,(float)y1 - (facteur*(float)a)*coef))
                {
                    col[j].block[k].sprite.setColor(Color(r,g,b));
                    breakBlock(&col[j],k);
                    //removeBlock(col[j].block,k,col[j].nbBlock);


                }

                //printf("%i\n", a);

                //printf("%i",a);
                /*float posd = x;
                float posr = (float)y1 - (facteur*(float)a)*coef;
                //printf("%lf",sqrt((double)pow((double)(x2-posd),2)+(double)pow((double)(y2-posr),2)))
                float a1 = ((float)abs(x2-(int)posd))*((float)abs(x2-(int)posd));
                float a2 = ((float)abs(y2-(int)posr))*((float)abs(y2-(int)posr));*/


                //val=sqrt(a1+a2);
                //printf("%f\n",val);
                val = val -col[0].block[0].sprite.getTexture()->getSize().y/4;
                a++;




            }
        }
    }
}


int collisionBlock(ColumnsGame col[],int nbColonne,int x,int y,int width,int height)
{
    int toReturn = 0;
    // 1 = top , 2=right side, 3= down side, 4 = left side
    int j = 0, k=0, l=0;
    BlockPoints gt;
    int total = 0;
    //printf("%i  %i\n",nbColonne,col[1].nbBlock);
    for(j=0;j<nbColonne;j++)
    {
        for(k=0;k<col[j].nbBlock;k++)
        {
            gt = getBlockBox(col[j].block[k]);
            if(y<=gt.a.y+(2 + PAS_BLOCK)&&y>=gt.a.y&&x>=gt.a.x-width&&x<=gt.b.x-width)
            {
                toReturn=1;
            }
            else if(y>=gt.a.y-height&&y<=gt.a.y+height&&x>=gt.b.x-(2 + PAS_BLOCK)&&x<=gt.b.x)
            {
                toReturn=2;
            }
            else if(y>=gt.c.y-(2 + PAS_BLOCK)&&y<=gt.c.y&&x>=gt.d.x-width&&x<=gt.b.x+width)
            {
                toReturn=3;
            }
            else if(y>=gt.d.y-height&&y<=gt.d.y+height&&x>=gt.d.x&&x<=gt.b.x+(2 + PAS_BLOCK))
            {
                toReturn=4;
            }


        }
    }
    return toReturn;
}

int toucheCoule(ColumnsGame col[],int nbColonne,int x,int y,int width,int height)
{
    int toReturn = 0;
    // 1 = top , 2=right side, 3= down side, 4 = left side
    int j = 0, k=0, l=0;
    BlockPoints gt;
    int total = 0;
    //printf("%i  %i\n",nbColonne,col[1].nbBlock);
    for(j=0;j<nbColonne;j++)
    {
        for(k=0;k<col[j].nbBlock;k++)
        {
            gt = getBlockBox(col[j].block[k]);
            if(x>=gt.a.x-width&&x<=gt.b.x+width&&y>=gt.a.y-height&&y<=gt.c.y+height&&col[j].block[k].destroyed==false)
            {
                toReturn=1;
            }



        }
    }
    return toReturn;
}

int collisionBlockLeft(ColumnsGame col[],int nbColonne,int x,int y,int width,int height)
{
    int toReturn = 0;
    // 1 = top , 2=right side, 3= down side, 4 = left side
    int j = 0, k=0, l=0;
    BlockPoints gt;
    int total = 0;
    //printf("%i  %i\n",nbColonne,col[1].nbBlock);
    for(j=0;j<nbColonne;j++)
    {
        for(k=0;k<col[j].nbBlock;k++)
        {
            gt = getBlockBox(col[j].block[k]);

            if(y+height>gt.a.y+3&&y<=gt.d.y&&x+width<=gt.d.x +(2 + PAS_BLOCK)&&x+width>=gt.d.x-1&&col[j].block[k].destroyed == false)
            {
                if(x+width>=gt.a.x)
                {
                    if(y+width>=gt.a.y&&y<=gt.d.y)
                    {
                        toReturn=1;
                    }
                }
                else
                {
                    toReturn=1;
                }

            }


        }
    }
    return toReturn;
}

int distanceBloc(ColumnsGame col[],int nbColonne,/*int x,int y,int width,int height,*/Perso * player)
{
    int toReturn = 0;
    int found = 0;
    // 1 = top , 2=right side, 3= down side, 4 = left side
    int j = 0, k=0, l=0, rr = 0;
    BlockPoints gt;
    int total = 0;
    //printf("%i  %i\n",nbColonne,col[1].nbBlock);
    for(j=0;j<nbColonne;j++)
    {
        for(k=0;k<col[j].nbBlock;k++)
        {
            //printf("%i\n",col[j].block[k].sprite.getPosition().y);
            //col[j].block[k].sprite.move(2,2);
            /*col[3].block[1].sprite.setOrigin(0,19);*/
            //printf("%i\n",col[3].block[1].y);
            //col[j].block[k].sprite.move(2,2);

            gt = getBlockBox(col[j].block[k]);
            //printf("google %i\n",col[j].block[k].y);
            for(rr=0;rr<15;rr++)
            {
                /*
                if(PosInBlock(col[j].block[k],x,y-((HAUTEUR_PLAYER)*rr))&&found==0&&col[j].block[k].destroyed==false)
                {

                    toReturn = abs((int)y-(int)col[j].block[k].y);
                    //printf("google %i\n",col[j].block[k].y);
                    found=1;
                }*/

                if (player->sprite.getGlobalBounds().intersects(col[j].block[k].sprite.getGlobalBounds())&&found==0&&col[j].block[k].destroyed==false)
                {
                    //printf("google %i\n",col[j].block[k].y);
                    if(player->sprite.getPosition().x+player->sprite.getTexture()->getSize().x<=col[j].block[k].x)
                    {
                        toReturn = abs((int)player->sprite.getPosition().y-(int)col[j].block[k].y);

                        found=1;
                    }


                }
            }



        }
    }

}

int collisionBlockRight(ColumnsGame col[],int nbColonne,int x,int y,int width,int height)
{
    int toReturn = 0;
    // 1 = top , 2=right side, 3= down side, 4 = left side
    int j = 0, k=0, l=0;
    BlockPoints gt;
    int total = 0;
    //printf("%i  %i\n",nbColonne,col[1].nbBlock);
    for(j=0;j<nbColonne;j++)
    {
        for(k=0;k<col[j].nbBlock;k++)
        {
            gt = getBlockBox(col[j].block[k]);

            if(y>=gt.a.y-height&&y<=gt.a.y+height&&x>=gt.b.x-(2 + PAS_BLOCK)&&x<=gt.b.x&&col[j].block[k].destroyed == false)
            {
                toReturn=1;
            }


        }
    }
    return toReturn;
}

int collisionBlockTop(ColumnsGame col[],int nbColonne,int x,int y,int width,int height)
{
    int toReturn = 0;
    // 1 = top , 2=right side, 3= down side, 4 = left side
    int j = 0, k=0, l=0;
    BlockPoints gt;
    int total = 0;
    //printf("%i  %i\n",nbColonne,col[1].nbBlock);
    for(j=0;j<nbColonne;j++)
    {
        for(k=0;k<col[j].nbBlock;k++)
        {
            gt = getBlockBox(col[j].block[k]);

            if(y+height<=gt.a.y+(4 + PAS_BLOCK)&&y+height>=gt.a.y&&x+width>=gt.a.x&&x<gt.b.x&&col[j].block[k].destroyed == false)
            {
                if(y>gt.a.y)
                {
                    if(x>=gt.a.x&&x+width<=gt.b.x)
                    {

                        toReturn=1;
                    }
                }
                else{
                    toReturn=1;
                }

            }


        }
    }
    return toReturn;
}

int collisionBlockBottom(ColumnsGame col[],int nbColonne,int x,int y,int width,int height)
{
    int toReturn = 0;
    // 1 = top , 2=right side, 3= down side, 4 = left side
    int j = 0, k=0, l=0;
    BlockPoints gt;
    int total = 0;
    //printf("%i  %i\n",nbColonne,col[1].nbBlock);
    for(j=0;j<nbColonne;j++)
    {
        for(k=0;k<col[j].nbBlock;k++)
        {
            gt = getBlockBox(col[j].block[k]);

            if(y>=gt.c.y-(2 + PAS_BLOCK)&&y<=gt.c.y+1&&x+width>gt.d.x&&x<gt.b.x&&col[j].block[k].destroyed == false)
            {
                if(y<gt.c.y)
                {
                    if(x>gt.c.x&&x+width<=gt.c.x)
                    {
                        toReturn=1;
                    }
                }
                else
                {
                    toReturn=1;
                }

            }


        }
    }
    return toReturn;
}
int sommeCube(int rayon)
{
    int a = 0;
    int somme = 1;
    for(a=0;a<rayon;a++)
    {
        somme += a*8;
    }
    return somme;
}
bool blockInRange(Block a,int x,int y,int width, int height)
{
    BlockPoints gt = getBlockBox(a);
    bool t = false;
    if(gt.a.x>=x&&gt.b.x<=x+width&&gt.c.y<=y+height&&gt.c.y>=y)
    {
        t= true;
    }
    return t;
}
void explosionFromPos(ColumnsGame col[],int nbColonne,int x,int y, int rayon)
{
    int j = 0, k=0, l=0;
    BlockPoints gt;
    int sommeDesCube = sommeCube(rayon);
    int xdebut = x-((rayon-1)*BLOCK_SIZE);
    int ydebut = y-((rayon-1)*BLOCK_SIZE);
    int zoneSize = ((rayon-1)*BLOCK_SIZE) *2;
    //printf("Xbegin at : %i for nb : %i\n", xdebut,sommeDesCube);
    int total = 0;
    //printf("%i  %i\n",nbColonne,col[1].nbBlock);
    for(j=0;j<nbColonne;j++)
    {
        for(k=0;k<col[j].nbBlock;k++)
        {

           int h = 0;
           int y=1;


           for(h=0;h<sommeDesCube;h++)
           {
               if(y>sqrt(rayon))
               {
                   y=1;
               }
               if(blockInRange(col[j].block[k],xdebut,ydebut,zoneSize,zoneSize))
               {

                   breakBlock(&col[j],k);

               }
               y++;
           }

        }
    }
}


void getRandomColumn(int columns[],int height, int probaBlock)
{
    int a = 0, b = 0, c=0;

    for(a=0;a<height;a++)
    {
        columns[a]=0;
    }

    for(b=0;b<height;b++)
    {
         c = (int)(rand()%probaBlock);
        //printf("the c value : %i\n", c);
        //system("pause");

        if(c == probaBlock-1)
        {

            columns[b]=1;
        }
    }
    //printf("%i  %i  %i  %i %i %i\n\n", columns[0],columns[1],columns[2],columns[3],columns[4],columns[5]);


}






ColumnsGame randColumn(int height, int probaBlock, Texture * txt, int x, int y,bool ground)
{
    //printf("Height : %i\n", height);
    ColumnsGame col;
    int spr = 0,u, b=0, kk=0;
    int columns[height];
    //printf("%d\n", ground);
    if(!ground)
    {
        getRandomColumn(col.columns,height, probaBlock);
    }
    else
    {
        int c = 0;
        for(c=0;c<height;c++)
        {
            col.columns[c] = 1;
        }
    }

    //memcpy(col.columns,columns,height);
    /*for(kk=0;kk<15;kk++)
    {
        printf("val: %i\n", col.columns[kk]);
    }*/
    //printf("%i  %i  %i  %i %i %i\n\n", col.columns[0],col.columns[1],col.columns[2],col.columns[3],col.columns[4],col.columns[5]);
    for(u=0;u<height;u++)
    {

        if(col.columns[u]==1)
        {
            Block blc;
            Sprite sprt;
            sprt.setTexture(*txt);
            sprt.setPosition(x,BLOCK_SIZE*u+y);
            //printf("%i\n", sprt.getPosition().x);
            blc.sprite  =sprt;
            blc.height = BLOCK_SIZE;
            blc.width = BLOCK_SIZE;
            blc.x = x;

            blc.y = BLOCK_SIZE*u+y;
            col.block[spr].sprite.setTexture(*txt);
            col.block[spr] = blc;
            if(ground)
            {
                col.block[spr].ground = true;
            }
            spr++;
            //printf("%i\n", blc.sprite.getPosition().x);
            col.nbBlock++;
        }
        //printf("%i\n",col.columns[u]);
    }

    return col;
}


ColumnsGame columnGroupR(ColumnsGame col[],int nbCol, int height, int probaBlock, Texture txt, int x)
{
    int a = 0;

    for(a=0;a<nbCol;a++)
    {
       // col[a]=randColumn(height, probaBlock, txt, x + BLOCK_SIZE*a);

    }

}


void columnGroup(ColumnsGame col[],int nbCol, int height, int probaBlock, Texture * txt, int x,int y ,bool ground)
{
    int a = 0;

    ColumnsGame c = randColumn(height, probaBlock, txt, x + BLOCK_SIZE*a, y, ground);

    //printf("%i %i %i\n\n", c.block[2].sprite.getPosition().x,c.block[1].sprite.getPosition().x,c.block[0].sprite.getPosition().x);
    for(a=0;a<nbCol;a++)
    {
        int k = 0;
        //printf("%i", c.nbBlock);
        for(k=0;k<c.nbBlock;k++)
        {
            //printf("%i\n",c.nbBlock);
            if(a!=0)
            {
                c.block[k].sprite.move(BLOCK_SIZE,0);
            }


        }
        col[a]=c;

        //printf("a: %i\n",col[a].nbBlock);
    }

}




void moveGroup(RenderWindow * fen,ColumnsGame col[], int nbColonne,int x, int y)
{
    int j = 0, k=0, l=0;
    int total = 0;
    //printf("%i  %i\n",nbColonne,col[1].nbBlock);
    for(j=0;j<nbColonne;j++)
    {
        for(k=0;k<col[j].nbBlock;k++)
        {
            col[j].block[k].sprite.move(x,y);
            col[j].block[k].x = col[j].block[k].x + x;
            col[j].block[k].y = col[j].block[k].y + y;
        }
    }
}






