# -*- coding: UTF-8 -*-

import json
import getopt
import sys
import requests
import smtplib
import re
from fake_useragent import UserAgent
from requests.cookies import RequestsCookieJar
from email.mime.text import MIMEText
from email.header import Header


# 会话
session = requests.session()

# # 邮件配置区

mail_user = "用户名"  # 用户名
mail_pass = "授权码"  # 口令
sender = '发送者邮箱'  # 发送者
def smtp(info, receiver):
    # 第三方 SMTP 服务
    mail_host = "smtp.qq.com"  # 设置服务器

    message = MIMEText(info, 'plain', 'utf-8')
    message['From'] = Header('天上来', 'utf-8')
    message['To'] = Header('地狱去', 'utf-8')

    subject = '路过人间'
    message['Subject'] = Header(subject, 'utf-8')

    try:
        smtpObj = smtplib.SMTP()
        smtpObj.connect(mail_host, 25)  # 25 为 SMTP 端口号
        smtpObj.login(mail_user, mail_pass)
        smtpObj.sendmail(sender, [receiver], message.as_string())
        smtpObj.close()
        print("邮件发送成功")
    except smtplib.SMTPException as e:
        print(e)
        print("Error: 无法发送邮件")

def login(username, password):
    # 登录网址
    url = "登录提交用户名和密码地址"
    ua = UserAgent()
    headers = {
        "User-Agent": ua.chrome
    }
    data = {
        "username": username,
        "password": password
    }

    # 登陆界面获取标识cookie
    res = session.get("登陆页面地址")
    # print("当前cookies: " + str(res.cookies))
    cookies = requests.utils.dict_from_cookiejar(res.cookies)
    session.cookies.update(cookies) # 将cookie保存至Session

    # 请求提交表单
    res = session.post(url=url, data=data, headers=headers, cookies=cookies)
    if res.json()['e'] != 0:
        print("登录失败，账号或密码错误")
        sys.exit(-1)

    cookies = requests.utils.dict_from_cookiejar(res.cookies)
    session.cookies.update(cookies)

    cookies = requests.utils.dict_from_cookiejar(session.cookies)
    print("重定向前cookie内容：" + str(cookies))

    # 请求重定向至提交当日信息页面
    res = session.get("提交信息页面地址", headers=headers, cookies=cookies)
    print(res.status_code)
    print("当前cookies: " + str(res.cookies))
    print(res.text)
    cookies = requests.utils.dict_from_cookiejar(res.cookies)
    session.cookies.update(cookies)

    # 用正则表达式处理响应的文本，并返回解析出来的data包
    tstr= res.text
    res = re.findall(r'.*?oldInfo: (.*),.*?', tstr)
    data = eval(res[0])
    return data

def submit(data, username, receiver):
    # 提交的目标地址
    url = "提交信息目标地址"

    #复制出来的data包
    headers = {'Accept': 'application/json,text/javascript,*/*;q=0.01',
               'Accept-Language': 'zh-CN,zh;q=0.8,zh-TW;q=0.7,zh-HK;q=0.5,en-US;q=0.3,en;q=0.2',
               'Accept-Encoding': 'gzip,deflate,br',
               'Content-Type': 'application/x-www-form-urlencoded;',
               'X-Requested-With': 'XMLHttpRequest',
               'Content-Length': '2082',
               'Connection': 'keep-alive',
               }
    res = session.post(url, headers=headers, data=data)

    if res.json()['e'] != '0':
        print("提交异常！" + res.text)
        smtp("用户[" + username + "]提交信息失败。\n\n提交信息：" + res.text, receiver)
    else:
        print("提交成功！" + res.text)
        smtp("用户[" + username + "]提交信息成功。\n\n 提交信息：" + res.text, receiver)

def main(argv):
    username = ''
    passwrod = ''
    receiver = ''

    if len(argv) < 1:
        print('Error: autoSubmitForm.py -u <username> -p <password>')
        sys.exit(-2)

    try:
        opts, args = getopt.getopt(argv, "hu:p:m:", ["help", "username=", "password=", "mail="])

    except getopt.GetoptError:
        print('Error: autoSubmitForm.py -u <username> -p <password> -m <your e-mail>')
        print("or autoSubmitForm.py --username=<username> --passwrod=<passwrod> --mail=<your e-mail>")
        sys.exit(-1)
    for opt, arg in opts:
        if opt in  ("-h", "help"):
            print('Error: autoSubmitForm.py -u <username> -p <password> -m <your e-mail>')
            print("or autoSubmitForm.py --username=<username> --passwrod=<passwrod> --mail=<your e-mail>")
        elif opt in ("-u", "--username"):
            username = arg
        elif opt in ("-p", "--password"):
            passwrod = arg
        elif opt in ("-m", "--mail"):
            receiver = arg
	# 模拟登录获得提交的数据
    data = login(username, passwrod)
    print('开始提交...')
    submit(data, username, receiver)
	print('结束')
    session.close()
if __name__ == '__main__':
    main(sys.argv[1:])
