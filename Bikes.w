def configure(ctx):
    if 'INCLUDES_BOOST' not in ctx.env:
        ctx.check_boost(includes=ctx.environ.get('BOOST_ROOT'))


def configure_PIC(ctx):
    configure(ctx)
    ctx.use('PIC')


def build(ctx):
    include_node = ctx.path.find_dir('include')
    include_glob = include_node.ant_glob

    src_glob = ctx.path.find_dir('src').ant_glob

    ctx.static_lib(
        use='BOOST C++11',

        includes=[include_node, include_node.find_dir('Bikes')],

        source=src_glob('*.cpp'),
        other_files=include_glob('Bikes/*.h'),

        export_includes=[include_node],
    )


build_PIC = build
