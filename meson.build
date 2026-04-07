project(
    'War-Plane',
    'cpp'
)

sources = files(
    'src/main.cpp',
    'src/Application.cpp',
    'src/utilities.cpp',
    'src/SceneNode.cpp',

    'src/entity/Entity.cpp',
    'src/entity/Aircraft.cpp',
    'src/entity/SpriteNode.cpp',

    'src/World.cpp',

    'src/command/CommandQueue.cpp',
    'src/entity/Player.cpp',

    'src/states/StateStack.cpp',
    'src/states/State.cpp',
    'src/states/Introduction.cpp',
)

executable(
    'warplane',
    sources,
    include_directories: include_directories('include'),
    dependencies: [ dependency('sfml-all', required: true) ]
)