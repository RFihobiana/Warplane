#pragma once

#include <memory>
#include <string>
#include <unordered_map>

template<typename ResourceID, typename Resource>
class ResourceHolder {

    public:
        void load(const ResourceID id, const std::string& filename);
        Resource& get(const ResourceID id);
        const Resource& get(const ResourceID id) const;

    private:
        std::unordered_map<ResourceID, std::unique_ptr<Resource>> m_data;
};

#include "ResourceHolder.inl"
