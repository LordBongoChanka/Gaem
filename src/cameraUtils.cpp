#include "cameraUtils.h"

void UpdateCamera(Camera2D &camera, int worldWidth, int worldHeight)
{
    if (camera.target.x - camera.offset.x < 0)
        camera.target.x = camera.offset.x;
    if (camera.target.y - camera.offset.y < 0)
        camera.target.y = camera.offset.y;
    if (camera.target.x + camera.offset.x > worldWidth)
        camera.target.x = worldWidth - camera.offset.x;
    if (camera.target.y + camera.offset.y > worldHeight)
        camera.target.y = worldHeight - camera.offset.y;
}
