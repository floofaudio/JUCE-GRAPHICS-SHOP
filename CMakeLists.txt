cmake_minimum_required(VERSION 3.15)

# Project name and version
project(JUCE_GRAPHICS_SHOP VERSION 0.1.0)

# Use FetchContent to fetch JUCE from GitHub
include(FetchContent)

FetchContent_Declare(
    JUCE
    GIT_REPOSITORY https://github.com/juce-framework/JUCE.git
    GIT_TAG        7.0.12 # Replace with the desired version or branch
)

FetchContent_MakeAvailable(JUCE)

# Add GUI app
juce_add_gui_app(JUCE_GRAPHICS_SHOP
    # Icon files
    ICON_BIG     Source/F128.png
    ICON_SMALL   Source/F64.png
)

# Add JUCE modules
target_link_libraries(JUCE_GRAPHICS_SHOP
    PRIVATE
        juce::juce_core
        juce::juce_data_structures
        juce::juce_events
        juce::juce_graphics
        juce::juce_gui_basics
        juce::juce_gui_extra
)

juce_generate_juce_header(JUCE_GRAPHICS_SHOP)

# Add source files
target_sources(JUCE_GRAPHICS_SHOP
    PRIVATE
        Source/MainMenuBarModel.cpp
        Source/RectangleController.cpp
        Source/TransformSection.cpp
        Source/GradientSection.cpp
        Source/ColourSection.cpp
        Source/ComponentController.cpp
        Source/Main.cpp
        Source/MainComponent.cpp
)

# Add include directories
target_include_directories(JUCE_GRAPHICS_SHOP
    PRIVATE
        ${JUCE_SOURCE_DIR}/modules
        ${CMAKE_CURRENT_SOURCE_DIR}/Source
)


# Set compiler options
target_compile_definitions(JUCE_GRAPHICS_SHOP
    PRIVATE
        JUCE_STRICT_REFCOUNTEDPOINTER=1
)

# Debug/Release configurations
set_target_properties(JUCE_GRAPHICS_SHOP PROPERTIES
    CMAKE_CXX_STANDARD 17
    CMAKE_CXX_STANDARD_REQUIRED YES
    CMAKE_POSITION_INDEPENDENT_CODE ON
)

# Debug
message(STATUS "JUCE modules available: ${JUCE_MODULE_AVAILABLE_juce_gui_basics}")
message(STATUS "Linking to juce_gui_basics: ${JUCE_LINK_LIBRARIES}")

