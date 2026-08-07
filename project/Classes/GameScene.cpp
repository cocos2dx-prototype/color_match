//
//  GameScene.cpp
//  ColorMatch-desktop
//
//  Created by hoangbui-fe on 6/8/26.
//

#include "GameScene.hpp"
#include "Constants.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
    return GameScene::create();
}

bool GameScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    _player = nullptr;
    _activeBlock = nullptr;

    _scoreLabel = nullptr;
    _blocksLabel = nullptr;
    _resultLabel = nullptr;

    _keyboardListener = nullptr;
    _mouseListener = nullptr;

    _score = 0;
    _processedBlocks = 0;
    _sequenceIndex = 0;

    _playerBlue = true;
    _gameOver = false;

    _sequence =
    {
        BlockColor::Blue,
        BlockColor::Red,
        BlockColor::Blue,
        BlockColor::Blue,
        BlockColor::Red,
        BlockColor::Red
    };

    createBackground();
    createPlayer();
    createHud();
    createResultLabel();
    createInput();

    spawnNextBlock();
    updateHud();

    scheduleUpdate();

    return true;
}

void GameScene::createBackground()
{
    auto background =
        LayerColor::create(
            Color4B(0, 0, 0, 255)
        );

    addChild(background);
}

void GameScene::createPlayer()
{
    _player = DrawNode::create();
    addChild(_player);

    _player->setPosition(
        Vec2(
            ColorMatch::PLAYER_START_X,
            ColorMatch::PLAYER_START_Y
        )
    );

    refreshPlayerVisual();
}

void GameScene::createHud()
{
    _scoreLabel =
        Label::createWithTTF(
            "",
            "fonts/arial.ttf",
            28
        );

    _scoreLabel->setAnchorPoint(Vec2(0.0f, 1.0f));

    _scoreLabel->setPosition(
        Vec2(
            ColorMatch::SCORE_LABEL_X,
            ColorMatch::SCORE_LABEL_Y
        )
    );

    addChild(_scoreLabel);

    _blocksLabel =
        Label::createWithTTF(
            "",
            "fonts/arial.ttf",
            28
        );

    _blocksLabel->setAnchorPoint(
        Vec2(0.5f, 1.0f)
    );

    _blocksLabel->setPosition(
        Vec2(
            ColorMatch::BLOCKS_LABEL_X,
            ColorMatch::BLOCKS_LABEL_Y
        )
    );

    addChild(_blocksLabel);
}

void GameScene::createResultLabel()
{
    _resultLabel =
        Label::createWithTTF(
            "",
            "fonts/arial.ttf",
            42
        );

    _resultLabel->setPosition(
        Vec2(
            ColorMatch::RESULT_LABEL_X,
            ColorMatch::RESULT_LABEL_Y
        )
    );

    _resultLabel->setVisible(false);

    addChild(_resultLabel, 10);
}

void GameScene::createInput()
{
    _keyboardListener =
        EventListenerKeyboard::create();

    _keyboardListener->onKeyPressed =
        [this](EventKeyboard::KeyCode keyCode, Event*)
        {
            if (_gameOver)
            {
                return;
            }

            _pressedKeys.insert(keyCode);

            if (keyCode ==
                EventKeyboard::KeyCode::KEY_SPACE)
            {
                togglePlayerColor();
            }
        };

    _keyboardListener->onKeyReleased =
        [this](EventKeyboard::KeyCode keyCode, Event*)
        {
            _pressedKeys.erase(keyCode);
        };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(
        _keyboardListener,
        this
    );

    _mouseListener =
        EventListenerMouse::create();

    _mouseListener->onMouseDown =
        [this](EventMouse*)
        {
            if (_gameOver)
            {
                restartGame();
            }
        };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(
        _mouseListener,
        this
    );
}

void GameScene::update(float delta)
{
    if (_gameOver)
    {
        return;
    }

    updatePlayer(delta);
    updateBlock(delta);
    checkCollision();
}

void GameScene::updatePlayer(float delta)
{
    float movement = 0.0f;

    if (_pressedKeys.count(
            EventKeyboard::KeyCode::KEY_A))
    {
        movement -= 1.0f;
    }

    if (_pressedKeys.count(
            EventKeyboard::KeyCode::KEY_D))
    {
        movement += 1.0f;
    }

    Vec2 position = _player->getPosition();

    position.x +=
        movement *
        ColorMatch::PLAYER_SPEED *
        delta;

    const float halfSize =
        ColorMatch::PLAYER_SIZE * 0.5f;

    position.x =
        clampf(
            position.x,
            halfSize,
            ColorMatch::DESIGN_WIDTH - halfSize
        );

    _player->setPosition(position);
}

