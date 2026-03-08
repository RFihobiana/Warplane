#pragma once

#include "textures/ResourceHolder.hpp"
#include <memory>
#include <string>
#include <utility>

template<typename ResourceID, typename Resource>
void ResourceHolder<ResourceID, Resource>::load(const ResourceID id, const std::string& filename) {
    std::unique_ptr<Resource> resource(new Resource());
    resource->loadFromFile(filename);
    m_data.insert(std::make_pair(id, std::move(resource)));
}

template<typename ResourceID, typename Resource>
Resource& ResourceHolder<ResourceID, Resource>::get(const ResourceID id) {
    auto resource = m_data.find(id);
    return *resource->second;
}

template<typename ResourceID, typename Resource>
const Resource& ResourceHolder<ResourceID, Resource>::get(const ResourceID id) const {
    auto resource = m_data.find(id);
    return *resource->second;
}
