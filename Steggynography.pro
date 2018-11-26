TEMPLATE = app
TARGET = steg

UI_HEADERS_DIR = ui
OBJECTS_DIR = obj

QT -= core gui
CONFIG += console c++14
CONFIG -= app_bundle gui

INCLUDEPATH += \
    /usr/local/include/glm/glm \
    /usr/local/include/glm \
    /usr/local/include \
    $$PWD/include 

DEPPATH = $$PWD/dep
DEPS = $$system(ls $${DEPPATH})
!isEmpty(DEPS) {
  for(d, DEPS) {
    INCLUDEPATH += $${DEPPATH}/$${d}
    INCLUDEPATH += $${DEPPATH}/$${d}/include
  }
}

HEADERS += $$files(include/*.h, true)
HEADERS += $$files(include/*.inl, true)
SOURCES += $$files(src/*.cpp, true)

# Linker libraries
LIBS +=  -ltbb -lOpenImageIO

#DEFINES += _GLIBCXX_PARALLEL
DEFINES += GLM_ENABLE_EXPERIMENTAL GLM_FORCE_CTOR_INIT

STEGGYNOGRAPHY_NAMESPACE =steg
QMAKE_CXXFLAGS += \
  -DSTEGGYNOGRAPHY_NAMESPACE=\"$${STEGGYNOGRAPHY_NAMESPACE}\" \
  -DEND_STEGGYNOGRAPHY_NAMESPACE="}" \
  -DBEGIN_STEGGYNOGRAPHY_NAMESPACE=\"namespace $${STEGGYNOGRAPHY_NAMESPACE} {\"

# Standard flags
QMAKE_CXXFLAGS += -std=c++14 -g
# Optimisation flags
QMAKE_CXXFLAGS += -Ofast -march=native -frename-registers -funroll-loops -ffast-math -fassociative-math
# Intrinsics flags
QMAKE_CXXFLAGS += -mfma -mavx2 -m64 -msse -msse2 -msse3
# Enable all warnings
QMAKE_CXXFLAGS += -Wall -Wextra -pedantic-errors
# Vectorization info
QMAKE_CXXFLAGS += -ftree-vectorize -ftree-vectorizer-verbose=5

# Enable openmp
QMAKE_CXXFLAGS += -fopenmp
QMAKE_LFLAGS += -fopenmp

#QMAKE_CXXFLAGS += -fsanitize=undefined -fsanitize=address 
#QMAKE_LFLAGS += -fsanitize=undefined -fsanitize=address
