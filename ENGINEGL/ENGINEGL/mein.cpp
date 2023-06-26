#include "libreria.h"
#include "luz.h"

int main() {
    // Inicializar GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Crear ventana GLFW
    GLFWwindow* window = glfwCreateWindow(800, 600, "engine", NULL, NULL);
    if (window == NULL) {
        std::cout << "Error al crear la ventana GLFW" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Inicializar GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Error al inicializar GLAD" << std::endl;
        return -1;
    }
    glViewport(0, 0, 800, 600);

    // Definir shaders
    const char* vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "out vec3 luzPosicion;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "   luzPosicion = vec3(1.0, 1.0, 1.0);\n"
        "}\0";

    const char* fragmentShaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "in vec3 luzPosicion;\n"
        "uniform vec3 luzColor;\n"
        "void main()\n"
        "{\n"
        "   vec3 color = vec3(1.0f, 0.0f, 0.0f);\n"
        "   vec3 ambient = vec3(0.1f, 0.1f, 0.1f);\n"
        "   vec3 diffuse = vec3(0.5f, 0.5f, 0.5f);\n"
        "   vec3 normal = normalize(vec3(0.0f, 0.0f, 1.0f));\n"
        "   vec3 lightDirection = normalize(luzPosicion);\n"
        "   float diff = max(dot(normal, lightDirection), 0.0);\n"
        "   vec3 diffuseColor = diffuse * diff * luzColor;\n"
        "   vec3 ambientColor = ambient * color;\n"
        "   FragColor = vec4(ambientColor + diffuseColor, 1.0f);\n"
        "}\n\0";

    // Crear programa de shaders
    GLuint shaderProgram = createShaderProgram(vertexShaderSource, fragmentShaderSource);

    // Definir vértices
    GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f, // esquina izquierda
         0.5f, -0.5f, 0.0f, // esquina derecha 
         0.0f,  0.5f, 0.0f  // parte superior
    };

    GLuint VAO, VBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Configurar callback para redimensionar ventana
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Crear objeto Luz
    Luz luz;

    // Configurar la luz
    luz.configurar(shaderProgram);

    // Bucle principal
    while (!glfwWindowShouldClose(window)) {
        // Limpiar el color de fondo
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Usar el programa de shaders
        glUseProgram(shaderProgram);

        // Dibujar triángulo
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Liberar recursos
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}