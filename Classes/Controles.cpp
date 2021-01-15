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

#include "Controles.h"
#include "IntroScene.h"
#include "cocos2d.h"
#include "AudioEngine.h"

USING_NS_CC;

Scene* Controles::createScene(){
    return Controles::create();
}

void Controles::goBack(Ref *pSender){
    AudioEngine::stopAll();
    AudioEngine::play2d("audio/Zankoku na Tenshi no Teeze Instrumental.mp3",true,0.5f);
    Director::getInstance()->popScene();
    return;
}

bool Controles::init(){
// 1 - Scene init
    if ( !Scene::init() ) { return false; }
    auto origin = Director::getInstance()->getVisibleOrigin();
    auto winSize = Director::getInstance()->getVisibleSize();
    Vec2 visibleSize = Director::getInstance()->getVisibleSize();

    bg = DrawNode::create();
    bg->drawSolidRect(origin, winSize, Color4F(0.0,0.0,0.0,1.0));
    this->addChild(bg);

    back = MenuItemFont::create("Back", CC_CALLBACK_1(Controles::goBack, this));
    back->setFontNameObj("fonts/dirtyoldtown.ttf");
    back->setPosition(Point(winSize.width/2,0.08 *winSize.height));
    menu = Menu::create(back, NULL);
    menu->setPosition(Point(0,0));
    this->addChild(menu);

    ins = Label::createWithTTF("CONTROLS", "fonts/dirtyoldtown.ttf", 35);
    ins->setPosition(Vec2(winSize.width/2, 0.9*winSize.height));
    this->addChild(ins);

    pl1 = Label::createWithTTF("Player 1", "fonts/dirtyoldtown.ttf", 35);
    pl1->setPosition(Vec2(winSize.width/2, 0.8*winSize.height));
    this->addChild(pl1);

    pl2 = Label::createWithTTF("Player 2", "fonts/dirtyoldtown.ttf", 35);
    pl2->setPosition(Vec2(winSize.width/2, 0.45*winSize.height));
    this->addChild(pl2);

    m1 = Label::createWithTTF("Move", "fonts/dirtyoldtown.ttf", 35);
    m1->setPosition(Vec2(0.8*winSize.width/7, 0.8*winSize.height - 100));
    this->addChild(m1);

    m2 = Label::createWithTTF("Move", "fonts/dirtyoldtown.ttf", 35);
    m2->setPosition(Vec2(0.8*winSize.width/7, 0.45*winSize.height - 100));
    this->addChild(m2);

    k = Sprite::create("arrowKeys.png");
    k->setPosition(Vec2( 2.1*(winSize.width)/7, 0.8*winSize.height - 110));
    this->addChild(k);
    k->runAction(ScaleBy::create(0,0.6));

    auto b4 = Label::createWithTTF("E", "fonts/dirtyoldtown.ttf", 55);
    b4->setPosition(Vec2(4.9* (winSize.width)/6, 0.45*winSize.height - 110));
    this->addChild(b4);

    auto b3 = Label::createWithTTF("  W  \nA S D", "fonts/dirtyoldtown.ttf", 55);
    b3->setPosition(Vec2( 2.1*(winSize.width)/7, 0.45*winSize.height - 110));
    this->addChild(b3);

    b1 = Label::createWithTTF("Bomb", "fonts/dirtyoldtown.ttf", 35);
    b1->setPosition(Vec2(4.0 *winSize.width/7, 0.8*winSize.height - 110));
    this->addChild(b1);

    b2 = Label::createWithTTF("Bomb", "fonts/dirtyoldtown.ttf", 35);
    b2->setPosition(Vec2(4.0 *winSize.width/7, 0.45*winSize.height - 110));
    this->addChild(b2);

    auto sp = Sprite::create("spaceKey.png");
    sp->setPosition(Vec2(4.9* (winSize.width)/6, 0.8*winSize.height - 110));
    this->addChild(sp);
    sp->runAction(ScaleBy::create(0,0.5,0.4));

    return true;
}


