#include <raylib.h>
#include"IIcon.h"
class ImageIcon: public IIcon
{
    public:
    ImageIcon() = default;
    ImageIcon(const char* imagePath, Vector2 pos, float scale);
    ~ImageIcon();
    void Update() override;
    void Draw() override;
    private:
    Texture2D texture;
    Vector2 position;
};