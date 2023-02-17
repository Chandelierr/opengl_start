#include <iostream>
#include <glad/glad.h>
#include <stdio.h>
#include <stdlib.h>
#include <GLFW/glfw3.h>
#include <cmath>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);
int prepareShader();
void triangle(GLFWwindow *window);
void rectangle(GLFWwindow *window);
void threeColorTriangle(GLFWwindow *window);
// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

//普通顶点着色器源码
// const char *vertexShaderSource = "#version 330 core\n"
//                                  "layout (location = 0) in vec3 aPos;\n"// 位置变量的属性位置值为0
//                                  "out vec4 vertexColor;\n" // 为片段着色器指定一个颜色输出
//                                  "void main()\n"
//                                  "{\n"
//                                  "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"// 注意我们如何把一个vec3作为vec4的构造器的参数
//                                  "   vertexColor = vec4(0.5, 0.0, 0.0, 1.0);\n"// 把输出变量设置为暗红色
//                                  "}\0";
// 三角三颜色 通顶点着色器源码
const char *vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"// 位置变量的属性位置值为0
                                 "layout (location = 1) in vec3 aColor; \n" //// 颜色变量的属性位置值为 1
                                 "out vec4 ourColor;\n" // 为片段着色器指定一个颜色输出
                                 "void main()\n"
                                 "{\n"
                                 "   gl_Position = vec4(aPos, 1.0);\n"// 注意我们如何把一个vec3作为vec4的构造器的参数
                                 "   ourColor = vec4(aColor, 1.0);\n"// 把输出变量设置为暗红色
                                 "}\0";
//片段着色器源码， ourColor是uniform定义的，可以由openGL传递                                      
// const char *fragmentShaderSource = "#version 330 core\n"
//                                    "out vec4 FragColor;\n"
//                                    "uniform vec4 ourColor;\n" // 在OpenGL程序代码中设定这个变量
//                                 //    "in vec4 vertexColor;\n" // 从顶点着色器传来的输入变量（名称相同、类型相同）"
//                                    "void main()\n"
//                                    "{\n"
//                                 //    "   FragColor = vertexColor;\n"
//                                    "   FragColor = ourColor;\n"
//                                    "   //FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
//                                    "}\n\0";

//片段着色器
const char *fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "in vec4 ourColor;\n" 
                                   "void main()\n"
                                   "{\n"
                                   "   FragColor = ourColor;\n"
                                   "}\n\0";

int main(int, char **)
{
    std::cout << "Hello, world!\n";
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    //如果使用的是Mac OS X系统，你还需要加下面这行代码到你的初始化代码中这些配置才能起作用
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "fail to create window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "failed to initalize GLAD" << std::endl;
        return -1;
    }
    // triangle(window);
    // rectangle(window);
    threeColorTriangle(window);
    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

int prepareShader()
{
    //-----------------------------start-----------------------------
    //创建顶点着色器vertexShader
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    //顶点着色器源码vertexShaderSource 附加到顶点着色器对象 vertexShader,   并编译
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    //检测顶点着色器编译的结果，如果编译失败，打印错误信息
    int  vertexShaderSuccess;
    char vertexShaderInfoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vertexShaderSuccess);
    if(!vertexShaderSuccess)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, vertexShaderInfoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << vertexShaderInfoLog << std::endl;
    }

    //-----------------------------start-----------------------------
    //创建片段着色器fragmentShader
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);    

    //片段着色器源码fragmentShaderSource 附加到片段着色器对象fragmentShader,   并编译
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    int  fragmentShaderSuccess;
    char fragmentShaderInfoLog[512];
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fragmentShaderSuccess);
    if(!fragmentShaderSuccess)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, fragmentShaderInfoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << fragmentShaderInfoLog << std::endl;
    }

    //-----------------------------start-----------------------------
    //着色器准备就绪，创建一个着色器程序shaderProgram
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    //把之前编译的两个着色器附加到程序对象上，然后用glLinkProgram链接它们：
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    //检查链接的结果
    int  linkProgramSuccess;
    char linkProgramInfoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &linkProgramSuccess);
    if(!linkProgramSuccess)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, linkProgramInfoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << linkProgramInfoLog << std::endl;
    }

    //链接完成后不再需要也被链接的着色器，释放
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return shaderProgram;
}

