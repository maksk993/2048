#include "ShaderProgram.hpp"

ShaderProgram::ShaderProgram(const std::string& vertexShaderSourcePath, const std::string& fragmentShaderSourcePath) {
    std::string vertexShaderSource = load(vertexShaderSourcePath);
    std::string fragmentShaderSource = load(fragmentShaderSourcePath);
    const char* vss_c_str = vertexShaderSource.c_str();
    const char* fss_c_str = fragmentShaderSource.c_str();

    GLuint vertexShaderID, fragmentShaderID;

    bool success = true;
    if (!createShader(vss_c_str, GL_VERTEX_SHADER, vertexShaderID)) {
        success = false;
        std::cerr << "Vertex shader not created\n";
    }

    if (!success || !createShader(fss_c_str, GL_FRAGMENT_SHADER, fragmentShaderID)) {
        glDeleteShader(vertexShaderID);
        std::cerr << "Fragment shader not created\n";
    }
    else {
        createShaderProgram(vertexShaderID, fragmentShaderID);
    }
}

ShaderProgram::~ShaderProgram() {
    glDeleteProgram(m_ID);
}

ShaderProgram::ShaderProgram(ShaderProgram&& other) noexcept {
    m_ID = other.m_ID;
    other.m_ID = 0;
}

ShaderProgram& ShaderProgram::operator=(ShaderProgram&& other) noexcept {
    if (this != &other) {
        glDeleteProgram(m_ID);
        m_ID = other.m_ID;
        other.m_ID = 0;
    }
    return *this;
}

GLuint ShaderProgram::getID() const {
    return m_ID;
}

void ShaderProgram::use() const {
    glUseProgram(m_ID);
}

void ShaderProgram::setInt(const std::string& name, const GLint value) {
    glUniform1i(glGetUniformLocation(m_ID, name.c_str()), value);
}

void ShaderProgram::setMatrix4(const std::string& name, const glm::mat4& matrix) {
    glUniformMatrix4fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
}

std::string ShaderProgram::load(const std::string& path) {
    std::ifstream file(path);

    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << path << std::endl;
        return "";
    }

    std::stringstream buffer;
    buffer << file.rdbuf();

    file.close();
    return buffer.str();
}

bool ShaderProgram::createShader(const char* shaderSource, GLenum shaderType, GLuint& shaderID) {
    shaderID = glCreateShader(shaderType);
    glShaderSource(shaderID, 1, &shaderSource, nullptr);
    glCompileShader(shaderID);

    GLint success;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLchar infoLog[1024];
        glGetProgramInfoLog(shaderID, 1024, nullptr, infoLog);

        std::string shaderTypeStr;
        switch (shaderType) {
        case GL_VERTEX_SHADER:
            shaderTypeStr = "GL_VERTEX_SHADER";
            break;
        case GL_FRAGMENT_SHADER:
            shaderTypeStr = "GL_FRAGMENT_SHADER";
            break;
        default:
            break;
        }

        std::cerr << "Can't compile " << shaderTypeStr << ":\n" << infoLog << std::endl;
        return false;
    }
    return true;
}

void ShaderProgram::createShaderProgram(GLuint& vertexShaderID, GLuint& fragmentShaderID) {
    m_ID = glCreateProgram();
    glAttachShader(m_ID, vertexShaderID);
    glAttachShader(m_ID, fragmentShaderID);
    glLinkProgram(m_ID);

    GLint success;
    glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
    if (!success)
    {
        GLchar infoLog[1024];
        glGetShaderInfoLog(m_ID, 1024, nullptr, infoLog);
        std::cerr << "Can't link shader program:\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);
}