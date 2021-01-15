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

#include "IntroScene.h"
#include "Juego.h"
#include "Select.h"
#include "cocos2d.h"
#include "AudioEngine.h"

USING_NS_CC;

Scene* Juego::createScene(){
    return Juego::create();
}

bool Juego::init(){
// 1 - Scene init
    if ( !Scene::init() ) { return false; }
// 2 Window
    srand (time(NULL));
    //audioIDscene = AudioEngine::play2d("audio/Zankoku na Tenshi no Teeze Instrumental.mp3",0.5f,true);
    auto origin = Director::getInstance()->getVisibleOrigin();
    auto winSize = Director::getInstance()->getVisibleSize();
    Vec2 visibleSize = Director::getInstance()->getVisibleSize();
    auto s_visibleRect = Director::getInstance()->getOpenGLView()->getVisibleRect();
// 3 Background
    bg = DrawNode::create();
    bg->drawSolidRect(origin, winSize, Color4F(0.0,0.0,0.0,1.0));
    this->addChild(bg);
// Keyboard Event Listener
    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyReleased = CC_CALLBACK_2(Juego::keyReleased, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);

    auto eventListener = EventListenerKeyboard::create();
    Director::getInstance()->getOpenGLView()->setIMEKeyboardState(true);
    eventListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event){
        // If a key already exists, do nothing as it will already have a time stamp
        // Otherwise, set's the timestamp to now
        if(keys.find(keyCode) == keys.end()){
            keys[keyCode] = std::chrono::high_resolution_clock::now();
        }
    };
    eventListener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event){
        // remove the key.  std::map.erase() doesn't care if the key doesnt exist
        keys.erase(keyCode);
    };
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener,this);
    this->scheduleUpdate();

    return true;
}

