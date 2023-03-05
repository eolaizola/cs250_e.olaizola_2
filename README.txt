/* ---------------------------------------------------------------------------------------------------------
Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.

Project: cs250_e.olaizola_2
Author: Eritz Olaizola
Login: e.olaizola
StudentID: 540001219
Creation date: 01/30/2023
----------------------------------------------------------------------------------------------------------*/

How to run the program: The program can be tested using visual studio x64 on release, as in debug will be really slow(low fps).

How to use the program: Controls-       
					• 1: wireframe mode
					• 2: solid mode
					• a: Rotates tank body/Right rotation(ccw)
					• d: Rotates tank body/Left rotation (cw)
					• q: Rotates turret/Left rotation (ccw)
					• e: Rotates turret/Right rotation (cw)
					• r: Rotates gun/Up rotation (cw)
					• f: Rotates gun/Down rotation (ccw)
					• space: Move tank body forward
					• p: Reset the scene

Importants parts of the code: The program has 4 important cpps (FrameBuffer.cpp, cs250Parser.cpp, Rasterier.cpp, Input.cpp)

						-FrameBuffer.cpp(8 functions, 109 lines): This file creates and frees the frame buffer
                                                                                          Also providing the ability to set and get pixeles on the frame buffer.

						-cs250Parser(3 functions, 283 lines): The parser provided a load and unload data, reading from a file that is required for the rasterizer,
										      in order to draw the triangles and lines, providing points and vertices.

						-Rasterizer.cpp(10 functions, 382 lines): One of the most important files, as it draw the lines and triangles, also tyransforming the model coordintes
                                                                                          to viewport coordinates with the help of Matrix4.cpp, providing the matrices.

						-Input.cpp(4 functions, 155 lines): Is not very important, but still is worth mentioning, because it allow us to move the tank and updates the hierarchy of the objects.

Known issues and problems: I would like to mention, that the frame knowing how the draw triangle draws clock wise, converting the triangles back-faced
                           I needed to do a little hack that is mentioned on the comments in the code, the trick being changing the order of the vertices that the functions recieve,
                           flipping the triangle, and converting it to a counter clock wise triangle (front-faced).


Comments: The window can be resize, and when on it the tank will also be resized according to the window.(Tested and its should work)
	  The zip is about 1.41Mb, beacause i wasn't sure if we need to keep the debug dll and files.