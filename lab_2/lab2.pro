TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        base_exception.cpp \
        base_matrix.cpp \
        main.cpp

HEADERS += \
    base_exception.h \
    base_matrix.h \
    const_iterator.h \
    const_iterator.hpp \
    iterator.h \
    iterator.hpp \
    iterator_exceptions.h \
    matrix.h \
    matrix.hpp \
    matrix_exceptions.h
