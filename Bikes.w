#! /usr/bin/env python
# -*- coding: utf-8 -*-
#===============================================================================
def configure(ctx):
    if 'INCLUDES_BOOST' not in ctx.env:
        ctx.check_boost()
#===============================================================================
def build(ctx):
    inc_path = 'include'
    inc_node = ctx.path.find_dir(inc_path)
    inc_glob = inc_node.ant_glob
    src_glob = ctx.path.find_dir('src').ant_glob

    ctx.static_lib(
        use = 'BOOST',
        includes = [inc_node, inc_node.find_dir('Bikes')],
        source = src_glob('*.cpp'),
        other_files = inc_glob('Bikes/*.h'),
        export_includes = inc_path,
    )
