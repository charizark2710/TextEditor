#pragma once
#include "Renderer.h"

class Texture
{
private:
    unsigned int rendererId;
    std::string filePath;
    unsigned char *localBuffer;
    //bit per pixel
    int width, height, BPP;

public:
    Texture(const std::string& path);
    ~Texture();
    void Bind(unsigned int slot = 0) const;
    void UnBind() const;

    inline int getWidth() const { return width; }
    inline int getHeight() const { return height; }
};

