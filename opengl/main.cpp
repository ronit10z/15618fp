#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <iostream>
#include <fstream>
#include <random>
#include <vector>

#include "gl_utility.h"

std::vector<unsigned char> image;
int npoints;
float* xs;
float* ys;
float* ws;
heatmap_t* hm;
int renderW, renderH;
float width, height;
Quad* leveledPts;

int main(int argc, char** argv)
{

    if (argc != 3) {
        return -1;
    } else {
        renderW = std::atoi(argv[1]);
        renderH = std::atoi(argv[2]);
        image.resize(renderW * renderH * 4);
        hm = heatmap_new(renderW, renderH);
    }

    std::cin >> npoints;

    int weighted;
    std::cin >> weighted;

    std::cin >> width >> height;

    leveledPts = new Quad(Point(0, 0), Point(width, height));
    float x, y, w;

    if (weighted == 0) {
        for (int i = 0; i < npoints; i++) {
            std::cin >> x >> y;
            Node n(Point(x, y, 1.0f));
            leveledPts->insert(&n);
        }
    } else {
        for (int i = 0; i < npoints; i++) {
            std::cin >> x >> y >> w;
            Node n(Point(x, y, w));
            leveledPts->insert(&n);
        }
    }

    // init GLUT and create window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(renderW, renderH);
    glutCreateWindow("Heatmap");

    glutDisplayFunc(renderScene);
    glutIdleFunc(renderScene);
    glutMouseFunc(zooming);

    glEnable(GL_TEXTURE_2D);
    setupTexture();

    // enter GLUT event processing cycle
    glutMainLoop();

    return 0;
}
