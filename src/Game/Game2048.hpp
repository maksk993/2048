#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <time.h>
#include <memory>
#include <utility>
#include <vector>
#include <unordered_map>
#include "../Graphics/Sprite.hpp"
#include "../Utilities/FlexibleSizes.hpp"

class Game2048 {
    GLFWwindow* window;
    const size_t m_windowWidth;
    const size_t m_windowHeight;

    static const int FIELD_WIDTH = 4;
    static const int FIELD_HEIGHT = 4;

    struct Cell {
        bool have_count;
        int count;
    };
 
    std::vector<std::vector<Cell>> field;
    std::vector<std::vector<Cell>> previousFieldState; // for CTRL + Z

    std::array<std::array<GLfloat, 8>, 16> texCoords = { {
        {0.0f, 0.75f,   0.25f, 0.75f,   0.25f, 1.0f,   0.0f, 1.0f}, // empty cell
        {0.25f, 0.75f,   0.5f, 0.75f,   0.5f, 1.0f,   0.25f, 1.0f}, // 2
        {0.5f, 0.75f,   0.75f, 0.75f,   0.75f, 1.0f,   0.5f, 1.0f}, // 4
        {0.75f, 0.75f,   1.0f, 0.75f,   1.0f, 1.0f,   0.75f, 1.0f}, // 8

        {0.0f, 0.5f,   0.25f, 0.5f,   0.25f, 0.75f,   0.0f, 0.75f}, // 16
        {0.25f, 0.5f,   0.5f, 0.5f,   0.5f, 0.75f,   0.25f, 0.75f}, // 32
        {0.5f, 0.5f,   0.75f, 0.5f,   0.75f, 0.75f,   0.5f, 0.75f}, // 64
        {0.75f, 0.5f,   1.0f, 0.5f,   1.0f, 0.75f,   0.75f, 0.75f}, // 128

        {0.0f, 0.25f,   0.25f, 0.25f,   0.25f, 0.5f,   0.0f, 0.5f}, // 256
        {0.25f, 0.25f,   0.5f, 0.25f,   0.5f, 0.5f,   0.25f, 0.5f}, // 512
        {0.5f, 0.25f,   0.75f, 0.25f,   0.75f, 0.5f,   0.5f, 0.5f}, // 1024
        {0.75f, 0.25f,   1.0f, 0.25f,   1.0f, 0.5f,   0.75f, 0.5f}, // 2048

        {0.0f, 0.0f,   0.25f, 0.0f,   0.25f, 0.25f,   0.0f, 0.25f}, // 4096
        {0.25f, 0.0f,   0.5f, 0.0f,   0.5f, 0.25f,   0.25f, 0.25f}, // 8192
        {0.5f, 0.0f,   0.75f, 0.0f,   0.75f, 0.25f,   0.5f, 0.25f}, // 16384
        {0.75f, 0.0f,   1.0f, 0.0f,   1.0f, 0.25f,   0.75f, 0.25f} // 32768
    } };
    std::unordered_map<int, std::shared_ptr<Sprite>> cellSpriteMap;
    std::shared_ptr<ShaderProgram> cellShaderProg;
    size_t cellWidthAndHeight;

    bool zPressed = false;
    bool ctrlPressed = false;
    bool shouldNewCellBeGenerated = false;
    bool shouldFieldStateBeSaved = false;
    bool gameOver = false;
    int NumberOfUsedCells;

    void update();
    void loadResources();
    void fieldInit();

    void showGame();
    void animationLeft(int j, int i, float& k);
    void animationRight(int j, int i, float& k);
    void animationDown(int j, int i, float& k);
    void animationUp(int j, int i, float& k);
    int getNumberOfUsedCells();

    bool isCellInField(int x, int y);
    void generateNewCell();
    void savePreviousFieldState();
    void loadPreviousFieldState();
    bool areThereAnyPossibleMoves();
    void restartGame();

    static void keysCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    void handleKey(int key, int action);

    void moveCell(int x, int y, int dx, int dy);
    std::pair<int, int> getNewCellPosition(int x, int y, int key, int count);
    void mergeCells(int x, int y, int dx, int dy);

    enum class EAnimations { RIGHT, LEFT, DOWN, UP, NONE };
    EAnimations m_currentAnimation;

public:
    Game2048(GLFWwindow* _window, size_t width, size_t height);
    void run();
};