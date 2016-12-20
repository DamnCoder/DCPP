using System;
using System.IO;
using System.Collections.Generic;
using System.Text;

namespace CMakeConfigure
{
	class MainClass
	{
		static string[] srcfileExtensions = 
		{
			".cpp",
		};

		static string[] includeFileExtensions = 
		{
			".h",
			".inl",
		};

		static string utilitiesFolder = "../";
		static string projectFolder = "../../project";

		static string srcFolder = "src";
		static string includeFolder = "include";

		static readonly string CMAKELIST_TEMPLATE_FILENAME = "CMakeLists_Template.txt";
		static readonly string CMAKELIST_OUTPUT_FILENAME = "CMakeLists.txt";

		static string PRJ_INCLUDE_KEY = "#[PRJ_INCLUDE]";
		static string PRJ_SOURCES_KEY = "#[PRJ_SOURCE_FILES]";
		static string PRJ_HEADERS_KEY = "#[PRJ_HEADER_FILES]";

		private static void AddWhereKeys(List<string> cmakeLineList, Dictionary<string, List<string>> newLinesTable)
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

		public static string CreateSet(string keyName, string value)
		{
			return "SET("+keyName+" "+value+")";
		}

		public static string CreateProject(string projectName)
		{
			return "PROJECT("+projectName+")";
		}

		public static string CreateInclude(string path)
		{
			return "INCLUDE_DIRECTORIES("+path+")";
		}

		public static void Main (string[] args)
		{
			string[] cmakeTemplateLines = File.ReadAllLines(Path.Combine(utilitiesFolder, CMAKELIST_TEMPLATE_FILENAME));

			// This is going to be the final CMakeLists.txt lines
			List<string> cmakeLineList = new List<string>(cmakeTemplateLines);

			// Table with all the lines to add for each key in the template
			Dictionary<string, List<string>> newLinesTable = new Dictionary<string, List<string>> ();


			// This list will contain the paths to sources and includes, it will be reused for both
			List<string> pathList = new List<string> ();

			// Project includes
			string completeIncludePath = Path.GetFullPath(Path.Combine(projectFolder, includeFolder));
			pathList.Add(includeFolder);
			PathsHelp.GetAllDirectoryPaths(completeIncludePath, completeIncludePath, pathList);
			newLinesTable.Add(PRJ_INCLUDE_KEY, CreateMultipleIncludeDirectories(pathList));

			pathList.Clear();

			// Header files
			PathsHelp.GetAllFilesPaths(completeIncludePath, completeIncludePath, includeFileExtensions, pathList);
			newLinesTable.Add(PRJ_HEADERS_KEY, CreateSetMultiline("HEADERS", pathList));

			pathList.Clear();

			// Source files
			string completSrcPath = Path.GetFullPath(Path.Combine(projectFolder, srcFolder));
			PathsHelp.GetAllFilesPaths(completSrcPath, completSrcPath, srcfileExtensions, pathList);
			newLinesTable.Add(PRJ_SOURCES_KEY, CreateSetMultiline("SOURCES", pathList));

			// Add the new lines where the keys are in the template
			AddWhereKeys(cmakeLineList, newLinesTable);

			File.WriteAllLines(Path.Combine(projectFolder, CMAKELIST_OUTPUT_FILENAME), cmakeLineList.ToArray());
		}
	}
}