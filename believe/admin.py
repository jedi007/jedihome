from django.contrib import admin

# Register your models here.
from  .models import  UserData
from  .models import  FrinendModel

class ModelDataAdmin(admin.ModelAdmin):
        list_display = ["data_id", "name", "telephone", "birthday", "create_date"]
        # def  getTitle(self.obj):
        #         return [bt.name for bt in obj.title.all()]
        #filter_horizontal = ('limit_date',)

admin.site.register(UserData,ModelDataAdmin)
admin.site.register(FrinendModel)

#admin.site.register(ModelData)