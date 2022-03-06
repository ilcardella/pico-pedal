#pragma once

// List of all supported effects.
// To save memory, use this enum to identify the effects and dynamically allocate
// only the effect that is used
enum class Effects
{
    CLEAN,
    DISTORTION,
    ECHO,
    DELAY,
    REVERB
};
