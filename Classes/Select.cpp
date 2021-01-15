/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "Select.h"
#include "Juego.h"
#include "cocos2d.h"
#include "AudioEngine.h"

USING_NS_CC;

Scene* Select::createScene(){
    return Select::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename){
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in SelectScene.cpp\n");
}

void Select::goBack(Ref *pSender){
    if( Juego::numPlayers != -1){
        if( ( Juego::numPlayers == 1 && Juego::indPlayer1 != -1)|| 
        ( Juego::numPlayers == 2 && Juego::indPlayer1 != -1 && Juego::indPlayer2 != -1))
            Director::getInstance()->popScene();
    }
    return;
}

void Select::Shinji(Ref *pSender){
    if(Juego::indPlayer2 == 0) return;
    Juego::indPlayer1 = 0;
    return;
}

void Select::Asuka(Ref *pSender){
    if(Juego::indPlayer2 == 1) return;
    Juego::indPlayer1 = 1;
    return;
}

void Select::Misato(Ref *pSender){
    if(Juego::indPlayer2 == 2) return;
    Juego::indPlayer1 = 2;
    return;
}

void Select::Rei(Ref *pSender){
    if(Juego::indPlayer2 == 3) return;
    Juego::indPlayer1 = 3;
    return;
}

void Select::Shinji2(Ref *pSender){
    if(Juego::indPlayer1 == 0) return;
    Juego::indPlayer2 = 0;
    return;
}

void Select::Asuka2(Ref *pSender){
    if(Juego::indPlayer1 == 1) return;
    Juego::indPlayer2 = 1;
    return;
}

void Select::Misato2(Ref *pSender){
    if(Juego::indPlayer1 == 2) return;
    Juego::indPlayer2 = 2;
    return;
}

void Select::Rei2(Ref *pSender){
    if(Juego::indPlayer1 == 3) return;
    Juego::indPlayer2 = 3;
    return;
}

void Select::Uno(Ref *pSender){
    Juego::numPlayers = 1;
    Juego::indPlayer2 = -1;
    return;
}

void Select::Dos(Ref *pSender){
    Juego::numPlayers = 2;
    Juego::indPlayer2 = -1;
    return;
}

