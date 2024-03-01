#include "Core.h"
#include "Layer.h"

#include <vector>

namespace Core {

class LayerStack {
   private:
    std::vector<Layer*> layers;
    uint32_t layerInsertIndex = 0;

   public:
    LayerStack();
    ~LayerStack();

    void PushLayer(Layer* layer);
    void PushOverlay(Layer* overlay);
    void PopLayer(Layer* layer);
    void PopOverlay(Layer* overlay);

    std::vector<Layer*>::iterator begin() { return layers.begin(); }
    std::vector<Layer*>::iterator end() { return layers.end(); }
};

}  // namespace Core