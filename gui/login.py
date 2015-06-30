# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'login.ui'
#
# Created: Tue Jun 30 10:26:37 2015
#      by: PyQt4 UI code generator 4.11.3
#
# WARNING! All changes made in this file will be lost!

from PyQt4 import QtCore, QtGui

try:
    _fromUtf8 = QtCore.QString.fromUtf8
except AttributeError:
    def _fromUtf8(s):
        return s

try:
    _encoding = QtGui.QApplication.UnicodeUTF8
    def _translate(context, text, disambig):
        return QtGui.QApplication.translate(context, text, disambig, _encoding)
except AttributeError:
    def _translate(context, text, disambig):
        return QtGui.QApplication.translate(context, text, disambig)

class Ui_Dialog(object):
    def setupUi(self, Dialog):
        Dialog.setObjectName(_fromUtf8("Dialog"))
        Dialog.resize(320, 240)
        self.widget = QtGui.QWidget(Dialog)
        self.widget.setGeometry(QtCore.QRect(20, 50, 273, 96))
        self.widget.setObjectName(_fromUtf8("widget"))
        self.verticalLayout = QtGui.QVBoxLayout(self.widget)
        self.verticalLayout.setMargin(0)
        self.verticalLayout.setObjectName(_fromUtf8("verticalLayout"))
        self.lineEdit_username = QtGui.QLineEdit(self.widget)
        self.lineEdit_username.setObjectName(_fromUtf8("lineEdit_username"))
        self.verticalLayout.addWidget(self.lineEdit_username)
        self.lineEdit_password = QtGui.QLineEdit(self.widget)
        self.lineEdit_password.setObjectName(_fromUtf8("lineEdit_password"))
        self.verticalLayout.addWidget(self.lineEdit_password)
        self.horizontalLayout = QtGui.QHBoxLayout()
        self.horizontalLayout.setObjectName(_fromUtf8("horizontalLayout"))
        spacerItem = QtGui.QSpacerItem(40, 20, QtGui.QSizePolicy.Expanding, QtGui.QSizePolicy.Minimum)
        self.horizontalLayout.addItem(spacerItem)
        self.pushButton_signin = QtGui.QPushButton(self.widget)
        self.pushButton_signin.setObjectName(_fromUtf8("pushButton_signin"))
        self.horizontalLayout.addWidget(self.pushButton_signin)
        self.pushButton_signup = QtGui.QPushButton(self.widget)
        self.pushButton_signup.setObjectName(_fromUtf8("pushButton_signup"))
        self.horizontalLayout.addWidget(self.pushButton_signup)
        self.verticalLayout.addLayout(self.horizontalLayout)

        self.retranslateUi(Dialog)
        QtCore.QObject.connect(self.pushButton_signin, QtCore.SIGNAL(_fromUtf8("clicked()")), Dialog.accept)
        QtCore.QObject.connect(self.pushButton_signup, QtCore.SIGNAL(_fromUtf8("clicked()")), Dialog.reject)
        QtCore.QMetaObject.connectSlotsByName(Dialog)

    def retranslateUi(self, Dialog):
        Dialog.setWindowTitle(_translate("Dialog", "Dialog", None))
        self.lineEdit_username.setPlaceholderText(_translate("Dialog", "Enter your Username", None))
        self.lineEdit_password.setPlaceholderText(_translate("Dialog", "Enter your Password", None))
        self.pushButton_signin.setText(_translate("Dialog", "Sign In", None))
        self.pushButton_signup.setText(_translate("Dialog", "Sign up", None))

