#include "Shaders.h"

//--------------------------------------------------------------------------------------
// Create vertex and fragment shaders from the corresponding source code
//--------------------------------------------------------------------------------------
void Shaders::initShaders(const char *vShaderFile, const char *fShaderFile) {

    unsigned int vShader = createShader(GL_VERTEX_SHADER  , vShaderFile);
    unsigned int fShader = createShader(GL_FRAGMENT_SHADER, fShaderFile);
    program = createProgram(vShader, fShader);
    
}

//--------------------------------------
// Create a shader (vertices/fragments)
//--------------------------------------
unsigned int Shaders::createShader(unsigned long shader, const char* shaderFile) {
   
 // A shader object is created
    unsigned int shaderID = glCreateShader(shader);
    
 // Its source code contained in a glsl file is assigned
    std::string   code = "";
    std::ifstream file(shaderFile, std::ios::in);
    if(file.is_open()) {
        std::string line;
        while(getline(file, line)) code += line + "\n";
        file.close();
    }
    else {
        std::cout << "The file " << shaderFile << " could not be open." << std::endl;
        return 0;
    }
    const char *shaderSrc = code.c_str();
    glShaderSource(shaderID, 1, &shaderSrc, NULL);
    
 // Compiles with error handling
    int compiled;    
    glCompileShader(shaderID);
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compiled);
    if(compiled == GL_FALSE) {
        int logSize;
        glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &logSize);
        char *logMsg = new char[logSize];
        glGetShaderInfoLog(shaderID, logSize, NULL, logMsg);
        std::cout << "Error compiling Shader " << shaderFile << ": " << logMsg;
        delete[] logMsg;
        return 0;
    }
    
    return shaderID;
}

//-------------------------------------------------------------------
// Creates a program (handle) that uses the specified shaders
//-------------------------------------------------------------------
unsigned int Shaders::createProgram(unsigned int vShader, unsigned int fShader) {
    
 // A program object is created
    unsigned int program = glCreateProgram();
    
 // Shaders are attached and corresponding objects are removed
    glAttachShader(program, vShader);
    glAttachShader(program, fShader);
    glDeleteShader(vShader);
    glDeleteShader(fShader);
    
 // The program is linked with error control
    int linked;    
    glLinkProgram(program);
    glGetShaderiv(program, GL_COMPILE_STATUS, &linked);
    if(linked == GL_FALSE) {
        int logSize;
        glGetShaderiv(program, GL_INFO_LOG_LENGTH, &logSize);
        char *logMsg = new char[logSize];
        glGetShaderInfoLog(program, logSize, NULL, logMsg);
        std::cout << "Error linking Shader: " << logMsg;
        delete[] logMsg;
        return 0;
    }
    
    return program;    
}

//-----------------------------------------------------
// Sets the value of a uniform variable of type vec3
//-----------------------------------------------------
void Shaders::setVec3(const std::string &name, glm::vec3 value) {
    
   glUniform3fv(glGetUniformLocation(program,name.c_str()), 1, glm::value_ptr(value));
    
}

//-----------------------------------------------------
// Sets the value of a uniform variable of type mat4
//-----------------------------------------------------
void Shaders::setMat4(const std::string &name, glm::mat4 value) {
    
   glUniformMatrix4fv(glGetUniformLocation(program,name.c_str()), 1, GL_FALSE, glm::value_ptr(value)); 
    
}

