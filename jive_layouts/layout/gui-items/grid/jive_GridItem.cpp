#include <jive_layouts/jive_layouts.h>

//======================================================================================================================
namespace jive
{
    //==================================================================================================================
    GridItem::GridItem(std::unique_ptr<GuiItem> itemToDecorate)
        : GuiItemDecorator{ std::move(itemToDecorate) }
        , order{ tree, "order" }
        , justifySelf{ tree, "justify-self", juce::GridItem::JustifySelf::autoValue }
        , alignSelf{ tree, "align-self", juce::GridItem::AlignSelf::autoValue }
        , column{ tree, "column" }
        , row{ tree, "row" }
        , area{ tree, "area" }
        , width{ tree, "width", juce::GridItem::notAssigned }
        , minWidth{ tree, "min-width" }
        , maxWidth{ tree, "max-width", juce::GridItem::notAssigned }
        , height{ tree, "height", juce::GridItem::notAssigned }
    {
    }

    //==================================================================================================================
    GridItem::operator juce::GridItem()
    {
        juce::GridItem gridItem{ getComponent() };

        gridItem.order = order;

        gridItem.justifySelf = justifySelf;
        gridItem.alignSelf = alignSelf;

        gridItem.column = column;
        gridItem.row = row;
        gridItem.area = area;

        gridItem.width = width;
        gridItem.minWidth = minWidth;
        gridItem.maxWidth = maxWidth;
        gridItem.height = height;

        return gridItem;
    }
} // namespace jive

//======================================================================================================================
#if JIVE_UNIT_TESTS
bool compare(juce::GridItem::Property a, juce::GridItem::Property b)
{
    return a.getName() == b.getName() && a.getNumber() == b.getNumber();
}

bool compare(juce::GridItem::StartAndEndProperty a,
             juce::GridItem::StartAndEndProperty b)
{
    return compare(a.start, b.start) && compare(a.end, b.end);
}

class GridItemUnitTest : public juce::UnitTest
{
public:
    GridItemUnitTest()
        : juce::UnitTest{ "jive::GridItem", "jive" }
    {
    }

    void runTest() final
    {
        testComponent();
        testOrder();
        testJustifySelf();
        testAlignSelf();
        testColumn();
        testRow();
        testArea();
        testWidth();
        testMinWidth();
        testMaxWidth();
        testHeight();
    }

private:
    std::unique_ptr<jive::GridItem> createGridItem(juce::ValueTree tree)
    {
        return std::make_unique<jive::GridItem>(std::make_unique<jive::GuiItem>(std::make_unique<juce::Component>(),
                                                                                tree));
    }

    void testComponent()
    {
        beginTest("component");

        juce::ValueTree tree{ "Component" };
        auto item = createGridItem(tree);

        auto gridItem = static_cast<juce::GridItem>(*item);
        expect(gridItem.associatedComponent == &item->getComponent());
    }

    void testOrder()
    {
        beginTest("order");

        {
            juce::ValueTree tree{ "Component" };
            auto item = createGridItem(tree);

            auto gridItem = static_cast<juce::GridItem>(*item);
            expect(gridItem.order == 0);

            tree.setProperty("order", 123, nullptr);

            gridItem = static_cast<juce::GridItem>(*item);
            expect(gridItem.order == 123);
        }
        {
            juce::ValueTree tree{
                "Component",
                {
                    { "order", 456 },
                },
            };
            auto item = createGridItem(tree);

            auto gridItem = static_cast<juce::GridItem>(*item);
            expect(gridItem.order == 456);
        }
    }

