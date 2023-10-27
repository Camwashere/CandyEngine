#pragma once

namespace Candy
{
  class DebugPanel
  {
  public:
    bool enabled = true;
    float step=100.f;
  public:
    void OnRenderUI();
  };
}