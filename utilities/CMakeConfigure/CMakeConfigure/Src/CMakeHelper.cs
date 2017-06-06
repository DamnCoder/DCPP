﻿using System;
using System.Collections.Generic;

namespace CMakeConfigure
{
	public static class CMakeHelper
	{
		public static void AddWhereKeys(List<string> cmakeLineList, Dictionary<string, List<string>> newLinesTable)
		{
			for (int i = 0; i < cmakeLineList.Count; ++i) 
			{
				var line = cmakeLineList [i];

				if(newLinesTable.ContainsKey(line))
				{
					List<string> newLineList = newLinesTable[line];
					int addedPathIndex = i;
					foreach (var newLine in newLineList)
					{
						cmakeLineList.Insert(++addedPathIndex, newLine);
					}
				}
			}
		}

		public static List<string> CreateSetMultiline(string keyName, List<string> paths)
		{
			List<string> setLines = new List<string>();

			setLines.Add("SET("+keyName);
			foreach(string path in paths)
			{
				setLines.Add("\t"+path);
			}
			setLines.Add(")");

			return setLines;
		}

		public static List<string> CreateMultipleIncludeDirectories(List<string> paths)
		{
			List<string> includeLines = new List<string>();

			foreach(string path in paths)
			{
				includeLines.Add(CreateInclude(path));
			}
			return includeLines;
		}

		public static string CreateProject(string projectName)
		{
			return "PROJECT("+projectName+")";
		}

		public static string CreateSet(string keyName, string value)
		{
			return "SET("+keyName+" "+value+")";
		}

		public static string CreateInclude(string path)
		{
			return "INCLUDE_DIRECTORIES("+path+")";
		}

		public static List<string> AddMultipleSubdirectory(List<string> nameList)
		{
			List<string> subdirectoryLines = new List<string>();

			foreach(string name in nameList)
			{
				subdirectoryLines.Add(AddSubdirectory(name));
			}
			return subdirectoryLines;
		}

		public static string AddSubdirectory(string name)
		{
			return 	"ADD_SUBDIRECTORY(${EXTERNALS_PATH}/"+name+"/project ${PROJECT_BINARY_DIR}/"+name+")\n"+
					"INCLUDE_DIRECTORIES(${EXTERNALS_PATH}/"+name+"/project/include)\n";
		}
	}
}

