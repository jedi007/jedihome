# Generated by Django 3.0 on 2020-02-16 12:05

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('believe', '0002_auto_20200127_2013'),
    ]

    operations = [
        migrations.CreateModel(
            name='FrinendModel',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('telephone', models.TextField(unique=True, verbose_name='电话')),
                ('friendTel', models.TextField(unique=True, verbose_name='好友电话')),
                ('add_date', models.DateTimeField(auto_now=True, verbose_name='添加时间')),
            ],
        ),
    ]