void Juego::Iniciar(){

// Colores
// Blanco // Negro // Gris // Red // Green // Blue // Yellow // Morado // Celeste
// Asuka - Rojo
// Rei - Azul celeste
// Shinji - Blanco
// Misato - Morado
    colors.emplace_back(Color4F(1.0,1.0,1.0,1.0));  // Blanco
    colors.emplace_back(Color4F(0.0,0.0,0.0,1.0));  // Negro
    colors.emplace_back(Color4F(0.1,0.1,0.1,1.0));  // Gris
    colors.emplace_back(Color4F(1.0,0.0,0.0,1.0));  // Red
    colors.emplace_back(Color4F(0.0,1.0,0.0,1.0));  // Green
    colors.emplace_back(Color4F(0.0,0.0,1.0,1.0));  // Blue
    colors.emplace_back(Color4F(1.0,1.0,0.0,1.0));  // Yellow
    colors.emplace_back(Color4F(1.0 * float(106.0/255.0),1.0 * float(32.0/255.0),1.0,1.0));  // Morado
    colors.emplace_back(Color4F(1.0 * float(161.0/255.0),1.0 * float(215.0/255.0),1.0,1.0));  // Celeste

    bombColor.emplace_back(Color4F(float(255.0/255.0) ,float(77.0/255.0),float(77.0/255.0),1.0));  // Rojo
    bombColor.emplace_back(Color4F(float(255.0/255.0) ,float(183.0/255.0),float(66.0/255.0),1.0));  // Rojo
    bombColor.emplace_back(Color4F(float(242.0/255.0) ,float(255.0/255.0),float(40.0/255.0),1.0));  // Amarillo
    bombColor.emplace_back(Color4F(float(219.0/255.0) ,float(255.0/255.0),float(137.0/255.0),1.0));  // VERDE

// Menu Derecha
    auto item_menu_1 = MenuItemFont::create(" Quit\nGame", CC_CALLBACK_1(Juego::goBack, this));
    auto *menu = Menu::create(item_menu_1, NULL);
    item_menu_1->setFontNameObj("fonts/dirtyoldtown.ttf");
    // item_menu_1->setFontSize(20);
    item_menu_1->setPosition(Point(900 + item_menu_1->getContentSize().width/2 ,640));
    menu->setPosition(Point(0,0));
    this->addChild(menu);
// Score
    scShinji = Sprite::createWithSpriteFrame(getAnimation("Shinji_Player_%d.png",1, 1).front() );
    scAsuka = Sprite::createWithSpriteFrame(getAnimation("Asuka_Player_%d.png",1, 1).front() );
    scMisato = Sprite::createWithSpriteFrame(getAnimation("Misato_Player_%d.png",1, 1).front() );
    scRei = Sprite::createWithSpriteFrame(getAnimation("Rei_Player_%d.png",1, 1).front() );
    scShinji->setPosition(Vec2(inDist + dist*0, hei));
    scAsuka->setPosition(Vec2(inDist + dist*1, hei));
    scMisato->setPosition(Vec2(inDist + dist*2, hei));
    scRei->setPosition(Vec2(inDist + dist*3, hei));
    this->addChild(scShinji);
    this->addChild(scAsuka);
    this->addChild(scMisato);
    this->addChild(scRei);
    scShinji->runAction(ScaleBy::create(1,1.7));
    scAsuka->runAction(ScaleBy::create(1,1.3));
    scMisato->runAction(ScaleBy::create(1,1.7));
    scRei->runAction(ScaleBy::create(1,1.3));
// Label Score
    for(int i = 0; i<4; i++){
        scLabel.emplace_back(Label::createWithTTF("0000", "fonts/dirtyoldtown.ttf", 20));
        scLabel[i]->setPosition(Vec2(inDist + dist*(i+0.4), hei));
        this->addChild(scLabel[i]);
    }
    ScoreLabel = Label::createWithTTF("Score", "fonts/dirtyoldtown.ttf", 40);
    ScoreLabel->setPosition(Vec2(480 - ScoreLabel->getContentSize().width/2, 2.35*hei));
    this->addChild(ScoreLabel);

// cout<<"Medidas\n" << "X: " << s_visibleRect.origin.x+s_visibleRect.size.width << "\nY : "<< s_visibleRect.origin.y+s_visibleRect.size.height<<'\n';
//      ----------------           FONDO        ----------------------
//    Pantalla: 1024 x   768 y
///   20 ancho,    14 alto    + 2 y 2 extras, recuadro
//    22*40 = 880      1024-880 = 144      144/2 = 72
//    16*40 = 640      768-640 = 128      128/2 = 64
//draw->drawPolygon(rectangle, 4, white, 1, white);
    
    mat.assign(ancho, vector<int>(alto,1));
    for(int i = 1; i < ancho -1;i++){for(int j = 1; j<alto-1;j++){checkEdificios.emplace_back(i,j);}}
// Edificios     Entre 30 y 35 edificios
    numEdificios = 35+rand()%6;
    std::random_shuffle( checkEdificios.begin(), checkEdificios.end() );
    int crunch = 0;
    while(edificios.size() < numEdificios || crunch >= checkEdificios.size()){
        if(canGenerateBuilding(checkEdificios[crunch].fi,checkEdificios[crunch].se))edificios.insert(checkEdificios[crunch++]); 
        else crunch++;
    }
    for(auto edi : edificios){
        // cout<<edi.fi<< ' '<<edi.se<<'\n';
    }
    checkEdificios.clear();
    updateMatrix();
    
//  Time
    timeLabel = Label::createWithTTF("TIME", "fonts/dirtyoldtown.ttf", 30);
    string sTime = to_string(playTime/60)+"-"+(playTime%60<10?"0":"")+to_string(playTime%60);
    timeNumberLabel = Label::createWithTTF(sTime, "fonts/dirtyoldtown.ttf", 30);
    timeLabel->setPosition(Vec2(952, 2.4*hei));
    timeNumberLabel->setPosition(Vec2(952, 1.5*hei));
    this->addChild(timeLabel);
    this->addChild(timeNumberLabel);

// Players
    p1.sprite = Sprite::createWithSpriteFrame(getAnimation("Shinji_Player_%d.png",1, 1).front() );
    p1.name = "Shinji";
    p1.x = inix + 20;
    p1.y = iniy + 20;
    this->addChild(p1.sprite);
    p1.sprite->setPosition(Vec2(p1.x, p1.y));

    p2.sprite = Sprite::createWithSpriteFrame(getAnimation("Asuka_Player_%d.png",1, 1).front() );
    p2.name = "Asuka";
    p2.x = inix + ancho*dt - 20;
    p2.y = iniy + 20;
    this->addChild(p2.sprite);
    p2.sprite->setPosition(Vec2(p2.x, p2.y));
    p2.sprite->runAction(ScaleBy::create(1,0.75));

    p3.sprite = Sprite::createWithSpriteFrame(getAnimation("Misato_Player_%d.png",1, 1).front() );
    p3.name = "Misato";
    p3.x = inix + 20;
    p3.y = iniy + alto*dt - 20;
    this->addChild(p3.sprite);
    p3.sprite->setPosition(Vec2(p3.x, p3.y));
    
    p4.sprite = Sprite::createWithSpriteFrame(getAnimation("Rei_Player_%d.png",1, 1).front() );
    p4.name = "Rei";
    p4.x = inix + ancho*dt - 20;
    p4.y = iniy + alto*dt - 20;
    this->addChild(p4.sprite);
    p4.sprite->setPosition(Vec2(p4.x, p4.y));
    p4.sprite->runAction(ScaleBy::create(1,0.75));
   
    pl[0] = p1;
    pl[1] = p2;
    pl[2] = p3;
    pl[3] = p4;

    return;
    //return true;
}

