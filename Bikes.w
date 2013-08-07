#! /usr/bin/env python
# -*- coding: utf-8 -*-
#===============================================================================
def configure(ctx):
    if 'INCLUDES_BOOST' not in ctx.env:
        ctx.check_boost()
#===============================================================================
def build(ctx):
    src_glob = ctx.path.find_dir('src').ant_glob

    ctx.scattered_lib(
        use='BOOST',
        includes=[
            'include',
            'include/Bikes',
        ],
        source=src_glob('*.cpp'),
        export_includes='include',
    )
