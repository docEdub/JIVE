#pragma once

//======================================================================================================================
namespace jive
{
    //==================================================================================================================
    class ContainerItem : public GuiItemDecorator
    {
    public:
        //==============================================================================================================
        explicit ContainerItem(std::unique_ptr<GuiItem> itemToDecorate);

        //==============================================================================================================
        void addChild(std::unique_ptr<GuiItem> child) override;

    protected:
        //==============================================================================================================
        void boxModelInvalidated(BoxModel& boxModel) override;

        //==============================================================================================================
        virtual juce::Rectangle<float> calculateIdealSize(juce::Rectangle<float> constraints) const = 0;

        //==============================================================================================================
        void layoutChanged();

    private:
        //==============================================================================================================
        TypedValue<float> idealWidth;
        TypedValue<float> idealHeight;
    };
} // namespace jive
