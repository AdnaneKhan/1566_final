#include "Texture.hpp"

void Texture::turbulentBlueGradient(unsigned char height,
	unsigned char *r, unsigned char *g, unsigned char *b){
	if (height < CHAR_MAX / 8)
		*r = 8 * height;
	else
		*r = CHAR_MAX;
	if (height < CHAR_MAX / 2 - 5)
		*g = 2 * height + 5;
	else
		*g = CHAR_MAX;
	*b = *g / 2;
}

void Texture::noisySunGradient(unsigned char height,
	unsigned char *r, unsigned char *g, unsigned char *b){
	*r = (rand() + height) % 255;
	*g = *r / 4 + height;
	*b = *r / 10 + height;
}

void Texture::turbulentYellowGradient(unsigned char height,
	unsigned char *r, unsigned char *g, unsigned char *b){
	if (height < CHAR_MAX / 8)
		*r = 8 * height;
	else
		*r = CHAR_MAX;
	*g = *r;
	if (height < CHAR_MAX / 4)
		*b = 4 * height;
	else
		*b = CHAR_MAX;

}

void Texture::turbulentRedGradient(unsigned char height,
	unsigned char *r, unsigned char *g, unsigned char *b){
	if (height < CHAR_MAX / 8)
		*r = 8 * height;
	else
		*r = CHAR_MAX;
	if (height < CHAR_MAX / 2 - 5)
		*g = 2 * height + 5;
	else
		*g = CHAR_MAX;
	*b = *g / 2;
}

void Texture::turbulentGreenGradient(unsigned char height,
	unsigned char *r, unsigned char *g, unsigned char *b){
	if (height < CHAR_MAX / 8)
		*g = 8 * height;
	else
		*g = CHAR_MAX;
	if (height < CHAR_MAX / 2 - 5)
		*r = 2 * height + 5;
	else
		*r = CHAR_MAX;
	*b = *r / 2;
}

void Texture::blandLandGradient(unsigned char height,
	unsigned char *r, unsigned char *g, unsigned char *b){
	*r = height + (rand() / (RAND_MAX / 4));
	*g = 3 * height + 2 * ((unsigned char)sqrtf((float)height));
	*b = 80 + (rand() / (RAND_MAX / 8)) - 2 * height;

	//These if statements were added at a later date, to possibly
	// make this type of land less bland.
	if (height < 5)
		*b = *b - 2 * height*height;
	if (height < 20)
		*r = *r + 2 * height;
	if (height > 30){
		*b = *r = *g;
	}
	else
		*g = *g + 2 * height + ((unsigned char)sqrtf((float)height));
}

void Texture::iceyGradient(unsigned char height,
	unsigned char *r, unsigned char *g, unsigned char *b){
	*r = height + (rand() / (RAND_MAX / 4)) + ((unsigned char)sqrtf((float)height));
	*g = 10 * height;
	*b = 20 + (rand() / (RAND_MAX / 8)) - 2 * height;
}

void Texture::badLandGradient(unsigned char height,
	unsigned char *r, unsigned char *g, unsigned char *b){
	*r = 3 * height + (rand() / (RAND_MAX / 4)) + ((unsigned char)sqrtf((float)height)) + 20;
	*g = 2 * height;
	*b = height;
	if (height < 10){
		*g += 30;
		*b += 30;
		*r -= 20;
	}
	if (height < 5){
		*g += 10;
		*b += 10;
	}
}

void Texture::moonyGradient(unsigned char height,
	unsigned char *r, unsigned char *g, unsigned char *b){
	*r = 3 * height + ((unsigned char)sqrtf((float)height)) + 40;
	*g = 3 * height + 40;
	*b = 3 * height - ((unsigned char)sqrtf((float)height)) + 40;
}

void bmp2rgb(GLubyte img[], int size) {
	int i;
	GLubyte temp;

	for (i = 0; i<size; i += 3) {
		temp = img[i + 2];
		img[i + 2] = img[i + 1];
		img[i + 1] = temp;
	}
}

void Texture::bind_texture() {

		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
			x_dim, y_dim,
			0, GL_RGBA, GL_UNSIGNED_BYTE, this->brownianImage);


}

GLuint Texture::get_texture() {
	if (!first_run) {
		bind_texture();
		first_run = true;
	}

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

void Texture::generate_texture(textureType to_generate) {

	switch (to_generate) {
	case EARTHY_TEX:
		brownian(this->brownianImage, blandLandGradient, 9999999);
		
		break;
	case ICEY_TEX :
		scanLines(this->brownianImage, iceyGradient, 2999999);

	
		break;
	case BADLAND_TEX: 
		brownian(this->brownianImage, badLandGradient, 5999999);
	
		break;
	case MOON_TEX: 

		brownian(brownianImage, moonyGradient, 999999);

		break;
	case TURB_RED:
		std::cout << "gen red\n";
		multiBrown(this->brownianImage, turbulentRedGradient, 999999,MAX_WALKERS);
		break;
	}

	this->texType = to_generate;
}

Texture::Texture(std::string file_name, int t_x, int t_y) {
	this->img = (GLubyte*) malloc(t_x*t_y*3*(sizeof(GLubyte)));
	// Indicates allocation was done
	this->tex = 1;
	this->x_dim = t_x;
	this->y_dim = t_y;
	load_texture(file_name, t_x, t_y);
	this->first_run = 1;
}

Texture::Texture(textureType to_generate,int t_x, int t_y) {
	this->x_dim = t_x;
	this->y_dim = t_y;
	generate_texture(to_generate);

	this->first_run = 0;
}

Texture::~Texture() {
	// IF we allocated then free
	if (tex = 1) {
		free(img);
	}
}