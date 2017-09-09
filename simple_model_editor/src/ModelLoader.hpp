#ifndef MODEL_LOADER_HPP
#define MODEL_LOADER_HPP

#include <GL/glew.h>

#include <algorithm>
#include <iterator>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#include "Model.hpp"
#include "Logger.hpp"

class ModelLoader
{
    public:
        static Model * load(std::string filename);

    private:
        /****************************************
         * Data members
        ****************************************/
};

#endif
