//
// Created by TriD on 22.03.2015.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "View.h"
#include "GameMap.h"

using std::cout;
using std::endl;
using std::ifstream;
using std::string;
using std::vector;

using glm::vec3;

View::View(): cameraLocation(4.0f, 3.0f, 3.0f), cameraDirection(0.0f, 0.0f, 1.0f) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        cout << "Failed to init SDL" << endl;
        return;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    window = SDL_CreateWindow("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    if (window == nullptr) {
        cout << "Failed to create window" << endl;
        SDL_Quit();
        return;
    }

    initOpenGL();
    loadShaders();
}

View &View::getInstance() {
    static View view;
    return view;
}

void glDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, void *param) {
    cout << message << endl;
}

void View::initOpenGL() {
    glContext = SDL_GL_CreateContext(window);

    //Enable OpenGL dynamics
    glewExperimental = GL_TRUE;
    if (GLenum i = glewInit()) {
        cout << glewGetErrorString(i) << endl;
    }

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glEnable(GL_DEBUG_OUTPUT);

    glDebugMessageCallback((GLDEBUGPROC) glDebugCallback, NULL);

    glClearColor(0, 0, 0, 0);
}

void View::loadShaders() {
    std::ifstream vertexShaderFile("res/shaders/shader.vs");
    string vertexShaderData((std::istreambuf_iterator<char>(vertexShaderFile)), std::istreambuf_iterator<char>());
    std::ifstream fragmentShaderFile("res/shaders/shader.fs");
    string fragmentShaderData((std::istreambuf_iterator<char>(fragmentShaderFile)), std::istreambuf_iterator<char>());

    GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

    char const *cstrVertexShaderData = vertexShaderData.c_str();
    char const *cstrFragmentShaderData = fragmentShaderData.c_str();

    GLint result;
    GLint infoLogLength;

    glShaderSource(vertexShaderId, 1, &cstrVertexShaderData, NULL);
    glCompileShader(vertexShaderId);
    glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &result);
    glGetShaderiv(vertexShaderId, GL_INFO_LOG_LENGTH, &infoLogLength);
    char* log = new char[infoLogLength];
    glGetShaderInfoLog(vertexShaderId, infoLogLength, nullptr, log);

    glShaderSource(fragmentShaderId, 1, &cstrFragmentShaderData, NULL);
    glCompileShader(fragmentShaderId);
    glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &result);
    log = new char[infoLogLength];
    glGetShaderInfoLog(fragmentShaderId, infoLogLength, nullptr, log);

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShaderId);
    glAttachShader(shaderProgram, fragmentShaderId);

    glLinkProgram(shaderProgram);

    glUseProgram(shaderProgram);
}

void View::generateMapView(GameMap *map) {
    vector<vec3> vertices;
    GLuint *indices;

    mapSize = 0;

    for (int i = 0; i < map->mapData.size(); i++) {
        for (int k = 0; k < map->mapData[i].size(); k++) {
            //vertex 0
            vertices.push_back(vec3(k, 0, i));
            //vertex 1
            vertices.push_back(vec3(k + 1, 0, i));
            //vertex 2
            vertices.push_back(vec3(k, 0, i + 1));
            //vertex 3
            vertices.push_back(vec3(k + 1, 0, i + 1));
        }
        mapSize += map->mapData[i].size();
    }

    indices = new GLuint[mapSize * 6];

    for (GLuint i = 0; i < mapSize; i++) {
        // First triangle 012
        indices[i * 6] = i;
        indices[i * 6 + 1] = i + 1;
        indices[i * 6 + 2] = i + 2;
        // Second triangle 213
        indices[i * 6 + 3] = i + 2;
        indices[i * 6 + 4] = i + 1;
        indices[i * 6 + 5] = i + 3;
    }

    GLuint vertexArrayId;
    glGenVertexArrays(1, &vertexArrayId);
    glBindVertexArray(vertexArrayId);

    glGenBuffers(1, &floorVertices);
    glBindBuffer(GL_ARRAY_BUFFER, floorVertices);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vec3), &vertices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &floorIndices);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, floorIndices);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mapSize * 6 * sizeof(GLuint), indices, GL_STATIC_DRAW);
    delete[] indices;
}

void View::draw() {
    /*glm::vec3 translationVector(-5.0f, 0.0f, 0.0f);
    glm::vec3 rotationVector(1.0f, 0.0f, 0.0f);
    glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), translationVector);
    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), -glm::pi<float>()/2, rotationVector);*/
    glm::mat4 cameraMatrix = glm::lookAt(cameraLocation, cameraDirection, vec3(0.0f, 1.0f, 0.0f));


    /*GLint rotationLocation = glGetUniformLocation(shaderProgram, "u_rotation");
    glUniformMatrix4fv(rotationLocation, 1, GL_FALSE, (GLfloat const *) &rotationMatrix);
    GLint translationLocation = glGetUniformLocation(shaderProgram, "u_translation");
    glUniformMatrix4fv(translationLocation, 1, GL_FALSE, (GLfloat const *) &translationMatrix);*/
    GLint cameraLocation = glGetUniformLocation(shaderProgram, "u_camera");
    glUniformMatrix4fv(cameraLocation, 1, GL_FALSE, (GLfloat const *) &cameraMatrix);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, floorVertices);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, floorIndices);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), 0);

    glDrawElements(GL_TRIANGLES, mapSize * 6, GL_UNSIGNED_INT, 0);
    SDL_GL_SwapWindow(window);
}
