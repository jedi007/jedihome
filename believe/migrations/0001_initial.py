# Generated by Django 3.0 on 2020-01-27 05:29

from django.db import migrations, models


class Migration(migrations.Migration):

    initial = True

    dependencies = [
    ]

    operations = [
        migrations.CreateModel(
            name='UserData',
            fields=[
                ('data_id', models.AutoField(primary_key=True, serialize=False, verbose_name='ID号')),
                ('name', models.TextField(verbose_name='昵称')),
                ('telephone', models.TextField(verbose_name='电话')),
                ('sex', models.TextField(verbose_name='性别')),
                ('birthday', models.DateTimeField(auto_now=True, verbose_name='生日')),
                ('create_date', models.DateTimeField(auto_now=True, verbose_name='创建时间')),
            ],
        ),
    ]