void GameScene::updateBlock(float delta)
{
    if (_activeBlock == nullptr)
    {
        return;
    }

    Vec2 position =
        _activeBlock->getPosition();

    position.y -=
        ColorMatch::BLOCK_SPEED *
        delta;

    _activeBlock->setPosition(position);
    
    if (_activeBlock->getBounds().getMaxY() <= 0.0f) {

        ++_processedBlocks;

        _activeBlock->removeFromParent();
        _activeBlock = nullptr;

        updateHud();

        if (_processedBlocks >=
            ColorMatch::TOTAL_BLOCKS)
        {
            finishGame();
        }
        else
        {
            spawnNextBlock();
        }
    }
}

Rect GameScene::getPlayerBounds() const
{
    const float halfSize =
        ColorMatch::PLAYER_SIZE * 0.5f;

    return Rect(
        _player->getPositionX() - halfSize,
        _player->getPositionY() - halfSize,
        ColorMatch::PLAYER_SIZE,
        ColorMatch::PLAYER_SIZE
    );
}

void GameScene::checkCollision()
{
    if (_activeBlock == nullptr)
    {
        return;
    }

    if (!getPlayerBounds().intersectsRect(
            _activeBlock->getBounds()))
    {
        return;
    }

    const bool playerBlue =
        _playerBlue;

    const bool blockBlue =
        _activeBlock->getBlockColor() ==
        BlockColor::Blue;

    if (playerBlue == blockBlue)
    {
        _score +=
            ColorMatch::SCORE_PER_MATCH;
    }

    ++_processedBlocks;

    _activeBlock->removeFromParent();
    _activeBlock = nullptr;

    updateHud();

    if (_processedBlocks >=
        ColorMatch::TOTAL_BLOCKS)
    {
        finishGame();
    }
    else
    {
        spawnNextBlock();
    }
}

void GameScene::spawnNextBlock()
{
    if (_sequenceIndex >=
        static_cast<int>(_sequence.size()))
    {
        return;
    }

    _activeBlock =
        FallingBlock::create(
            _sequence[_sequenceIndex]
        );

    addChild(_activeBlock);

    _activeBlock->setPosition(
        Vec2(
            ColorMatch::BLOCK_START_X,
            ColorMatch::BLOCK_START_Y
        )
    );

    ++_sequenceIndex;
}

void GameScene::togglePlayerColor()
{
    _playerBlue = !_playerBlue;

    refreshPlayerVisual();
}

void GameScene::refreshPlayerVisual()
{
    _player->clear();

    const float halfSize =
        ColorMatch::PLAYER_SIZE * 0.5f;

    Vec2 vertices[4] =
    {
        Vec2(-halfSize, -halfSize),
        Vec2( halfSize, -halfSize),
        Vec2( halfSize,  halfSize),
        Vec2(-halfSize,  halfSize)
    };

    Color4F color =
        _playerBlue
            ? Color4F(0.2f, 0.4f, 1.0f, 1.0f)
            : Color4F(1.0f, 0.2f, 0.2f, 1.0f);

    _player->drawSolidPoly(
        vertices,
        4,
        color
    );
}

void GameScene::updateHud()
{
    _scoreLabel->setString(
        StringUtils::format(
            "Score: %d",
            _score
        )
    );

    _blocksLabel->setString(
        StringUtils::format(
            "Blocks: %d / %d",
            _processedBlocks,
            ColorMatch::TOTAL_BLOCKS
        )
    );
}

void GameScene::finishGame()
{
    _gameOver = true;

    _resultLabel->setString(
        StringUtils::format(
            "FINAL SCORE: %d\n\nCLICK TO PLAY AGAIN",
            _score
        )
    );

    _resultLabel->setVisible(true);
}

void GameScene::restartGame()
{
    _score = 0;
    _processedBlocks = 0;
    _sequenceIndex = 0;

    _playerBlue = true;
    _gameOver = false;

    _pressedKeys.clear();

    if (_activeBlock != nullptr)
    {
        _activeBlock->removeFromParent();
        _activeBlock = nullptr;
    }

    _player->setPosition(
        Vec2(
            ColorMatch::PLAYER_START_X,
            ColorMatch::PLAYER_START_Y
        )
    );

    refreshPlayerVisual();

    _resultLabel->setVisible(false);

    updateHud();

    spawnNextBlock();
}

void GameScene::onExit()
{
    if (_keyboardListener != nullptr)
    {
        _eventDispatcher->removeEventListener(
            _keyboardListener
        );

        _keyboardListener = nullptr;
    }

    if (_mouseListener != nullptr)
    {
        _eventDispatcher->removeEventListener(
            _mouseListener
        );

        _mouseListener = nullptr;
    }

    Scene::onExit();
}
