#pragma once

#include <BinaryData.h>
#include <jive_core/jive_core.h>

namespace jive_demo::icons
{
    namespace small
    {
        [[nodiscard]] static auto back()
        {
            return jive::parseXML(binary_data::backsmall_svg,
                                  binary_data::backsmall_svgSize);
        }

        [[nodiscard]] static auto next()
        {
            return jive::parseXML(binary_data::nextsmall_svg,
                                  binary_data::nextsmall_svgSize);
        }
    } // namespace small

    namespace large
    {
        [[nodiscard]] static auto build()
        {
            return jive::parseXML(binary_data::buildlarge_svg,
                                  binary_data::buildlarge_svgSize);
        }

        [[nodiscard]] static auto code()
        {
            return jive::parseXML(binary_data::codelarge_svg,
                                  binary_data::codelarge_svgSize);
        }

        [[nodiscard]] static auto layout()
        {
            return jive::parseXML(binary_data::layoutlarge_svg,
                                  binary_data::layoutlarge_svgSize);
        }

        [[nodiscard]] static auto palette()
        {
            return jive::parseXML(binary_data::palettelarge_svg,
                                  binary_data::palettelarge_svgSize);
        }
    } // namespace large
} // namespace jive_demo::icons
