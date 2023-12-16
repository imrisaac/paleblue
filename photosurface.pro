TEMPLATE = app

QT += qml quick
SOURCES += \
	settingsmanager.cpp \
	main.cpp \
	qtbuttonimageprovider.cpp \

HEADERS += \
	settingsmanager.h \
	qtbuttonimageprovider.h
	
RESOURCES += 
	photosurface.qrc
	
OTHER_ILES += \
	*.qml
	resources/*
	fonts/*

target.path = $$[QT_INSTALL_EXAMPLES]/demos/photosurface
INSTALLS += target
ICON = resources/icon.png
macos: ICON = resources/photosurface.icns
win32: RC_FILE = resources/photosurface.rc

