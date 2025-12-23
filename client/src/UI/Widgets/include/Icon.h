#include <raylib.h>

class Icon
{
    public:
    Icon() = default;
    Icon(const char* imagePath, Vector2 pos, float scale);
    ~Icon();
    void Update();
    void Draw();
    private:
    Texture2D texture;
    Vector2 position;
};