#!/usr/bin/python3
import subprocess as sp
from pathlib import Path
import shutil as sh
import argparse

BUILD_DIR = 'build'

def parse_arg():
    parser = argparse.ArgumentParser(description='build linden global placer.')
    parser.add_argument('--quiet',
        dest='quiet',
        action='store_true',
        default=False,
        help='Disable verbose info while building',
    )
    parser.add_argument('--mode',
        dest='mode',
        action='store',
        choices=['debug', 'release'],
        default='debug',
        help='Set compile mode: debug, release.',
    )
    args = parser.parse_args()
    return args

def plan(BUILD_DIR, args):
    cmd = ['cmake', '-G', 'Ninja']
    if args.mode == 'debug':
        build_dir = Path(f'{BUILD_DIR}/debug')
        cmd += ['-DCMAKE_BUILD_TYPE=Debug']
    elif args.mode == 'release':
        build_dir = Path(f'{BUILD_DIR}/release')
        cmd += ['-DCMAKE_BUILD_TYPE=Release']
    cmd += ['../..']
    if not args.quiet:
        print(cmd)
    build_dir.mkdir(parents=True, exist_ok=True)
    sp.check_call(cmd, cwd=build_dir)
    return build_dir

def build(args, build_dir):
    if args.quiet:
        cmd = ['ninja']
    else:
        cmd = ['ninja', '--verbose']
    sp.check_call(cmd, cwd=build_dir)

if __name__ == '__main__':
    args = parse_arg()
    build_dir = plan(BUILD_DIR, args)
    build(args, build_dir)
