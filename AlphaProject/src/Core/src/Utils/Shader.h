#include <string>

#ifdef __WINDOWS__
#include <glad/glad.h>
#endif  // WINDOWS

#ifdef __APPLE__
#include <GL/glew.h>
#endif  // __APPLE__

namespace Core::Utils {

class Shader {
   private:
    GLuint rendererId;

   public:
    ~Shader();

    GLuint GetRendererID() { return rendererId; }

    static Shader* FromGLSLTextFiles(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);

   private:
    Shader() = default;

    void LoadFromGLSLTextFiles(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
    GLuint CompileShader(GLenum type, const std::string& source);
};

}  // namespace Core::Utils