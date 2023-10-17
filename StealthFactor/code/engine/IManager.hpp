#pragma once
namespace engine
{
    class IManager
    {
    public:

        virtual ~IManager() = default;

        virtual void initialize() = 0;
        virtual void update() = 0;
        virtual void clear() = 0;
    };
}