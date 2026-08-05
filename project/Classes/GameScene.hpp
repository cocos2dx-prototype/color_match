//
//  GameScene.hpp
//  ColorMatch-desktop
//
//  Created by hoangbui-fe on 6/8/26.
//

#ifndef GameScene_hpp
#define GameScene_hpp

#include <array>
#include <unordered_set>

#include "cocos2d.h"
#include "FallingBlock.hpp"

class GameScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init() override;

    virtual void update(float delta) override;

    virtual void onExit() override;

    CREATE_FUNC(GameScene);

private:
    void createBackground();
    void createPlayer();
    void createHud();
    void createResultLabel();
    void createInput();

    void updatePlayer(float delta);
    void updateBlock(float delta);
    void checkCollision();

    void spawnNextBlock();

    void togglePlayerColor();
    void refreshPlayerVisual();

    void updateHud();

    void finishGame();
    void restartGame();

    cocos2d::Rect getPlayerBounds() const;

private:
    cocos2d::DrawNode* _player;

    FallingBlock* _activeBlock;

    cocos2d::Label* _scoreLabel;
    cocos2d::Label* _blocksLabel;
    cocos2d::Label* _resultLabel;

    cocos2d::EventListenerKeyboard* _keyboardListener;
    cocos2d::EventListenerMouse* _mouseListener;

    std::unordered_set<cocos2d::EventKeyboard::KeyCode> _pressedKeys;

    std::array<BlockColor, 6> _sequence;

    int _score;
    int _processedBlocks;
    int _sequenceIndex;

    bool _playerBlue;
    bool _gameOver;
};

#endif /* GameScene_hpp */
