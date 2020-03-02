from django.db import models
from datetime import datetime

# Create your models here.
class UserData(models.Model):
        data_id  =  models.AutoField(primary_key=True, verbose_name="ID号")
        name      =  models.TextField(verbose_name="昵称")
        telephone      =  models.TextField(unique=True, verbose_name="电话")
        password      =  models.TextField(verbose_name="密码")
        sex      =  models.TextField(verbose_name="性别")
        birthday      =  models.DateTimeField(default=datetime.strptime("2000-1-1 00:00:00", '%Y-%m-%d %H:%M:%S'),verbose_name="生日")
        create_date  =  models.DateTimeField(auto_now=True, verbose_name="创建时间")

        loginTime      =  models.DateTimeField(default=datetime.strptime("2000-1-1 00:00:00", '%Y-%m-%d %H:%M:%S'),verbose_name="登陆时间")
        loginIP            =  models.TextField(default="0.0.0.0",  verbose_name="登陆IP")

        def  __str__(self):
                return  self.name         #现实在后台管理 标题中


class FrinendModel(models.Model):
        telephone      =  models.TextField( verbose_name="电话")
        friendTel         =  models.TextField( verbose_name="好友电话")
        add_date  =  models.DateTimeField(auto_now=True, verbose_name="添加时间")

        loginIP            =  models.TextField(default="0.0.0.0",  verbose_name="登陆IP")

        def  __str__(self):
                return  self.telephone         #现实在后台管理 标题中