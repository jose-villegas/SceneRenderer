#include "Textures.h"
using namespace ECollections;

Textures ^Textures::Instance()
{
    if (!_eInstance) {
        _eInstance = gcnew Textures();
    }

    return _eInstance;
}

Textures::Textures()
{
    this->_eTexCollection = gcnew System::Collections::Hashtable();
    // call this ONLY when linking with FreeImage as a static library
#ifdef FREEIMAGE_LIB
    FreeImage_Initialise();
#endif
    // Default Texture
    loadTexture("../Resources/white.png", 0, GL_RGBA, GL_RGBA, 0, 0);
}

Textures::~Textures()
{
    // call this ONLY when linking with FreeImage as a static library
#ifdef FREEIMAGE_LIB
    FreeImage_DeInitialise();
#endif
    unloadAllTextures();
}

bool Textures::loadTexture(const char *filename, const unsigned int texID, GLenum image_format , GLint internal_format , GLint level,
                           GLint border)
{
    //image format
    FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
    //pointer to the image, once loaded
    FIBITMAP *dib = nullptr;
    //pointer to the image data
    BYTE *bits = nullptr;
    //image width and height
    unsigned int width = 0, height = 0, bpp = 0;
    //OpenGL's image ID to map to
    GLuint gl_texID;
    //check the file signature and deduce its format
    fif = FreeImage_GetFileType(filename, 0);

    //if still unknown, try to guess the file format from the file extension
    if (fif == FIF_UNKNOWN) {
        fif = FreeImage_GetFIFFromFilename(filename);
    }

    //if still unkown, return failure
    if (fif == FIF_UNKNOWN) {
        return false;
    }

    //check that the plugin has reading capabilities and load the file
    if (FreeImage_FIFSupportsReading(fif)) {
        dib = FreeImage_Load(fif, filename);
    }

    //if the image failed to load, return failure
    if (!dib) {
        return false;
    }

    //retrieve the image data
    bits = FreeImage_GetBits(dib);
    //get the image width and height
    width = FreeImage_GetWidth(dib);
    height = FreeImage_GetHeight(dib);
    bpp = FreeImage_GetBPP(dib);

    //if this somehow one of these failed (they shouldn't), return failure
    if ((bits == 0) || (width == 0) || (height == 0)) {
        return false;
    }

    //if this texture ID is in use, unload the current texture
    if (_eTexCollection->Contains(texID)) {
        // glDeleteTextures(1, &(_eTexCollection[texID]->oglTexID));
        interior_ptr<unsigned int> intTexPtr = &((((Types::Texture ^)_eTexCollection[texID]))->oglTexID);
        pin_ptr<unsigned int> pinnedPtr = &intTexPtr[0];
        glDeleteTextures(1, pinnedPtr);
    }

    glGenTextures(1, &gl_texID);													// generate an OpenGL texture ID for this texture
    // _eTexCollection[texID] = new Types::Texture(filename, width, height, bpp, gl_texID, texID);	// store the texture
    Types::Texture ^newTexture = gcnew Types::Texture(gcnew System::String(filename), width, height, bpp, gl_texID, texID);
    _eTexCollection->Add(texID, newTexture);
    glBindTexture(GL_TEXTURE_2D, gl_texID);											// bind to the new texture ID
    // store the texture data for OpenGL use
    glTexImage2D(GL_TEXTURE_2D, level, internal_format, width, height, border, image_format, GL_UNSIGNED_BYTE, bits);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
    // Free FreeImage's copy of the data
    FreeImage_Unload(dib);
    // return success
    return true;
}

bool Textures::loadTexture(const char *filename, GLenum image_format, GLint internal_format, GLint level, GLint border)
{
    int unique_texID = 1;

    for each(Types::Texture ^ var in _eTexCollection) {
        if (var->texID == unique_texID) {
            unique_texID++;
        } else {
            break;
        }
    }

    return loadTexture(filename, unique_texID, image_format, internal_format, level, border);
}

bool Textures::unloadTexture(const unsigned int texID)
{
    bool result = true;

    if (_eTexCollection->Contains(texID)) {
        interior_ptr<unsigned int> intTexPtr = &((((Types::Texture ^)_eTexCollection[texID]))->oglTexID);
        pin_ptr<unsigned int> pinnedPtr = &intTexPtr[0];
        glDeleteTextures(1, pinnedPtr);
        _eTexCollection->Remove(texID);
    }

    return result;
}

bool Textures::bindTexture(const unsigned int texID)
{
    bool result = true;

    if (_eTexCollection->Contains(texID)) {
        ((Types::Texture ^)_eTexCollection[texID])->bind();
    } else {
        result = false;
    }

    return result;
}

void Textures::unloadAllTextures()
{
    for each(Types::Texture ^ var in _eTexCollection) {
        unloadTexture(var->texID);
    }

    //clear the texture map
    _eTexCollection->Clear();
}

unsigned int Textures::count(void)
{
    return _eTexCollection->Count;
}
