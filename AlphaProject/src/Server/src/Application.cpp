#include "EntryPoint.h"
#include "ApplicationLayer.h"
#include "Server.h"

using namespace Core;

class ClientApplication : public Application {
   public:
    ClientApplication() {
        PushLayer(new ApplicationLayer());
    }
};

int main() {
    std::unique_ptr<ClientApplication> app = std::make_unique<ClientApplication>();

    app->Run();

    return 0;
}