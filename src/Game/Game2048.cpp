#include "Game2048.hpp"

Game2048::Game2048(GLFWwindow* _window, size_t width, size_t height) : window(_window), m_windowWidth(width), m_windowHeight(height) {
    glfwSetWindowUserPointer(window, this);
    glfwSetKeyCallback(window, keysCallback);
    srand(time(NULL));

    cellWidthAndHeight = FlexibleSizes::getSize(m_windowWidth, FIELD_WIDTH);

    std::shared_ptr<Texture> cellTexture = std::make_shared<Texture>("res/textures/cells.png");
    cellShaderProg = std::make_shared<ShaderProgram>("res/shaders/vSprite.txt", "res/shaders/fSprite.txt");
    for (size_t i = 0, j = 0; j < texCoords.size(); i <<= 1, j++) {
        cellSpriteMap[i] = std::make_shared<Sprite>(cellTexture, cellShaderProg, glm::vec2(0.f), glm::vec2(cellWidthAndHeight), 0.f, texCoords[j]);
        if (i == 0) i++;
    }

    fieldInit();
}

void Game2048::run() {
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        showGame();

        glfwSwapBuffers(window);
    }
}

void Game2048::fieldInit() {
    std::memset(field, 0, sizeof(field));
    generateNewCell();
    generateNewCell();
    savePreviousFieldState();
}

void Game2048::showGame() {
    cellShaderProg->use();
    cellShaderProg->setInt("tex", 0);

    glm::mat4 projectionMatrix = glm::ortho(0.f, static_cast<float>(m_windowWidth), 0.f, static_cast<float>(m_windowHeight), -1.f, 1.f);
    cellShaderProg->setMatrix4("projectionMat", projectionMatrix);

    for (size_t j = 0; j < FIELD_HEIGHT; j++) {
        for (size_t i = 0; i < FIELD_WIDTH; i++) {
            cellSpriteMap[field[j][i].count]->setPosition(glm::vec2(j * cellWidthAndHeight, i * cellWidthAndHeight));
            cellSpriteMap[field[j][i].count]->render();
        }
    }
}

bool Game2048::isCellInField(int x, int y) {
    return x >= 0 && y >= 0 && x < FIELD_WIDTH && y < FIELD_HEIGHT;
}

void Game2048::generateNewCell() {
    for (size_t i = 0; i < 1; i++) {
        int x = rand() % FIELD_WIDTH;
        int y = rand() % FIELD_HEIGHT;
        if (field[x][y].have_count) i--;
        else {
            field[x][y].have_count = true;
            if (rand() % 10 + 1 < 10) field[x][y].count = 2;
            else field[x][y].count = 4;
        }
    }
}

void Game2048::savePreviousFieldState() {
    for (int j = 0; j < FIELD_HEIGHT; j++)
        for (int i = 0; i < FIELD_WIDTH; i++)
            previousFieldState[i][j] = field[i][j];
}

void Game2048::loadPreviousFieldState() {
    gameOver = false;
    std::swap(field, previousFieldState);
}

bool Game2048::areThereAnyPossibleMoves() {
    bool possibleMoves = false;
    for (int j = 0; j < FIELD_HEIGHT; j++)
        for (int i = 0; i < FIELD_WIDTH; i++)
            if (field[i][j].have_count) {
                if (isCellInField(i + 1, j))
                    if (!field[i + 1][j].have_count || (field[i + 1][j].have_count && field[i][j].count == field[i + 1][j].count)) {
                        possibleMoves = true;
                        break;
                    }
                if (isCellInField(i - 1, j))
                    if (!field[i - 1][j].have_count || (field[i - 1][j].have_count && field[i][j].count == field[i - 1][j].count)) {
                        possibleMoves = true;
                        break;
                    }
                if (isCellInField(i, j + 1))
                    if (!field[i][j + 1].have_count || (field[i][j + 1].have_count && field[i][j].count == field[i][j + 1].count)) {
                        possibleMoves = true;
                        break;
                    }
                if (isCellInField(i, j - 1))
                    if (!field[i][j - 1].have_count || (field[i][j - 1].have_count && field[i][j].count == field[i][j - 1].count)) {
                        possibleMoves = true;
                        break;
                    }
            }
    return possibleMoves;
}

void Game2048::restartGame() {
    gameOver = false;
    fieldInit();
}

void Game2048::keysCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    Game2048* game = static_cast<Game2048*>(glfwGetWindowUserPointer(window));
    game->handleKey(key, action);
}

