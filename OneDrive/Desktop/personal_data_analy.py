import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import csv

df=pd.read_csv("personal_data.csv")

#cleaning data
"""print(df.isnull().sum())
print(df.duplicated().sum())
print(df.dtypes)"""

def general_data():
    avg_monthly_income=sum(df['Monthly_Income'])/len(df['Monthly_Income'])
    avg_spending_score=sum(df['Spending_Score'])/len(df['Spending_Score'])
    avg_hours_online_day=sum(df['Hours_Online_Per_Day'])/len(df['Hours_Online_Per_Day'])
    avg_savings=sum(df['Savings'])/len(df['Savings'])
    avg_health_score=sum(df['Health_Score'])/len(df['Health_Score'])
    print("Average monthly income=",avg_monthly_income)
    print("Average spending scores=",avg_spending_score)
    print("Average hours online per day=",avg_hours_online_day)
    print("Average savings=",avg_savings)
    print("Average health score=",avg_health_score)

def income_analysis():
    x=[df['Name'][i] for i in range(len(df['Name']))]
    y=[]
    for i in range(len(df['Monthly_Income'])):
        y.append(df['Monthly_Income'][i])
    colors=['blue' if(v!=max(y) and v!=min(y))
            else 'green' if v==max(y)
            else 'red' for v in y]
    plt.bar(x,y,color=colors)
    plt.title("Income Analysis")
    plt.xlabel("Users")
    plt.ylabel("Income")
    plt.show()
    high_row = df.loc[df['Monthly_Income'].idxmax()] #.idxmax fetch the index of row where Monthly_Income is maximun then loc(fetch the entire row)
    low_row = df.loc[df['Monthly_Income'].idxmin()]  
    print(high_row['Name'], "earns highest salary")
    print(low_row['Name'], "earns lowest salary")


def compare(name1, name2):
    row1 = df.loc[df['Name'] == name1].iloc[0]
    row2 = df.loc[df['Name'] == name2].iloc[0]
    headings = ['Monthly_Income','Spending_Score','Hours_Online_Per_Day','Savings','Health_Score']
    row1_info = [float(row1[h]) for h in headings]
    row2_info = [float(row2[h]) for h in headings]
    # Normalize
    max_vals = [max(row1_info[i], row2_info[i]) for i in range(len(headings))]
    row1_norm = [row1_info[i] / max_vals[i] if max_vals[i] != 0 else 0 for i in range(len(headings))]
    row2_norm = [row2_info[i] / max_vals[i] if max_vals[i] != 0 else 0 for i in range(len(headings))]
    x = np.arange(len(headings))
    width = 0.35
    bars1=plt.bar(x - width/2, row1_norm, width, label=name1)
    bars2=plt.bar(x + width/2, row2_norm, width, label=name2)
    # Add original values as labels
    for i, bar in enumerate(bars1):
        plt.text(bar.get_x() + bar.get_width()/2,bar.get_height(),f'{int(row1_info[i])}',ha='center', va='bottom', fontsize=8)

    for i, bar in enumerate(bars2):
        plt.text(bar.get_x() + bar.get_width()/2,bar.get_height(),f'{int(row2_info[i])}',ha='center', va='bottom', fontsize=8)

    plt.xticks(x, headings, rotation=30)
    plt.title("Comparison graph (Normalized)")
    plt.xlabel("Categories")
    plt.ylabel("Relative Values (0–1)")
    plt.legend()
    plt.tight_layout()
    plt.show()

def enter_record():
    with open("personal_data.csv","a") as f:
        write=csv.writer(f)
        name=input("Enter your name:")
        age=int(input("Enter your age:"))
        gender=input("Enter your gender(Male or Female):")
        city=input("City:")
        occupation=input("Occupation:")
        monthly_income=int(input("Enter your monthly income:"))
        spending_score=int(input("Spending Score:"))
        hours_online=int(input("Enter approx hours you spend online each day:"))
        savings=int(input("Enter savings:"))
        health_score=int(input("Enter health score(0-100):"))
        write.writerow([name,age,gender,city,occupation,monthly_income,spending_score,hours_online,savings,health_score])
        print("Saved!!!")

