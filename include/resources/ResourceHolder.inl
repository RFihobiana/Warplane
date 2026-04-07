#pragma once

#include "resources/ResourceHolder.hpp"
#include <cassert>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>

template<typename ResourceID, typename Resource>
void ResourceHolder<ResourceID, Resource>::load(const ResourceID& id, const std::string& filename) {
    std::unique_ptr<Resource> resource(new Resource());
    if(!resource->loadFromFile(filename)) {
        throw std::runtime_error("ResourceHolder::load - Failed to load " + filename);
    }
    auto inserted = m_data.insert(std::make_pair(id, std::move(resource)));
    assert(inserted.second);
}

template<typename ResourceID, typename Resource>
template<typename Parameter>
void ResourceHolder<ResourceID, Resource>::load(const ResourceID& id, const std::string& filename, const Parameter& second_param) {
    std::unique_ptr<Resource> resource(new Resource());
    if(!resource->loadFromFile(filename, second_param)) {
        throw std::runtime_error("ResourceHolder::load - Failed to load " + filename);
    }
}

template<typename ResourceID, typename Resource>
Resource& ResourceHolder<ResourceID, Resource>::get(const ResourceID id) {
    auto resource = m_data.find(id);
    assert(resource != m_data.end());
    return *resource->second;
}

template<typename ResourceID, typename Resource>
const Resource& ResourceHolder<ResourceID, Resource>::get(const ResourceID id) const {
    auto resource = m_data.find(id);
    assert(resource != m_data.end());
    return *resource->second;
}

template<typename ResourceID, typename Resource>
bool ResourceHolder<ResourceID, Resource>::has(const ResourceID& resource_id) const {
    return m_data.find(resource_id) != m_data.end();
}
