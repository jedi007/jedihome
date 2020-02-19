from django.shortcuts import render

from django.http import HttpResponse

from django.http import JsonResponse

from datetime import datetime

from  believe.models  import  UserData
from  believe.models  import  FrinendModel

# Create your views here.

def hello_world(request):
        return  HttpResponse("Hellow Django World at jedihome")


def  regist_account(request):
        if request.method == 'POST':
                user_obj = UserData()
                #user_obj.save()  #对象调动save方法保存到数据库
                for key in request.POST:
                        valuelist = request.POST.getlist(key)
                        if key == "name":
                                user_obj.name = valuelist[0]
                        if key == "telephone":
                                user_obj.telephone = valuelist[0]
                        if key == "password":
                                user_obj.password = valuelist[0]
                        if key == "sex":
                                user_obj.sex = valuelist[0]
                        if key == "birthday": 
                                user_obj.birthday = datetime.strptime(valuelist[0], '%Y-%m-%d %H:%M:%S')

                exist_user = UserData.objects.filter(telephone=user_obj.telephone)
                
                if exist_user:
                        result = {"result":-1}
                        return JsonResponse(result)
                else:
                        user_obj.save()
        else:
                result = {"result":-2}
                return JsonResponse(result)

        result = {"result":0}
        return JsonResponse(result)


def  login(request):
        if request.method == 'POST':
                user_obj = UserData()
                #user_obj.save()  #对象调动save方法保存到数据库
                for key in request.POST:
                        if key == "telephone":
                                valuelist = request.POST.getlist(key)
                                user_obj.telephone = valuelist[0]                   
                        if key == "password":
                                valuelist = request.POST.getlist(key)
                                user_obj.password = valuelist[0]

                exist_user_list = UserData.objects.filter(telephone=user_obj.telephone)
                
                if exist_user_list:
                        exist_user = exist_user_list[0]
                        if exist_user.password == user_obj.password :
                                result = {"result":0, "user":{ "name":exist_user.name, "telephone":exist_user.telephone, "sex":exist_user.sex, "birthday":exist_user.birthday.strftime("%Y-%m-%d %H:%M:%S") } }
                                return JsonResponse(result)
                        else:
                                result = {"result":-102}
                                return JsonResponse(result)
                else:
                        result = {"result":-101}
                        return JsonResponse(result)

        result = {"result":-103}
        return JsonResponse(result)


def  searchUser(request):
        if request.method == 'POST':
                user_obj = UserData()
                #user_obj.save()  #对象调动save方法保存到数据库
                for key in request.POST:
                        if key == "telephone":
                                valuelist = request.POST.getlist(key)
                                user_obj.telephone = valuelist[0]

                exist_user_list = UserData.objects.filter(telephone=user_obj.telephone)
                
                if exist_user_list:
                        exist_user = exist_user_list[0]
                        result = {"result":0, "user":{ "name":exist_user.name, "telephone":exist_user.telephone, "sex":exist_user.sex, "birthday":exist_user.birthday.strftime("%Y-%m-%d %H:%M:%S") } }
                        return JsonResponse(result)
                else:
                        result = {"result":-101}
                        return JsonResponse(result)

        result = {"result":-103}
        return JsonResponse(result)

def addFriend(request): 
        if request.method == 'POST':
                friend_obj = FrinendModel()
                for key in request.POST:
                        if key == "telephone":
                                valuelist = request.POST.getlist(key)
                                friend_obj.telephone = valuelist[0]

                        if key == "friendTel":
                                valuelist = request.POST.getlist(key)
                                friend_obj.friendTel = valuelist[0]

                if friend_obj.telephone != "" and friend_obj.friendTel != "":
                        friend_obj.save()
                        result = {"result":0}
                        return JsonResponse(result)
                else:
                        result = {"result":-101}
                        return JsonResponse(result)

        result = {"result":-103}
        return JsonResponse(result)
