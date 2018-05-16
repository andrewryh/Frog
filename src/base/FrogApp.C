#include "FrogApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "ModulesApp.h"
#include "MooseSyntax.h"

template <>
InputParameters
validParams<FrogApp>()
{
  InputParameters params = validParams<MooseApp>();
  return params;
}

FrogApp::FrogApp(InputParameters parameters) : MooseApp(parameters)
{
  Moose::registerObjects(_factory);
  ModulesApp::registerObjects(_factory);
  FrogApp::registerObjects(_factory);

  Moose::associateSyntax(_syntax, _action_factory);
  ModulesApp::associateSyntax(_syntax, _action_factory);
  FrogApp::associateSyntax(_syntax, _action_factory);

  Moose::registerExecFlags(_factory);
  ModulesApp::registerExecFlags(_factory);
  FrogApp::registerExecFlags(_factory);
}

FrogApp::~FrogApp() {}

void
FrogApp::registerApps()
{
  registerApp(FrogApp);
}

void
FrogApp::registerObjects(Factory & factory)
{
    Registry::registerObjectsTo(factory, {"FrogApp"});
}

void
FrogApp::associateSyntax(Syntax & /*syntax*/, ActionFactory & action_factory)
{
  Registry::registerActionsTo(action_factory, {"FrogApp"});

  /* Uncomment Syntax parameter and register your new production objects here! */
}

void
FrogApp::registerObjectDepends(Factory & /*factory*/)
{
}

void
FrogApp::associateSyntaxDepends(Syntax & /*syntax*/, ActionFactory & /*action_factory*/)
{
}

void
FrogApp::registerExecFlags(Factory & /*factory*/)
{
  /* Uncomment Factory parameter and register your new execution flags here! */
}

/***************************************************************************************************
 *********************** Dynamic Library Entry Points - DO NOT MODIFY ******************************
 **************************************************************************************************/
extern "C" void
FrogApp__registerApps()
{
  FrogApp::registerApps();
}

extern "C" void
FrogApp__registerObjects(Factory & factory)
{
  FrogApp::registerObjects(factory);
}

extern "C" void
FrogApp__associateSyntax(Syntax & syntax, ActionFactory & action_factory)
{
  FrogApp::associateSyntax(syntax, action_factory);
}

extern "C" void
FrogApp__registerExecFlags(Factory & factory)
{
  FrogApp::registerExecFlags(factory);
}