void Juego::update(float delta){

    Node::update(delta);
    float delt = 2; 
    //Aproximado
    delta = 1.5; 
    //cout<<"Update "<<delta<<'\n';

    if(startGame == false){
        startGame = true;
        auto scene = Select::createScene();
        Director::getInstance()->pushScene(scene);
        Iniciar();
    }


    if(isKeyPressed(EventKeyboard::KeyCode::KEY_LEFT_ARROW)){
        pl[indPlayer1].updateCoord(-delt,0.0,limIzq, limDer, limDown, limUp);}
    if(isKeyPressed(EventKeyboard::KeyCode::KEY_RIGHT_ARROW)){
        pl[indPlayer1].updateCoord(delt,0.0,limIzq, limDer, limDown, limUp);}
    if(isKeyPressed(EventKeyboard::KeyCode::KEY_DOWN_ARROW)){
        pl[indPlayer1].updateCoord(0.0,-delt,limIzq, limDer, limDown, limUp);}
    if(isKeyPressed(EventKeyboard::KeyCode::KEY_UP_ARROW)){
        pl[indPlayer1].updateCoord(0.0,delt,limIzq, limDer, limDown, limUp); }

    if(numPlayers > 1 && isKeyPressed(EventKeyboard::KeyCode::KEY_A )) {
        pl[indPlayer2].updateCoord(-delt,0.0,limIzq, limDer, limDown, limUp);
    }
    if(numPlayers > 1 && isKeyPressed(EventKeyboard::KeyCode::KEY_D)) {
        pl[indPlayer2].updateCoord(delt,0.0,limIzq, limDer, limDown, limUp);
    }
    if(numPlayers > 1 && isKeyPressed(EventKeyboard::KeyCode::KEY_S)) {
        pl[indPlayer2].updateCoord(0.0,-delt,limIzq, limDer, limDown, limUp);
    }
    if(numPlayers > 1 && isKeyPressed(EventKeyboard::KeyCode::KEY_W)) {
        pl[indPlayer2].updateCoord(0.0,delt,limIzq, limDer, limDown, limUp);
    }

    updateMatrix();
    updateBombas();

    tiempo = (tiempo+1)%50;
    tiempoBombas = (tiempoBombas+1)%30;

// Si se acaba el tiempo del reloj
    if(playTime <= 0){
        ScoreLabel->setString("Final Score");
        ScoreLabel->setPosition(Vec2(480 - ScoreLabel->getContentSize().width/2, 2.35*hei));
        actPlayTime();
        return;
    }

// Una vez pasado el tiempo, se mantiene el mismo scoreboard
    calcPlayerScore();

    if(tiempo%10 == 0){
        // cout<<"segundooooooooooooooooooooooooooooooooooooooooooooooooooooooooo\n";
        moveBots();
    }
    if(tiempo == 0){
        //  Time
        actPlayTime();
    }

    return;
}

