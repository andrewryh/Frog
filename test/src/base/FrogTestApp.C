//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html
#include "FrogTestApp.h"
#include "FrogApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "MooseSyntax.h"
#include "ModulesApp.h"

template <>
InputParameters
validParams<FrogTestApp>()
{
  InputParameters params = validParams<FrogApp>();
  return params;
}

FrogTestApp::FrogTestApp(InputParameters parameters) : MooseApp(parameters)
{
  Moose::registerObjects(_factory);
  ModulesApp::registerObjects(_factory);
  FrogApp::registerObjectDepends(_factory);
  FrogApp::registerObjects(_factory);

  Moose::associateSyntax(_syntax, _action_factory);
  ModulesApp::associateSyntax(_syntax, _action_factory);
  FrogApp::associateSyntaxDepends(_syntax, _action_factory);
  FrogApp::associateSyntax(_syntax, _action_factory);

  Moose::registerExecFlags(_factory);
  ModulesApp::registerExecFlags(_factory);
  FrogApp::registerExecFlags(_factory);

  bool use_test_objs = getParam<bool>("allow_test_objects");
  if (use_test_objs)
  {
    FrogTestApp::registerObjects(_factory);
    FrogTestApp::associateSyntax(_syntax, _action_factory);
    FrogTestApp::registerExecFlags(_factory);
  }
}

FrogTestApp::~FrogTestApp() {}

void
FrogTestApp::registerApps()
{
  registerApp(FrogApp);
  registerApp(FrogTestApp);
}

void
FrogTestApp::registerObjects(Factory & /*factory*/)
{
  /* Uncomment Factory parameter and register your new test objects here! */
}

void
FrogTestApp::associateSyntax(Syntax & /*syntax*/, ActionFactory & /*action_factory*/)
{
  /* Uncomment Syntax and ActionFactory parameters and register your new test objects here! */
}

void
FrogTestApp::registerExecFlags(Factory & /*factory*/)
{
  /* Uncomment Factory parameter and register your new execute flags here! */
}

/***************************************************************************************************
 *********************** Dynamic Library Entry Points - DO NOT MODIFY ******************************
 **************************************************************************************************/
// External entry point for dynamic application loading
extern "C" void
FrogTestApp__registerApps()
{
  FrogTestApp::registerApps();
}

// External entry point for dynamic object registration
extern "C" void
FrogTestApp__registerObjects(Factory & factory)
{
  FrogTestApp::registerObjects(factory);
}

// External entry point for dynamic syntax association
extern "C" void
FrogTestApp__associateSyntax(Syntax & syntax, ActionFactory & action_factory)
{
  FrogTestApp::associateSyntax(syntax, action_factory);
}

// External entry point for dynamic execute flag loading
extern "C" void
FrogTestApp__registerExecFlags(Factory & factory)
{
  FrogTestApp::registerExecFlags(factory);
}