bool Select::init(){
// 1 - Scene init
    if ( !Scene::init() ) { return false; }
    auto origin = Director::getInstance()->getVisibleOrigin();
    auto winSize = Director::getInstance()->getVisibleSize();
    Vec2 visibleSize = Director::getInstance()->getVisibleSize();
    srand (time(NULL));

    AudioEngine::play2d("audio/Fly Me To The Moon (Neon Genesis Evangelion).mp3",true,0.5);

    bg = DrawNode::create();
    bg->drawSolidRect(origin, winSize, Color4F(0.0,0.0,0.0,1.0));
    this->addChild(bg);

    nP = Label::createWithTTF("Number of Players", "fonts/dirtyoldtown.ttf", 35);
    this->addChild(nP);

    itemShinji2 = MenuItemFont::create("Shinji", CC_CALLBACK_1(Select::Shinji2, this));
    itemShinji2->setFontNameObj("fonts/dirtyoldtown.ttf");

    itemAsuka2 = MenuItemFont::create("Asuka", CC_CALLBACK_1(Select::Asuka2, this));
    itemAsuka2->setFontNameObj("fonts/dirtyoldtown.ttf");

    itemMisato2 = MenuItemFont::create("Misato", CC_CALLBACK_1(Select::Misato2, this));
    itemMisato2->setFontNameObj("fonts/dirtyoldtown.ttf");

    itemRei2 = MenuItemFont::create("Rei", CC_CALLBACK_1(Select::Rei2, this));
    itemRei2->setFontNameObj("fonts/dirtyoldtown.ttf");

    itemUno = MenuItemFont::create("1", CC_CALLBACK_1(Select::Uno, this));
    itemUno->setFontNameObj("fonts/dirtyoldtown.ttf");
    
    itemDos = MenuItemFont::create("2", CC_CALLBACK_1(Select::Dos, this));
    itemDos->setFontNameObj("fonts/dirtyoldtown.ttf");

    itemShinji = MenuItemFont::create("Shinji", CC_CALLBACK_1(Select::Shinji, this));
    itemShinji->setFontNameObj("fonts/dirtyoldtown.ttf");

    itemAsuka = MenuItemFont::create("Asuka", CC_CALLBACK_1(Select::Asuka, this));
    itemAsuka->setFontNameObj("fonts/dirtyoldtown.ttf");

    itemMisato = MenuItemFont::create("Misato", CC_CALLBACK_1(Select::Misato, this));
    itemMisato->setFontNameObj("fonts/dirtyoldtown.ttf");

    itemRei = MenuItemFont::create("Rei", CC_CALLBACK_1(Select::Rei, this));
    itemRei->setFontNameObj("fonts/dirtyoldtown.ttf");

    itemRei->setFontSize(60);

    item_start = MenuItemFont::create("Start", CC_CALLBACK_1(Select::goBack, this));
    item_start->setFontNameObj("fonts/dirtyoldtown.ttf");

    item_start->setFontSize(30);

    menu = Menu::create(itemUno, itemDos, item_start,itemShinji,itemAsuka, itemMisato, itemRei, NULL);
    menu->setPosition(Point(0,0));
    this->addChild(menu);
    menu2 = Menu::create(itemShinji2,itemAsuka2, itemMisato2, itemRei2, NULL);
    menu2->setPosition(Point(0,0));
    this->addChild(menu2);

    pl1 = Label::createWithTTF("Player 1", "fonts/dirtyoldtown.ttf", 35);
    this->addChild(pl1);

    pl2 = Label::createWithTTF("Player 2", "fonts/dirtyoldtown.ttf", 35);
    this->addChild(pl2);

// Sprites
    scShinji = Sprite::createWithSpriteFrame(getAnimation("Shinji_Player_%d.png",1, 1).front() );
    scAsuka = Sprite::createWithSpriteFrame(getAnimation("Asuka_Player_%d.png",1, 1).front() );
    scMisato = Sprite::createWithSpriteFrame(getAnimation("Misato_Player_%d.png",1, 1).front() );
    scRei = Sprite::createWithSpriteFrame(getAnimation("Rei_Player_%d.png",1, 1).front() );
    scShinji->runAction(ScaleBy::create(1,1.7 * 1.4));
    scAsuka->runAction(ScaleBy::create(1,1.3 * 1.35));
    scMisato->runAction(ScaleBy::create(1,1.7 * 1.45));
    scRei->runAction(ScaleBy::create(1,1.3 * 1.35));
    this->addChild(scShinji);
    this->addChild(scAsuka);
    this->addChild(scMisato);
    this->addChild(scRei);
    scShinji2 = Sprite::createWithSpriteFrame(getAnimation("Shinji_Player_%d.png",1, 1).front() );
    scAsuka2 = Sprite::createWithSpriteFrame(getAnimation("Asuka_Player_%d.png",1, 1).front() );
    scMisato2 = Sprite::createWithSpriteFrame(getAnimation("Misato_Player_%d.png",1, 1).front() );
    scRei2 = Sprite::createWithSpriteFrame(getAnimation("Rei_Player_%d.png",1, 1).front() );
    scShinji2->runAction(ScaleBy::create(1,1.7 * 1.4));
    scAsuka2->runAction(ScaleBy::create(1,1.3 * 1.35));
    scMisato2->runAction(ScaleBy::create(1,1.7 * 1.45));
    scRei2->runAction(ScaleBy::create(1,1.3 * 1.35));
    this->addChild(scShinji2);
    this->addChild(scAsuka2);
    this->addChild(scMisato2);
    this->addChild(scRei2);

    Juego::numPlayers = 1;
    Juego::indPlayer1 = 0;
    Juego::indPlayer2 = -1;

    posUno();

    this->scheduleUpdate();
    return true;
}


void Select::update(float delta){
     
    if(Juego::numPlayers == 1) posUno();
    else posDos();

    pintar();

    return;
}

