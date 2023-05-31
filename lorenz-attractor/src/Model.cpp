#include "Model.h"

//-----------------------------------------------------------------------------------------------------
// Read model attributes from a text file and store them in the corresponding vectors
// -----------------------------------------------------------------------------------------------------
void Model::initModel(const char *modelFile) {

// Import the model using the Assimp library
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(modelFile,
                                             aiProcess_Triangulate |
                                             aiProcess_JoinIdenticalVertices |
                                             aiProcess_PreTransformVertices |
                                             aiProcess_GenSmoothNormals |
                                             aiProcess_CalcTangentSpace |
                                             aiProcess_GenUVCoords);
    if (!scene) {
        std::cout << "The file " << modelFile << " could not be open." << std::endl;
        std::cin.get();
        exit(1);
    }

    // Extracts the attributes (positions, normals, textures, indices) from the imported model
    aiNode *node = scene->mRootNode;
    aiMesh *mesh = scene->mMeshes[node->mMeshes[0]];
    for (int i = 0; i < mesh->mNumVertices; i++) {
        positions.push_back(glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z));
        normals.push_back(glm::normalize(glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z)));
        if (mesh->mTextureCoords[0])
            textureCoords.push_back(glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y));
        else textureCoords.push_back(glm::vec2(0.0f, 0.0f));
    }
    for (int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for (int j = 0; j < face.mNumIndices; j++) indices.push_back(face.mIndices[j]);
    }

    // Create a VAO with the model attributes
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vboPositions);
    glGenBuffers(1, &vboNormals);
    glGenBuffers(1, &vboTextureCoords);
    glGenBuffers(1, &eboIndices);
    glBindVertexArray(vao);
    // Positions
    glBindBuffer(GL_ARRAY_BUFFER, vboPositions);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * positions.size(), &(positions.front()), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);
    // Normals
    glBindBuffer(GL_ARRAY_BUFFER, vboNormals);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * normals.size(), &(normals.front()), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(1);
    // Textures
    glBindBuffer(GL_ARRAY_BUFFER, vboTextureCoords);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * textureCoords.size(), &(textureCoords.front()), GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(2);
    // Indexes
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboIndices);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short) * indices.size(), &(indices.front()), GL_STATIC_DRAW);
    glBindVertexArray(0);

}

//--------------------------------
// Render the VAO with the model
//--------------------------------
void Model::renderModel(unsigned long mode) {

    glPolygonMode(GL_FRONT_AND_BACK, mode);
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_SHORT, (void *) 0);
    glBindVertexArray(0);

}

//-----------------------------------
// Class destroyer
//-----------------------------------
Model::~Model() {

    glDeleteBuffers(1, &vao);
    glDeleteBuffers(1, &vboPositions);
    glDeleteBuffers(1, &vboNormals);
    glDeleteBuffers(1, &vboTextureCoords);
    glDeleteBuffers(1, &eboIndices);

}
