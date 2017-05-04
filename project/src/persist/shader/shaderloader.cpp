//
//  shaderloader.cpp
//  DCPPTest
//
//  Created by Jorge López on 4/5/17.
//
//

#include "shaderloader.h"

namespace dc
{
	CShader CShaderLoader::Load(const char* filePath, const int type)
	{
		FILE* fp = fopen(filePath, "r");
		
		if(!fp)
		{
			printf("File not found: %s!\n", filePath);
			return 0;
		}
		
		long lSize;
		
		fseek( fp , 0L , SEEK_END);
		lSize = ftell( fp );
		rewind( fp );
		
		/* allocate memory for entire content */
		char* buffer = (char*) malloc(lSize * sizeof(char));
		if( !buffer )
		{
			fclose(fp);
			fputs("memory alloc fails", stderr);
			exit(1);
		}
		
		/* copy the file into the buffer */
		if(fread( buffer , lSize, 1 , fp) != 1)
		{
			fclose(fp);
			free(buffer);
			fputs("entire read fails", stderr);
			exit(1);
		}
		
		/* do your work here, buffer is a string contains the whole text */
		CShader shader(type);
		shader.Create(buffer, lSize);
		
		//printf("%s\n", buffer);
		
		fclose(fp);
		free(buffer);
		
		return shader;
	}

}
