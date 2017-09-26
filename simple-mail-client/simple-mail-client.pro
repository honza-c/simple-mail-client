TEMPLATE = subdirs

SUBDIRS += \
    mail-client \
    mail-client-test \
    mail-client-core

mail-client.depends = mail-client-core
mail-client-test.depends = mail-client-core