void Juego::updateMatrix(){
    bg->clear();
    auto origin = Director::getInstance()->getVisibleOrigin();
    auto winSize = Director::getInstance()->getVisibleSize();
    bg->drawSolidRect(origin, winSize, Color4F(0.0,0.0,0.0,1.0));
    for(int i = -1; i<= ancho;i++){
        for(int j = -1; j<=alto;j++){
            if( i == -1 || i == ancho || j == -1 || j == alto){
                bg->drawSolidRect(
                    Vec2(inix + dt*  i,    iniy + dt*   j  ),
                    Vec2(inix + dt* (i+1), iniy + dt* (j+1)),
                    Color4F(0.4,0.2,0.3,1.0));
            }else if(mat[i][j] == 1){
                bg->drawRect(
                    Vec2(inix + dt*  i,    iniy + dt*   j  ),
                    Vec2(inix + dt* (i+1), iniy + dt* (j+1)),
                    colors[2]);
            }else if(mat[i][j] == 2){ // Player 1
                bg->drawSolidRect(
                    Vec2(inix + dt*  i,    iniy + dt*   j  ),
                    Vec2(inix + dt* (i+1), iniy + dt* (j+1)),
                    colors[0]);
            }else if(mat[i][j] == 3){ // Player 2
                bg->drawSolidRect(
                    Vec2(inix + dt*  i,    iniy + dt*   j  ),
                    Vec2(inix + dt* (i+1), iniy + dt* (j+1)),
                    colors[3]);
            }else if(mat[i][j] == 4){ // Player 3
                bg->drawSolidRect(
                    Vec2(inix + dt*  i,    iniy + dt*   j  ),
                    Vec2(inix + dt* (i+1), iniy + dt* (j+1)),
                    colors[7]);
            }else if(mat[i][j] == 5){ // Player 4
                bg->drawSolidRect(
                    Vec2(inix + dt*  i,    iniy + dt*   j  ),
                    Vec2(inix + dt* (i+1), iniy + dt* (j+1)),
                    colors[8]);
            }
        }
    }

// Blanco // Negro // Gris // Red // Green // Blue // Yellow // Morado // Celeste
// Asuka - Rojo
// Rei - Azul celeste
// Shinji - Blanco
// Misato - Morado

    // Obstaculos
    for(pair<int,int> edi : edificios){
        // cout<<edi.se.fi<<' '<<edi.se.se<<'\n';
        int indColor = checkColor(edi.fi, edi.se);
        bg->drawSolidCircle(
            Vec2(inix + edi.fi*  dt + dt/2,    iniy + edi.se*   dt  +dt/2),
            radio*1.25, angle, segments, colors[1]);
        bg->drawSolidCircle(
            Vec2(inix + edi.fi*  dt + dt/2,    iniy + edi.se*   dt  +dt/2),
            radio, angle, segments, colors[indColor]);
    }

    return;
}

void Juego::updateBombas(){
    // Bombas
    while(!bombAux.empty()) bombAux.pop();
    while(!bombas.empty()){
        Juego::Bomba *bom = bombas.front();
        bombas.pop();
        if(tiempoBombas == 0) bom->tiempo--;

        if(bom->tiempo == -1){
            pintarMatrix(bom);     
            pl[bom->playerInd].bombas++;
            delete bom;
        }else{
            bg->drawSolidCircle(
                Vec2(inix + bom->x * dt + dt/2, iniy + bom->y *  dt  +dt/2),
                radio*1.55, angle, segments, colors[1]);
            bg->drawSolidCircle(
                Vec2(inix + bom->x * dt + dt/2, iniy + bom->y *  dt  +dt/2),
                radio*1.4, angle, segments, bombColor[bom->tiempo]);
            bombAux.push(bom);
        }
    }
    bombas = bombAux; 
    return;
}

void Juego::calcPlayerScore(){
    for(int i = 0; i<4; i++){
        pl[i].score = 0;
    }
    for(int i = 0; i < ancho;i++){
        for(int j = 0; j < alto;j++){

            // Edificio
            if(edificios.count({i,j}) > 0){
                int indColor = checkColor(i, j);
                if(indColor == 2) pl[0].score+=200; // Shinji, Player 1
                else if(indColor == 3) pl[1].score+=200; // Asuka, Player 2
                else if(indColor == 4) pl[2].score+=200; // Misato, Player 3
                else if(indColor == 5) pl[3].score+=200; // Rei
            }
            // Casilla - 50 puntos
            // Edificio marcado = 200 puntos
            if(mat[i][j] == 2){ // Player 1
                pl[0].score+=50; 
            }else if(mat[i][j] == 3){ // Player 2
                pl[1].score+=50; 
            }else if(mat[i][j] == 4){ // Player 3
                pl[2].score+=50; 
            }else if(mat[i][j] == 5){ // Player 4
                pl[3].score+=50; 
            
            }
        }
    }

    for(int i = 0; i<4; i++){
        string s = to_string(pl[i].score);
        while(s.size()<4) s = "0"+s;
        scLabel[i]->setString(s.c_str());
    }
    return;
}

