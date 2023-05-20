#include "RenderCommand.hpp"
namespace Candy::Graphics {
    UniquePtr<RendererAPI> RenderCommand::rendererAPI=RendererAPI::Create();
}