void Select::updateMatrix(){
    bg->clear();
    auto origin = Director::getInstance()->getVisibleOrigin();
    auto winSize = Director::getInstance()->getVisibleSize();
    bg->drawSolidRect(origin, winSize, Color4F(0.0,0.0,0.0,1.0));
    return;
}

Vector<cocos2d::SpriteFrame*> Select::getAnimation(const char *format, int count, int delta){
    auto spritecache = SpriteFrameCache::getInstance();
    Vector<cocos2d::SpriteFrame*> animFrames;
    char str[100];
    for(int i = delta + 1; i <= count+delta; i++){
        sprintf(str, format, i);
        // cout<<"String: "<<str<<'\n';
        animFrames.pushBack(spritecache->getSpriteFrameByName(str));
    }
    return animFrames;
}

void Select::posUno(){
    auto origin = Director::getInstance()->getVisibleOrigin();
    auto winSize = Director::getInstance()->getVisibleSize();
    int d = 40;
    float idk; 
    float dist = 240;

    item_start->setPosition(Point(winSize.width/2, 0.9 * winSize.height));
    nP->setPosition(Vec2(winSize.width/2, 4.0*winSize.height/5));
    itemUno->setPosition(Point( 1.3*winSize.width/3, 3.6*winSize.height/5));
    itemDos->setPosition(Point( 1.7*winSize.width/3, 3.6*winSize.height/5));

    idk = 2.2;
    itemShinji->setPosition(Point( winSize.width/5, idk * winSize.height/5 - d));
    itemAsuka->setPosition(Point((2.0 * winSize.width)/5, idk * winSize.height/5 - d));
    itemMisato->setPosition(Point( (3.0 * winSize.width)/5, idk * winSize.height/5 - d));
    itemRei->setPosition(Point( (4.0 * winSize.width)/5, idk * winSize.height/5 - d));
    pl1->setPosition(Vec2(winSize.width/2,3.0* winSize.height/5));
    idk = 2.2;
    scShinji->setPosition(Vec2( (1.0 * winSize.width)/5, idk*winSize.height/5 + d));
    scAsuka->setPosition(Vec2( (2.0 * winSize.width)/5, idk*winSize.height/5 + d));
    scMisato->setPosition(Vec2( (3.0 * winSize.width)/5, idk*winSize.height/5 + d));
    scRei->setPosition(Vec2( (4.0 * winSize.width)/5, idk* winSize.height/5 + d));
    
    itemShinji2->setPosition(Point( winSize.width*2.0, 2.0 * winSize.height));
    itemAsuka2->setPosition(Point((2.0 * winSize.width), 2.0 * winSize.height));
    itemMisato2->setPosition(Point( (3.0 * winSize.width), 2.0 * winSize.height));
    itemRei2->setPosition(Point( (4.0 * winSize.width), 2.0 * winSize.height));
    scShinji2->setPosition(Vec2( (2.0 * winSize.width),2.0* winSize.height));
    scAsuka2->setPosition(Vec2( (2.0 * winSize.width), 2.0* winSize.height));
    scMisato2->setPosition(Vec2( (2.0 * winSize.width),2.0* winSize.height));
    scRei2->setPosition(Vec2( 2.0 * winSize.width, 2.0*winSize.height));
    pl2->setPosition(Vec2(2*winSize.width, 2*winSize.height));
    return;
}