void Game2048::handleKey(int key, int action) {
    shouldBeNewCellGenerated = false;
    shouldBeFieldStateSaved = true;

    if (key == GLFW_KEY_LEFT && action == GLFW_PRESS && !gameOver) { // left
        for (size_t j = 0; j < FIELD_HEIGHT; j++)
            for (size_t i = 0; i < FIELD_WIDTH; i++)
                if (field[i][j].have_count) {
                    int count = field[i][j].count;
                    moveCell(i, j, -1, 0);
                    std::pair<int, int> new_position = getNewCellPosition(i, j, key, count);
                    mergeCells(new_position.first, new_position.second, 1, 0);
                }
    }
    else if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS && !gameOver) { // right
        for (size_t j = 0; j < FIELD_HEIGHT; j++)
            for (int i = FIELD_WIDTH - 1; i >= 0; i--)
                if (field[i][j].have_count) {
                    int count = field[i][j].count;
                    moveCell(i, j, 1, 0);
                    std::pair<int, int> new_position = getNewCellPosition(i, j, key, count);
                    mergeCells(new_position.first, new_position.second, -1, 0);
                }
    }
    else if (key == GLFW_KEY_UP && action == GLFW_PRESS && !gameOver) { // up
        for (int j = FIELD_HEIGHT - 1; j >= 0; j--)
            for (size_t i = 0; i < FIELD_WIDTH; i++)
                if (field[i][j].have_count) {
                    int count = field[i][j].count;
                    moveCell(i, j, 0, 1);
                    std::pair<int, int> new_position = getNewCellPosition(i, j, key, count);
                    mergeCells(new_position.first, new_position.second, 0, -1);
                }
    }
    else if (key == GLFW_KEY_DOWN && action == GLFW_PRESS && !gameOver) { // down
        for (size_t j = 0; j < FIELD_HEIGHT; j++)
            for (size_t i = 0; i < FIELD_WIDTH; i++)
                if (field[i][j].have_count) {
                    int count = field[i][j].count;
                    moveCell(i, j, 0, -1);
                    std::pair<int, int> new_position = getNewCellPosition(i, j, key, count);
                    mergeCells(new_position.first, new_position.second, 0, 1);
                }
    }
    else if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    if (key == GLFW_KEY_LEFT_CONTROL || key == GLFW_KEY_RIGHT_CONTROL) {
        ctrlPressed = (action != GLFW_RELEASE);
    }
    if (key == GLFW_KEY_Z) {
        zPressed = (action != GLFW_RELEASE);
    }
    if (ctrlPressed && zPressed) {
        loadPreviousFieldState();
    }

    if (shouldBeNewCellGenerated) generateNewCell();
    else if (!areThereAnyPossibleMoves()) gameOver = true;

    if (gameOver && (key == GLFW_KEY_LEFT || key == GLFW_KEY_RIGHT || key == GLFW_KEY_UP || key == GLFW_KEY_DOWN) && action == GLFW_PRESS) {
        restartGame();
    }
}

void Game2048::moveCell(int x, int y, int dx, int dy) {
    if (x + dx >= 0 && x + dx < FIELD_WIDTH && y + dy >= 0 && y + dy < FIELD_HEIGHT && !field[x + dx][y + dy].have_count) {
        if (shouldBeFieldStateSaved) { // save #1
            savePreviousFieldState();
            shouldBeFieldStateSaved = false;
        }
        std::swap(field[x][y], field[x + dx][y + dy]);
        shouldBeNewCellGenerated = true;
        moveCell(x + dx, y + dy, dx, dy);
    }
}

std::pair<int, int> Game2048::getNewCellPosition(int x, int y, int key, int count) {
    while (x >= 0 && x < FIELD_WIDTH && y >= 0 && y < FIELD_HEIGHT && field[x][y].count != count) {
        if (key == GLFW_KEY_LEFT) x--;
        else if (key == GLFW_KEY_RIGHT) x++;
        else if (key == GLFW_KEY_DOWN) y--;
        else y++;
    }
    return std::make_pair(x, y);
}

void Game2048::mergeCells(int x, int y, int dx, int dy) {
    while (x + dx >= 0 && x + dx < FIELD_WIDTH && y + dy >= 0 && y + dy < FIELD_HEIGHT && (field[x][y].count == field[x + dx][y + dy].count || !field[x + dx][y + dy].have_count)) {
        if (field[x][y].count == field[x + dx][y + dy].count) {
            if (shouldBeFieldStateSaved) { // save #2
                savePreviousFieldState();
                shouldBeFieldStateSaved = false;
            }
            field[x][y].count <<= 1;
            field[x + dx][y + dy].count = 0;
            field[x + dx][y + dy].have_count = false;
            shouldBeNewCellGenerated = true;
            break;
        }
        if (dx < 0) dx--;
        else if (dx > 0) dx++;
        if (dy < 0) dy--;
        else if (dy > 0) dy++;
    }
}