#include "Texture.h"
#include <SDL2/SDL_image.h>

Texture::Texture(const char *image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType)
{
    // Assigns the type of the texture ot the texture object
    type = texType;

    // Load in the image as a surface with SDL_Image
    SDL_Surface *imageSurface = IMG_Load(image);

    // Generates an OpenGL texture object
    glGenTextures(1, &ID);
    // Assigns the texture to a Texture Unit
    glActiveTexture(slot);
    glBindTexture(texType, ID);

    // See if image has transparancy
    int mode = imageSurface->format->BytesPerPixel == 4 ? GL_RGBA : GL_RGB;

    // Configures the type of algorithm that is used to make the image smaller or bigger
    glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Configures the way the texture repeats (if it does at all)
    glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Assigns the image to the OpenGL Texture object
    glTexImage2D(texType, 0, mode, imageSurface->w, imageSurface->h, 0, format, pixelType, imageSurface->pixels);

    // Free up surface since we are done with it
    SDL_FreeSurface(imageSurface);

    // Generates MipMaps
    glGenerateMipmap(texType);

    // Unbinds the OpenGL Texture object so that it can't accidentally be modified
    glBindTexture(texType, 0);
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
    glBindTexture(type, ID);
}

void Texture::Unbind()
{
    glBindTexture(type, 0);
}

void Texture::Delete()
{
    glDeleteTextures(1, &ID);
}