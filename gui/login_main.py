from PyQt4.QtGui import *  
from PyQt4.QtCore import *  
import sys  
import login  
  
class TestDialog(QDialog,login.Ui_Dialog):
	def __init__(self,parent=None):
		super(TestDialog,self).__init__(parent)
		self.setupUi(self)

		# ui = login.Ui_Dialog()
		print self.lineEdit_username.text()

  
app=QApplication(sys.argv)  
dialog=TestDialog()  
dialog.show()  
app.exec_()  