DIR=$(DESTDIR)
CC=gcc
TARGET=test lib1652817.so
all:$(TARGET)


test: test.o lib1652817.so
	$(CC) -o $@ $< -L. -l1652817
lib1652817.so:readconfig.c
	gcc -shared -fPIC -o $@ $<

install:test lib1652817.so
	cp test $(DIR)/usr/sbin/test-1652817
	cp lib1652817.so $(DIR)/usr/lib64
	mkdir -p $(DIR)/usr/1652817
	cp 1652817.dat $(DIR)/usr/1652817
	cp 1652817.conf $(DIR)/etc
	
rpm:
	mkdir -pv /root/rpmbuild/{BUILD,BUILDROOT,RPMS,SOURCES,SPECS,SRPMS}
	cp test-1652817.tar.bz2 /root/rpmbuild/SOURCES
	cp test.spec /root/rpmbuild/SPECS
	rpmbuild -ba /root/rpmbuild/SPECS/test.spec
	cp /root/rpmbuild/RPMS/x86_64/test-1652817-zyc.x86_64.rpm test-1652817.rpm
	
uninstall:
	rm -f /usr/sbin/test-1652817
	rm -f /usr/lib64/lib1652817.so
	rm -f /etc/1652817.conf
	rm -f /usr/1652817/1652817.dat
	rm -f /etc/systemd/system/test-1652817.service
	rm -rf /root/rpmbuild
	if [ -d "/usr/1652817" ]; then if [ "`ls -A /usr/1652817`" = "" ]; then `rm -rf /usr/1652817`;fi;fi;
clean:
	rm -f test lib1652817.so
	rm -f *.o
	rm -f *.rpm
