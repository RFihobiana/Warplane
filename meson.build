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

run_command('cp', '-r', 'assets', meson.current_build_dir() / 'assets', check: true)