//------------------------------------------------------
// Sets the value of a uniform variable of type Light
//------------------------------------------------------
void Shaders::setLight(const std::string &name, Light value) {
    
    glUniform3fv(glGetUniformLocation(program,(name+".position"   ).c_str()), 1, glm::value_ptr(value.position ));
    glUniform3fv(glGetUniformLocation(program,(name+".direction"  ).c_str()), 1, glm::value_ptr(value.direction));
    glUniform3fv(glGetUniformLocation(program,(name+".ambient"    ).c_str()), 1, glm::value_ptr(value.ambient  ));
    glUniform3fv(glGetUniformLocation(program,(name+".diffuse"    ).c_str()), 1, glm::value_ptr(value.diffuse  ));
    glUniform3fv(glGetUniformLocation(program,(name+".specular"   ).c_str()), 1, glm::value_ptr(value.specular ));
    glUniform1f (glGetUniformLocation(program,(name+".innerCutOff").c_str()), glm::cos(glm::radians(value.innerCutOff)));
    glUniform1f (glGetUniformLocation(program,(name+".outerCutOff").c_str()), glm::cos(glm::radians(value.outerCutOff)));
    glUniform1f (glGetUniformLocation(program,(name+".c0"         ).c_str()), value.c0);
    glUniform1f (glGetUniformLocation(program,(name+".c1"         ).c_str()), value.c1);
    glUniform1f (glGetUniformLocation(program,(name+".c2"         ).c_str()), value.c2);
            
}

std::string toString(const int &i) {
    std::stringstream ss;
    ss << i;
    return ss.str();
}

//---------------------------------------------------------
// Sets the value of a uniform variable of type Material
//---------------------------------------------------------
void Shaders::setMaterial(const std::string &name, Material value) {
    
    glUniform4fv(glGetUniformLocation(program,(name+".ambient"  ).c_str()), 1, glm::value_ptr(value.ambient ));
    glUniform4fv(glGetUniformLocation(program,(name+".diffuse"  ).c_str()), 1, glm::value_ptr(value.diffuse ));
    glUniform4fv(glGetUniformLocation(program,(name+".specular" ).c_str()), 1, glm::value_ptr(value.specular));
    glUniform4fv(glGetUniformLocation(program,(name+".emissive" ).c_str()), 1, glm::value_ptr(value.emissive));
    glUniform1f (glGetUniformLocation(program,(name+".shininess").c_str()), value.shininess);
            
}

//--------------------------------------------------------------------
// Sets the value of a uniform variable (sampler2D) of type Texture
//--------------------------------------------------------------------
void Shaders::setTextures(const std::string &name, Textures value) {
   
    glActiveTexture(GL_TEXTURE0 + value.diffuse);
    glBindTexture(GL_TEXTURE_2D,value.diffuse);
    glUniform1i(glGetUniformLocation(program,(name+".diffuse").c_str()), value.diffuse);
    
    glActiveTexture(GL_TEXTURE0 + value.specular);
    glBindTexture(GL_TEXTURE_2D,value.specular);
    glUniform1i(glGetUniformLocation(program,(name+".specular").c_str()), value.specular);
    
    glActiveTexture(GL_TEXTURE0 + value.emissive);
    glBindTexture(GL_TEXTURE_2D,value.emissive);
    glUniform1i(glGetUniformLocation(program,(name+".emissive").c_str()), value.emissive);
    
    if(value.normal!=0) {
        glActiveTexture(GL_TEXTURE0 + value.normal);
        glBindTexture(GL_TEXTURE_2D,value.normal);
        glUniform1i(glGetUniformLocation(program,(name+".normal"  ).c_str()), value.normal);
    }
    
    glUniform1f (glGetUniformLocation(program,(name+".shininess").c_str()), value.shininess);
            
}

//------------------------------------------------------
// Sets the value of a uniform variable of type float
//------------------------------------------------------
void Shaders::setFloat(const std::string &name, float value) {
    
    glUniform1f(glGetUniformLocation(program,name.c_str()),value);
            
}

//------------------------------------------------------
// Sets the value of a uniform variable of type bool
//------------------------------------------------------
void Shaders::setBool(const std::string &name, int value) {
    
    glUniform1i(glGetUniformLocation(program,name.c_str()),value);
            
}

//-----------------------------------------
// Use the shader to render the scene
//-----------------------------------------
void Shaders::useShaders() {
    
    glUseProgram(program);
    
}

//-----------------------------------
// Class destroyer
//-----------------------------------
Shaders::~Shaders() {

    glDeleteProgram(program);

}
