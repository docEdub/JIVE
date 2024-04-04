#pragma once

#include <juce_data_structures/juce_data_structures.h>

namespace jive
{
    class Object : public juce::DynamicObject
    {
    public:
        using ReferenceCountedPointer = juce::ReferenceCountedObjectPtr<Object>;

        struct Listener
        {
            virtual ~Listener() = default;

            virtual void propertyChanged(Object& object,
                                         const juce::Identifier& propertyName) = 0;
        };

        Object();
        Object(std::initializer_list<juce::NamedValueSet::NamedValue> initialProperties);
        Object(const Object& other);
        Object(Object&& other);
        Object(const juce::DynamicObject& other);

        void setProperty(const juce::Identifier& propertyName,
                         const juce::var& newValue) override;
        const juce::NamedValueSet& getProperties() const;

        Object* getParent() noexcept;
        const Object* getParent() const noexcept;
        Object* getRoot() noexcept;
        const Object* getRoot() const noexcept;

        void addListener(Listener& listener) const;
        void removeListener(Listener& listener) const;

        const juce::var& operator[](const juce::Identifier& name) const noexcept;

    private:
        class InternalListener;

        mutable juce::ListenerList<Listener> listeners;
        const std::unique_ptr<Listener> internalListener;
        Object* parent = nullptr;

        JUCE_LEAK_DETECTOR(Object)
    };

    juce::var parseJSON(const juce::String& jsonString);
} // namespace jive

namespace juce
{
    template <>
    struct VariantConverter<jive::Object::ReferenceCountedPointer>
    {
        static jive::Object::ReferenceCountedPointer fromVar(const var& value);
        static var toVar(jive::Object::ReferenceCountedPointer object);
    };
} // namespace juce
