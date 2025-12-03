#include <iostream>

// Сначала GLAD
#include <glad/glad.h>
// Потом GLFW
#include <GLFW/glfw3.h>

const unsigned int WINDOW_WIDTH = 800;
const unsigned int WINDOW_HEIGHT = 600;

// Callback, вызывается при изменении размера окна
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

// Обработка ввода с клавиатуры
void processInput(GLFWwindow* window)
{
    // Если нажали ESC — закрываем окно
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

int main()
{
    // 1. Инициализируем GLFW
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // 2. Настраиваем версию OpenGL: 3.3 Core
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // 3. Создаём окно
    GLFWwindow* window = glfwCreateWindow(
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        "Quaternion UAV Demo",
        nullptr,
        nullptr
    );

    if (window == nullptr)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Делаем контекст окна текущим
    glfwMakeContextCurrent(window);

    // 4. Инициализируем GLAD (после создания контекста!)
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    // 5. Устанавливаем начальный viewport
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // 6. Главный цикл приложения
    while (!glfwWindowShouldClose(window))
    {
        // Обрабатываем ввод
        processInput(window);

        // Очищаем экран (только цвет, пока без отрисовки объектов)
        glClearColor(0.1f, 0.1f, 0.2f, 1.0f); // тёмно-синий фон
        glClear(GL_COLOR_BUFFER_BIT);

        // Меняем местами буферы и обрабатываем события
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // 7. Освобождаем ресурсы
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
