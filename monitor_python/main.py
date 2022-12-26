import psutil 

print(psutil.pids()  )
pids= psutil.pids()
p = psutil.Process( pids[3] )
#print(p)

spaces = 10

print("|" +  ("-"*10 + "|" )*3 )

def display():
    for i in range(50):
        print("""  """)

#display()

