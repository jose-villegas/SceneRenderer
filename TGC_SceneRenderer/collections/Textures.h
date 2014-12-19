#pragma once
#define DEFAULT_TEXTURE_ID 0

#include "../types/Texture.h"
#include <fstream>
#include <iostream>
#include <streambuf>
#include <map>
#include <windows.h>

namespace collections {

    class Textures {
        public:
            virtual ~Textures();
            // creates Unique Static Instance
            static Textures *Instance();
            // loads a new texture
            bool loadTexture(const std::string &sFilename, const unsigned int texID, types::Texture::TextureType textureType);
            // loads a new texture with unique texID (slower)
            bool loadTexture(const std::string &sFilename, types::Texture::TextureType textureType);
            // frees memory reserved for texID texture
            bool unloadTexture(const unsigned int &texID);
            // sets texID texture as the current active texture
            bool bindTexture(const unsigned int &texID);
            // frees memory reserved for all the textures
            void unloadAllTextures();
            // amount of textures loaded
            unsigned int count(void) const;
            // return default texture's texID, white default texture
            types::Texture *getDefaultTexture() { return getTexture(DEFAULT_TEXTURE_ID); }
            types::Texture *getTexture(const unsigned &texID);

        protected:
            Textures(const Textures &cpy);
            Textures();
            static Textures *_eInstance;
            // Texture Collection
            std::map<unsigned int, types::Texture *> textures;
    };

}
