#导入网页设计模块
from pywebio.output import *
from pywebio import pin as pin
from pywebio.session import Session
import pywebio
from pywebio.session import hold
#导入绘图模块
from pyecharts.charts import Bar
from pyecharts import options as opts
from pyecharts.globals import ThemeType
from pyecharts.charts import Pie
from pyecharts.charts import WordCloud
#导入爬虫模块
from selenium import webdriver
from selenium.webdriver.common.by import By
#导入数据处理模块
import pandas as pd
from collections import Counter
import numpy as np
import time



#爬虫
driver = webdriver.Chrome() 
def ScrapeInfo(keyword):
    #创建一个空列表，用于储存所有工作的信息
    all_job_jnfo=[]
    for page in range(1,5):
        driver.get(
        f'https://www.liepin.com/zhaopin/?inputFrom=www_index&workYearCode=0&key={keyword}&scene=input&ckId=707tb0ltlcmt32pm6014rdf5zdb3bfba&dq=')
        #动态等待，数据加载好就执行，不必真等待10s
        driver.implicitly_wait(10) 
        #通过CSS标签来选择所要爬取的信息
        job_lists = driver.find_elements(By.CSS_SELECTOR,'.job-detail-box')
        for job in job_lists:
            #创建一个空列表，用于存储每个工作的信息
            job_jnfo=[]
            orgin_title = job.find_element(By.CSS_SELECTOR,'.job-title-box .ellipsis-1').text   #职位
            #使用split()来删去职位中（）内的内容
            orgin_title1=orgin_title.split('（')[0]
            #使用lower()来使职位中所有单词全部小写
            title=orgin_title1.lower()
            area = job.find_element(By.CSS_SELECTOR, '.job-dq-box .ellipsis-1').text    #城市
            #删去工作地点中具体的区县，为下一步数据处理提供方便
            if '-' in area:
                city=area.split('-')[0]
            else:
                city=area
            salary = job.find_element(By.CSS_SELECTOR, '.job-salary').text    #薪资
            #将“面议”和“日薪”全部转化为月薪（面议取8k/月）
            if "面议" in salary:
                mini_salary=int(8)*1000
            else:
                if "天" in salary:
                    mini_salary=int(salary.split('-')[0])*30
                mini_salary=int(salary.split('-')[0])*1000
            exp = job.find_element(By.CSS_SELECTOR, '.job-labels-box span:nth-child(1)').text   #经验
            edu = job.find_element(By.CSS_SELECTOR, '.job-labels-box span:nth-child(2)').text   #学历
            company = job.find_element(By.CSS_SELECTOR, '.company-name').text   #公司名称
            company_info = job.find_element(By.CSS_SELECTOR, '.company-tags-box span:nth-child(1)').text    #公司领域
            company_num = job.find_element(By.CSS_SELECTOR, '.company-tags-box span:last-of-type').text   #公司规模
            #防止公司规模未被填写
            if '人' in company_num:
                pass
            else:
                company_num = '未知'
            job_jnfo.append(title)
            job_jnfo.append(city)
            job_jnfo.append(mini_salary)
            job_jnfo.append(exp)
            job_jnfo.append(edu)
            job_jnfo.append(company)
            job_jnfo.append(company_info)
            job_jnfo.append(company_num)
            all_job_jnfo.append(job_jnfo)
            print(title, city, mini_salary, exp, edu, company, company_info, company_num)
            #等待数据加载完成
            time.sleep(0.06)
        #跳到下一页，继续进行数据的爬取
        driver.find_element(By.CSS_SELECTOR,'.ant-pagination-next').click()
    return all_job_jnfo
#将字典中value<5的key删去，归为“其他”
def remove_small_values(d):
    d['其他']=0
    keys_to_remove=[]
    for key,value in d.items():
        if value<5:
            keys_to_remove.append(key)
            d['其他']=d['其他']+1
    for key in keys_to_remove:
        del d[key]
    return d
def delete(d1):
    keys_to_remove1=[]
    for key,value in d1.items():
        if '月' in key:
            keys_to_remove1.append(key)
    for key in keys_to_remove1:
        del d1[key]
    return d1