void Select::posDos(){
    auto origin = Director::getInstance()->getVisibleOrigin();
    auto winSize = Director::getInstance()->getVisibleSize();
    int d = 40;
    float idk; 
    float dist = 240;

    item_start->setPosition(Point(winSize.width/2, 0.9 * winSize.height));
    nP->setPosition(Vec2(winSize.width/2, 4.0*winSize.height/5));
    itemUno->setPosition(Point( 1.3*winSize.width/3, 3.6*winSize.height/5));
    itemDos->setPosition(Point( 1.7*winSize.width/3, 3.6*winSize.height/5));

    idk = 2.2;
    itemShinji->setPosition(Point( winSize.width/5, idk * winSize.height/5 - d));
    itemAsuka->setPosition(Point((2.0 * winSize.width)/5, idk * winSize.height/5 - d));
    itemMisato->setPosition(Point( (3.0 * winSize.width)/5, idk * winSize.height/5 - d));
    itemRei->setPosition(Point( (4.0 * winSize.width)/5, idk * winSize.height/5 - d));
    pl1->setPosition(Vec2(winSize.width/2,3.0* winSize.height/5));
    idk = 2.2;
    scShinji->setPosition(Vec2( (1.0 * winSize.width)/5, idk*winSize.height/5 + d));
    scAsuka->setPosition(Vec2( (2.0 * winSize.width)/5, idk*winSize.height/5 + d));
    scMisato->setPosition(Vec2( (3.0 * winSize.width)/5, idk*winSize.height/5 + d));
    scRei->setPosition(Vec2( (4.0 * winSize.width)/5, idk* winSize.height/5 + d));

    idk = 2.2;
    itemShinji2->setPosition(Point( winSize.width/5,-dist+ idk * winSize.height/5 - d));
    itemAsuka2->setPosition(Point((2.0 * winSize.width)/5,-dist+ idk * winSize.height/5 - d));
    itemMisato2->setPosition(Point( (3.0 * winSize.width)/5,-dist+ idk * winSize.height/5 - d));
    itemRei2->setPosition(Point( (4.0 * winSize.width)/5,-dist+ idk * winSize.height/5 - d));
    pl2->setPosition(Vec2(winSize.width/2,-dist + 3.0* winSize.height/5));
    idk = 2.2;
    scShinji2->setPosition(Vec2( (1.0 * winSize.width)/5,-dist+ idk*winSize.height/5 + d ));
    scAsuka2->setPosition(Vec2( (2.0 * winSize.width)/5,-dist + idk*winSize.height/5 + d));
    scMisato2->setPosition(Vec2( (3.0 * winSize.width)/5,-dist+ idk*winSize.height/5 + d));
    scRei2->setPosition(Vec2( (4.0 * winSize.width)/5,-dist + idk* winSize.height/5 + d));

    return;
}

void Select::pintar(){
    if(Juego::numPlayers == 1){
        itemUno->runAction(TintTo::create(0,0,255,255));
        itemDos->runAction(TintTo::create(0,255,255,255));
    }else if(Juego::numPlayers == 2){
        itemUno->runAction(TintTo::create(0,255,255,255));
        itemDos->runAction(TintTo::create(0,0,255,255));
    }else{
        itemUno->runAction(TintTo::create(0,255,255,255));
        itemDos->runAction(TintTo::create(0,255,255,255));
    }

    if(Juego::indPlayer1 == 0) itemShinji->runAction(TintTo::create(0,0,255,255));
    else itemShinji->runAction(TintTo::create(0,255,255,255));

    if(Juego::indPlayer2 == 0) itemShinji2->runAction(TintTo::create(0,0,255,255));
    else itemShinji2->runAction(TintTo::create(0,255,255,255));

    if(Juego::indPlayer1 == 1) itemAsuka->runAction(TintTo::create(0,0,255,255));
    else itemAsuka->runAction(TintTo::create(0,255,255,255));

    if(Juego::indPlayer2 == 1) itemAsuka2->runAction(TintTo::create(0,0,255,255));
    else itemAsuka2->runAction(TintTo::create(0,255,255,255));

    if(Juego::indPlayer1 == 2) itemMisato->runAction(TintTo::create(0,0,255,255));
    else itemMisato->runAction(TintTo::create(0,255,255,255));

    if(Juego::indPlayer2 == 2) itemMisato2->runAction(TintTo::create(0,0,255,255));
    else itemMisato2->runAction(TintTo::create(0,255,255,255));

    if(Juego::indPlayer1 == 3) itemRei->runAction(TintTo::create(0,0,255,255));
    else itemRei->runAction(TintTo::create(0,255,255,255));

    if(Juego::indPlayer2 == 3) itemRei2->runAction(TintTo::create(0,0,255,255));
    else itemRei2->runAction(TintTo::create(0,255,255,255));

    return;
}

