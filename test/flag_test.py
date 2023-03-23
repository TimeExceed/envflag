import subprocess as sp
from pathlib import Path
import testa

BASE_DIR = Path('../build/debug/test/').absolute()

@testa.is_(expect=b'xixi')
def str_flag():
    exe = BASE_DIR.joinpath('str_flag')
    out = sp.check_output([exe], env={'str_flag': 'xixi'})
    return out

@testa.throw(throw=sp.CalledProcessError)
def missing_str_flag():
    exe = BASE_DIR.joinpath('str_flag')
    out = sp.check_output([exe], env={})
    return out

if __name__ == '__main__':
    testa.main()
