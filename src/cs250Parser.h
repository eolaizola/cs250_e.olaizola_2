#pragma once

#include "MathLib/Point4.h"
#include "MathLib/Matrix4.h"
#include <string>
#include <vector>

class CS250Parser
{
  public:
    static void LoadDataFromFile(const char * filename);
    static void UnloadData();
    static Matrix4 GetPerspectiveMatrix();
    static Matrix4 GetViewportMatrix(int wWidth, int wHeight);

    struct Face
    {
        int indices[3];
    };

    static float   left;
    static float   right;
    static float   top;
    static float   bottom;
    static float   focal;
    static float   nearPlane;
    static float   farPlane;
    static float   distance;
    static float   height;
    static Point4  position;
    static Vector4 view;
    static Vector4 up;

    struct Shape
    {
        std::string         name;
        std::vector<Point4> vertices;
        std::vector<Face>   faces;
        std::vector<Point4> colors;
    };

    static std::vector<Shape> shapes;

    struct Transform
    {
        std::string name;
        std::string shape;

        Point4  pos;
        Vector4 rot;
        Vector4 sca;

        std::string parent;
    };
    static std::vector<Transform> objects;
};