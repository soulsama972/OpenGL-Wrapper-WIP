#include<iostream>

// gl
#include<GL/glew.h>
#include<GLFW/glfw3.h>

// renderer
#include"shader.h"
#include"textrue.h"
#include"renderer.h"
#include"vertexArray.h"
#include"indexBuffer.h"
#include"vertexBuffer.h"
#include"vertexBufferLayout.h"
#include"objLoader.h"
// math
#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"

// imgui
#include"imgui/imgui.h"
#include"imgui/imgui_impl_glfw.h"
#include"imgui/imgui_impl_opengl3.h"

// test case
#include"tests/testMenu.h"
#include"tests/testTextrue.h"
#include"tests/testDrawSqure.h"
#include"tests/testDrawModel.h"
#include"tests/testClearColor.h"
int main(void)
{
    GLFWwindow* window;
    Renderer renderer;
    Test* currentTest = nullptr;
    TestMenu menu(currentTest);

    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(1920, 1080, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (GLEW_OK != glewInit())
        std::cout << "error" << std::endl;

    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");
    ImGui::StyleColorsDark();

    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    GLCall(glEnable(GL_BLEND));

    //GLCall(glEnable(GL_CULL_FACE));
    //GLCall(glEnable(GL_DEPTH_TEST));
    //GLCall(glDepthFunc(GL_LEQUAL));


    menu.RegisterTest<TestClearColor>("clearColor");
    menu.RegisterTest<TestDrawSqure>("DrawSqure");
    menu.RegisterTest<TestTextrue2D>("testDrawTextrue");
    menu.RegisterTest<TestDrawModel>("testDrawModel");
    currentTest = &menu;
    currentTest = new TestDrawModel();


    int x = 1;
    {
        while (!glfwWindowShouldClose(window))
        {
            renderer.Clear();
            currentTest->ImGuiBegin();
            if (currentTest)
            {
                currentTest->OnUpdate(0.0f);
                currentTest->OnRender();
                currentTest->OnImGuiRender();
            }
            menu.ExitToMenu();
            currentTest->ImGuiEnd();

            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();

    return 0;
}