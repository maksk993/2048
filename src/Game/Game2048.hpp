#pragma once
#ifndef __GAME2048_HPP__
#define __GAME2048_HPP__

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <time.h>
#include <memory>
#include <utility>
#include "../Graphics/Texture.hpp"

class Game2048 {
    GLFWwindow* window;

    static const int FIELD_WIDTH = 4;
    static const int FIELD_HEIGHT = 4;

    struct Cell {
        bool have_count;
        int count;
    };

    Cell field[FIELD_WIDTH][FIELD_HEIGHT];
    Cell previousFieldState[FIELD_WIDTH][FIELD_HEIGHT];

    GLfloat vertices[8] = { 0.0f, 0.0f,   1.0f, 0.0f,   1.0f, 1.0f,   0.0f, 1.0f }; // size 8 because 2 coords (x, y) for each of 4 vertices (2 * 4 = 8)
    GLfloat texCoords[128] = {
        0.0f, 0.75f,   0.25f, 0.75f,   0.25f, 1.0f,   0.0f, 1.0f, // empty cell
        0.25f, 0.75f,   0.5f, 0.75f,   0.5f, 1.0f,   0.25f, 1.0f, // 2
        0.5f, 0.75f,   0.75f, 0.75f,   0.75f, 1.0f,   0.5f, 1.0f, // 4
        0.75f, 0.75f,   1.0f, 0.75f,   1.0f, 1.0f,   0.75f, 1.0f, // 8

        0.0f, 0.5f,   0.25f, 0.5f,   0.25f, 0.75f,   0.0f, 0.75f, // 16
        0.25f, 0.5f,   0.5f, 0.5f,   0.5f, 0.75f,   0.25f, 0.75f, // 32
        0.5f, 0.5f,   0.75f, 0.5f,   0.75f, 0.75f,   0.5f, 0.75f, // 64
        0.75f, 0.5f,   1.0f, 0.5f,   1.0f, 0.75f,   0.75f, 0.75f, // 128

        0.0f, 0.25f,   0.25f, 0.25f,   0.25f, 0.5f,   0.0f, 0.5f, // 256
        0.25f, 0.25f,   0.5f, 0.25f,   0.5f, 0.5f,   0.25f, 0.5f, // 512
        0.5f, 0.25f,   0.75f, 0.25f,   0.75f, 0.5f,   0.5f, 0.5f, // 1024
        0.75f, 0.25f,   1.0f, 0.25f,   1.0f, 0.5f,   0.75f, 0.5f, // 2048

        0.0f, 0.0f,   0.25f, 0.0f,   0.25f, 0.25f,   0.0f, 0.25f, // 4096
        0.25f, 0.0f,   0.5f, 0.0f,   0.5f, 0.25f,   0.25f, 0.25f, // 8192
        0.5f, 0.0f,   0.75f, 0.0f,   0.75f, 0.25f,   0.5f, 0.25f, // 16384
        0.75f, 0.0f,   1.0f, 0.0f,   1.0f, 0.25f,   0.75f, 0.25f // 32768
    };
    std::shared_ptr<Texture> cellTexture;

    bool zPressed = false;
    bool ctrlPressed = false;
    bool shouldBeNewCellGenerated = false;
    bool shouldBeFieldStateSaved = false;
    bool gameOver = false;

    void fieldInit();
    void showGame();
    void showCellTex(size_t count);
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

public:
    Game2048(GLFWwindow* _window);
    void run();
};

#endif // !__GAME2048_HPP__