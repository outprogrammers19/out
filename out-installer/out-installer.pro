TEMPLATE = aux

INSTALLER = OUT-installer

INPUT = $$PWD/config/config.xml $$PWD/packages
installer.input = INPUT
installer.output = $$INSTALLER
installer.commands = binarycreator --offline-only -c $$PWD/config/config.xml -p $$PWD/packages ${QMAKE_FILE_OUT}
installer.CONFIG += target_predeps no_link combine

QMAKE_EXTRA_COMPILERS += installer

OTHER_FILES += \
    packages/tz.ac.out/meta/package.xml \
    packages/tz.ac.out/meta/install-script.qs\
    packages/tz.ac.out/meta/files-list.txt\

