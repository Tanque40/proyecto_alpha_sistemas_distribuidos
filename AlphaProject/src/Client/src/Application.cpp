#include "EntryPoint.h"
#include "ApplicationLayer.h"

using namespace Core;

class ClientApplication : public Application {
   public:
    ClientApplication() : Application("Client Alpha Project") {
        PushLayer(new ApplicationLayer());
    }
};

int main() {
    std::unique_ptr<ClientApplication> app = std::make_unique<ClientApplication>();
    app->Run();
    return 0;
}