#pragma once
#include "renderer/texture.hpp"

class OpenglTexture : public Texture
{
  public:
    OpenglTexture(const Image &image);
    void select(int slot) override;
    void deselect() override;
    uint32_t getId() override;
    virtual ~OpenglTexture();

  private:
    uint32_t m_id = 0;
};
