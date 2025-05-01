const MAX_DATA = 1024;

struct file_data{
    char data[MAX_DATA];
    int len;
};

program FILE_TRANSFER_PROG{
    version FILE_TRANSFER_VERS{
        int send_file(file_data)=1;
    }=1;
}=0x20000001;