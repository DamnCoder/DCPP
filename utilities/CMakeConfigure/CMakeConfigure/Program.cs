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

		static readonly string utilitiesFolder = "../";
		static readonly string projectFolder = "../../project";

		static readonly string srcFolder = "src";
		static readonly string includeFolder = "include";

		static readonly string SHARED_LIB = "SHARED_LIB";
		static readonly string STATIC_LIB = "STATIC_LIB";

		static readonly string STATICLIB_TEMPLATE_FILENAME = "CMakeLists_StaticLib_Template.txt";
		static readonly string SHAREDLIB_TEMPLATE_FILENAME = "CMakeLists_SharedLib_Template.txt";
		static readonly string EXECUTABLE_TEMPLATE_FILENAME = "CMakeLists_Executable_Template.txt";

		static readonly string CMAKELIST_OUTPUT_FILENAME = "CMakeLists.txt";

		static string PRJ_NAME_KEY = "#[PROJECT_NAME]";
		static string BUILD_TYPE_KEY = "#[BUILD_TYPE]";

		static string PRJ_INCLUDE_KEY = "#[PRJ_INCLUDE]";
		static string PRJ_SOURCES_KEY = "#[PRJ_SOURCE_FILES]";
		static string PRJ_HEADERS_KEY = "#[PRJ_HEADER_FILES]";

		public static void Main (string[] args)
		{
			if(args.Length < 3)
			{
				Console.WriteLine("CORRECT USE: mono CMakeConfigure.exe <template_type> <project_name> <build_type>");
				return;
			}

			string templateType = args[0];
			string projectName = args[1];
			string buildType = args[2];

			string CMAKE_TEMPLATE_FILENAME = EXECUTABLE_TEMPLATE_FILENAME;

			if (templateType == SHARED_LIB)
			{
				CMAKE_TEMPLATE_FILENAME = SHAREDLIB_TEMPLATE_FILENAME;
			}
			else if (templateType == STATIC_LIB)
			{
				CMAKE_TEMPLATE_FILENAME = STATICLIB_TEMPLATE_FILENAME;
			}

			string[] cmakeTemplateLines = File.ReadAllLines(Path.Combine(utilitiesFolder, CMAKE_TEMPLATE_FILENAME));

			// This is going to be the final CMakeLists.txt lines
			List<string> cmakeLineList = new List<string>(cmakeTemplateLines);

			// Table with all the lines to add for each key in the template
			Dictionary<string, List<string>> newLinesTable = new Dictionary<string, List<string>> ();

			newLinesTable.Add(PRJ_NAME_KEY, new List<string>() { CMakeHelper.CreateProject(projectName) });
			newLinesTable.Add(BUILD_TYPE_KEY, new List<string>() { CMakeHelper.CreateSet("CMAKE_BUILD_TYPE", buildType) });


			// This list will contain the paths to sources and includes, it will be reused for both
			List<string> pathList = new List<string> ();

			// Project includes
			string completeIncludePath = Path.GetFullPath(Path.Combine(projectFolder, includeFolder));
			pathList.Add(includeFolder);
			PathsHelp.GetAllDirectoryPaths(completeIncludePath, completeIncludePath, pathList);
			newLinesTable.Add(PRJ_INCLUDE_KEY, CMakeHelper.CreateMultipleIncludeDirectories(pathList));

			pathList.Clear();

			// Header files
			PathsHelp.GetAllFilesPaths(completeIncludePath, completeIncludePath, includeFileExtensions, pathList);
			newLinesTable.Add(PRJ_HEADERS_KEY, CMakeHelper.CreateSetMultiline("HEADERS", pathList));

			pathList.Clear();

			// Source files
			string completSrcPath = Path.GetFullPath(Path.Combine(projectFolder, srcFolder));
			PathsHelp.GetAllFilesPaths(completSrcPath, completSrcPath, srcfileExtensions, pathList);
			newLinesTable.Add(PRJ_SOURCES_KEY, CMakeHelper.CreateSetMultiline("SOURCES", pathList));

			// Add the new lines where the keys are in the template
			CMakeHelper.AddWhereKeys(cmakeLineList, newLinesTable);

			string outputPath = Path.Combine(projectFolder, CMAKELIST_OUTPUT_FILENAME);
			File.WriteAllLines(outputPath, cmakeLineList.ToArray());

			string fullOutputPath = Path.GetFullPath(outputPath);
			Console.WriteLine("CMakeLists.txt generated succesfully "+fullOutputPath);
			
		}
	}
}