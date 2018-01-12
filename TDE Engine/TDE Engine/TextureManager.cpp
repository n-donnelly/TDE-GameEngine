#include "TextureManager.h"
#include "Includes.h"
#include <iostream>
#include <fstream>

using namespace std;

namespace TDE
{
	TextureManager::TextureManager(void)
	{
		mNumImages = 0;
		mNumAtlases = 0;
		mColorKey = TDEColor(-1, -1, -1, -1);
	}


	TextureManager::~TextureManager(void)
	{
	}

	/*
		Loads image given as input.
		Loads as a surface, converts to OpenGL texture
		Creates an image with the texture pointer and adds both to list of
		textures and images
	*/
	bool TextureManager::LoadImage(const char* aPath, const char* name)
	{
		if(name == "")
		{
			printf("Name invalid\n");
			return false; 
		}

		if(mImages.find(name) != mImages.end())
		{
			printf("%s already present", name);
			return false;
		}

		SDL_Surface* surface = IMG_Load(aPath);

		if(surface == NULL)
		{
			printf("The image at %s cannot be loaded\n", aPath);
			return false;
		}

		if(surface->format->BytesPerPixel < 2)
		{
			printf("The image %s does not have applicable colors", aPath);
			return false;
		}

		//Retrieves GLuint texture from surface
		Texture aTex = LoadTexFromSurface(surface, aPath);

		//Somethign happened to the Texture so that it's not properly initialised
		if(aTex.GetError() != 0)
			return false;

		glAtlases.insert(pair<string, Texture>(aTex.GetName(), aTex));
		mNumAtlases++;

		TDEImage aImage(aTex.GetName(), 0, 0, (int)aTex.GetWidth(), (int)aTex.GetHeight(), name);
		mImages.insert(pair<string, TDEImage>(aImage.GetName(), aImage));
		mNumImages++;

		return true;
	}

	bool TextureManager::LoadImage(const char* aPath, const char* name, int imWidth, int imHeight)
	{
		if(name == "" || imWidth <= 0 || imHeight <= 0)
		{
			printf("Name, width or height invalid\n");
			return false; 
		}

		if(mImages.find(name) != mImages.end())
		{
			printf("%s already present\n", name);
			return false;
		}

		SDL_Surface* surface = IMG_Load(aPath);

		if(surface->w < imWidth || surface->h < imHeight)
		{
			imWidth = surface->w;
			imHeight = surface->h;
		}

		if(surface == NULL)
		{
			printf("The image at %s cannot be loaded\n", aPath);
			printf("IMG_Load at line 67 in TextureManager: %s\n", IMG_GetError());
			return false;
		}

		if(surface->format->BytesPerPixel < 2)
		{
			printf("The image %s does not have applicable colors", aPath);
			return false;
		}

		//Retrieves GLuint texture from surface
		Texture aTex = LoadTexFromSurface(surface, aPath);

		//Somethign happened to the Texture so that it's not properly initialised
		if(aTex.GetError() != 0)
			return false;

		glAtlases.insert(pair<string, Texture>(aTex.GetName(), aTex));
		mNumAtlases++;

		TDEImage aImage(aTex.GetName(), 0, 0, imWidth, imHeight, name);
		mImages.insert(pair<string, TDEImage>(aImage.GetName(), aImage));
		mNumImages++;

		return true;
	}

	Texture TextureManager::LoadAtlas(const char* aPath)
	{
		SDL_Surface* surface = IMG_Load(aPath);

		if(surface == NULL)
		{
			printf("The image at %s cannot be loaded\n", aPath);
			return Texture();
		}

		if(surface->format->BytesPerPixel < 2)
		{
			printf("The image %s does not have applicable colors", aPath);
			return Texture();
		}

		//Retrieves GLuint texture from surface
		Texture aTex = LoadTexFromSurface(surface, aPath); 
		return aTex;
	}

	bool TextureManager::LoadAtlasesFromXML(const char* aPath, TDEColor alphaKey)
	{
		mColorKey = alphaKey;
		char aCurrentLine[256];
		fstream aXMLFile;

		aXMLFile.open(aPath, fstream::in);
		if(aXMLFile.is_open())
		{
			aXMLFile.getline(aCurrentLine, 256);
			aXMLFile.getline(aCurrentLine, 256);
			string atlasPaths(aCurrentLine);
			atlasPaths = GetXMLValue("path=", atlasPaths);

			while(!aXMLFile.eof())
			{
				aXMLFile.getline(aCurrentLine, 256);
				if(string(aCurrentLine).find("<Resource") != string::npos)
					MakeResources(&aXMLFile, atlasPaths, aCurrentLine);
			}
			return true;
		}
		else
		{
			printf("Could not open file at %s\n", aPath);
			return false;
		}
	}

