def main():
    driver_handle = open('/proc/pyjama_driver')
    msg_from_kernal_space = driver_handle.readline()
    print(msg_from_kernal_space)
    driver_handle.close()

if '__main__' == __name__:
    main()
