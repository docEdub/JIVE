#pragma once

namespace jive
{
    class GuiItem
    {
    public:
        GuiItem(std::unique_ptr<juce::Component> component,
                const juce::ValueTree& sourceState,
#if JIVE_GUI_ITEMS_HAVE_STYLE_SHEETS
                StyleSheet::ReferenceCountedPointer styleSheet,
#endif
                GuiItem* parent = nullptr);

        GuiItem(std::unique_ptr<juce::Component> component,
                View::ReferenceCountedPointer sourceView,
#if JIVE_GUI_ITEMS_HAVE_STYLE_SHEETS
                StyleSheet::ReferenceCountedPointer styleSheet,
#endif
                GuiItem* parent = nullptr);

        GuiItem(const GuiItem& other);
        virtual ~GuiItem();

        [[nodiscard]] const std::shared_ptr<const juce::Component> getComponent() const;
        [[nodiscard]] std::shared_ptr<juce::Component> getComponent();
        [[nodiscard]] const View::ReferenceCountedPointer getView() const;
        [[nodiscard]] View::ReferenceCountedPointer getView();

        virtual void insertChild(std::unique_ptr<GuiItem> child, int index);
        virtual void setChildren(std::vector<std::unique_ptr<GuiItem>>&& children);
        virtual void removeChild(GuiItem& childToRemove);
        [[nodiscard]] virtual juce::Array<const GuiItem*> getChildren() const;
        [[nodiscard]] virtual juce::Array<GuiItem*> getChildren();
        [[nodiscard]] virtual const GuiItem* getParent() const;
        [[nodiscard]] virtual GuiItem* getParent();

        [[nodiscard]] bool isTopLevel() const;
        [[nodiscard]] virtual bool isContainer() const;
        [[nodiscard]] virtual bool isContent() const;

        virtual void layOutChildren() {}

        juce::ValueTree state;

    protected:
        virtual void childrenChanged() {}

    private:
        friend class GuiItemDecorator;

        class Remover : private juce::ValueTree::Listener
        {
        public:
            explicit Remover(GuiItem& guiItem);
            ~Remover();

        private:
            void valueTreeChildRemoved(juce::ValueTree&, juce::ValueTree&, int) final;

            GuiItem& item;
            GuiItem* parent;
        };

        GuiItem(std::shared_ptr<juce::Component> component,
                GuiItem* parent,
#if JIVE_GUI_ITEMS_HAVE_STYLE_SHEETS
                StyleSheet::ReferenceCountedPointer sheet,
#endif
                View::ReferenceCountedPointer sourceView);

        void insertChild(std::unique_ptr<GuiItem> child, int index, bool invokeCallback);

#if JIVE_GUI_ITEMS_HAVE_STYLE_SHEETS
        const StyleSheet::ReferenceCountedPointer styleSheet;
#endif

        const std::shared_ptr<juce::Component> component;
        GuiItem* const parent;
        juce::OwnedArray<GuiItem> children;
        std::unique_ptr<Remover> remover;
        View::ReferenceCountedPointer view;

        JUCE_DECLARE_WEAK_REFERENCEABLE(GuiItem)
        JUCE_LEAK_DETECTOR(GuiItem)
    };

    [[nodiscard]] BoxModel& boxModel(GuiItem& decoratedItem);
    [[nodiscard]] const BoxModel& boxModel(const GuiItem& decoratedItem);
} // namespace jive