    void testJustifySelf()
    {
        beginTest("justify-self");

        {
            juce::ValueTree tree{ "Component" };
            auto item = createGridItem(tree);

            auto gridItem = static_cast<juce::GridItem>(*item);
            expect(gridItem.justifySelf == juce::GridItem::JustifySelf::autoValue);

            tree.setProperty("justify-self", "start", nullptr);

            gridItem = static_cast<juce::GridItem>(*item);
            expect(gridItem.justifySelf == juce::GridItem::JustifySelf::start);

            tree.setProperty("justify-self", "end", nullptr);

            gridItem = static_cast<juce::GridItem>(*item);
            expect(gridItem.justifySelf == juce::GridItem::JustifySelf::end);

            tree.setProperty("justify-self", "centre", nullptr);

            gridItem = static_cast<juce::GridItem>(*item);
            expect(gridItem.justifySelf == juce::GridItem::JustifySelf::center);

            tree.setProperty("justify-self", "stretch", nullptr);

            gridItem = static_cast<juce::GridItem>(*item);
            expect(gridItem.justifySelf == juce::GridItem::JustifySelf::stretch);

            tree.setProperty("justify-self", "auto", nullptr);

            gridItem = static_cast<juce::GridItem>(*item);
            expect(gridItem.justifySelf == juce::GridItem::JustifySelf::autoValue);
        }
        {
            juce::ValueTree tree{
                "Component",
                {
                    { "justify-self", "end" },
                },
            };
            auto item = createGridItem(tree);

            auto gridItem = static_cast<juce::GridItem>(*item);
            expect(gridItem.justifySelf == juce::GridItem::JustifySelf::end);
        }
    }

    void testAlignSelf()
    {
        beginTest("align-self");

        {
            juce::ValueTree tree{ "Component" };
            auto item = createGridItem(tree);

            auto gridItem = static_cast<juce::GridItem>(*item);
            expect(gridItem.alignSelf == juce::GridItem::AlignSelf::autoValue);

            tree.setProperty("align-self", "start", nullptr);

            gridItem = static_cast<juce::GridItem>(*item);
            expect(gridItem.alignSelf == juce::GridItem::AlignSelf::start);

            tree.setProperty("align-self", "end", nullptr);

            gridItem = static_cast<juce::GridItem>(*item);
            expect(gridItem.alignSelf == juce::GridItem::AlignSelf::end);

            tree.setProperty("align-self", "centre", nullptr);

            gridItem = static_cast<juce::GridItem>(*item);
            expect(gridItem.alignSelf == juce::GridItem::AlignSelf::center);

            tree.setProperty("align-self", "stretch", nullptr);

            gridItem = static_cast<juce::GridItem>(*item);
            expect(gridItem.alignSelf == juce::GridItem::AlignSelf::stretch);

            tree.setProperty("align-self", "auto", nullptr);

            gridItem = static_cast<juce::GridItem>(*item);
            expect(gridItem.alignSelf == juce::GridItem::AlignSelf::autoValue);
        }
        {
            juce::ValueTree tree{
                "Component",
                {
                    { "align-self", "end" },
                },
            };
            auto item = createGridItem(tree);

            auto gridItem = static_cast<juce::GridItem>(*item);
            expect(gridItem.alignSelf == juce::GridItem::AlignSelf::end);
        }
    }

    void testColumn()
    {
        beginTest("column");

        {
            juce::ValueTree tree{ "Component" };
            auto item = createGridItem(tree);

            auto gridItem = static_cast<juce::GridItem>(*item);
            expect(compare(gridItem.column, juce::GridItem::StartAndEndProperty{}));

            tree.setProperty("column", "3 / span 4", nullptr);

            gridItem = static_cast<juce::GridItem>(*item);
            expect(compare(gridItem.column, juce::GridItem::StartAndEndProperty{ 3, juce::GridItem::Span{ 4 } }));
        }
        {
            juce::ValueTree tree{
                "Component",
                {
                    { "column", "this-line / 42" },
                },
            };
            auto item = createGridItem(tree);

            auto gridItem = static_cast<juce::GridItem>(*item);
            expect(compare(gridItem.column, juce::GridItem::StartAndEndProperty{ "this-line", 42 }));
        }
    }

    void testRow()
    {
        beginTest("row");

        {
            juce::ValueTree tree{ "Component" };
            auto item = createGridItem(tree);

            auto gridItem = static_cast<juce::GridItem>(*item);
            expect(compare(gridItem.row, juce::GridItem::StartAndEndProperty{}));

            tree.setProperty("row", "2 / another-line", nullptr);

            gridItem = static_cast<juce::GridItem>(*item);
            expect(compare(gridItem.row, juce::GridItem::StartAndEndProperty{ 2, "another-line" }));
        }
        {
            juce::ValueTree tree{
                "Component",
                {
                    { "row", "14 / span 7" },
                },
            };
            auto item = createGridItem(tree);

            auto gridItem = static_cast<juce::GridItem>(*item);
            expect(compare(gridItem.row, juce::GridItem::StartAndEndProperty{ 14, juce::GridItem::Span{ 7 } }));
        }
    }

