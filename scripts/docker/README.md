# Docker images

These docker images use [spack](https://github.com/spack/spack) to build a
CUDA-enabled development environment for Celeritas. There are two sets of
images:
- `dev` (this directory) which leaves spack fully installed and
  debug symbols intact; and
- `ci` (`ci` subdirectory) which only copies the necessary software stack (thus
  requiring lower bandwidth on the CI servers).

Additionally there are two image configurations:
- `focal-cuda11`: Ubuntu 20 "Focal" with CUDA 11.
- `bionic-minimal`: Ubuntu 18 "Bionic" with only googletest/nljson.

## Building

The included `build.sh` script drives the two subsequent docker builds. Its
argument should be an image configuration name, or `cuda` or `minimal` as
shortcuts for those.

If the final docker push fails, you may have to log in with your `docker.io`
credentials first:
```console
$ docker login -u sethrj
```

## Running

The CI image is (in color) run with:
```console
$ docker run --rm -ti -e "TERM=xterm-256color" celeritas/ci-cuda11
```
Note that the `--rm` option automatically deletes the state of the container
after you exit the docker client. This means all of your work will be
destroyed.

The `launch-testing` script will clone an active github pull request, build,
and set up an image to use locally:
```console
$ ./ci/launch-testing.sh 123
```

To mount the image with your local source directory:
```console
$ docker run --rm -ti -e "TERM=xterm-256color" \
    -v /rnsdhpc/code/celeritas:src \
    celeritas/ci-cuda11
```


The `dev` image runs as root, but the `ci-cuda11` runs as a user `celeritas`.
This is the best way to [make OpenMPI happy](https://github.com/open-mpi/ompi/issues/4451).

Note that the Jenkins CI runs as root regardless of the `run` command, so it
defines `MPIEXEC_PREFLAGS=--allow-run-as-root` for CMake.

