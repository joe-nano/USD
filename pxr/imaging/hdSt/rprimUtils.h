//
// Copyright 2019 Pixar
//
// Licensed under the Apache License, Version 2.0 (the "Apache License")
// with the following modification; you may not use this file except in
// compliance with the Apache License and the following modification to it:
// Section 6. Trademarks. is deleted and replaced with:
//
// 6. Trademarks. This License does not grant permission to use the trade
//    names, trademarks, service marks, or product names of the Licensor
//    and its affiliates, except as required to comply with Section 4(c) of
//    the License and to reproduce the content of the NOTICE file.
//
// You may obtain a copy of the Apache License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the Apache License with the above modification is
// distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied. See the Apache License for the specific
// language governing permissions and limitations under the Apache License.
//
#ifndef PXR_IMAGING_HD_ST_RPRIM_UTILS_H
#define PXR_IMAGING_HD_ST_RPRIM_UTILS_H

#include "pxr/pxr.h"
#include "pxr/imaging/hdSt/api.h"
#include "pxr/imaging/hd/sceneDelegate.h"

#include <boost/shared_ptr.hpp>

#include <string>

PXR_NAMESPACE_OPEN_SCOPE

class HdChangeTracker;
class HdDrawItem;
class HdRprim;
struct HdRprimSharedData;
class HdStDrawItem;
class HdStInstancer;
typedef boost::shared_ptr<class HdStResourceRegistry>
    HdStResourceRegistrySharedPtr;
typedef boost::shared_ptr<class HdStShaderCode> HdStShaderCodeSharedPtr;

// -----------------------------------------------------------------------------
// Primvar descriptor filtering utilities
// -----------------------------------------------------------------------------
// Get filtered primvar descriptors for drawItem
HDST_API
HdPrimvarDescriptorVector
HdStGetPrimvarDescriptors(
    HdRprim const * prim,
    HdStDrawItem const * drawItem,
    HdSceneDelegate * delegate,
    HdInterpolation interpolation);

// Get filtered instancer primvar descriptors for drawItem
HDST_API
HdPrimvarDescriptorVector
HdStGetInstancerPrimvarDescriptors(
    HdStInstancer const * instancer,
    HdRprim const * prim,
    HdStDrawItem const * drawItem,
    HdSceneDelegate * delegate);

// -----------------------------------------------------------------------------
// Material shader utility
// -----------------------------------------------------------------------------
// Resolves the material shader for the given prim (using a fallback
// material as necessary), including optional mixin shader source code.
HDST_API
HdStShaderCodeSharedPtr
HdStGetMaterialShader(
    HdRprim const * prim,
    HdSceneDelegate * delegate,
    std::string const & mixinSource = std::string());

// -----------------------------------------------------------------------------
// Constant primvar processing utilities
// -----------------------------------------------------------------------------
// Returns whether constant primvars need to be populated/updated based on the
// dirty bits for a given rprim.
HDST_API
bool HdStShouldPopulateConstantPrimvars(
    HdDirtyBits const *dirtyBits,
    SdfPath const& id);

// Given prim information it will create sources representing
// constant primvars and hand it to the resource registry.
HDST_API
void HdStPopulateConstantPrimvars(
    HdRprim *prim,
    HdRprimSharedData *sharedData,
    HdSceneDelegate *delegate,
    HdDrawItem *drawItem,
    HdDirtyBits *dirtyBits,
    HdPrimvarDescriptorVector const& constantPrimvars);

// -----------------------------------------------------------------------------
// Topological visibility processing utility
// -----------------------------------------------------------------------------
// Creates/Updates/Migrates the topology visiblity BAR with element and point
// visibility encoded using one bit per element/point of the topology.
HDST_API
void HdStProcessTopologyVisibility(
    VtIntArray invisibleElements,
    int numTotalElements,
    VtIntArray invisiblePoints,
    int numTotalPoints,
    HdRprimSharedData *sharedData,
    HdStDrawItem *drawItem,
    HdChangeTracker *changeTracker,
    HdStResourceRegistrySharedPtr const &resourceRegistry,
    SdfPath const& rprimId);

PXR_NAMESPACE_CLOSE_SCOPE

#endif // PXR_IMAGING_HD_ST_RPRIM_UTILS_H