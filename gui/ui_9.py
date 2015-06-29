# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file '9.ui'
#
# Created: Mon Jun 29 11:15:38 2015
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
        self.splitter = QtGui.QSplitter(Dialog)
        self.splitter.setGeometry(QtCore.QRect(30, 60, 213, 55))
        self.splitter.setOrientation(QtCore.Qt.Vertical)
        self.splitter.setObjectName(_fromUtf8("splitter"))
        self.widget = QtGui.QWidget(self.splitter)
        self.widget.setObjectName(_fromUtf8("widget"))
        self.horizontalLayout_2 = QtGui.QHBoxLayout(self.widget)
        self.horizontalLayout_2.setMargin(0)
        self.horizontalLayout_2.setObjectName(_fromUtf8("horizontalLayout_2"))
        self.label_name = QtGui.QLabel(self.widget)
        self.label_name.setObjectName(_fromUtf8("label_name"))
        self.horizontalLayout_2.addWidget(self.label_name)
        self.lineEdit_name = QtGui.QLineEdit(self.widget)
        self.lineEdit_name.setObjectName(_fromUtf8("lineEdit_name"))
        self.horizontalLayout_2.addWidget(self.lineEdit_name)
        self.widget1 = QtGui.QWidget(self.splitter)
        self.widget1.setObjectName(_fromUtf8("widget1"))
        self.horizontalLayout = QtGui.QHBoxLayout(self.widget1)
        self.horizontalLayout.setMargin(0)
        self.horizontalLayout.setObjectName(_fromUtf8("horizontalLayout"))
        spacerItem = QtGui.QSpacerItem(40, 20, QtGui.QSizePolicy.Expanding, QtGui.QSizePolicy.Minimum)
        self.horizontalLayout.addItem(spacerItem)
        self.Button_ok = QtGui.QPushButton(self.widget1)
        self.Button_ok.setObjectName(_fromUtf8("Button_ok"))
        self.horizontalLayout.addWidget(self.Button_ok)
        self.Button_cancel = QtGui.QPushButton(self.widget1)
        self.Button_cancel.setObjectName(_fromUtf8("Button_cancel"))
        self.horizontalLayout.addWidget(self.Button_cancel)

        self.retranslateUi(Dialog)
        QtCore.QObject.connect(self.Button_ok, QtCore.SIGNAL(_fromUtf8("clicked()")), Dialog.accept)
        QtCore.QObject.connect(self.Button_cancel, QtCore.SIGNAL(_fromUtf8("clicked()")), Dialog.reject)
        QtCore.QMetaObject.connectSlotsByName(Dialog)

    def retranslateUi(self, Dialog):
        Dialog.setWindowTitle(_translate("Dialog", "Dialog", None))
        self.label_name.setText(_translate("Dialog", "Name", None))
        self.Button_ok.setText(_translate("Dialog", "OK", None))
        self.Button_cancel.setText(_translate("Dialog", "Cancel", None))

