#include "mitkPluginActivator.h"
#include "AtrialScarView.h"
#include "AtrialScarClipperView.h"
#include "YZSegView.h"

namespace mitk {

ctkPluginContext* PluginActivator::pluginContext = nullptr;

void PluginActivator::start(ctkPluginContext* context) {

    BERRY_REGISTER_EXTENSION_CLASS(AtrialScarView, context)
    BERRY_REGISTER_EXTENSION_CLASS(AtrialScarClipperView, context)
    BERRY_REGISTER_EXTENSION_CLASS(YZSegView, context)
    pluginContext = context;
}

void PluginActivator::stop(ctkPluginContext* context) {

    Q_UNUSED(context)
    pluginContext = nullptr;
}

ctkPluginContext* PluginActivator::getContext() {
    return pluginContext;
}

}

#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
#include <QtPlugin>
Q_EXPORT_PLUGIN2(my_cemrgproject_scar, mitk::PluginActivator)
#endif
