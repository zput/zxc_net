		
add_executable(zxc_echo  zxc_echo.cc)
target_link_libraries(zxc_echo zxc_net pthread)

                     # 在build.sh定义了安装目录, 
					 # [# DCMAKE_INSTALL_PREFIX=../Release-install]/lib or /include
install(TARGETS zxc_echo DESTINATION bin)




