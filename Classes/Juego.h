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

#ifndef __JUEGO_H__
#define __JUEGO_H__

#include "cocos2d.h"
using namespace cocos2d;

#include <bits/stdc++.h>
using namespace std;

#include "AudioEngine.h"

#define fi first
#define se second


// set the background music and continuously play it.
// audio->playBackgroundMusic("Zankoku na Tenshi no Teeze Instrumental.mp3", true);

class Juego : public cocos2d::Scene{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    // implement the "static create()" method manually
    CREATE_FUNC(Juego);

// Clases
    class Player{
    public:
        float x,y;
        Sprite* sprite;
        string name;
        int bombas = 2;
        int score = 0;
        int potencia = 1;

        
        Player() = default;
        Player(const Player&) = delete;
        ~Player(){}
        
        void updateCoord(float _x, float _y, float a, float b, float c, float d);
        int getCoordinateX();
        int getCoordinateY();

    };

    class Bomba{
    public:
        float x,y;
        int potencia = 2;
        int player, playerInd;
        int tiempo;

        Bomba() = default;
        Bomba(const Bomba&) = delete;
        ~Bomba(){}

    };

// Variables
    static int numPlayers; // = 2; 
    static int indPlayer1, indPlayer2;
    int numEdificios = 0;
    int numColors = 7;
    Player pl[4]; // Players
    vector<pair<int,int> > checkEdificios;
    static set<pair<int,int> > edificios;
    int dist = 220, inDist = 50, hei = 40;
    vector<Color4F> colors, bombColor;
    DrawNode* bg;
    Player p1, p2, p3, p4;
    int tiempo = 0, rojo = 0, colInd = 0;
    int tiempoBombas = 0;
    int ancho = 20, alto = 14;
    vector<vector<int>> mat;
    float radio = 12, angle = 180;
    unsigned int segments = 35;
    int inix = 40, iniy = 168, dt = 40;
    float R=0.0,G=0.0,B=0.0;
    Sprite *scShinji, *scAsuka, *scMisato, *scRei;
    vector<Label*> scLabel;
    Label *ScoreLabel, *timeLabel, *timeNumberLabel;
    float limIzq = inix+10, limDer = inix + ancho*dt - 10;
    float limUp = iniy + alto*dt - 10, limDown = iniy + 10;
    int audioIDscene;
    bool spacePressed = false;
    queue<Bomba*> bombas, bombAux;
    int playTime = 180;
    bool startGame= false;

// Functions
    virtual void update(float delta) override;
    void goBack(Ref *pSender);
    Vector<SpriteFrame*> getAnimation(const char *format, int count, int delta);
    int checkColor(int _x, int _y);
    void updateMatrix();
    void updateBombas();
    void calcPlayerScore();
    void moveBots();
    void pintarMatrix(Bomba* bom);
    void putBomba(int indPlay);
    void actPlayTime();
    bool canGenerateBuilding(int _x, int _y);
    void Iniciar();

    bool isKeyPressed(cocos2d::EventKeyboard::KeyCode);
    double keyPressedDuration(cocos2d::EventKeyboard::KeyCode);
    void keyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);

private:
    static std::map<cocos2d::EventKeyboard::KeyCode,
        std::chrono::high_resolution_clock::time_point> keys;

};

#endif

