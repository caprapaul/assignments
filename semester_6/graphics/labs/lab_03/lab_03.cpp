//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//
////# include <GL/glut.h>
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//
//
//#include <string>
//#include <iostream>
//#include <vector>
//#include <fstream>
//#include <windows.h>
//
//#define _USE_MATH_DEFINES
//#include <math.h>
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void processInput(GLFWwindow* window);
//std::vector<float> calotaSferica(int nMeridiane, int nParalele, float R, float a);
//void sphere(float radius, int sectorCount, int stackCount, std::vector<float>& vertices, std::vector<int>& lineIndices);
//
//// configurari
//const unsigned int SCR_WIDTH = 800;
//const unsigned int SCR_HEIGHT = 600;
//
//const unsigned int noParalele = 10;
//const unsigned int noMeridiane = 10;
//const float razaSferei = 1.0;
//const float razaCalotei = 1.0;
//
//
//std::string readFile(const char* filePath) {
//    std::string content;
//    std::ifstream fileStream(filePath, std::ios::in);
//
//    if (!fileStream.is_open()) {
//        std::cerr << "Could not read file " << filePath;
//        std::cerr << ". File does not exist." << std::endl;
//        return "";
//    }
//
//    std::string line = "";
//    while (!fileStream.eof()) {
//        std::getline(fileStream, line);
//        content.append(line + "\n");
//    }
//
//    fileStream.close();
//    return content;
//}
//
//
//
//
//int main()
//{
//    // glfw: initializare si configurare
//
//    glfwInit();
//    // precizam versiunea 3.3 de openGL
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//    // glfw cream fereastra
//
//    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Calota Sferica", NULL, NULL);
//    if (window == NULL)
//    {
//        std::cout << "Failed to create GLFW window" << std::endl;
//        glfwTerminate();
//        return -1;
//    }
//    // facem ca aceasta fereastra sa fie contextul curent
//
//    glfwMakeContextCurrent(window);
//
//    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//
//    // glad: incarcam referintele la functiile OpenGL
//
//    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//    {
//        std::cout << "Failed to initialize GLAD" << std::endl;
//        return -1;
//    }
//
//    // incarcam si compilam shaderele:
//
//    // vertex shader
//
//    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
//    if (0 == vertexShader)
//    {
//        std::cout << "Error creating vertex shader." << std::endl;
//        exit(1);
//    }
//
//    std::string shaderCode = readFile("calota.vert");
//    const char* codeArray = shaderCode.c_str();
//    glShaderSource(vertexShader, 1, &codeArray, NULL);
//
//    glCompileShader(vertexShader);
//
//    // verficam daca s-a reusit compilarea codului
//
//    int success;
//    char infoLog[512];
//    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
//    if (!success)
//    {
//        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
//        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
//    }
//
//    // fragment shader (repetam aceleasi operatii)
//
//    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//
//    shaderCode = readFile("basic.frag");
//    codeArray = shaderCode.c_str();
//    glShaderSource(fragmentShader, 1, &codeArray, NULL);
//
//
//    glCompileShader(fragmentShader);
//
//    // se verifica compilarea codului
//
//    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
//    if (!success)
//    {
//        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
//        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
//    }
//
//    // link shaders
//
//    unsigned int shaderProgram = glCreateProgram();
//    glAttachShader(shaderProgram, vertexShader);
//    glAttachShader(shaderProgram, fragmentShader);
//    glLinkProgram(shaderProgram);
//
//    // se verifica procesul de link
//
//    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
//    if (!success) {
//        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
//        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
//    }
//    glDeleteShader(vertexShader);
//    glDeleteShader(fragmentShader);
//
//    // initializam punctele de pe calota sferica
//    std::vector<float> vertices = {};
//    std::vector<int> indices = {};
//    //vertices = calotaSferica(noMeridiane, noParalele, razaSferei, razaCalotei);
//    sphere(razaSferei, noMeridiane, noParalele, vertices, indices);
//
//    unsigned int VBO, VAO, EBO;
//    glGenVertexArrays(1, &VAO);
//    glGenBuffers(1, &VBO);
//    glGenBuffers(1, &EBO);
//
//    // se face bind a obiectului Vertex Array, apoi se face bind si se stabilesc
//    // vertex buffer(ele), si apoi se configureaza vertex attributes.
//    glBindVertexArray(VAO);
//
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices.front(), GL_STATIC_DRAW);
//
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), &indices.front(), GL_STATIC_DRAW);
//
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(0);
//
//    glBindBuffer(GL_ARRAY_BUFFER, 0);
//
//    // se face unbind pentru VAO
//    glBindVertexArray(0);
//
//    // ciclu de desenare -- render loop
//
//    //definim cu cat rotim obiectul
//    float step = 1.0, angle = 0;
//
//
//    while (!glfwWindowShouldClose(window))
//    {
//        // input
//
//        processInput(window);
//
//        // render
//
//        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//        // specificam programul ce trebuie folosit
//        glUseProgram(shaderProgram);
//
//        // cream transformarile care ne definesc modul in care privim obiectul
//        glm::mat4 model = glm::mat4(1.0f);
//        glm::mat4 view = glm::mat4(1.0f);
//        glm::mat4 projection = glm::mat4(1.0f);
//
//        angle = angle + step;
//        if (angle > 360)
//            angle = angle - 360;
//
//
//        model = glm::translate(model, glm::glm::vec3(1.0f, 0.0f, 0.0f));  
//        model = glm::rotate(model, glm::radians(angle), glm::glm::vec3(0.0f, 0.0f, 1.0f));
//        model = glm::translate(model, glm::glm::vec3(-1.0f, 0.0f, 0.0f));
//        model = glm::rotate(model, glm::radians(angle), glm::glm::vec3(0.0f, 1.0f, 0.0f));
//        model = glm::rotate(model, glm::radians(-90.0f), glm::glm::vec3(1.0f, 0.0f, 0.0f));
//
//        view = glm::translate(view, glm::glm::vec3(0.0f, 0.0f, -5.0f));
//        projection = glm::perspective(glm::radians(-45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
//
//        // obtinem locatiile variabilelor uniforms in program
//        unsigned int modelLoc = glGetUniformLocation(shaderProgram, "model");
//        unsigned int viewLoc = glGetUniformLocation(shaderProgram, "view");
//        unsigned int projectionLoc = glGetUniformLocation(shaderProgram, "projection");
//
//        // transmitem valorile lor catre shadere (2 metode)
//        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
//        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
//
//        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, &projection[0][0]);
//
//        // specificam modul in care vrem sa desenam -- aici din spate in fata, si doar contur
//        // implicit pune fete, dar cum nu avem lumini si umbre deocamdata cubul nu va arata bine
//        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//
//        glBindVertexArray(VAO);
//
//        //glDrawArrays(GL_TRIANGLE_STRIP, 0, vertices.size() / 3);// vertices.size()/3-12, 12);//
//        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
//
//        // glfw: se inverseaza zonele tamponm si se trateaza evenimentele IO
//
//        glfwSwapBuffers(window);
//        Sleep(10);
//        glfwPollEvents();
//    }
//
//    // optional: se elibereaza resursele alocate
//
//    glDeleteVertexArrays(1, &VAO);
//    glDeleteBuffers(1, &VBO);
//
//    glDeleteProgram(shaderProgram);
//
//    // glfw: se termina procesul eliberand toate resursele alocate de GLFW
//
//    glfwTerminate();
//    return 0;
//}
//
//// se proceseaza inputurile de la utilizator
//
//void processInput(GLFWwindow* window)
//{
//    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//        glfwSetWindowShouldClose(window, true);
//}
//
//// glfw: ce se intampla la o redimensionalizare a ferestrei
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height)
//{
//    // ne asiguram ca viewportul este in concordanta cu noile dimensiuni
//
//    glViewport(0, 0, width, height);
//}
//
//void sphere(float radius, int sectorCount, int stackCount, std::vector<float>& vertices, std::vector<int>& indices) {
//    float x, y, z, xy;                              // vertex position
//    float nx, ny, nz, lengthInv = 1.0f / radius;    // vertex normal
//    float s, t;                                     // vertex texCoord
//
//    float sectorStep = 2 * M_PI / sectorCount;
//    float stackStep = M_PI / stackCount;
//    float sectorAngle, stackAngle;
//
//    for (int i = 0; i <= stackCount; ++i)
//    {
//        stackAngle = M_PI / 2 - i * stackStep;        // starting from pi/2 to -pi/2
//        xy = radius * cosf(stackAngle);             // r * cos(u)
//        z = radius * sinf(stackAngle);              // r * sin(u)
//
//        // add (sectorCount+1) vertices per stack
//        // the first and last vertices have same position and normal, but different tex coords
//        for (int j = 0; j <= sectorCount; ++j)
//        {
//            sectorAngle = j * sectorStep;           // starting from 0 to 2pi
//
//            // vertex position (x, y, z)
//            x = xy * cosf(sectorAngle);             // r * cos(u) * cos(v)
//            y = xy * sinf(sectorAngle);             // r * cos(u) * sin(v)
//            vertices.push_back(x);
//            vertices.push_back(y);
//            vertices.push_back(z);
//        }
//    }
//
//    int k1, k2;
//    for (int i = 0; i < stackCount; ++i)
//    {
//        k1 = i * (sectorCount + 1);     // beginning of current stack
//        k2 = k1 + sectorCount + 1;      // beginning of next stack
//
//        for (int j = 0; j < sectorCount; ++j, ++k1, ++k2)
//        {
//            // 2 triangles per sector excluding first and last stacks
//            // k1 => k2 => k1+1
//            if (i != 0)
//            {
//                indices.push_back(k1);
//                indices.push_back(k2);
//                indices.push_back(k1 + 1);
//            }
//
//            // k1+1 => k2 => k2+1
//            if (i != (stackCount - 1))
//            {
//                indices.push_back(k1 + 1);
//                indices.push_back(k2);
//                indices.push_back(k2 + 1);
//            }
//
//            // store indices for lines
//            // vertical lines for all stacks, k1 => k2
//            // lineIndices.push_back(k1);
//            // lineIndices.push_back(k2);
//            // if (i != 0)  // horizontal lines except 1st stack, k1 => k+1
//            // {
//            //     lineIndices.push_back(k1);
//            //     lineIndices.push_back(k1 + 1);
//            // }
//        }
//    }
//}
//
//std::vector <float> calotaSferica(int nMeridiane, int nParalele, float R, float a) {
//
//    std::vector <float> vertex = {};
//    std::cout << 'fgds' << vertex.size() << std::endl;
//    float alpha = asin(a / R);
//    double theta0, theta1, phi;
//    int i, j;
//
//    for (i = 1; i <= nParalele; i++) {
//
//        theta0 = (alpha) * ((double)(i - 1) / nParalele);
//        theta1 = (alpha) * ((double)i / nParalele);
//
//        for (j = 0; j <= nMeridiane; j++) {
//            phi = 2 * M_PI * (double)(j - 1) / nMeridiane;
//
//            vertex.push_back(R * cos(phi) * sin(theta0));
//            vertex.push_back(R * sin(phi) * sin(theta0));
//            vertex.push_back(R * cos(theta0));
//
//            vertex.push_back(R * cos(phi) * sin(theta1));
//            vertex.push_back(R * sin(phi) * sin(theta1));
//            vertex.push_back(R * cos(theta1));
//        }
//    }
//
//    return vertex;
//
//}
