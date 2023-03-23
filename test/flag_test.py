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

@testa.is_(expect=b'xixi')
def str_flag_w_default_set():
    exe = BASE_DIR.joinpath('str_flag_with_default')
    out = sp.check_output([exe], env={'str_flag_with_default': 'xixi'})
    return out

@testa.is_(expect=b'haha')
def str_flag_w_default():
    exe = BASE_DIR.joinpath('str_flag_with_default')
    out = sp.check_output([exe], env={})
    return out


@testa.is_(expect=b'1')
def i64_flag():
    exe = BASE_DIR.joinpath('i64_flag')
    out = sp.check_output([exe], env={'i64_flag': '1'})
    return out

@testa.throw(throw=sp.CalledProcessError)
def missing_i64_flag():
    exe = BASE_DIR.joinpath('i64_flag')
    out = sp.check_output([exe], env={})
    return out

@testa.is_(expect=b'1')
def i64_flag_w_default_set():
    exe = BASE_DIR.joinpath('i64_flag_with_default')
    out = sp.check_output([exe], env={'i64_flag_with_default': '1'})
    return out

@testa.is_(expect=b'123')
def i64_flag_w_default():
    exe = BASE_DIR.joinpath('i64_flag_with_default')
    out = sp.check_output([exe], env={})
    return out


@testa.is_(expect=b'true')
def bool_flag_true():
    exe = BASE_DIR.joinpath('bool_flag')
    out = sp.check_output([exe], env={'bool_flag': 'true'})
    return out

@testa.is_(expect=b'false')
def bool_flag_false():
    exe = BASE_DIR.joinpath('bool_flag')
    out = sp.check_output([exe], env={'bool_flag': 'false'})
    return out

@testa.throw(throw=sp.CalledProcessError)
def missing_bool_flag():
    exe = BASE_DIR.joinpath('bool_flag')
    out = sp.check_output([exe], env={})
    return out

@testa.is_(expect=b'false')
def bool_flag_w_default_set():
    exe = BASE_DIR.joinpath('bool_flag_with_default')
    out = sp.check_output([exe], env={'bool_flag_with_default': 'false'})
    return out

@testa.is_(expect=b'true')
def bool_flag_w_default():
    exe = BASE_DIR.joinpath('bool_flag_with_default')
    out = sp.check_output([exe], env={})
    return out


@testa.is_(expect=b'1.2')
def f64_flag():
    exe = BASE_DIR.joinpath('f64_flag')
    out = sp.check_output([exe], env={'f64_flag': '1.2'})
    return out

@testa.throw(throw=sp.CalledProcessError)
def missing_f64_flag():
    exe = BASE_DIR.joinpath('f64_flag')
    out = sp.check_output([exe], env={})
    return out

@testa.is_(expect=b'1.2')
def f64_flag_w_default_set():
    exe = BASE_DIR.joinpath('f64_flag_with_default')
    out = sp.check_output([exe], env={'f64_flag_with_default': '1.2'})
    return out

@testa.is_(expect=b'123')
def f64_flag_w_default():
    exe = BASE_DIR.joinpath('f64_flag_with_default')
    out = sp.check_output([exe], env={})
    return out

if __name__ == '__main__':
    testa.main()
