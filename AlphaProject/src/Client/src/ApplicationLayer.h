#include <EntryPoint.h>
#include <EntryPointUtils.h>

class ApplicationLayer : public Core::Layer {
   public:
    ApplicationLayer();
    virtual ~ApplicationLayer();

    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnEvent(Core::Event& event) override;
    virtual void OnUpdate(Core::Timestep timeStep) override;
    virtual void OnImGuiRender() override;
};