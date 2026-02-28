project(
    'War-Plane',
    'cpp'
)

sources = files(
    'src/main.cpp',
    'src/Game.cpp'
)

executable(
    'warplane',
    sources,
    include_directories: include_directories('include'),
    dependencies: [ dependency('sfml-all', required: true) ]
)