void triangle(GLFWwindow *window)
{
    unsigned int shaderProgram = prepareShader();

    //-----------------------------start-----------------------------
     //三个顶点， 分别有x、y、z， z轴都是0
    float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
    };

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    // 创建顶点缓冲对象VBO、顶点数组对象VAO
        // 顶点数组对象可以像顶点缓冲对象那样被绑定，任何随后的顶点属性调用都会储存在这个VAO中。
        //这样的好处就是，当配置顶点属性指针时，你只需要将那些调用执行一次，之后再绘制物体的时候只需要绑定相应的VAO就行了。
        //这使在不同顶点数据和属性配置之间切换变得非常简单，只需要绑定不同的VAO就行了。刚刚设置的所有状态都将存储在VAO中
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    // ..:: 初始化代码（只运行一次 (除非你的物体频繁改变)） :: ..
    //1. 绑定VAO
    glBindVertexArray(VAO);

    //2. 把顶点数组复制到缓冲中供OpenGL使用
    //新创建的缓冲VBO绑定到GL_ARRAY_BUFFER目标
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //定义的顶点数据复制到缓冲的内存,
    //GL_STATIC_DRAW ：表示传入的顶点数据不会或几乎不会改变。
    //GL_DYNAMIC_DRAW：数据会被改变很多。
    //GL_STREAM_DRAW ：数据每次绘制时都会改变。
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //3. 设置顶点属性指针
    //告诉OpenGL该如何解析顶点数据
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    //以顶点属性位置值作为参数，启用顶点属性
    glEnableVertexAttribArray(0);

    // 不懂note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // 不懂VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);


    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        //为屏幕设置新颜色：输入的深蓝绿色
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        //清空屏幕的颜色，并将屏幕设置为glClearColor输入的颜色
        glClear(GL_COLOR_BUFFER_BIT);

        // 激活着色器程序对象
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        // glDrawArrays(GL_TRIANGLES, 0, 6);
        //画三角形
        glDrawArrays(GL_TRIANGLES, 0, 3);
        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        // glBindVertexArray(0); // no need to unbind it every time

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        //检查并调用事件，交换缓冲
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    //  释放资源 optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
}

/**
 * @brief 三个角是三个颜色的三角形
 * 
 * @param window 
 */
void threeColorTriangle(GLFWwindow *window)
{
    unsigned int shaderProgram = prepareShader();

    //-----------------------------start-----------------------------
     //三个顶点， 分别有x、y、z， z轴都是0
    float vertices[] = {
    // 位置              // 颜色
     0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // 右下
    -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // 左下
     0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // 顶部
    };
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // 位置属性
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // 颜色属性
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);


    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);


    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
}


void rectangle(GLFWwindow *window)
{
    unsigned int shaderProgram = prepareShader();

    //-----------------------------start-----------------------------
     //只记顶点
    float vertices[] = {
    0.6f, 0.5f, 0.0f,   // 右上角
    0.5f, -0.5f, 0.0f,  // 右下角
    -0.6f, -0.5f, 0.0f, // 左下角
    -0.5f, 0.5f, 0.0f   // 左上角
    };

    //索引
    unsigned int indices[] = {
        // 注意索引从0开始! 
        // 此例的索引(0,1,2,3)就是顶点数组vertices的下标，
        // 这样可以由下标代表顶点组合成矩形

        0, 1, 3, // 第一个三角形
        1, 2, 3  // 第二个三角形
    };

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    // 创建顶点缓冲对象VBO、顶点数组对象VAO
        // 顶点数组对象可以像顶点缓冲对象那样被绑定，任何随后的顶点属性调用都会储存在这个VAO中。
        //这样的好处就是，当配置顶点属性指针时，你只需要将那些调用执行一次，之后再绘制物体的时候只需要绑定相应的VAO就行了。
        //这使在不同顶点数据和属性配置之间切换变得非常简单，只需要绑定不同的VAO就行了。刚刚设置的所有状态都将存储在VAO中
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    // ..:: 初始化代码（只运行一次 (除非你的物体频繁改变)） :: ..
    //1. 绑定VAO
    glBindVertexArray(VAO);

    //2. 把顶点数组复制到缓冲中供OpenGL使用
    //新创建的顶点缓冲对象VBO绑定到GL_ARRAY_BUFFER目标
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //定义的顶点数据vertices复制到缓冲的内存,
    //GL_STATIC_DRAW ：表示传入的顶点数据不会或几乎不会改变。
    //GL_DYNAMIC_DRAW：数据会被改变很多。
    //GL_STREAM_DRAW ：数据每次绘制时都会改变。
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

     //3. 把索引数组复制到缓冲中供OpenGL使用
    //新创建的元素/索引缓冲对象EBO绑定到GL_ELEMENT_ARRAY_BUFFER目标
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //定义的元素/索引数据indices复制到缓冲的内存,
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //4. 设置顶点属性指针
    //告诉OpenGL该如何解析顶点数据
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    //以顶点属性位置值作为参数，启用顶点属性
    glEnableVertexAttribArray(0);


    //note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    //解绑VBO，调用glVertexAttribPointer后会将VBO注册为顶点属性的绑定顶点缓冲区对象，因此之后我们可以安全地解除绑定
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
    //当 VAO 处于活动状态时，不要取消绑定 EBO，因为绑定的元素缓冲区对象存储在 VAO 中；保持 EBO 绑定。
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    //解绑VAO，这样其他VAO调用就不会意外修改此VAO，但这种情况很少发生。修改其他VAO无论如何都需要调用glBindVertexArray，因此我们通常不会在没有必要时取消绑定 VAO
    glBindVertexArray(0);
    
    //指定为线框模式，不指定的会会填充
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        //为屏幕设置新颜色：输入的深蓝绿色
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        //清空屏幕的颜色，并将屏幕设置为glClearColor输入的颜色
        glClear(GL_COLOR_BUFFER_BIT);

        // 激活着色器程序对象
        glUseProgram(shaderProgram);

        // 更新uniform颜色
        float timeValue = glfwGetTime();
        float greenValue = sin(timeValue) / 2.0f + 0.5f;
        int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
        glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);



        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        //画6个顶点，组成一个矩形
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        // glBindVertexArray(0); // no need to unbind it every time

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        //检查并调用事件，交换缓冲
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    //  释放资源 optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);
}
