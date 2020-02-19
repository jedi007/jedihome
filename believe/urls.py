from  django.urls  import  path,include

import believe.views

urlpatterns  =  [
        path('hello', believe.views.hello_world),
        path('regist_account', believe.views.regist_account),
        path('login', believe.views.login),
        path('searchUser', believe.views.searchUser),
        path('addFriend', believe.views.addFriend),
]