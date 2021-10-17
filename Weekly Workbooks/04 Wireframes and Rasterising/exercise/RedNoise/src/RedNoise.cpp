#include <CanvasTriangle.h>
#include <DrawingWindow.h>
#include <Utils.h>
#include <fstream>
#include <vector>
#include <iostream>
#include "glm/ext.hpp"
#include <glm/glm.hpp>
#define WIDTH 320
#define HEIGHT 200

//exercise part one 
std::vector<float> interpolateFloat(float start, float end, float size){
	float distance = end - start;
	std::vector<float> result;
	float point_difference = distance /(size-1);
	for (int i = 0; i< size;i++){
		float now = start + i * point_difference;
		result.push_back(now);
	}
	return result;
}

//Exercise part 02
std::vector<glm::vec3> interpolate3D(glm::vec3 start, glm::vec3 end, float size){
	glm::vec3 distance = end-start;
	glm::vec3 point_difference = distance/(glm::vec3(size-1,size-1,size-1));
	std::vector<glm::vec3> result;
	for(int i =0;i<size;i++){
		glm::vec3 now = start+(point_difference*glm::vec3(i,i,i));
		result.push_back(now);
	}
	return result;


}
// drawing for part 02
void draw02(DrawingWindow &window)
{
	glm::vec3 topLeft(255, 0, 0);        // red 
	glm::vec3 topRight(0, 0, 255);       // blue 
	glm::vec3 bottomRight(0, 255, 0);    // green 
	glm::vec3 bottomLeft(255, 255, 0);   // yellow
	std::vector<glm::vec3> result_column_left = interpolate3D(topLeft,bottomLeft,window.height);
	std::vector<glm::vec3> result_column_right = interpolate3D(topRight,bottomRight,window.height);
	
	window.clearPixels();
	for (size_t y = 0; y < window.height; y++)
	{
		for (size_t x = 0; x < window.width; x++)
		{
			std::vector<glm::vec3> column = interpolate3D(result_column_left[y],result_column_right[y],window.width);
			glm::vec3 result_column = column[x];
			uint32_t colour = (255 << 24) + (int(result_column[0]) << 16) + (int(result_column[1]) << 8) + int(result_column[2]);
			window.setPixelColour(x, y, colour);
		}
	}
}
void draw01(DrawingWindow &window)
{
	glm::vec3 topLeft(255, 0, 0);        // red 
	glm::vec3 topRight(0, 0, 255);       // blue 
	glm::vec3 bottomRight(0, 255, 0);    // green 
	glm::vec3 bottomLeft(255, 255, 0);   // yellow
	window.clearPixels();
	std::vector<float> result;
	result = interpolateFloat(0, window.width, window.width);
	
	for (size_t y = 0; y < window.height; y++)
	{
		for (size_t x = 0; x < window.width; x++)
		{
			float red = 255-result[x]/window.width *255;
			float green = 255-result[x]/window.width *255  ;
			float blue = 255- result[x]/window.width *255 ;
			uint32_t colour = (255 << 24) + (int(red) << 16) + (int(green) << 8) + int(blue);
			window.setPixelColour(x, y, colour);
		}
	}
}

void handleEvent(SDL_Event event, DrawingWindow &window)
{
	if (event.type == SDL_KEYDOWN)
	{
		if (event.key.keysym.sym == SDLK_LEFT)
			std::cout << "LEFT" << std::endl;
		else if (event.key.keysym.sym == SDLK_RIGHT)
			std::cout << "RIGHT" << std::endl;
		else if (event.key.keysym.sym == SDLK_UP)
			std::cout << "UP" << std::endl;
		else if (event.key.keysym.sym == SDLK_DOWN)
			std::cout << "DOWN" << std::endl;
	}
	else if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		window.savePPM("output.ppm");
		window.saveBMP("output.bmp");
	}
}

int main(int argc, char *argv[])
 {
	DrawingWindow window2= DrawingWindow(WIDTH, HEIGHT, false);
	DrawingWindow window1 = DrawingWindow(WIDTH, HEIGHT, false);
	SDL_Event event1;
	SDL_Event event2;
	while (true)
	{
		// We MUST poll for events - otherwise the window will freeze !
		if (window1.pollForInputEvents(event1)){
			handleEvent(event1, window1);
			draw01(window1);
			// Need to render the frame at the end, or nothing actually gets shown on the screen !
			window1.renderFrame();
		};
		if (window2.pollForInputEvents(event2)){
			handleEvent(event2, window2);
			draw02(window2);
			// Need to render the frame at the end, or nothing actually gets shown on the screen !
			window2.renderFrame();
		};
			
		
	}

}
