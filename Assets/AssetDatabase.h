#pragma once

namespace salvation
{
    namespace asset
    {
        enum class PackedDataType
        {
            Unknown = -1,
            Textures,
            Meshes,
            Count
        };

        enum class TextureFormat
        {
            Unknown = -1,
            RGBA,
            BC1,
            BC2,
            BC3,
            Count
        };

        class AssetDatabase
        {

        };
    }
}