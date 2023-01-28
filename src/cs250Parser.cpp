#include "CS250Parser.h"
#include <iostream>
#include <fstream>

float   CS250Parser::left;
float   CS250Parser::right;
float   CS250Parser::top;
float   CS250Parser::bottom;
float   CS250Parser::focal;
float   CS250Parser::nearPlane;
float   CS250Parser::farPlane;
float   CS250Parser::distance;
float   CS250Parser::height;
Point4  CS250Parser::position;
Vector4 CS250Parser::view;
Vector4 CS250Parser::up;

std::vector<CS250Parser::Shape> CS250Parser::shapes;

std::vector<CS250Parser::Transform> CS250Parser::objects;

void CS250Parser::LoadDataFromFile(const char * filename)
{
    std::ifstream in(filename);

    shapes.clear();
    objects.clear();

    if (!in.is_open())
    {
        printf("Could not open input file\n");
        exit(0);
    }

    std::string readStr;

    in >> readStr;

    while (readStr != "}")
    {
        if (readStr == "camera")
        {
            in >> readStr; // read open curly brace
            in >> readStr;

            while (readStr != "}")
            {
                if (readStr == "left")
                {
                    in >> left;
                }
                else if (readStr == "right")
                {
                    in >> right;
                }
                else if (readStr == "top")
                {
                    in >> top;
                }
                else if (readStr == "bottom")
                {
                    in >> bottom;
                }
                else if (readStr == "focal")
                {
                    in >> focal;
                }
                else if (readStr == "near")
                {
                    in >> nearPlane;
                }
                else if (readStr == "far")
                {
                    in >> farPlane;
                }
                else if (readStr == "distance")
                {
                    in >> distance;
                }
                else if (readStr == "height")
                {
                    in >> height;
                }
                else if (readStr == "position")
                {
                    in >> readStr;
                    sscanf_s(readStr.c_str(), "%f,%f,%f", &position.x, &position.y, &position.z);
                }
                else if (readStr == "view")
                {
                    in >> readStr;
                    sscanf_s(readStr.c_str(), "%f,%f,%f", &view.x, &view.y, &view.z);
                }
                else if (readStr == "up")
                {
                    in >> readStr;
                    sscanf_s(readStr.c_str(), "%f,%f,%f", &up.x, &up.y, &up.z);
                }
                in >> readStr;
            }
        }
        else if (readStr == "shapes")
        {
            in >> readStr; // read open curly brace

            in >> readStr;
            while (readStr != "}")
            {
                Shape newShape;
                newShape.name = readStr;
                in >> readStr; // read open curly brace

                in >> readStr;
                while (readStr != "}")
                {
                    if (readStr == "vertices")
                    {
                        in >> readStr; // read open curly brace
                        in >> readStr;
                        while (readStr != "}")
                        {
                            Point4 p;
                            sscanf_s(readStr.c_str(), "%f,%f,%f", &p.x, &p.y, &p.z);
                            newShape.vertices.push_back(p);
                            in >> readStr;
                        }
                    }
                    else if (readStr == "faces")
                    {
                        in >> readStr; // read open curly brace

                        in >> readStr;
                        while (readStr != "}")
                        {
                            Face face;
                            sscanf_s(readStr.c_str(), "%i,%i,%i", &face.indices[0], &face.indices[1], &face.indices[2]);
                            newShape.faces.push_back(face);
                            in >> readStr;
                        }
                    }
                    else if (readStr == "facecolors")
                    {
                        in >> readStr; // read open curly brace

                        in >> readStr;
                        while (readStr != "}")
                        {
                            Point4 color;
                            sscanf_s(readStr.c_str(), "\t%f,%f,%f\n", &color.x, &color.y, &color.z);
                            newShape.colors.push_back(color);
                            in >> readStr;
                        }
                    }

                    in >> readStr;
                }

                shapes.push_back(newShape);

                in >> readStr;
            }
           
        }
        else if (readStr == "scene")
        {
            in >> readStr; // read open curly brace

            in >> readStr;
            while (readStr != "}")
            {
                Transform transform;
                transform.name = readStr;

                in >> readStr;
                transform.shape = readStr;

                in >> readStr;
                sscanf_s(readStr.c_str(), "T(%f,%f,%f)", &transform.pos.x, &transform.pos.y, &transform.pos.z);
                in >> readStr;
                sscanf_s(readStr.c_str(), "R(%f,%f,%f)", &transform.rot.x, &transform.rot.y, &transform.rot.z);
                in >> readStr;
                sscanf_s(readStr.c_str(), "S(%f,%f,%f)", &transform.sca.x, &transform.sca.y, &transform.sca.z);

                in >> transform.parent;

                objects.push_back(transform);
                in >> readStr;
            }
        }
        in >> readStr;
    }

}

void CS250Parser::UnloadData()
{
    if (objects.size())
        std::cout << "Clearing..." << objects.size() << " Objects" << std::endl;

    //Reset all the values
    left = 0;
    right = 0;
    top = 0;
    bottom = 0;
    focal = 0;
    nearPlane = 0;
    farPlane = 0;
    distance = 0;
    height = 0;
    position.Zero();
    view.Zero();
    up.Zero();
    shapes.clear();
    objects.clear();

    if (!objects.size())
        std::cout << "Cleared...Now: " << objects.size() << " Objects" << std::endl;
}
