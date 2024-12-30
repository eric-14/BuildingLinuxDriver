def main():
    driver_handle =  open("/proc/Eric_Driver")
    driver_output = driver_handle.readline()
    print("message from driver handle is "+ driver_output)
    
    driver_handle.close()



main()