	/*
		Returns a pointer to the TDE Image on input of the Image name
		Compares the input to the names associated with each of the images
		If none is found, return the NULL pointer.
	*/
	TDEImage* TextureManager::GetImage(string aImageName)
	{
		map<string, TDEImage>::iterator it = mImages.find(aImageName);
		if(it == mImages.end())
			return NULL;
		else return &(it->second);
	}

	/*
		Outputs GLuint texture from SDL_Surface pointer

		Creates an OpenGL texture from an SDL_Surface
		Should ensure the right format is created
		Should also work with every image format and convert to suitable texture
	*/
	Texture TextureManager::LoadTexFromSurface(SDL_Surface* surface, const char* aSurfPath)
	{
		Texture theTex;
		GLuint aTex;
		int aWidth, aHeight, bpp;
		void* raw;
		Uint8 *srcPixel, *destPixel;
		Uint32 pixels = 0;
		GLenum format = GL_RGBA;

		if(!surface || aSurfPath == "")
			return Texture();

		bpp = surface->format->BytesPerPixel;
		aWidth = surface->w;
		aHeight = surface->h;

		//Allocates enough memory for texture
		raw = (void*)malloc(aWidth * aHeight * 4);
		destPixel = (Uint8 *)raw;

		//Locks the surface so the pixels can be accessed
		SDL_LockSurface(surface);
		SDL_Color color;
		for(int i = aHeight-1; i > 0; i--)
		{
			for(int j = 0; j < aWidth; j++)
			{
				//Alphas pixels that match color key
				unsigned int pix = ((unsigned int*)surface->pixels)[i*(surface->pitch/sizeof(unsigned int)) + j];
				color =  TranslateColor(pix);
				if (color.r == mColorKey.m_iRed && color.b == mColorKey.m_iBlue && color.g == mColorKey.m_iGreen)    
				{
					((unsigned int*)surface->pixels)[i*(surface->pitch/sizeof(unsigned int)) + j] = SDL_MapRGBA(surface->format, 0, 0, 0, 0);
				}

				srcPixel = (Uint8*)surface->pixels + (i * surface->pitch) + (j*bpp);

				switch (bpp)
				{
					case 1:
						pixels = *srcPixel;
						break;

					case 2:
						pixels = *(Uint16 *)srcPixel;
						break;

					case 3:
						if(SDL_BYTEORDER == SDL_BIG_ENDIAN) 
							pixels = srcPixel[0] << 16 | srcPixel[1] << 8 | srcPixel[2];
						else
							pixels = srcPixel[0] | srcPixel[1] << 8 | srcPixel[2] << 16;
						break;

					case 4:
						pixels = *(Uint32 *)srcPixel;
						break;

					default:
						printf("Problem with Bytes Per Pixel\n");
						return theTex;
						break;
				}
				SDL_GetRGBA( pixels, surface->format, &(destPixel[0]), &(destPixel[1]), &(destPixel[2]), &(destPixel[3]));
				destPixel++;
				destPixel++;
				destPixel++;
				destPixel++;
			}
		}

		//Frees the surface again
		SDL_UnlockSurface(surface);
		SDL_FreeSurface(surface);

		glGenTextures(1, &aTex);
		glBindTexture(GL_TEXTURE_2D, aTex);
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

		//Checks for for any memory errors
		GLenum errorCode = glGetError();
		if ( errorCode != 0 ) 
		{
			if ( errorCode == GL_OUT_OF_MEMORY ) 
				printf("Out of texture memory!\n");
			else if(errorCode == GL_INVALID_OPERATION)
				printf("Something is being done out of order: 1282");
			
			glDeleteTextures(1, &aTex);
			free (raw);
			theTex.SetError(1);
			return theTex;
		}

		//Builds the MipMaps for the texture
		gluBuild2DMipmaps( GL_TEXTURE_2D, 4, aWidth, aHeight, GL_RGBA, GL_UNSIGNED_BYTE, (Uint8 *)raw);

		errorCode = glGetError();
		if ( errorCode != 0 ) 
		{
			if ( errorCode == GL_OUT_OF_MEMORY ) 
				printf("Out of texture memory after MipMapping!\n");
			else if(errorCode == GL_INVALID_OPERATION)
				printf("Something is being done out of order: 1282");

			glDeleteTextures(1, &aTex);
			free (raw);
			theTex.SetError(1);
			return theTex;
		}

		theTex = Texture(aTex, aSurfPath, (float)aWidth, (float)aHeight, bpp, format, (Uint8 *)raw);

		return theTex;
	}

