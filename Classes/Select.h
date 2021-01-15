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

#ifndef __SELECT_H__
#define __SELECT_H__

#include "cocos2d.h"
using namespace cocos2d;

#include <bits/stdc++.h>
using namespace std;

#include "AudioEngine.h"

// #include "AudioEngine-linux.h"
//#include "audio/include/AudioEngine.h"
// using namespace CocosDenshion;
// auto audio = AudioEngine::getInstance();
// set the background music and continuously play it.
// audio->playBackgroundMusic("Zankoku na Tenshi no Teeze Instrumental.mp3", true);
// set the background music and play it just once.
// audio->playBackgroundMusic("Zankoku na Tenshi no Teeze Instrumental.mp3", false);


class Select : public cocos2d::Scene{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    // implement the "static create()" method manually
    CREATE_FUNC(Select);

// Variables
    DrawNode* bg;
    Sprite *scShinji, *scAsuka, *scMisato, *scRei;
    Sprite *scShinji2, *scAsuka2, *scMisato2, *scRei2;
    Menu *menu, *menu2;
    MenuItemFont *item_start, *itemRei, *itemMisato;
    MenuItemFont *itemAsuka, *itemShinji, *itemUno, *itemDos;
    MenuItemFont *itemRei2, *itemMisato2;
    MenuItemFont *itemAsuka2, *itemShinji2;
    Label *pl1,*pl2, *nP;

// Funciones
    void goBack(Ref *pSender);
    void Rei(Ref *pSender);
    void Asuka(Ref *pSender);
    void Shinji(Ref *pSender);
    void Misato(Ref *pSender);
    void Rei2(Ref *pSender);
    void Asuka2(Ref *pSender);
    void Shinji2(Ref *pSender);
    void Misato2(Ref *pSender);
    void NumPlayers(Ref *pSender);
    void Uno(Ref *pSender);
    void Dos(Ref *pSender);
    
    void updateMatrix();
    void posUno();
    void posDos();
    void pintar();

    Vector<SpriteFrame*> getAnimation(const char *format, int count, int delta);
    virtual void update(float delta) override;


};

#endif // __HELLOWORLD_SCENE_H__
