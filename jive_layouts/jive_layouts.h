#pragma once

/* BEGIN_JUCE_MODULE_DECLARATION
    ID:                 jive
    vendor:             James Johnson
    version:            0.1.0
    name:               James' Intuitive View Explicator
    license:            GPL/Commercial
    minimumCppStandard: 14
    dependencies:       juce_gui_basics
END_JUCE_MODULE_DECLARATION */

//======================================================================================================================
#include <juce_gui_basics/juce_gui_basics.h>

//======================================================================================================================
namespace jive
{
    class GuiItem;
} // namespace jive

//======================================================================================================================
#include "utilities/jive_TypedValue.h"

#include "layout/jive_BoxModel.h"

#include "layout/gui-items/jive_GuiItem.h"
#include "layout/gui-items/jive_GuiItemDecorator.h"

#include "layout/gui-items/flex/jive_GuiFlexContainer.h"
#include "layout/gui-items/flex/jive_GuiFlexItem.h"
#include "layout/gui-items/widgets/jive_ComboBox.h"
#include "layout/gui-items/widgets/jive_Label.h"

#include "layout/jive_ViewRenderer.h"
#include "utilities/jive_VariantConverters.h"