#ifndef CMGRAPHVIZWRITER_H
#define CMGRAPHVIZWRITER_H
/*============================================================================
  CMake - Cross Platform Makefile Generator
  Copyright 2000-2009 Kitware, Inc., Insight Software Consortium

  Distributed under the OSI-approved BSD License (the "License");
  see accompanying file Copyright.txt for details.

  This software is distributed WITHOUT ANY WARRANTY; without even the
  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the License for more information.
============================================================================*/
#include "cmStandardIncludes.h"
#include "cmLocalGenerator.h"
#include "cmGeneratedFileStream.h"
#include "cmTarget.h"


/** This class implements writing files for graphviz (dot) for graphs
 * representing the dependencies between the targets in the project. */
class cmGraphVizWriter
{
public:

  cmGraphVizWriter(const std::vector<cmLocalGenerator*>& localGenerators);

  void ReadSettings(const char* settingsFileName,
                    const char* fallbackSettingsFileName);

  void WritePerTargetFiles(const char* fileName);

  void WriteGlobalFile(const char* fileName);

protected:

  int collectAllTargets();

  int collectAllExternalLibs(int cnt);

  void WriteHeader(cmGeneratedFileStream& str) const;

  void WriteConnections(const char* targetName,
                        std::set<std::string>& insertedNodes,
                        std::set<std::string>& insertedConnections,
                        cmGeneratedFileStream& str) const;

  void WriteNode(const char* targetName, const cmTarget* target,
                 std::set<std::string>& insertedNodes,
                 cmGeneratedFileStream& str) const;

  void WriteFooter(cmGeneratedFileStream& str) const;

  bool IgnoreThisTarget(const char* name) const;

  bool GenerateForTargetType(cmTarget::TargetType targetType) const;

  cmStdString GraphType;
  cmStdString GraphName;
  cmStdString GraphHeader;
  cmStdString GraphNodePrefix;

  bool GenerateForExecutables;
  bool GenerateForStaticLibs;
  bool GenerateForSharedLibs;
  bool GenerateForModuleLibs;

  std::set<cmStdString> TargetsToIgnore;

  const std::vector<cmLocalGenerator*>& LocalGenerators;

  std::map<cmStdString, const cmTarget*> TargetPtrs;
  // maps from the actual target names to node names in dot:
  std::map<cmStdString, cmStdString> TargetNamesNodes;

};

#endif
