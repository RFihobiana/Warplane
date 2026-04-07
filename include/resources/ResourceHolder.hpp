#pragma once

#include <memory>
#include <string>
#include <unordered_map>

template<typename ResourceID, typename Resource>
class ResourceHolder {

    public:
        void load(const ResourceID& id, const std::string& filename);
        
        template<typename Parameter>
        void load(const ResourceID& id, const std::string& filename, const Parameter& second_param);

        Resource& get(const ResourceID id);
        const Resource& get(const ResourceID id) const;

        bool has(const ResourceID& resource_id) const;
    
    private:
        void insert(const ResourceID& id, std::unique_ptr<Resource> resource);

    private:
        std::unordered_map<ResourceID, std::unique_ptr<Resource>> m_data;
};

#include "ResourceHolder.inl"
