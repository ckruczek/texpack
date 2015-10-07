texpack - A latex package manager for arch linux [![GitHub release](https://img.shields.io/github/release/ckruczek/texpack.svg?style=flat-square)]()
=======

**Table of contents**

1.[Summary](#summary)

2.[Philosphy](#philosophy)

3.[Building on linux](#building-on-linux-with-git-gccclang-and-autotools)


## Summary

texpack is a latex package manager for arch linux. The main goal of texpack is to provide a common interface for installing, upgrading and removing tex-live packages. texpack supports the official sources of [CTAN](http://www.ctan.org).

## Philosophy

texpack is a tool designed by the rules of the KISS-Principle like the ArchLinux operating system.
Functionality provided by texpack is simmiliar to the one of pacman - the arch linux package manager.

## Building on linux with `git`, `gcc/clang` and `autotools`

Prerequisites

- `gcc` or `clang`
- `libcurl` 
- `autotools`

Clone `texpack` from github: https://github.com/ckruczek/texpack

```bash
$ git clone https://github.com/ckruczek/texpack
$ cd texpack
$ autoreconf --install
$ ./configure
$ make
```



