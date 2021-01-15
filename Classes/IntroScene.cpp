/*************  videoPlayer***************************************************************
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

#include "IntroScene.h"
#include "Juego.h"
#include "Controles.h"
#include "AudioEngine.h"

USING_NS_CC;

Scene* IntroScene::createScene(){
    return IntroScene::create();
}

static void problemLoading(const char* filename){
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in IntroSceneScene.cpp\n");
}


bool IntroScene::init(){
    if ( !Scene::init() ){
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto &winSize = visibleSize;

    srand (time(NULL));
    AudioEngine::preload("audio/EvangelionOpening.mp3");
    AudioEngine::preload("audio/Fly Me To The Moon (Neon Genesis Evangelion).mp3");
    AudioEngine::preload("audio/Zankoku na Tenshi no Teeze Instrumental.mp3");
    IntroScene::introID = AudioEngine::play2d("audio/EvangelionOpening.mp3",true,1.0f);

// Background TREES
    auto introSprite = Sprite::create("seeleTree.jpg");
    auto s_visibleRect = Director::getInstance()->getOpenGLView()->getVisibleRect();
    float scaleY = s_visibleRect.size.height/introSprite->getContentSize().height;
    float scaleX = s_visibleRect.size.width/introSprite->getContentSize().width;
    if(scaleX>scaleY){introSprite->setScale(scaleX);}else{introSprite->setScale(scaleY);}
    introSprite->setPosition(Point(s_visibleRect.origin.x+s_visibleRect.size.width/2, s_visibleRect.origin.y+s_visibleRect.size.height/2));
    this->addChild(introSprite);
    introSprite->runAction(ScaleBy::create(6,0.4));
    
    auto introTree = Sprite::create("treeWhite.jpg");
    this->addChild(introTree);
    introTree->setPosition(Point(s_visibleRect.origin.x+s_visibleRect.size.width/2, s_visibleRect.origin.y+s_visibleRect.size.height/2));

    // Actions
    introSprite->setOpacity(0);
    introTree->setOpacity(0);
    auto delayB1 = DelayTime::create(6);
    auto delayB2 = DelayTime::create(11.6);
    introSprite->runAction(Sequence::create(FadeIn::create(3),FadeOut::create(3),NULL));

    introTree->runAction(Sequence::create( DelayTime::create(6), ScaleBy::create(6,0.4), NULL ));
    introTree->runAction(Sequence::create( DelayTime::create(6), TintTo::create(2,8,143,255), NULL ));
    introTree->runAction(Sequence::create( DelayTime::create(6), 
    FadeIn::create(3),FadeOut::create(3),NULL));

    auto tittle = Sprite::create("evangelionTIttleWhite.png");
    tittle->setOpacity(0);
    tittle->setPosition(Point(s_visibleRect.origin.x+s_visibleRect.size.width/2, s_visibleRect.origin.y+s_visibleRect.size.height/2));
    tittle->runAction(Sequence::create(delayB2, FadeIn::create(3) ,NULL));
    this->addChild(tittle);

    auto theGame = Label::createWithTTF("THE GAME", "fonts/dirtyoldtown.ttf", 60);
    theGame->setPosition(Point(s_visibleRect.origin.x+s_visibleRect.size.width/2, s_visibleRect.origin.y+s_visibleRect.size.height/2 - 100));
    theGame->setOpacity(0);
    theGame->runAction( Sequence::create( 
        DelayTime::create(12), 
        FadeIn::create(3), NULL)
    );
    this->addChild(theGame);
    theGame->enableShadow();
    theGame->enableOutline(Color4B::BLACK, 3);

// Background TREES



// Background
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Players/Shinji_Player/Shinji_Player.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Players/Rei_Player/Rei_Player.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Players/Asuka_Player/Asuka_Player.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Players/Misato_Player/Misato_Player.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Players/Amarillo_Player/Amarillo_Player.plist");
    // Reis
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Players/Rei_Player/Rei_Uniforme/Rei_Player_Uniforme.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Players/Rei_Player/Rei_Blanco/Rei_Player_Blanco.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Players/Rei_Player/Rei_Negro/Rei_Player_Negro.plist");
    // Asukas
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Players/Asuka_Player/Asuka_Uniforme/Asuka_Player_Uniforme.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Players/Asuka_Player/Asuka_Rojo/Asuka_Player_Rojo.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Players/Asuka_Player/Asuka_Rosa/Asuka_Player_Rosa.plist");

// COSOS SPRITES
map<string, Vector<cocos2d::SpriteFrame*> > frames;
string playerName[] = {"Shinji", "Rei", "Asuka", "Misato", "Amarillo"};
vector<Sprite*> v, vRei, vAsuka, bloques, spritesTodos;
vector<Animation*> animar;//, animarRei, animarAsuka;
// COSOS SPRITES
for(int i=0;i<5;i++){
    string s = playerName[i]+"_Player_%d.png";
    frames[playerName[i]] = getAnimation(s.c_str(), 12, 0);
    v.emplace_back(Sprite::createWithSpriteFrame(frames[playerName[i]].front()));
    this->addChild(v[i]);
    v[i]->setOpacity(0);
    v[i]->setPosition(Vec2(winSize.width * (0.4+(i*.18)), 2 * winSize.height / 5));
    animar.emplace_back(Animation::createWithSpriteFrames( frames[playerName[i]], 1.0f/8));
    v[i]->runAction(Sequence::create(
        DelayTime::create(10),
        ((i == 0 || i == 3) ? (ScaleBy::create(1,3)):(ScaleBy::create(1,2))),
        FadeIn::create(4),
        RepeatForever::create(Animate::create(animar[i])), NULL
    ));
    v[i]->runAction(RepeatForever::create(Animate::create(animar[i])));
    spritesTodos.emplace_back(v[i]);
}
v[0]->setPosition(Vec2(0.5*winSize.width/5, 4*winSize.height / 5));   // Shinji
v[1]->setPosition(Vec2(0.5*winSize.width/5, winSize.height / 5));   // Rei
v[2]->setPosition(Vec2(4.5*winSize.width/5, winSize.height / 5)); // ASUKA
v[3]->setPosition(Vec2(4.5*winSize.width/5, 4*winSize.height / 5)); // Misato
v[4]->setPosition(Vec2( winSize.width/2, 4.2*winSize.height / 5));      // Amarillo

// MENU
    // auto startLabel = Label::createWithTTF("Start", "fonts/dirtyoldtown.ttf", 40);
    // Start Item
    auto startMenuItem = MenuItemFont::create("Play", CC_CALLBACK_1(IntroScene::Start, this));
    startMenuItem->setPosition(Vec2(origin.x + visibleSize.width/4,
                                    origin.y + startMenuItem->getContentSize().height*2.5));
    startMenuItem->setFontNameObj("fonts/dirtyoldtown.ttf");
    // Exit Item
    auto exitMenuItem = MenuItemFont::create("Exit", CC_CALLBACK_1(IntroScene::Exit, this));
    exitMenuItem->setPosition(Vec2(origin.x + 3 * visibleSize.width/4 ,
                                   origin.y + exitMenuItem->getContentSize().height*2.5));
    exitMenuItem->setFontNameObj("fonts/dirtyoldtown.ttf");
    // Controles
    auto control = MenuItemFont::create("Controls", CC_CALLBACK_1(IntroScene::Controles, this));
    control->setPosition(Vec2(origin.x + 2 * visibleSize.width/4 ,
                                   origin.y + control->getContentSize().height*2.5));
    control->setFontNameObj("fonts/dirtyoldtown.ttf");
    // Menu
    auto *startMenu = Menu::create(control,startMenuItem,exitMenuItem, NULL);
    startMenu->setPosition(Point(0,0));
    this->addChild(startMenu, 1);
    startMenu->setOpacity(0);


// ------------------------------------------------------ //
    startMenu->runAction(Sequence::create( 
        DelayTime::create(12), 
        TintTo::create(4,141,200,255), NULL ));
    startMenu->runAction( Sequence::create( 
        DelayTime::create(12), 
        FadeIn::create(3), NULL)
    );
// ------------------------------------------------------ //

// MENU

    return true;
}


void IntroScene::Start( IntroScene::Ref *pSender){
    AudioEngine::stopAll();
    auto scene = Juego::createScene();
    Director::getInstance()->pushScene(scene);
    return;
}

void IntroScene::Controles( IntroScene::Ref *pSender){
    AudioEngine::stopAll();
    auto scene = Controles::createScene();
    Director::getInstance()->pushScene(scene);
    return;
}

void IntroScene::Exit( IntroScene::Ref *pSender){
    Director::getInstance()->end();
    return;
}

Vector<cocos2d::SpriteFrame*> IntroScene::getAnimation(const char *format, int count, int delta){
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

