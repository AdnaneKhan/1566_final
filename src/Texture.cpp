#include "Texture.hpp"

void bmp2rgb(GLubyte img[], int size) {
	int i;
	GLubyte temp;

	for (i = 0; i<size; i += 3) {
		temp = img[i + 2];
		img[i + 2] = img[i + 1];
		img[i + 1] = temp;
	}
}

GLuint Texture::get_texture() {

	return this->texture;
}

void Texture::load_texture(std::string file_name, int t_x, int t_y) {
	this->debug_name = file_name;
		std::ifstream file_in;
		file_in.open(file_name, std::ios::in | std::ios::binary | std::ios::ate);

		if (file_in.is_open()) {
			file_in.seekg(8);
			file_in.read((char*)this->img, t_x*t_y*3);
			file_in.close();
			

			bmp2rgb(this->img, t_x*t_y * 3);
				// initialize the texture
				glGenTextures(1, &texture);
			
				glBindTexture(GL_TEXTURE_2D, texture);

			
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
					t_x, t_y,
					0, GL_RGB, GL_UNSIGNED_BYTE, this->img);

		

		} else {
			std::cerr << " Unable to read in " << file_name << std::endl;
		}
}

Texture::Texture(std::string file_name, int t_x, int t_y) {
	this->img = (GLubyte*) malloc(t_x*t_y*3*(sizeof(GLubyte)));
	// Indicates allocation was done
	this->tex = 1;
	load_texture(file_name, t_x, t_y);
}

Texture::~Texture() {
	// IF we allocated then free
	if (tex = 1) {
		free(img);
	}
}