def update_record(name, col):
    updated_rows = []
    indices = {'Age':1,'Gender':2,'City':3,'Occupation':4,
               'Monthly_Income':5,'Spending_Score':6,
               'Hours_Online_Per_Day':7,'Savings':8,'Health_Score':9}

    col = col.strip().replace(" ", "_").title()

    if col not in indices:
        print("Invalid column!")
        return

    with open("personal_data.csv", "r") as f:
        reader = csv.reader(f)
        for row in reader:
            if len(row) < 10:   # avoid error which we will get if the row have not completely filled values
                continue

            if row[0] == name:
                row[indices[col]] = input("Enter new value:")

            updated_rows.append(row)

    with open("personal_data.csv", "w", newline="") as f:
        writer = csv.writer(f)
        writer.writerows(updated_rows)

    print("Updated successfully")

def delete_entire_record(name):
    rows = []

    # Read all rows except the one to delete
    with open("personal_data.csv", "r", newline="") as f:
        reader = csv.reader(f)
        for row in reader:
            if row[0]!= name:
                rows.append(row)
    # Write the remaining rows back
    with open("personal_data.csv", "w", newline="") as f:
        writer = csv.writer(f)
        writer.writerows(rows)
    print("Row deleted successfully.")

def delete_value(name,col):
    rows = []
    indices={'Age':1,'Gender':2,'City':3,'Occupation':4,'Monthly_Income':5,'Spending_Score':6,'Hours_Online_Per_Day':7,'Savings':8,'Health_Score':9}
    col = col.strip().replace(" ", "_").title()

    if col not in indices:
        print("Invalid column!")
        return
    
    with open("personal_data.csv", "r", newline="") as f:
        reader = csv.reader(f)
        for row in reader:
            if len(row)<10:
                continue
            if row[0] == name:
                row[indices[col]]=""
            rows.append(row)

    with open("personal_data.csv", "w", newline="") as f:
        writer = csv.writer(f)
        writer.writerows(rows)
    print("Value deleted successfully.")

def individ_analy(name):
    row = df.loc[df['Name'] == name].iloc[0]
    headings = ['Monthly_Income','Spending_Score','Hours_Online_Per_Day','Savings','Health_Score']
     # Normalize
    row_info = [float(row[h]) for h in headings]
    max_vals = [max(df[h]) for h in headings]
    row_norm = [row_info[i] / max_vals[i] if max_vals[i] != 0 else 0 for i in range(len(headings))]
    x = np.arange(len(headings))
    width = 0.35
    bar=plt.bar(x - width/2, row_norm, width, label=name)
    for i, bar in enumerate(bar):
        plt.text(bar.get_x() + bar.get_width()/2,bar.get_height(),f'{int(row_info[i])}',ha='center', va='bottom', fontsize=8)

    plt.xticks(x, headings, rotation=30)
    plt.title("Individual Data (Normalized)")
    plt.xlabel("Categories")
    plt.ylabel("Relative Values (0–1)")
    plt.legend()
    plt.tight_layout()
    plt.show()

while True:
    print("\n1. View all data")
    print("2. General data(Avg values):")  #Avg income,spendings etc
    print("3.Income analysis")
    print("4.Compare")
    print("5.Individual Data")
    print("6.Add data\n7.Update data\n8.Delete data")
    choice=int(input("Enter your choice:"))
    print("Enter 0 to exit")
    if choice == 0:
        break
    match choice:
        case 1:
            print(df)
        case 2:
            general_data()
        case 3:
            income_analysis()
        case 4:
            name1=input("Enter your name:")
            name2=input("Enter other person name:")
            compare(name1,name2)
        case 5:
            name=input("Enter your name:")
            individ_analy(name)
        case 6:
            enter_record()
        case 7:
            name=input("Enter the person name whose data is to be updated:")
            col_name=input("Enter column name which you want to update:")
            update_record(name,col_name)
        case 8:
            name=input("Enter the person name whose data is to be deleted:")
            print("1.To delete entire data of person\n2.To delete a specific column value")
            user=int(input("Enter your choice:"))
            if(user==1):
                delete_entire_record(name)
            else:
                col_name=input("Enter column name which you want to delete:")
                delete_value(name,col_name)