from PyQt5 import uic
from PyQt5.QtWidgets import QApplication
import socket
from PyQt5.QtGui import QColor

#  确定服务器IP以及Port
serverName = '10.234.107.112'
serverPort = 2525

client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket.connect((serverName, serverPort))
class window:

    def __init__(self):
        # 从文件中加载UI
        self.password_ui = uic.loadUi("password_input.ui")
        self.password_ui.pushButton_2.clicked.connect(self.password_verification)

        self.userid_ui = uic.loadUi("userid_input.ui")
        self.userid_ui.pushButton_1.clicked.connect(self.userid_verification)

        self.main_ui = uic.loadUi("main_window.ui")
        self.main_ui.pushButton_3.clicked.connect(self.balance_inquiry)
        self.main_ui.pushButton_4.clicked.connect(self.withdraw_ui)
        self.main_ui.pushButton_5.clicked.connect(self.exit)

        self.withdraw_ui = uic.loadUi("withdraw.ui")
        self.withdraw_ui.pushButton_7.clicked.connect(self.withdraw)
        self.withdraw_ui.pushButton_8.clicked.connect(self.back1)

        self.balance_ui = uic.loadUi("balance.ui")
        self.balance_ui.pushButton_6.clicked.connect(self.back2)

    # userid验证
    def userid_verification(self):
        userid = self.userid_ui.userid_lineedit.text()
        message = "HELO " + userid + '\n'

        # 向服务器发送请求
        client_socket.send(message.encode())
        response1 = client_socket.recv(1024).decode()
        if response1 == '5':
            response2 = client_socket.recv(1024).decode()
            response = response1 + response2
            print(response)

            # 如果验证成功，跳转输入password界面,否则提示userid非法！
            if response == ("500 AUTH REQUIRE" + '\n'):
                self.userid_ui.label_3.clear()
                self.userid_ui.close()
                self.password_ui.show()
            else:
                self.userid_ui.label_3.clear()
                self.userid_ui.label_3.setText("用户名错误请重试！")
        else:
            print(response1)
            if response1 == ("500 AUTH REQUIRE" + '\n'):
                self.userid_ui.label_3.clear()
                self.userid_ui.close()
                self.password_ui.show()
            else:
                self.userid_ui.label_3.clear()
                self.userid_ui.label_3.setText("用户名错误请重试！")

    # password验证
    def password_verification(self):
        password = self.password_ui.password_lineedit.text()
        message = "PASS " + password + '\n'

        client_socket.send(message.encode())
        response1 = client_socket.recv(1024).decode()
        print(response1)
        if response1 == '5':
            response2 = client_socket.recv(1024).decode()
            response = response1 + response2


            if response == ("525 OK!" + '\n'):
                self.password_ui.label_3.clear()
                self.password_ui.close()
                self.main_ui.show()
            else:
                self.password_ui.label_3.clear()
                self.password_ui.label_3.setText("密码错误请重试！")
        else:
            if response1 == ("525 OK!" + '\n'):
                self.password_ui.label_3.clear()
                self.password_ui.close()
                self.main_ui.show()
            else:
                self.password_ui.label_3.clear()
                self.password_ui.label_3.setText("密码错误请重试！")

    # 查询余额
    def balance_inquiry(self):
        message = "BALA" + '\n'

        client_socket.send(message.encode())
        orgin_balance1 = client_socket.recv(1024).decode()
        if orgin_balance1 == 'A':
            orgin_balance2 = client_socket.recv(1024).decode()
            orgin_balance = orgin_balance1 + orgin_balance2
            balance = orgin_balance.split(':')[1]

            self.balance_ui.show()
            self.balance_ui.label_2.setText(f'该账户可用余额为：\n\n     {balance}元')
            self.main_ui.hide()
        else:
            if 'AMNT:' in orgin_balance1:
                balance = orgin_balance1.split(':')[1]

                self.balance_ui.show()
                self.balance_ui.label_2.setText(f'该账户可用余额为：\n\n     {balance}元')
                self.main_ui.hide()

    def withdraw_ui(self):
        self.withdraw_ui.show()
        self.main_ui.hide()

    def exit(self):
        message = "BYE" + '\n'

        client_socket.send(message.encode())
        response1 = client_socket.recv(1024).decode()
        if response1 == 'B':
            response2 = client_socket.recv(1024).decode()
            response = response1 + response2

            if response == ("BYE" + '\n'):
                client_socket.close()
                self.main_ui.close()
        else:
            if response1 == ("BYE" + '\n'):
                client_socket.close()
                self.main_ui.close()

    def back(self):
        self.main_ui.show()
        self.balance_ui.close()

    # 取款
    def withdraw(self):
        amount = self.withdraw_ui.amount_lineedit.text()
        message = "WDRA " + amount + '\n'

        client_socket.send(message.encode())
        response1 = client_socket.recv(1024).decode()
        if response1 == '5':
            response2 = client_socket.recv(1024).decode()
            response = response1 + response2

            if response == ("525 OK!" + '\n'):
                self.withdraw_ui.label_3.setText("取款成功！")
                text_color1 = QColor("green")
                self.withdraw_ui.label_3.setStyleSheet("color: {}".format(text_color1.name()))
                self.withdraw_ui.amount_lineedit.clear()
            else:
                self.withdraw_ui.label_3.setText("取款失败或余额不足！")
                text_color2 = QColor("red")
                self.withdraw_ui.label_3.setStyleSheet("color: {}".format(text_color2.name()))
                self.withdraw_ui.amount_lineedit.clear()
        else:
            if response1 == ("525 OK!" + '\n'):
                self.withdraw_ui.label_3.setText("取款成功！")
                text_color1 = QColor("green")
                self.withdraw_ui.label_3.setStyleSheet("color: {}".format(text_color1.name()))
                self.withdraw_ui.amount_lineedit.clear()
            else:
                self.withdraw_ui.label_3.setText("取款失败或余额不足！")
                text_color2 = QColor("red")
                self.withdraw_ui.label_3.setStyleSheet("color: {}".format(text_color2.name()))
                self.withdraw_ui.amount_lineedit.clear()

    def back1(self):
        self.withdraw_ui.close()
        self.main_ui.show()

    def back2(self):
        self.balance_ui.close()
        self.main_ui.show()


if __name__ == "__main__":
    app = QApplication([])
    user_window = window()
    user_window.userid_ui.show()
    app.exec_()
