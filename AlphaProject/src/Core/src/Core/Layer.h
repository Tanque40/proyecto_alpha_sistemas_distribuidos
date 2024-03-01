#pragma once

#include "Core.h"
#include "TimeStep.h"
#include "Events/Event.h"

namespace Core {

class Layer {
   protected:
    std::string debugName;

   public:
    Layer(const std::string& name = "Layer");
    virtual ~Layer() = default;

    virtual void OnAttach() {}
    virtual void OnDetach() {}
    virtual void OnUpdate(TimeStep ts) {}
    virtual void OnImGuiRender() {}
    virtual void OnEvent(Event& event) {}

    inline const std::string& GetName() const { return debugName; }
};

}  // namespace Core