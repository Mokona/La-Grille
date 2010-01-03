# Custom project builder
import os
import os.path
from SCons.Script import *

def recursive_glob(env, dirnode, pattern):
    globalList = []

    sourcePath = os.path.join(dirnode, '*')
    list = env.Glob(sourcePath)
    for entry in list:
        if isinstance(entry, SCons.Node.FS.Dir):
            globalList.extend(recursive_glob(env, str(entry), pattern))

    path = os.path.join(dirnode, pattern)
    globalList.extend(env.Glob(os.path.join(dirnode, pattern)))

    return globalList

def method_library_project(env, libraryName):
    # print "Custom Library Project Builder"

    # Using set because on win32 .cpp and .cpp~ are collected the same way
    # The set is sorted because, it sometimes happens that Glob + set doesn't lead to the same
    # dependency order, thus provoking a useless build if nothing else changed.
    newList = recursive_glob(env, libraryName, "*.cpp")

    # sourcePath = os.path.join(libraryName, '*.cpp')
    # sourceFiles =  [x for x in sorted(set(env.Glob(sourcePath)))]
    sourceFiles = [x for x in sorted(set(newList))]

    target = libraryName + '/' + libraryName

    # TODO : could write the next lines if in verbose mode
    # print sourceFiles
    # print target

    return env.Library(target, sourceFiles)

def method_program_project(env, programName, description, configuration):
    # print "Custom Program Project Builder"

    neededLibraries = []
    neededLibraryPaths = []

    # Checking for Intern dependecies
    # TODO : rather than append, we should merge
    for intern in description[0]:
        neededLibraries.append(configuration['INTERN'][intern]['LIB'])
        neededLibraryPaths.append(os.path.relpath(configuration['INTERN'][intern]['LIBPATH']))

    for extern in description[1]:
        neededLibraries.append(configuration['EXTERN'][extern]['LIB'])
        neededLibraryPaths.append(configuration['EXTERN'][extern]['LIBPATH'])

    # print neededLibraries
    # print neededLibraryPaths

    # Using set because on win32 .cpp and .cpp~ are collected the same way
    # The set is sorted because, it sometimes happens that Glob + set doesn't lead to the same
    # dependency order, thus provoking a useless build if nothing else changed.
    newList = recursive_glob(env, programName, "*.cpp")
    # sourcePath = os.path.join(programName, '*.cpp')
    # sourceFiles =  [x for x in sorted(set(env.Glob(sourcePath)))]
    sourceFiles = [x for x in sorted(set(newList))]

    target = programName + '/' + programName

    # TODO : could write the next lines if in verbose mode
    # print sourceFiles
    # print target

    return env.Program(target, sourceFiles, LIBS = neededLibraries, LIBPATH = neededLibraryPaths)

