#include "fonction.h"

using namespace sf;


void blockAnimate(Sprite allSprites[],Block spr, Texture allTexture[])
{

    allSprites[0] = spr.sprite;
    if(sizeof(allTexture)+1>0)
    {
        int a = 0;
        for(a=0;a<sizeof(allTexture)+1;a++)
        {
            spr.sprite.setTexture(allTexture[a]);
            allSprites[a+1] = spr.sprite;
        }
    }
}

void blockResize(Block * spr,int width, int height,int blocksize)
{
    int getWidth, getHeight;
    /*if(spr->width!=0&&spr->height!=0)
    {
        getWidth = spr->width;
        getHeight = spr->height;
    }
    else{
        getWidth = spr->sprite.getTexture()->copyToImage().getSize().x;
        getHeight = spr->sprite.getTexture()->copyToImage().getSize().y;
    }*/
    float widthF = (float)width/(float)blocksize;
    float heightF = (float)height/(float)blocksize;
    spr->sprite.setScale(widthF,heightF);
    //spr->sprite.setPosition(spr->sprite.getPosition().x -(spr->sprite.getScale().x/12)*blocksize,spr->sprite.getPosition().y -(spr->sprite.getScale().y/12)*blocksize);
    spr->width = getWidth;
    spr->height = getHeight;
}

void blockArrayRotateAnimate(Block spr[], float finalRotation)
{
    int nb = sizeof(spr)+1, a = 0;
    float pas = finalRotation/nb;
    for(a=0;a<nb;a++)
    {
        spr[a].sprite.setRotation((a+1)*pas);
    }
}

void moveBlock(Block * a, int x, int y)
{
    a->x = a->sprite.getPosition().x;
    a->y = a->sprite.getPosition().y;

    a->sprite.move(x,y);
}

void FlipBlockHorizontal(Block & spr)
{
    Texture tx;
    Image g = spr.sprite.getTexture()->copyToImage();
    g.flipHorizontally();
    tx.loadFromImage(g);
    spr.sprite.setTexture(tx);
}
void FlipBlockVertical(Block & spr)
{
    Texture tx;
    Image g = spr.sprite.getTexture()->copyToImage();
    g.flipVertically();
    tx.loadFromImage(g);
    spr.sprite.setTexture(tx);
}

void opacityBlock(Block * spr,float opacite)
{
    sf::Color color(spr->sprite.getColor().r,spr->sprite.getColor().g,spr->sprite.getColor().b, (float)(255*(opacite/100)));
    spr->sprite.setColor(color);
    spr->destroyed = true;
}



