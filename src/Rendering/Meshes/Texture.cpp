#include "Texture.h"
// #include <SDL2/SDL_image.h>

Texture::Texture(const char *image, const char *texType, GLuint slot)
{
    // Assigns the type of the texture ot the texture object
    type = texType;

    // Load in the image as a surface with SDL_Image
    // SDL_Surface *imageSurface = IMG_Load(image);

    // // Generates an OpenGL texture object
    // glGenTextures(1, &ID);
    // // Assigns the texture to a Texture Unit
    // glActiveTexture(GL_TEXTURE0 + slot);
    // unit = slot;
    // glBindTexture(GL_TEXTURE_2D, ID);

    // // See if image has transparancy
    // int numColCh = imageSurface->format->BytesPerPixel;
    // int mode = numColCh == 4
    //                ? GL_RGBA
    //            : numColCh == 3
    //                ? GL_RGB
    //                : GL_RED;

    // // Configures the type of algorithm that is used to make the image smaller or bigger
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // // Configures the way the texture repeats (if it does at all)
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // // Assigns the image to the OpenGL Texture object
    // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageSurface->w, imageSurface->h, 0, mode, GL_UNSIGNED_BYTE, imageSurface->pixels);

    // // Generates MipMaps
    // glGenerateMipmap(GL_TEXTURE_2D);

    // // Free up surface since we are done with it
    // SDL_FreeSurface(imageSurface);

    // // Unbinds the OpenGL Texture object so that it can't accidentally be modified
    // glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::texUnit(Shader &shader, const char *uniform, GLuint unit)
{
    // Gets the location of the uniform
    GLuint texUni = glGetUniformLocation(shader.ID, uniform);
    // Shader needs to be activated before changing the value of a uniform
    shader.Activate();
    // Sets the value of the uniform
    glUniform1i(texUni, unit);
}

void Texture::Bind()
{
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::Unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Delete()
{
    glDeleteTextures(1, &ID);
}