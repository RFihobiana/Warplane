project(
    'War-Plane',
    'cpp',
    default_options: ['cpp_std=c++20']
)

sources = files(
    'src/main.cpp',
    'src/Application.cpp',
    'src/utilities.cpp',
    'src/SceneNode.cpp',

    'src/entity/Entity.cpp',
    'src/entity/Aircraft.cpp',
    'src/entity/SpriteNode.cpp',
    'src/entity/DataTable.cpp',

    'src/World.cpp',

    'src/command/CommandQueue.cpp',
    'src/entity/Player.cpp',

    'src/log/Log.cpp',

    'src/states/StateStack.cpp',
    'src/states/State.cpp',
    'src/states/Introduction.cpp',
    'src/states/MenuState.cpp',
    'src/states/GameState.cpp',
    'src/states/PauseState.cpp',
    'src/states/ParallelTask.cpp',
    'src/states/LoadingState.cpp',
    'src/states/SettingState.cpp',

    'src/GUI/Component.cpp',
    'src/GUI/Label.cpp',
    'src/GUI/Button.cpp',
    'src/GUI/Container.cpp',
    'src/GUI/Logger.cpp',
)

executable(
    'warplane',
    sources,
    include_directories: include_directories('include'),
    dependencies: [ dependency('sfml-all', required: true) ]
)