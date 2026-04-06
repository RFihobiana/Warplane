project(
    'War-Plane',
    'cpp'
)

sources = files(
    'src/main.cpp',
    'src/Game.cpp',
    'src/utilities.cpp',
    'src/SceneNode.cpp',

    'src/entity/Entity.cpp',
    'src/entity/Aircraft.cpp',
    'src/entity/SpriteNode.cpp',

    'src/World.cpp',

    'src/command/Command.cpp',
    'src/command/CommandQueue.cpp',
)

executable(
    'warplane',
    sources,
    include_directories: include_directories('include'),
    dependencies: [ dependency('sfml-all', required: true) ]
)