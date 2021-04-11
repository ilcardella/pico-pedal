ifeq ($(origin .RECIPEPREFIX), undefined)
  $(error This Make does not support .RECIPEPREFIX. Please use GNU Make 4.0 or later)
endif
.RECIPEPREFIX = >

DOCKER_IMAGE = guitar_fx_lib_builder
DOCKER_USER = -u $(shell id -u):$(shell id -g)
DOCKER_BUILD = docker build --rm -f docker/Dockerfile --target builder -t $(DOCKER_IMAGE) .
DOCKER_RUN = docker run --rm -t -v ${PWD}:/build -w /build $(DOCKER_USER) $(DOCKER_IMAGE):latest

default: ci

docker:
> $(DOCKER_BUILD)

test:
> $(DOCKER_RUN) scripts/test-project.sh

ci: docker test

clean:
> rm -rf build

install: clean
> scripts/install.sh

.PHONY: default ci test docker clean install
