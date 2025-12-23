#include"../include/Icon.h"
Icon::Icon(const char* imagePath, Vector2 pos, float scale)
{
    Image img = LoadImage(imagePath);
    int width = static_cast<int>(img.width * scale);
    int height = static_cast<int>(img.height * scale);
    texture = LoadTextureFromImage(img);
    UnloadImage(img); // Free image memory after loading texture cause we already have texture in GPU after LoadTextureFromImage
    position = pos;
}

Icon::~Icon()
{
    UnloadTexture(texture);
}

void Icon::Update()
{
    // Update logic if needed
}

void Icon::Draw()
{
    DrawTextureV(texture, position, WHITE);
}