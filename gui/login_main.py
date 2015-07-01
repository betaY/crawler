from PyQt4.QtGui import *  
from PyQt4.QtCore import *  
import sys  
import login  
  
class TestDialog(QDialog,login.Ui_Dialog):
	def __init__(self,parent=None):
		super(TestDialog,self).__init__(parent)
		self.setupUi(self)

		# ui = login.Ui_Dialog()

		# username = self.lineEdit_username
		# signin = self.pushButton_signin
		# print signin
		self.connect(self.pushButton_signin, SIGNAL("clicked()"), self.signin_button_click)
	def signin_button_click(self):
		username = self.lineEdit_username.text()
		password = self.lineEdit_password.text()
		print "username: ",username,"\npassword: ", password

  
app=QApplication(sys.argv)  
dialog=TestDialog()  
dialog.show()  
app.exec_()  