//
//	objloader.h
//	DCPP
//
//	Created by Jorge López on 26/4/17
//

#include "objloader.h"

#include <cmath>
#include <dirent.h>

#include "renderer/vertexproperty.h"
#include "mesh/mesh.h"

namespace dc
{
	CArray<CMesh*> CObjLoader::Load(const char* modelPath)
	{
		FILE* fp = fopen(modelPath, "r");
		
		if(!fp)
		{
			printf("File not found: %s!\n", modelPath);
			return 0;
		}
		
		char * line = NULL;
		size_t len = 0;
		ssize_t read;
		
		char header[2];
		
		float vertex[3];
		float uv[2];
		
		unsigned int vertexIndex[3];
		unsigned int normalIndex[3];
		unsigned int uvIndex[3];
		
		TFloatArray vertexArray;
		TFloatArray uvArray;
		TFloatArray normalArray;
		
		TUIntArray	indexArray;
		while ((read = getline(&line, &len, fp)) != -1)
		{
			sscanf(line, "%s", header);
			if(strcmp(header, "v") == 0)
			{
				sscanf(line, "%*s %f %f %f", &vertex[0], &vertex[1], &vertex[2]);
				
				vertexArray.Append(vertex, 3);
				
				//printf("Stored %f %f %f\n", vertex[0], vertex[1], vertex[2]);
			}
			else if(strcmp(header, "vt") == 0)
			{
				sscanf(line, "%*s %f %f", &uv[0], &uv[1]);
				
				uvArray.Append(uv, 2);
				
				//printf("Stored %f %f\n", uv[0], uv[1]);
			}
			else if(strcmp(header, "vn") == 0)
			{
				sscanf(line, "%*s %f %f %f", &vertex[0], &vertex[1], &vertex[2]);
				
				normalArray.Append(vertex, 3);
				
				//printf("Stored %f %f %f\n", vertex[0], vertex[1], vertex[2]);
			}
			
			else if(strcmp(header, "f") == 0)
			{
				sscanf(line, "%*s %d%*c%d%*c%d %d%*c%d%*c%d %d%*c%d%*c%d",
					   &vertexIndex[0], &uvIndex[0], &normalIndex[0],
					   &vertexIndex[1], &uvIndex[1], &normalIndex[1],
					   &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
				
				
				printf("Stored Vertex Index %d %d %d\n", vertexIndex[0], vertexIndex[1], vertexIndex[2]);
				printf("Stored Normal Index %d %d %d\n", normalIndex[0], normalIndex[1], normalIndex[2]);
				printf("Stored UV Index %d %d %d\n", uvIndex[0], uvIndex[1], uvIndex[2]);
			}
			//printf("Retrieved line of length %zu :\n", read);
			//printf("%s", line);
		}
		
		fclose(fp);
		if (line)
			free(line);
		
		CArray<CMesh*> meshArray;
		
		return meshArray;
	}
}