// ---------------------------  BOOOTS -------------------------------------------

void Juego::moveBots(){
    float delt = 2; 
    for(int i=0;i<4;i++){
        if( i == indPlayer1 || i == indPlayer2) continue;

        int ran = rand()%7;
        int ranBom = rand()%100;
        int maxiMOves = 8;

        if(ran == 0){
            for(int j=0;j<maxiMOves;j++)
                pl[i].updateCoord(-delt,0.0,limIzq, limDer, limDown, limUp);
        }else if(ran == 1){
            for(int j=0;j<maxiMOves;j++)
                pl[i].updateCoord(delt,0.0,limIzq, limDer, limDown, limUp);
        }else if(ran == 2){
            for(int j=0;j<maxiMOves;j++)
                pl[i].updateCoord(0.0,-delt,limIzq, limDer, limDown, limUp);
        }else if(ran == 3){
            for(int j=0;j<maxiMOves;j++)
                pl[i].updateCoord(0.0,delt,limIzq, limDer, limDown, limUp);
        }

        int _x = int(pl[i].x/dt)-1, _y = int((pl[i].y)/dt)-4;
        if(pl[i].bombas > 0 && mat[_x][_y] != i+2){ 
            // cout<<"Play Ind: "<<i<<"   x: "<<_x<<"   y: "<<_y<<"   mat: "<<mat[_x][_y]<<'\n';
            putBomba(i);
        }
    }
    return;
}

// ---------------------------  BOOOTS -----------------------------------------

void Juego::pintarMatrix(Juego::Bomba *bom){
    mat[bom->x][bom->y] = bom->player;
    for(int i = bom->x+1; i < min(ancho, int(bom->x+bom->potencia+1) ); i++){
        mat[i][bom->y] = bom->player; 
        if(edificios.count({i,bom->y}) > 0) break; }
    for(int i = bom->x-1; i >= max(0, int(bom->x - bom->potencia) ); i--){
        mat[i][bom->y] = bom->player;
        if(edificios.count({i,bom->y}) > 0) break; }
    for(int i = bom->y+1; i < min(alto, int(bom->y+bom->potencia+1) ); i++){
        mat[bom->x][i] = bom->player; 
        if(edificios.count({bom->x,i}) > 0) break; }
    for(int i = bom->y-1; i >= max(0, int(bom->y-bom->potencia) ); i--){
        mat[bom->x][i] = bom->player; 
        if(edificios.count({bom->x,i}) > 0) break; }
    return;
}

void Juego::Player::updateCoord( float _x, float _y, float a, float b, float c, float d){
    
    int _x_ = x + _x;
    int _y_ = y + _y;
    _y_-= 18;
    //if(name == "Misato"){
    //cout<<(_x_/40)-1<<' '<<(_y_/40)-4<<'\n';cout<<_x<<' '<<_y<<'\n';}

    if(edificios.count({(_x_/40)-1,(_y_/40)-4})) return;

    x+= _x;
    y+= _y;
    x = max( a, x);
    x = min( b, x);
    y = max( c, y);
    y = min( d, y);
    sprite->setPosition(Vec2(x,y));
    int frameNum = 0;
    if(_x < 0.0 && _y == 0.0) frameNum = 4;
    if(_x > 0.0 && _y == 0.0) frameNum = 7;
    if(_x == 0.0 && _y < 0.0) frameNum = 1;
    if(_x == 0.0 && _y > 0.0) frameNum = 10;
    string frame = name + "_Player_"+to_string(frameNum)+".png";
    sprite->setSpriteFrame(frame.c_str());
    return;
}

bool Juego::canGenerateBuilding(int _x, int _y){
    int a[8][2] = {
        {1,1},  { 1,0} , {1,-1},
        {0,1},           {0,-1},
        {-1,1}, {-1,0} , {-1,-1}
    };
    int cont = 0;
    for(int i = 0; i<8 ; i++){
        if( edificios.count({_x +a[i][0],_y + a[i][1]}) == 0 ) cont++;
    }
        // cout<<_x<<' '<<_y<<'\n';
    if(cont == 8) return true;
    return false;
}

