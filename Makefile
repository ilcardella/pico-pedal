ifeq ($(origin .RECIPEPREFIX), undefined)
  $(error This Make does not support .RECIPEPREFIX. Please use GNU Make 4.0 or later)
endif
.RECIPEPREFIX = >

DOCKER_IMAGE = guitar-fx-builder
DOCKER_USER = -u $(shell id -u):$(shell id -g)
DOCKER_BUILD = docker build --rm -f docker/Dockerfile --target builder -t $(DOCKER_IMAGE) .
DOCKER_RUN = docker run --rm -t -v ${PWD}:/build -w /build $(DOCKER_USER) $(DOCKER_IMAGE):latest

default: build

docker:
> $(DOCKER_BUILD)

build:
> $(DOCKER_RUN) make local-build

local-build: clean
> scripts/build.sh

clean:
> rm -rf build

ci: docker build

.PHONY: default docker build local-build clean ci
