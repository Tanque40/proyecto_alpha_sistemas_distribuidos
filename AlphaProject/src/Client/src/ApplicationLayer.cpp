#include "ApplicationLayer.h"

using namespace Core;
using namespace Core::Utils;

ApplicationLayer::ApplicationLayer() {
}

void ApplicationLayer::OnAttach() {
    EnableDebugging();
}

void ApplicationLayer::OnDetach() {
}

void ApplicationLayer::OnUpdate(Core::Timestep timeStep) {
}

void ApplicationLayer::OnImGuiRender() {
}

void ApplicationLayer::OnEvent(Core::Event& event) {
}

ApplicationLayer::~ApplicationLayer() {
}
