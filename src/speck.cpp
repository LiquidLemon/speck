#include <fstream>
#include "ppm.hpp"
#include "renderer.hpp"
#include "obj.hpp"
#include <algorithm>

#include <iostream>

int main() {
  srand(time(0));
  Renderer render(PPMImage(1024, 1024));

  std::ifstream head("obj/african_head.obj");
  if (!head.good()) {
    throw std::runtime_error("Failed opening .obj");
  }

  Obj obj;
  obj.read(head);
  head.close();

  std::ifstream diffuse("obj/african_head_diffuse.ppm", std::ios::binary);
  if (!diffuse.good()) {
    std::cerr << "Failed to load texture" << std::endl;
    exit(1);
  }
  auto texture = PPMImage::loadP6(diffuse);
  diffuse.close();
  texture.flipVertically();

  Vector3f light({ 0, 0, 1 });
  light.normalize();

  int zBufferSize = render.getImage().getWidth() * render.getImage().getHeight();
  float *zBuffer = new float[zBufferSize];
  std::fill(zBuffer, zBuffer + zBufferSize, -std::numeric_limits<float>::max());

  for (auto &face : obj.faces) {
    std::array<Vector3f, 3> worldCoords;

    std::transform(face.vertices.begin(), face.vertices.end(), worldCoords.begin(),
      [&](int i) -> Vector3f { return obj.vertices[i]; }
    );

    std::array<Vector2f, 3> uvs;

    std::transform(face.uvs.begin(), face.uvs.end(), uvs.begin(),
      [&](int i) -> Vector2f { return obj.uvs[i]; }
    );

    std::array<Vector3f, 3> screenCoords;
    std::transform(worldCoords.begin(), worldCoords.end(), screenCoords.begin(),
      [&](auto& v) -> Vector3f {
        return {
          (1 + v[0]) * render.getImage().getWidth() / 2,
          (1 + v[1]) * render.getImage().getHeight() / 2,
          v[2]
        };
      }
    );

    auto normal = (worldCoords[0] - worldCoords[1])^(worldCoords[0] - worldCoords[2]);
    normal.normalize();
    float intensity = light * normal;
    if (intensity > 0) {
      render.triangle(screenCoords, intensity, zBuffer, uvs, texture);
    }
  }

  delete[] zBuffer;

  render.getImage().flipVertically();

  std::ofstream output("test.p6", std::ios::binary);
  if (!output.good()) {
    throw std::runtime_error("Couldn't open output");
  }

  render.getImage().write(output);

  output.close();
}