    void testArea()
    {
        beginTest("area");

        {
            juce::ValueTree tree{ "Component" };
            auto item = createGridItem(tree);

            auto gridItem = static_cast<juce::GridItem>(*item);
            expect(gridItem.area.isEmpty());

            tree.setProperty("area", "just-here", nullptr);

            gridItem = static_cast<juce::GridItem>(*item);
            expect(gridItem.area == "just-here");
        }
        {
            juce::ValueTree tree{
                "Component",
                {
                    { "area", "abc" },
                },
            };
            auto item = createGridItem(tree);

            auto gridItem = static_cast<juce::GridItem>(*item);
            expect(gridItem.area == "abc");
        }
    }

    void testWidth()
    {
        beginTest("width");

        {
            juce::ValueTree tree{ "Component" };
            auto item = createGridItem(tree);

            auto gridItem = static_cast<juce::GridItem>(*item);
            expect(gridItem.width == juce::GridItem::notAssigned);

            tree.setProperty("width", 112.f, nullptr);

            gridItem = static_cast<juce::GridItem>(*item);
            expect(gridItem.width == 112.f);
        }
        {
            juce::ValueTree tree{
                "Component",
                {
                    { "width", 374.6f },
                },
            };
            auto item = createGridItem(tree);

            auto gridItem = static_cast<juce::GridItem>(*item);
            expect(gridItem.width == 374.6f);
        }
    }

    void testMinWidth()
    {
        beginTest("min-width");

        {
            juce::ValueTree tree{ "Component" };
            auto item = createGridItem(tree);

            auto gridItem = static_cast<juce::GridItem>(*item);
            expect(gridItem.minWidth == 0.f);

            tree.setProperty("min-width", 493.6f, nullptr);

            gridItem = static_cast<juce::GridItem>(*item);
            expect(gridItem.minWidth == 493.6f);
        }
        {
            juce::ValueTree tree{
                "Component",
                {
                    { "min-width", 12.6f },
                },
            };
            auto item = createGridItem(tree);

            auto gridItem = static_cast<juce::GridItem>(*item);
            expect(gridItem.minWidth == 12.6f);
        }
    }

    void testMaxWidth()
    {
        beginTest("max-width");

        {
            juce::ValueTree tree{ "Component" };
            auto item = createGridItem(tree);

            auto gridItem = static_cast<juce::GridItem>(*item);
            expect(gridItem.maxWidth == juce::GridItem::notAssigned);

            tree.setProperty("max-width", 30.4f, nullptr);

            gridItem = static_cast<juce::GridItem>(*item);
            expect(gridItem.maxWidth == 30.4f);
        }
        {
            juce::ValueTree tree{
                "Component",
                {
                    { "max-width", 986.f },
                },
            };
            auto item = createGridItem(tree);

            auto gridItem = static_cast<juce::GridItem>(*item);
            expect(gridItem.maxWidth == 986.f);
        }
    }

    void testHeight()
    {
        beginTest("height");

        {
            juce::ValueTree tree{ "Component" };
            auto item = createGridItem(tree);

            auto gridItem = static_cast<juce::GridItem>(*item);
            expect(gridItem.height == juce::GridItem::notAssigned);

            tree.setProperty("height", 112.f, nullptr);

            gridItem = static_cast<juce::GridItem>(*item);
            expect(gridItem.height == 112.f);
        }
        {
            juce::ValueTree tree{
                "Component",
                {
                    { "height", 374.6f },
                },
            };
            auto item = createGridItem(tree);

            auto gridItem = static_cast<juce::GridItem>(*item);
            expect(gridItem.height == 374.6f);
        }
    }
};

static GridItemUnitTest gridItemUnitTest;
#endif