	/*
		Adds an image to the texture manager.
		Adds the image to the vector of images and increments the number of images
	*/
	void TextureManager::AddImage(TDEImage aImage)
	{
		mImages.insert(pair<string, TDEImage>(aImage.GetName(), aImage));
		mNumImages++;
	}

	/*
		Takes the chosen value name and the line it is on and then returns the value
	*/
	string TextureManager::GetXMLValue(char* valString, string theLine)
	{
		int startIndex, stopIndex, nameLength;
		string restOfLine = theLine;

		nameLength = strlen(valString) + 1;
		startIndex = theLine.find(valString) + nameLength;
		restOfLine = theLine.substr(startIndex);
		stopIndex = restOfLine.find("\"");
		return theLine.substr(startIndex, stopIndex);
	}

	/*
		Takes an XML line and the parent GL Texture as input
		Outputs an Image made from the values present on the XML line
		Uses GetString function
	*/
	TDEImage TextureManager::MakeImage(std::string theLine, string texName)
	{
		string aImName = GetXMLValue("name=", theLine);
		string aImID = GetXMLValue("atlasID=", theLine);
		int aHeight = atoi(GetXMLValue("height=", theLine).c_str());
		int aWidth = atoi(GetXMLValue("width=", theLine).c_str());
		int aImU = atoi(GetXMLValue("u=", theLine).c_str());
		int aImV = atoi(GetXMLValue("v=", theLine).c_str());
		printf("Made Image: %s\n", aImName.c_str());
		TDEImage returnImage(texName, aImU, aImV, aWidth, aHeight, aImName);
		return returnImage;
	}

	void TextureManager::MakeResources(fstream* theStream, std::string resPath, char* line)
	{
		if(!theStream)
			return;

		string rName = GetXMLValue("name=", line);
		string rPath = GetXMLValue("path=", line);
		string loadPath = resPath + "\\" + rPath;

		//DEBUG - INFO
		printf("Loading Atlas %s\n", rName.c_str());

		Texture theTex = LoadAtlas((char *)loadPath.c_str());
		theTex.SetName(rName);
		glAtlases.insert(pair<string, Texture>(theTex.GetName(), theTex));
		mNumAtlases++;

		theStream->getline(line, 256);
		string test(line);
		test = test.substr(test.find("<"));

		while(test.compare("</Resource>") != 0 && !theStream->eof())
		{
			TDEImage theImage = MakeImage(test, theTex.GetName());
			mImages.insert(pair<string, TDEImage>(theImage.GetName(), theImage));
			mNumImages++;

			theStream->getline(line, 256);
			test = string(line);
			test = test.substr(test.find("<"));
		}
	}

	Texture* TextureManager::GetTexture(string texName)
	{
		map<string, Texture>::iterator it = glAtlases.find(texName);
		if(it == glAtlases.end())
			return NULL;

		return &(it->second);
	}

	void TextureManager::PrintAtlases()
	{
		printf("Printing Atlases\nNumber: %d\n\n", mNumAtlases);
		for(map<string, Texture>::iterator it = glAtlases.begin(); it != glAtlases.end(); it++)
		{
			printf("Name:\t%s\n", it->second.GetName().c_str());
			printf("Height and Width: \t%f, %f\n\n", it->second.GetHeight(), it->second.GetWidth());
		}
	}

	void TextureManager::PrintImages()
	{
		printf("Printing Images\nNumber: %d\n\n", mNumImages);

		for(map<string, TDEImage>::iterator it = mImages.begin(); it != mImages.end(); it++)
		{
			printf("Name:\t%s\n", it->second.GetName().c_str());
			printf("Width, Height: \t%d, %d\n", it->second.GetWidth(), it->second.GetHeight());
			printf("U V: \t\t%d, %d\n", it->second.GetAtlasX(), it->second.GetAtlasY());
		}
	}

	SDL_Color TextureManager::TranslateColor(Uint32 intCol)                           
	{
		#if SDL_BYTEORDER == SDL_BIG_ENDIAN
			SDL_Color color={(int_color & 0x00ff0000)/0x10000,(int_color & 0x0000ff00)/0x100,(int_color & 0x000000ff),0};
		#else
			SDL_Color color={(intCol & 0x000000ff),(intCol & 0x0000ff00)/0x100,(intCol & 0x00ff0000)/0x10000,0};    
		#endif
		return color;
	}
}