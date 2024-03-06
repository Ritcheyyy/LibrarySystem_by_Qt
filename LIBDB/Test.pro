QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    USEROperator.cpp \
    advice_for_library.cpp \
    borrow_record.cpp \
    changepassword.cpp \
    check_admini.cpp \
    checkpassword.cpp \
    dealapply.cpp \
    deletereserve.cpp \
    detailoperation.cpp \
    detailoperation_for_visitor.cpp \
    editbook.cpp \
    editnotice.cpp \
    edituser.cpp \
    first_window_for_administrator.cpp \
    first_window_for_user.cpp \
    first_window_for_visitor.cpp \
    forget_questioncheck.cpp \
    forgetpassword.cpp \
    forgetpasswordapply.cpp \
    forgetpasswordcheck.cpp \
    loginwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    personalpage.cpp \
    readnotice.cpp \
    register_for_administrator.cpp \
    registerwindow.cpp \
    reserveoperation.cpp \
    returnbook.cpp \
    setmail.cpp \
    setquestion.cpp \
    user_apply.cpp

HEADERS += \
    USEROperator.h \
    advice_for_library.h \
    borrow_record.h \
    changepassword.h \
    check_admini.h \
    checkpassword.h \
    dealapply.h \
    deletereserve.h \
    detailoperation.h \
    detailoperation_for_visitor.h \
    editbook.h \
    editnotice.h \
    edituser.h \
    first_window_for_administrator.h \
    first_window_for_user.h \
    first_window_for_visitor.h \
    forget_questioncheck.h \
    forgetpassword.h \
    forgetpasswordapply.h \
    forgetpasswordcheck.h \
    loginwindow.h \
    mainwindow.h \
    personalpage.h \
    readnotice.h \
    register_for_administrator.h \
    registerwindow.h \
    reserveoperation.h \
    returnbook.h \
    setmail.h \
    setquestion.h \
    user_apply.h

FORMS += \
    advice_for_library.ui \
    borrow_record.ui \
    changepassword.ui \
    check_admini.ui \
    checkpassword.ui \
    dealapply.ui \
    deletereserve.ui \
    detailoperation.ui \
    detailoperation_for_visitor.ui \
    editbook.ui \
    editnotice.ui \
    edituser.ui \
    first_window_for_administrator.ui \
    first_window_for_user.ui \
    first_window_for_visitor.ui \
    forget_questioncheck.ui \
    forgetpassword.ui \
    forgetpasswordapply.ui \
    forgetpasswordcheck.ui \
    loginwindow.ui \
    mainwindow.ui \
    personalpage.ui \
    readnotice.ui \
    register_for_administrator.ui \
    registerwindow.ui \
    reserveoperation.ui \
    returnbook.ui \
    setmail.ui \
    setquestion.ui \
    user_apply.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    userdataDB_zh_CN.ts \
    userdataDB_zh_CN.ts