int Juego::checkColor(int _x, int _y){
// Blanco // Negro // Gris // Red // Green // Blue // Yellow // Morado // Celeste
// Asuka - Rojo
// Rei - Azul celeste
// Shinji - Blanco
// Misato - Morado
    int a[9][2] = {
        {1,1},  { 1,0} , {1,-1},
        {0,1},  { 0,0} , {0,-1},
        {-1,1}, {-1,0} , {-1,-1}
    };
    int cont = 0;
    for(int i = 0; i<9 ; i++){
        if( mat[_x -1][_y-1] == mat[_x +a[i][0]][_y + a[i][1]]) cont++;
        //else if( mat[_x +a[i][0]][_y + a[i][1]] == 0) cont++; // Edificio
    }
    if(cont == 9){
        if(mat[_x-1][_y-1] == 2) return 0; // Shinji, Player 1
        else if(mat[_x-1][_y-1] == 3) return 3; // Asuka, Player 2
        else if(mat[_x-1][_y-1] == 4) return 7; // Misato, Player 3
        else if(mat[_x-1][_y-1] == 5) return 8; // Rei
        else return 6; // Empty
    }
    return 6;
}

void Juego::goBack(Ref *pSender){
    AudioEngine::stopAll();
    AudioEngine::play2d("audio/Zankoku na Tenshi no Teeze Instrumental.mp3",true,0.5f);
    Director::getInstance()->popScene();
    // AudioEngine::resume(IntroScene::introID);
    return;
}

bool Juego::isKeyPressed(EventKeyboard::KeyCode code) {
    // Check if the key is currently pressed by seeing it it's in the std::map keys
    // In retrospect, keys is a terrible name for a key/value paried datatype isnt it?
    if(keys.find(code) != keys.end())
        return true;
    return false;
}

double Juego::keyPressedDuration(EventKeyboard::KeyCode code) {
    if(!isKeyPressed(EventKeyboard::KeyCode::KEY_CTRL))
        return 0;  // Not pressed, so no duration obviously
    // Return the amount of time that has elapsed between now and when the user
    // first started holding down the key in milliseconds
    // Obviously the start time is the value we hold in our std::map keys
    return std::chrono::duration_cast<std::chrono::milliseconds>
            (std::chrono::high_resolution_clock::now() - keys[code]).count();
}

void Juego::keyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event){
    //if(numPlayers > 1 && keyCode == EventKeyboard::KeyCode::KEY_ENTER){

// Parar si ya se acabo el tiempo de juego
    if(playTime <= 0){return;}


    if(keyCode == EventKeyboard::KeyCode::KEY_SPACE){
        if(pl[indPlayer1].bombas > 0) putBomba(indPlayer1);
    }
    if(numPlayers > 1 && keyCode == EventKeyboard::KeyCode::KEY_E){
        if(pl[indPlayer2].bombas > 0) putBomba(indPlayer2);
    }
    
    return;
}

void Juego::putBomba(int indPlay){
    int _x = int(pl[indPlay].x/dt)-1, _y = int((pl[indPlay].y)/dt)-4;
    if(edificios.count({_x,_y}) > 0) return; // NO poner sobre edificios
    Juego::Bomba *b = new Bomba();
    b->tiempo = 4;
    b->player = indPlay + 2;
    b->playerInd = indPlay;
    pl[indPlay].bombas--;
    b->potencia = pl[indPlay].potencia;
    b->x = _x, b->y = _y;
    bombas.push(b);
    return;
}

int Juego::Player::getCoordinateX(){
    return int(x/40.0);
}

int Juego::Player::getCoordinateY(){
    return int(y/40.0);
}

void Juego::actPlayTime(){
    playTime = max(0, playTime-1); 
    string s = to_string(playTime/60)+"-"+(playTime%60<10?"0":"")+to_string(playTime%60);
    timeNumberLabel->setString(s.c_str());
    return;
}

Vector<cocos2d::SpriteFrame*> Juego::getAnimation(const char *format, int count, int delta){
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

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename){
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in JuegoScene.cpp\n");
}

// Because cocos2d-x requres createScene to be static, we need to make other non-pointer members static
std::map<cocos2d::EventKeyboard::KeyCode,
std::chrono::high_resolution_clock::time_point> Juego::keys;
int Juego::indPlayer1;
int Juego::indPlayer2;
int Juego::numPlayers;
set<pair<int,int> > Juego::edificios;


