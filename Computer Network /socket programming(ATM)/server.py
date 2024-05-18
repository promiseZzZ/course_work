from socket import *
from datetime import datetime  
import pymysql 

Userid='0'
global Balance
Balance=0

#连接数据库

db = pymysql.connect(
    host="localhost", 
    port=3306,
    user='root',    #在这里输入用户名
    password='zasx1554',     #在这里输入密码
    charset='utf8mb4',
    database='computer'     #指定操作的数据库
    )

print ('The server is ready to receive')

#账户密码余额等基础信息

#日志的创建
def day_creat_entry():
    current_time = datetime.now() 
    with open('C:\\Users\\Administrator\\Desktop\\计算机网络\\实验\\ATM\\day_record.txt', 'a') as file:  
        file.write(str(current_time)+' '+str(Userid)+' '+"进入使用了ATM机!\n")  
    file.close()
def day_creat_not_entry():
      current_time = datetime.now() 
      with open('C:\\Users\\Administrator\\Desktop\\计算机网络\\实验\\ATM\\day_record.txt', 'a') as file:  
         file.write(str(current_time)+' '+str(Userid)+' '+"尝试进入使用ATM机,但是失败了\n")  
      file.close()
def day_creat_balance():
      current_time = datetime.now() 
      with open('C:\\Users\\Administrator\\Desktop\\计算机网络\\实验\\ATM\\day_record.txt', 'a') as file:  
         file.write(str(current_time)+' '+str(Userid)+' '+"查询了余额！\n")  
      file.close()
def day_creat_withdraw_true(value):
      current_time = datetime.now() 
      with open('C:\\Users\\Administrator\\Desktop\\计算机网络\\实验\\ATM\\day_record.txt', 'a') as file:  
         file.write(str(current_time)+' '+str(Userid)+' '+"取出了"+str(value)+"\n")  
      file.close()
def day_creat_withdraw_false(value):
      current_time = datetime.now() 
      with open('C:\\Users\\Administrator\\Desktop\\计算机网络\\实验\\ATM\\day_record.txt', 'a') as file:  
         file.write(str(current_time)+' '+str(Userid)+' '+"尝试取出"+str(value)+"但是失败了！\n")  
      file.close()


#各种回复报文段
messagebegin="500 AUTH REQUIRE\n"
messagewrong="401 ERROR!\n"
messageok="525 OK!\n"
messagebye="BYE\n"

#验证是否是合法id
def check_userid():
   connectionSocket.send(messagebegin.encode())

#验证密码
def check_password():
   connectionSocket.send(messageok.encode())
   day_creat_entry()

#查询余额
def check_balance():
    global Balance
    cursor = db.cursor()
    sql="SELECT balance FROM atm WHERE Userid = %s ;"%(Userid,)
    cursor.execute(sql)
    temp=cursor.fetchone()
    Balance=temp[0]
    messsage_balance="AMNT:"+str(Balance)+'\n'
    day_creat_balance()
    connectionSocket.send(messsage_balance.encode())

#取款
def with_draw(value):
   global Balance
   if(value>Balance):
        connectionSocket.send(messagewrong.encode())
        day_creat_withdraw_false(value)
   else:
       connectionSocket.send(messageok.encode())
       Balance=Balance-value
       day_creat_withdraw_true(value)

#结束会话
def bye():
    connectionSocket.send(messagebye.encode())


serverPort = 2525
serverSocket = socket(AF_INET, SOCK_STREAM)
serverSocket.bind(('0.0.0.0', serverPort))
serverSocket.listen(1)

while 1:
    connectionSocket, addr = serverSocket.accept()
    while 1:
        try:
            sentence = connectionSocket.recv(1024).decode()
            if not sentence:
                break
   #验证id
            if(sentence[:5]=="HELO " or sentence[:2]=="H"):
                cursor = db.cursor()
                if (sentence[:2]=="H"):
                    sentence=connectionSocket.recv(1024).decode()
                    sql="SELECT EXISTS (SELECT 1 FROM atm WHERE Userid = '%s\');"%(sentence[4:-1],)
                    cursor.execute(sql)
                    temp=cursor.fetchone()
                    if(temp[0]):
                        Userid=sentence[4:-1]
                        check_userid()
                    else:
                        connectionSocket.send(messagewrong.encode())
                else:
                    sql="SELECT EXISTS (SELECT 1 FROM atm WHERE Userid = '%s\');"%(sentence[5:-1],)
                    cursor.execute(sql)
                    temp=cursor.fetchone()
                    if(temp[0]):
                        Userid=sentence[5:-1]
                        check_userid()
                    else:
                        connectionSocket.send(messagewrong.encode())

   #验证密码
            if(sentence[:5]=="PASS "or sentence[:2]=="P"):
                if(sentence[:2]=="P"):
                    sentence=connectionSocket.recv(1024).decode()
                    sql="SELECT * FROM atm WHERE Userid = %s AND Password = '%s\';"%(Userid,sentence[4:-1])
                    cursor.execute(sql)
                    temp=cursor.fetchone()
                    if(temp==None):
                        connectionSocket.send(messagewrong.encode())
                        day_creat_not_entry() 
                    else:
                        check_password()
                else:
                    sql="SELECT * FROM atm WHERE Userid = %s AND Password = '%s\';"%(Userid,sentence[5:-1])
                    cursor.execute(sql)
                    temp=cursor.fetchone()
                    if(temp==None):
                        connectionSocket.send(messagewrong.encode())
                        day_creat_not_entry() 
                    else:
                        check_password()

   #查询余额
            if(sentence=="BALA\n"):
                check_balance()
   
   #取款
            if(sentence[:5]=="WDRA "or sentence[:2]=="W"):
                if(sentence[:2]=="W"):
                    sentence=connectionSocket.recv(1024).decode()
                    value=int(sentence[4:-1])
                    with_draw(value)
                    cursor = db.cursor()
                    sql="UPDATE atm SET Balance =%s WHERE Userid = %s;"
                    cursor.execute(sql,(Balance,Userid))
                    db.commit()
                else:
                    value=int(sentence[5:-1])
                    with_draw(value)
                    cursor = db.cursor()
                    sql="UPDATE atm SET Balance =%s WHERE Userid = %s;"
                    cursor.execute(sql,(Balance,Userid))
                    db.commit()

            if(sentence[:2]=="B"):
                sentence=connectionSocket.recv(1024).decode()
                if(sentence[:1]=="A"):
                    check_balance()
                else:
                    bye() 
   #结束会话
            if(sentence=="BYE\n"):
                bye()      
        except ConnectionResetError:
            print("ConnectionResetError: 远程主机强制关闭了连接")
            break
    connectionSocket.close()
db.close()
serverSocket.close()

