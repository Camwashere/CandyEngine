
#include <Candy/CandyEngineBase.hpp>
namespace Candy::Graphics{
    class UniformBuffer
    {
    private:
        uint32 rendererID=0;
    public:
        UniformBuffer(uint32 size, uint32 binding);
        ~UniformBuffer();
        
        void SetData(const void* data, uint32 size, uint32 offset=0);
    };
}

