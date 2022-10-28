#include <iostream>
#include <math.h>
#include <GLFW/glfw3.h>


const int WIDTH = 500;
const int HEIGHT = 500;


double map_range(double value, double a, double b, double c, double d) {
    value = (value - a) / (b - a);
    return c + value * (d - c);
}

void makePixel(int x, int y, int r, int g, int b, GLubyte* pixels, int width, int height)
{
    if (0 <= x && x < width && 0 <= y && y < height) {
        int position = (x + y * width) * 3;
        pixels[position] = r;
        pixels[position + 1] = g;
        pixels[position + 2] = b;
    }
}


int main()
{
    GLFWwindow* window = nullptr;
    
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_RESIZABLE, 0);
    window = glfwCreateWindow(WIDTH, HEIGHT, "Window", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);


    GLubyte* pixelBuffer = new GLubyte[WIDTH * HEIGHT * 3];

    int maxIteration = 100;

    double sizeMin = -2.5;
    double sizeMax = 2.5;


    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        for (int x = 0; x < WIDTH; x++) {
            for (int y = 0; y < HEIGHT; y++) {
            
                double a = map_range(x, 0, WIDTH, sizeMin, sizeMax);
                double b = map_range(y, 0, HEIGHT, sizeMin, sizeMax);

                int n = 0;

                double ca = a;
                double cb = b;

                while (n < maxIteration) {
                    double aa = a * a - b * b;
                    double bb = 2 * a * b;

                    a = aa + ca;
                    b = bb + cb;

                    if (a + b > 16) {
                        break;
                    }

                    n++;
                }

                double bright = map_range(n, 0, maxIteration, 0, 255);
                
                if (n >= maxIteration) {
                    bright = 0;
                }


                makePixel(x, y, bright, bright, bright, pixelBuffer, WIDTH, HEIGHT);
            }
        }

        glDrawPixels(WIDTH, HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, pixelBuffer);
        

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}