def search(keyword):
  #查询
  def data_query():
    c=pin.pin['input1']
    e=pin.pin['input2']
    m=pin.pin['input3']
    if c != '默认城市' and e!= '默认学历' and m!= None:
        a=data.query('城市==@c and 学历==@e and 最低薪资>=@m')
        with use_scope('result1',clear=True):
            pin.put_input('input1',
                      label='城市:',type='text',value='默认城市')
            pin.put_input('input2',
                      label='学历:',type='text',value='默认学历')
            pin.put_input('input3',
                      label='期望最低薪资:',type='float')
            put_button('搜索',onclick=lambda: data_query(),color='warning',outline=True)  
            put_scrollable(put_html(a.to_html(border=0)),height=800,keep_bottom=True)   
    elif c=='默认城市' and e !='默认学历' and m==None:
       a=data.query('学历==@e')
       with use_scope('result1',clear=True):
            pin.put_input('input1',
                      label='城市:',type='text',value='默认城市')
            pin.put_input('input2',
                      label='学历:',type='text',value='默认学历')
            pin.put_input('input3',
                      label='期望最低薪资:',type='float')
            put_button('搜索',onclick=lambda: data_query(),color='warning',outline=True)  
            put_scrollable(put_html(a.to_html(border=0)),height=800,keep_bottom=True)
    elif c!='默认城市' and e =='默认学历' and m==None:
       a=data.query('城市==@c')
       with use_scope('result1',clear=True):
            pin.put_input('input1',
                      label='城市:',type='text',value='默认城市')
            pin.put_input('input2',
                      label='学历:',type='text',value='默认学历')
            pin.put_input('input3',
                      label='期望最低薪资:',type='float')
            put_button('搜索',onclick=lambda: data_query(),color='warning',outline=True)  
            put_scrollable(put_html(a.to_html(border=0)),height=800,keep_bottom=True)
    elif c=='默认城市' and e =='默认学历' and m!=None:
       a=data.query('最低薪资>=@m')
       with use_scope('result1',clear=True):
            pin.put_input('input1',
                      label='城市:',type='text',value='默认城市')
            pin.put_input('input2',
                      label='学历:',type='text',value='默认学历')
            pin.put_input('input3',
                      label='期望最低薪资:',type='float')
            put_button('搜索',onclick=lambda: data_query(),color='warning',outline=True)  
            put_scrollable(put_html(a.to_html(border=0)),height=800,keep_bottom=True)
    elif c!='默认城市' and e !='默认学历' and m==None:
       a=data.query('城市==@c and 学历==@e')
       with use_scope('result1',clear=True):
            pin.put_input('input1',
                      label='城市:',type='text',value='默认城市')
            pin.put_input('input2',
                      label='学历:',type='text',value='默认学历')
            pin.put_input('input3',
                      label='期望最低薪资:',type='float')
            put_button('搜索',onclick=lambda: data_query(),color='warning',outline=True)  
            put_scrollable(put_html(a.to_html(border=0)),height=800,keep_bottom=True)
    elif c!='默认城市' and e =='默认学历' and m!=None:
       a=data.query('城市==@c and 最低薪资>=@m')
       with use_scope('result1',clear=True):
            pin.put_input('input1',
                      label='城市:',type='text',value='默认城市')
            pin.put_input('input2',
                      label='学历:',type='text',value='默认学历')
            pin.put_input('input3',
                      label='期望最低薪资:',type='float')
            put_button('搜索',onclick=lambda: data_query(),color='warning',outline=True)  
            put_scrollable(put_html(a.to_html(border=0)),height=800,keep_bottom=True)
    elif c=='默认城市' and e !='默认学历' and m!=None:
       a=data.query('学历==@e and 最低薪资>=@m')
       with use_scope('result1',clear=True):
            pin.put_input('input1',
                      label='城市:',type='text',value='默认城市')
            pin.put_input('input2',
                      label='学历:',type='text',value='默认学历')
            pin.put_input('input3',
                      label='期望最低薪资:',type='float')
            put_button('搜索',onclick=lambda: data_query(),color='warning',outline=True)  
            put_scrollable(put_html(a.to_html(border=0)),height=800,keep_bottom=True)              
  #绘制条形图
  def draw_bar():
    bar=(
        Bar(init_opts=opts.InitOpts(theme=ThemeType.VINTAGE))
        .add_xaxis(list(average_salary3.index.tolist()))
        .add_yaxis('salary by city in 2023' , list(average_salary3.values.tolist()))
        .add_yaxis('salary by city in 2022',list(average_salary4.values.tolist()))
        .set_global_opts(title_opts=opts.TitleOpts(title="招聘职位'薪资—城市信息'分析柱状图"),
        legend_opts=opts.LegendOpts(type_="scroll", pos_right='right', orient="vertical"))
        .set_colors(["peru"])
    )
    return bar
  #绘制饼图
  def draw_pie():
    pie=(
        Pie(init_opts=opts.InitOpts(theme=ThemeType.VINTAGE))
        .add('',[list(z) for z in zip(edu_list,num_list)])
        .set_global_opts(title_opts=opts.TitleOpts(title="招聘职位'要求学历信息'分析饼图"),
        legend_opts=opts.LegendOpts(type_="scroll", pos_right='right', orient="vertical"))
        .set_series_opts(label_opts=opts.LabelOpts(formatter="{b}:{c} {d}%"))
    )
    return pie
  #绘制词云
  def draw_wordcloud():
    wordcloud=(
        WordCloud(init_opts=opts.InitOpts(theme=ThemeType.VINTAGE))
        .add('',list1,word_size_range=[20,100])
        .set_global_opts(title_opts=opts.TitleOpts(title="招聘'职位信息'分析"))
    )
    return wordcloud
  keyword=pin.pin['keyword']
  #弹出等待窗口
  popup('请稍后', '正在查询中……', size=PopupSize.NORMAL)
  ScrapeInfo(keyword)
  #数据处理
  data=pd.DataFrame(ScrapeInfo(keyword),columns=['职位',
  '城市',
  '最低薪资',
  '经验',
  '学历',
  '公司名称',
  '公司领域',
  '公司规模',])
  job_info_2022=pd.DataFrame(pd.read_csv('zhilian2022.csv',usecols=['positionWorkCity','salaryReal'],header=0))
  city_list_2022=list(job_info_2022['positionWorkCity'])
  salary_list_2022f=list(job_info_2022['salaryReal'])
  salary_list_2022=[]
  for i in salary_list_2022f:
    salary=i.split('-')[0]
    salary=int(salary)
    salary_list_2022.append(salary)
  city_list=list(data['城市'])
  salary_list=list(data['最低薪资'])
  #获取城市对应最低薪资的平均值
  df=pd.DataFrame({'city_list':city_list,'salary_list':salary_list})
  df1=pd.DataFrame({'city_list_2022':city_list_2022,'salary_list_2022':salary_list_2022})
  average_salary1=df.groupby('city_list')['salary_list'].mean()
  average_salary2=df1.groupby('city_list_2022')['salary_list_2022'].mean()
  average_salary4=np.round(average_salary2)
  average_salary3=np.round(average_salary1)
  #对学历、职位进行计数
  edu_counter=Counter(data['学历'])
  title_counter=dict(Counter(data['职位']))
  tuple1=tuple(title_counter.items())
  list1=list(tuple1)
  delete(edu_counter)
  remove_small_values(title_counter)
  edu_list=edu_counter.keys()
  num_list=edu_counter.values()
  wordcloud=draw_wordcloud()
  bar=draw_bar()
  pie=draw_pie()
  #关闭弹窗
  close_popup()
  put_text(f"关于{keyword}的信息：").style('font-size:30px')
  #使用输出域scope输出,"clear=True"保证下次输出时先清除当前输出域的内容
  with use_scope('result1',clear=True):
    pin.put_input('input1',
                label='城市:',type='text',value='默认城市')
    pin.put_input('input2',
                label='学历:',type='text',value='默认学历')
    pin.put_input('input3',
                      label='期望最低薪资:',type='float')
    put_button('搜索',onclick=lambda: data_query(),color='warning',outline=True)
    put_scrollable(put_html(data.to_html(border=0)),height=800,keep_bottom=True)
  with use_scope('result2',clear=True):
    put_html(bar.render_notebook())
    put_html(pie.render_notebook())
    put_html(wordcloud.render_notebook())
    
  
def main():
  pywebio.session.set_env(title='猎聘招聘信息查询网站',output_max_width='1080px')
  img=open('liepin.jpg','rb').read()
  put_image(img,width='650px',height='200px')
  put_text("欢迎使用猎聘招聘信息查询系统！").style('color:gold;font-size:45px;text-algin:center')
  #使用pin对象达到重复输入的目的
  pin.put_input(
      'keyword',
      label='猎聘招聘信息查询:',
      type='text',
      #占位
      placeholder='搜索职位/公司/内容关键词:',  
      #提示
      help_text='关键词越准确，结果越精准!',
      #常驻输入联想                  
      datalist=['python开发', 'java', 'c++','c#','前端','后端'])
  put_button("查询", onclick=lambda: search(pin.pin['keyword']), color='warning',outline=True)
if __name__ == '__main__':
    main()