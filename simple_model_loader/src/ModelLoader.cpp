#include "ModelLoader.hpp"

Model * ModelLoader::load(std::string filename)
{
    std::vector<GLfloat> vertexData;
    std::vector<GLuint>  indices;

    LOG("Loading " + filename);

    std::ifstream file(filename);
    
    if (file.is_open())
    {
        std::stringstream buffer;

        std::string line;

        while (std::getline(file, line))
        {
            std::istringstream buffer(line);

            char type;
            buffer >> type;

            if (type == 'v')
            {
                std::copy(std::istream_iterator<GLfloat>(buffer),
                          std::istream_iterator<GLfloat>(),
                          back_inserter(vertexData));
            }
            else if (type == 'e')
            {
                std::copy(std::istream_iterator<GLuint>(buffer),
                          std::istream_iterator<GLuint>(),
                          back_inserter(indices));
            }
        }

        file.close();
    }

    return new Model(&vertexData, &indices);
}
