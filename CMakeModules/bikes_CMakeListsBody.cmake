# bikes_CMakeListsBody
#===============================================================================
macro(CMakeBikes_run)
# DEV ->
message("\n>>>>>>>>>> [ ${PROJECT_NAME} ] >>>>>>>>>>")
message("\nLet's go biking!")
#...............................................................................
# Дополнительные опции ->
#set(CMAKE_USE_RELATIVE_PATHS TRUE)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
# <- Дополнительные опции 
#...............................................................................
# Инициализация переменных ->
get_sub_project_flag(THIS_SUB_PROJECT) 
set(USE_QT_AUTOMOC)
set(ANYFILE *)
set(ANYFILES *)
set(LINK_LIST)
set(TMP_SUBPROJECT_NAME)
set(SUBPROJECTS_LIST)
set(REQUIRED_INCLUDE_DIRS)
set(TARGET_LIST)
if(NOT THIS_SUB_PROJECT)
	get_filename_component(BUILD_DIR ${${PROJECT_NAME}_BINARY_DIR} NAME)
	set(HINT_IGNOR_DIRS ${HINT_IGNOR_DIRS} ${BUILD_DIR})
endif()

message_var(THIS_SUB_PROJECT)
if(NOT PRIVATE_DEFINITIONS)
	set(PRIVATE_DEFINITIONS)
endif()
# <- Инициализация переменных
#...............................................................................
# Поиск исходников ->
br()
find_project_files(${CMAKE_CURRENT_SOURCE_DIR} ANYFILE HINT_EXT_HEADERS HFILES)
message_var(HFILES)
find_project_files(${CMAKE_CURRENT_SOURCE_DIR} ANYFILE HINT_EXT_SOURCES SFILES)
message_var(SFILES)
set(SHFILES ${HFILES} ${SFILES})
set(TFILES ${SHFILES})
# <- Поиск исходников
#..............................................................................
# Определение личных каталогов включения ->
br()
if(HFILES)
	get_files_dir_list(HFILES PRIVATE_INCLUDE_DIRS)
	get_public_include_dirs(PRIVATE_INCLUDE_DIRS HINT_PUBLIC_INCLUDE_PREFIX PUBLIC_INCLUDE_DIRS)		
else()
	set(PRIVATE_INCLUDE_DIRS)
	set(PUBLIC_INCLUDE_DIRS)
endif()
message_var(PRIVATE_INCLUDE_DIRS)
message_var(PUBLIC_INCLUDE_DIRS)
# <- Определение личных каталогов включения
#...............................................................................
br()
# Определение типа проекта ->
if(${PROJECT_TYPE} STREQUAL AUTO)
	if((NOT HFILES) AND (NOT SFILES))
		set(PROJECT_TYPE AGGREGATION)
	else()
		if(SFILES)
			if(HFILES)
				find_project_files(${CMAKE_CURRENT_SOURCE_DIR} HINT_EXPORT_HEADER HINT_EXT_HEADERS EFILES)
				if(EFILES)
					set(PROJECT_TYPE SHARED_LIB)
				else()
					find_project_files(${CMAKE_CURRENT_SOURCE_DIR} HINT_MAIN_SOURCE HINT_EXT_SOURCES MAINFILE)
					if(MAINFILE)
						set(PROJECT_TYPE EXECUTABLE)
					else()
						set(PROJECT_TYPE STATIC_LIB)
					endif()
				endif()
			else()
				set(PROJECT_TYPE EXECUTABLE)
			endif()
		else()
			set(PROJECT_TYPE HEADERS_LIB)
		endif()
	endif()
endif()
message_var(PROJECT_TYPE)
# <- Определение типа проекта
#..............................................................................
# Определение цели(целей?) ->
set(EXEC_OUT)
set(LIB_OUT)
set(EXPORT_DEFINITION)
set(TARGET_EXISTS)
if(${PROJECT_TYPE} STREQUAL EXECUTABLE)	
	if(MSVC)
		set(EXEC_TYPE WIN32)
	else()
		set(EXEC_TYPE)
	endif()
	set(${TARGET_NAME}_TYPE EXEC)
	set(${TARGET_NAME}_TYPE_PARAM ${EXEC_TYPE})	
	set(EXEC_OUT ${TARGET_NAME})
	set(TARGET_LIST ${TARGET_LIST} ${TARGET_NAME})	
	#add_executable(${TARGET_NAME} ${EXEC_TYPE} ${TFILES} )
	set(TARGET_EXISTS true)
elseif( (NOT (${PROJECT_TYPE} STREQUAL AGGREGATION)) AND (NOT (${PROJECT_TYPE} STREQUAL HEADERS_LIB)) )

	if(${PROJECT_TYPE} STREQUAL SHARED_OR_STATIC_LIB)
		option(${PROJECT_NAME}_STATIC "Статическая сборка" OFF)		
		if(${PROJECT_NAME}_STATIC)
			set(PROJECT_TYPE STATIC_LIB)
		else()
			set(PROJECT_TYPE SHARED_LIB)
		endif()
	endif()

	if(${PROJECT_TYPE} STREQUAL SHARED_LIB)
		set(LIB_TYPE SHARED)
		set(EXPORT_DEFINITION ${DEF_FOR_SHARED_EXPORT})
	else()
		set(LIB_TYPE STATIC)		
		set(EXPORT_DEFINITION ${DEF_FOR_STATIC_EXPORT})
	endif()
	set(${TARGET_NAME}_TYPE LIB)
	set(${TARGET_NAME}_TYPE_PARAM ${LIB_TYPE})	
	set(LIB_OUT ${TARGET_NAME})
	set(TARGET_LIST ${TARGET_LIST} ${TARGET_NAME})	
	#add_library(${TARGET_NAME} ${LIB_TYPE} ${TFILES})	
	set(TARGET_EXISTS true)
else()	
set(TARGET_EXISTS false)
endif()
message_var(LIB_OUT)
message_var(EXEC_OUT)
message_var(TARGET_LIST)
# <- Определение цели(целей?)
#...............................................................................
#=============================================================================================================
#...............................................................................
# Подключение подпроектов ->
br()
find_dirs(${CMAKE_CURRENT_SOURCE_DIR} HINT_DEPENDENCIES_DIR dpn_dirs)
find_dirs(${CMAKE_CURRENT_SOURCE_DIR} HINT_SAMPLES_DIR smp_dirs)
list_dirs_without_cmakelists(${CMAKE_CURRENT_SOURCE_DIR} src_dirs)
if(src_dirs AND (dpn_dirs OR smp_dirs))
	list(REMOVE_ITEM src_dirs ${dpn_dirs} ${smp_dirs})
endif()

set(PARENT_DEPENDENCIES_LIBS ${CMAKEBIKES_DEPENDENCIES_LIBS})
message_var(PARENT_DEPENDENCIES_LIBS)

#set(CMAKEBIKES_DEPENDENCIES_LIBS)
set(SUBPROJECTS_DPN)
if(dpn_dirs)
	add_subdirs(dpn_dirs ON SUBPROJECTS_DPN)
endif()

set(LIBS_DPN)
if(SUBPROJECTS_DPN)	
	get_subvariables_list(SUBPROJECTS_DPN CMAKEBIKES_ _LIB_LIST LIBS_DPN)
endif()

set(SUBPROJECTS_SRC)
set(CMAKEBIKES_DEPENDENCIES_LIBS ${PARENT_DEPENDENCIES_LIBS} ${LIBS_DPN})
add_subdirs(CMAKE_CURRENT_SOURCE_DIR OFF SUBPROJECTS_ROOT)
if(src_dirs)
	add_subdirs(src_dirs ON SUBPROJECTS_SRC)
endif()

set(SUBPROJECTS_SMP)
set(CMAKEBIKES_DEPENDENCIES_LIBS ${CMAKEBIKES_DEPENDENCIES_LIBS} ${LIB_OUT})
if(smp_dirs)
	option(${PROJECT_NAME}_SAMPLES "Include ${PROJECT_NAME}'s sample-projects." ON)
	if(${PROJECT_NAME}_SAMPLES)
		add_subdirs(smp_dirs ON SUBPROJECTS_SMP)
	endif()
endif()

set(CMAKEBIKES_DEPENDENCIES_LIBS ${PARENT_DEPENDENCIES_LIBS} ${LIBS_DPN})

set(SUBPROJECTS 
	${SUBPROJECTS_ROOT}
	${SUBPROJECTS_DPN} 
	${SUBPROJECTS_SMP} 
	${SUBPROJECTS_SRC}
	)

set(SUBSUBPROJECTS)
foreach(p ${SUBPROJECTS})
	get_all_subproject_list(${p} spl)
	set(SUBSUBPROJECTS ${SUBSUBPROJECTS} ${spl})
endforeach()
set(SUBPROJECTS_ALL ${SUBPROJECTS} ${SUBSUBPROJECTS})

message_var(SUBPROJECTS)
message_var(SUBPROJECTS_ALL)
#foreach(p ${SUBPROJECTS_ALL})	
#	message_project_vars(${p})
#endforeach()
# <- Подключение подпроектов 
#...............................................................................
# Компоновка проекта ->
set(LINK_LIST)
set(LINK_LIBS)

if(REQUIRED_LIBS)
	list(REMOVE_DUPLICATES REQUIRED_LIBS)
	list(FIND REQUIRED_LIBS AUTO f)
	if(NOT (${f} EQUAL -1))
		set(LINK_LIBS ${LINK_LIST} ${PARENT_DEPENDENCIES_LIBS} ${LIBS_DPN})
	endif()
	list(FIND REQUIRED_LIBS DEPENDENCIES f)	
	if(NOT (${f} EQUAL -1))
		set(LINK_LIBS ${LINK_LIST} ${LIBS_DPN})	
	endif()
	list(FIND REQUIRED_LIBS PARENT_DEPENDENCIES f)	
	if(NOT (${f} EQUAL -1))
		set(LINK_LIBS ${LINK_LIST} ${PARENT_DEPENDENCIES_LIBS})
	endif()	
	list(REMOVE_ITEM REQUIRED_LIBS AUTO DEPENDENCIES PARENT_DEPENDENCIES NO)
	set(LINK_LIBS ${LINK_LIBS} ${REQUIRED_LIBS})	
	if(LINK_LIBS)
		list(REMOVE_DUPLICATES LINK_LIBS)
	endif()
	set(LINK_LIST ${LINK_LIST} ${LINK_LIBS})
endif()

message_var(LINK_LIBS)
message_var(LINK_LIST)
# <- Компоновка проекта
#...............................................................................
# Поиск и подключение пакетов ->
include_qt()
if(USE_BOOST)
	find_package(boost REQUIRED)	
	set(REQUIRED_INCLUDE_DIRS ${REQUIRED_INCLUDE_DIRS} ${Boost_INCLUDE_DIR})
endif()
# <- Поиск и подключение пакетов
#...............................................................................
# Предварительное определение внешних каталогов включения ->
set(BAD_LIBS)
set(RLINK)

if(LINK_LIBS)
	get_required_include_dirs(LINK_LIBS rid BAD_LIBS)
	set(REQUIRED_INCLUDE_DIRS ${REQUIRED_INCLUDE_DIRS} ${rid})
endif()

if(REQUIRED_INCLUDE)
	get_required_include_dirs(REQUIRED_INCLUDE RID BL)
	set(REQUIRED_INCLUDE_DIRS ${REQUIRED_INCLUDE_DIRS} ${RID})
	set(BAD_LIBS ${BAD_LIBS} ${BL})
endif()

if(REQUIRED_INCLUDE_DIRS)
	list(REMOVE_DUPLICATES REQUIRED_INCLUDE_DIRS)
else()
	set(REQUIRED_INCLUDE_DIRS)
endif()

#message_var(REQUIRED_INCLUDE_DIRS)
message_var(BAD_LIBS)

if(NOT ADDITIONAL_INCLUDE_DIRS)
	set(ADDITIONAL_INCLUDE_DIRS)
endif()

set(INCLUDE_DIRS ${PRIVATE_INCLUDE_DIRS} ${PUBLIC_INCLUDE_DIRS} ${REQUIRED_INCLUDE_DIRS} ${ADDITIONAL_INCLUDE_DIRS})


if(USE_QT)			
#	message_var(${PROJECT_NAME}_BINARY_DIR)
	set(INCLUDE_DIRS ${INCLUDE_DIRS} ${${PROJECT_NAME}_BINARY_DIR})
endif()
# <- Предварительное определение внешних каталогов включения
#...............................................................................
if(INCLUDE_DIRS)
	list(REMOVE_DUPLICATES INCLUDE_DIRS)
	include_directories(${INCLUDE_DIRS}) #~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~!!!!!!!!!!!!!!!!!!
endif()
#...............................................................................
get_property(INCLUDED_DIRS DIRECTORY PROPERTY INCLUDE_DIRECTORIES)
message_var(INCLUDED_DIRS)
# Генерируемые файлы ->
set(GFILES)
if(USE_QT)
	set(MOC_SOURCES)
	if(USE_QT_AUTOMOC)		
		message_var(USE_QT_AUTOMOC)
	else()
		find_moc_files(SHFILES MOC_SOURCES)
		message_var(MOC_SOURCES)
	endif()
	
	find_qrc_files(${CMAKE_CURRENT_SOURCE_DIR} QRFILES QR_SOURCES)
	message_var(QRFILES)
	message_var(QR_SOURCES)	
	set(GFILES ${MOC_SOURCES} ${QR_SOURCES})
	
	set(TFILES ${TFILES} ${GFILES})	
endif()


# <- Генерируемые файлы
#...............................................................................
foreach(t ${TARGET_LIST})
	set(${t}_FILES ${TFILES})
endforeach()
#...............................................................................
# Создание цели(целей) ->
if(USE_QT)
	set(LINK_LIST ${LINK_LIST} ${QT_LIBRARIES})
endif()

message_var(TARGET_LIST)

foreach(t ${TARGET_LIST})	
	if(${${t}_TYPE} STREQUAL EXEC)
		add_executable(${t} ${${t}_TYPE_PARAM} ${${t}_FILES})
	else()
		add_library(${t} ${${t}_TYPE_PARAM} ${${t}_FILES})
	endif()
	set_target_properties(${t} PROPERTIES DEBUG_POSTFIX "_d")		
	if(LINK_LIST)
		target_link_libraries(${t} ${LINK_LIST})		
	endif()
	
endforeach()
# <- Создание цели(целей)
#...............................................................................
# Окончательное определение внешних каталогов включения ->
if(TARGET_EXISTS)
	set(REQUIRED_INCLUDE_DIRS)
	foreach(t ${TARGET_LIST})
		get_target_property(tinclude ${t} INCLUDE_DIRECTORIES)
		set(${t}_INCLUDED_DIRS ${tinclude})
		message_var(${t}_INCLUDED_DIRS)
		if(tinclude)
			set(REQUIRED_INCLUDE_DIRS ${REQUIRED_INCLUDE_DIRS} ${tinclude})	
		endif()
	endforeach()

	if(REQUIRED_INCLUDE_DIRS)		
		list(REMOVE_DUPLICATES REQUIRED_INCLUDE_DIRS)	
		set(INCLUDE_DIRS ${REQUIRED_INCLUDE_DIRS})
		if(PUBLIC_INCLUDE_DIRS OR PRIVATE_INCLUDE_DIRS)
			list(REMOVE_ITEM REQUIRED_INCLUDE_DIRS ${PUBLIC_INCLUDE_DIRS} ${PRIVATE_INCLUDE_DIRS})	
		endif()
	else()
		set(REQUIRED_INCLUDE_DIRS)
		set(INCLUDE_DIRS)
	endif()
endif()
message_var(REQUIRED_INCLUDE_DIRS)
# <- Окончательное определение внешних каталогов включения 
#...............................................................................
# Определение каталогов включения пользователей ->

set(USERS_INCLUDE_LIBS)
if(USERS_INCLUDE)
	set(uid)
	list(REMOVE_DUPLICATES USERS_INCLUDE)
	
	list(FIND USERS_INCLUDE AUTO f)	
	if(NOT (${f} EQUAL -1))			
		set(uid ${uid} ${PUBLIC_INCLUDE_DIRS} ${REQUIRED_INCLUDE_DIRS})		
		set(USERS_INCLUDE_LIBS ${USERS_INCLUDE_LIBS} ${BAD_LIBS})
	endif()		
	list(FIND USERS_INCLUDE PUBLIC f)
	if(NOT (${f} EQUAL -1))			
		set(uid ${uid} ${PUBLIC_INCLUDE_DIRS})		
	endif()	
	list(FIND USERS_INCLUDE PRIVATE f)
	if(NOT (${f} EQUAL -1))			
		set(uid ${uid} ${PRIVATE_INCLUDE_DIRS})		
	endif()	
	list(FIND USERS_INCLUDE DEPENDENCIES f)
	if(NOT (${f} EQUAL -1))			
		set(uid ${uid} ${REQUIRED_INCLUDE_DIRS})				
		set(USERS_INCLUDE_LIBS ${USERS_INCLUDE_LIBS} ${BAD_LIBS})
	endif()	
	list(FIND USERS_INCLUDE ADDITIONAL f)
	if(NOT (${f} EQUAL -1))			
		set(uid ${uid} ${ADDITIONAL_INCLUDE_DIRS})		
	endif()	
	foreach(lib ${LINK_LIBS})
		list(FIND USERS_INCLUDE ${lib} f)
		if(NOT (${f} EQUAL -1))
			set(USERS_INCLUDE_LIBS ${USERS_INCLUDE_LIBS} ${lib})
		endif()
	endforeach()
	list(REMOVE_ITEM USERS_INCLUDE NO AUTO PUBLIC PRIVATE DEPENDENCIES ADDITIONAL ${LINK_LIBS})	
	foreach(d ${USERS_INCLUDE})
		get_filename_component(p ${d} ABSOLUTE)
		if(EXISTS ${p})
			set(uid ${uid} ${p})
		endif()
	endforeach()
	if(uid)
		list(REMOVE_DUPLICATES uid)			
		set(USERS_INCLUDE ${uid})
	else()	
		set(USERS_INCLUDE)
	endif()		
	if(USERS_INCLUDE_LIBS)
		list(REMOVE_DUPLICATES USERS_INCLUDE_LIBS)
	endif()
endif()		

#if(INCLUDE_DIRS)
#	foreach(t ${TARGET_LIST})				
#		set_property(TARGET ${t} PROPERTY INCLUDE_DIRECTORIES ${INCLUDE_DIRS})	
#	endforeach()
#endif()

message_var(ADDITIONAL_INCLUDE_DIRS)
message_var(USERS_INCLUDE)
# <- Определение каталогов включения пользователей 
#...............................................................................
# Определения препроцессора ->
message_var(PRIVATE_DEFINITIONS)
if(PRIVATE_DEFINITIONS)
	foreach(def ${PRIVATE_DEFINITIONS})
		add_definitions(-D${def})
	endforeach()
endif()

message_var(EXPORT_DEFINITION)
if(EXPORT_DEFINITION)
	add_definitions(-D${EXPORT_DEFINITION})
endif()

set(EXTERNAL_DEFINITIONS)
if(LINK_LIBS)
	#get_subvariables_list(LINK_LIBS CMAKEBIKES_ _USERS_DEFINITIONS EXTERNAL_DEFINITIONS)
	get_required_definitions(LINK_LIBS EXTERNAL_DEFINITIONS)
	if(EXTERNAL_DEFINITIONS)
		list(REMOVE_DUPLICATES EXTERNAL_DEFINITIONS)
		list(REMOVE_ITEM EXTERNAL_DEFINITIONS NO)
		if(EXTERNAL_DEFINITIONS)
			foreach(def ${EXTERNAL_DEFINITIONS})
				add_definitions(-D${def})
			endforeach()
		endif()
	endif()
endif()
message_var(EXTERNAL_DEFINITIONS)

if(USERS_DEFINITIONS)
	set(def)
	list(REMOVE_DUPLICATES USERS_DEFINITIONS)
	list(FIND USERS_DEFINITIONS AUTO f)
	if(NOT (${f} EQUAL -1))
		list(REMOVE_ITEM USERS_DEFINITIONS AUTO STATIC_EXPORT)
		set(USERS_DEFINITIONS ${USERS_DEFINITIONS} STATIC_EXPORT)
	endif()
	if(EXPORT_DEFINITION)
		list(FIND USERS_DEFINITIONS STATIC_EXPORT f)
		if(NOT (${f} EQUAL -1))		
			if(${EXPORT_DEFINITION} STREQUAL ${DEF_FOR_STATIC_EXPORT})		
				set(def ${def} ${DEF_FOR_STATIC_EXPORT})
			endif()
		endif()
		list(FIND USERS_DEFINITIONS SHARED_EXPORT f)
		if(NOT (${f} EQUAL -1))
			if(${EXPORT_DEFINITION} STREQUAL ${SHARED_EXPORT})		
				set(def ${def} ${DEF_FOR_SHARED_EXPORT})
			endif()
		endif()
	endif()
	list(FIND USERS_DEFINITIONS PRIVATE f)
	if(NOT (${f} EQUAL -1))
		if(PRIVATE_DEFINITIONS)
			set(def ${def} ${PRIVATE_DEFINITIONS})
		endif()
	endif()
	list(REMOVE_ITEM USERS_DEFINITIONS AUTO STATIC_EXPORT SHARED_EXPORT PRIVATE)
	set(def ${def} ${USERS_DEFINITIONS})
	if(def)
		list(REMOVE_DUPLICATES def)
		set(USERS_DEFINITIONS ${def})
	else()
		set(USERS_DEFINITIONS)
	endif()
else()
set(USERS_DEFINITIONS)
endif()
message_var(USERS_DEFINITIONS)
# <- Определения препроцессора 
#...............................................................................
# CMakeBikes variables ->
set(CMAKEBIKES_${PROJECT_NAME}_LIB_LIST ${LIB_OUT})
set(CMAKEBIKES_${PROJECT_NAME}_EXEC_LIST ${EXEC_OUT})
set(CMAKEBIKES_${PROJECT_NAME}_TARGET_LIST ${TARGET_LIST} ${SUBTARGETS_ALL})
set(CMAKEBIKES_${PROJECT_NAME}_USERS_INCLUDE_DIRS ${USERS_INCLUDE})
set(CMAKEBIKES_${PROJECT_NAME}_USERS_INCLUDE_LIBS ${USERS_INCLUDE_LIBS})
set(CMAKEBIKES_${PROJECT_NAME}_USERS_DEFINITIONS ${USERS_DEFINITIONS})
set(CMAKEBIKES_${PROJECT_NAME}_SUBPROJECT_LIST ${SUBPROJECTS})
foreach(t ${LIB_OUT} ${EXEC_OUT})
	set(CMAKEBIKES_${t}_REQUIRED_INCLUDE ${BAD_LIBS})
	set(CMAKEBIKES_${t}_USERS_INCLUDE_DIRS ${USERS_INCLUDE})
	set(CMAKEBIKES_${t}_USERS_INCLUDE_LIBS ${USERS_INCLUDE_LIBS})
	set(CMAKEBIKES_${t}_USERS_DEFINITIONS ${USERS_DEFINITIONS})
endforeach()
# <- CMakeBikes variables 
#...............................................................................
# BAD_LIBS ->
set(SUBTARGETS_ALL)
if(SUBPROJECTS_ALL)
	get_subvariables_list(SUBPROJECTS_ALL CMAKEBIKES_ _TARGET_LIST SUBTARGETS_ALL)
endif()
message_var(SUBTARGETS_ALL)
foreach(t ${SUBTARGETS_ALL})
	if(CMAKEBIKES_${t}_REQUIRED_INCLUDE)		
		get_required_include_dirs(CMAKEBIKES_${t}_REQUIRED_INCLUDE rInclude badLibs)
		get_required_definitions(CMAKEBIKES_${t}_REQUIRED_INCLUDE rDef)		
		if(rInclude)
			get_target_property(tinclude ${t} INCLUDE_DIRECTORIES)
			if(tinclude)
				set(tinclude ${tinclude} ${rInclude})
			else()
				set(tinclude ${rInclude})
			endif()
			list(REMOVE_DUPLICATES tinclude)			
			set_property(TARGET ${t} PROPERTY INCLUDE_DIRECTORIES ${tinclude})			
		endif()
		if(rDef)
			get_target_property(tDef ${t} COMPILE_DEFINITIONS)
			if(tDef)
				set(tDef ${tDef} ${rDef})
			else()
				set(tDef ${rDef})
			endif()
			list(REMOVE_DUPLICATES tDef)
			set_property(TARGET ${t} PROPERTY COMPILE_DEFINITIONS ${tDef})
		endif()
		set(CMAKEBIKES_${t}_REQUIRED_INCLUDE ${badLibs})
	endif()
endforeach()
# <- BAD_LIBS
#=============================================================================================================
#...............................................................................
# Предкомпилированный заголовок ->
if(${USE_PRECOMPILED_HEADER} STREQUAL AUTO)
	find_project_files(${CMAKE_CURRENT_SOURCE_DIR} HINT_PRECOMPILED_HEADER HINT_EXT_HEADERS hs)
	if(hs)
		list(GET hs 0 USE_PRECOMPILED_HEADER)
	else()
		set(USE_PRECOMPILED_HEADER)
	endif()
endif()
message_var(USE_PRECOMPILED_HEADER)
if(USE_PRECOMPILED_HEADER)
	include(cotire)
	set_target_properties(${TARGET_NAME} PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT ${USE_PRECOMPILED_HEADER})
	set_target_properties(${TARGET_NAME} PROPERTIES COTIRE_ADD_UNITY_BUILD false)
	cotire(${TARGET_NAME})
endif()
# <- предкомпилированный заголовок
#...............................................................................
if(USE_QT_AUTOMOC)		
	foreach(t ${TARGET_LIST})
		set_target_properties(${t} PROPERTIES AUTOMOC true)
		#message("set_target_properties(${t} PROPERTIES AUTOMOC true)")
	endforeach()
endif()
#...............................................................................
# Группировка файлов ->
if(SFILES)
	group_files(SFILES ${CMAKE_CURRENT_SOURCE_DIR} NO sources)	
endif()
if(HFILES)
	group_files(HFILES ${CMAKE_CURRENT_SOURCE_DIR} NO headers)	
endif()
if(QRFILES)
	group_files(QRFILES ${CMAKE_CURRENT_SOURCE_DIR} NO resources)
endif()
if(GFILES)
	source_group(generated FILES ${GFILES})
endif()
# <- Группировка файлов
#...............................................................................
# Группировка подпроектов ->
if(SUBPROJECTS_ALL)
	group_projects(SUBPROJECTS AUTO)
endif()
# <- Группировка подпроектов
#...............................................................................
# install ->
if(USE_INSTALL)		
	if( (${USE_INSTALL} STREQUAL YES) OR (${USE_INSTALL} STREQUAL ON) OR (${USE_INSTALL} STREQUAL TRUE))
		if((NOT (${PROJECT_TYPE} STREQUAL STATIC_LIB)) AND (TARGET ${TARGET_NAME}))
			install(TARGETS ${TARGET_NAME} RUNTIME DESTINATION "./")
		endif()
	elseif(TARGET ${TARGET_NAME})		
		if(NOT (${PROJECT_TYPE} STREQUAL STATIC_LIB))
			install(TARGETS ${TARGET_NAME} RUNTIME DESTINATION "./${USE_INSTALL}")
		endif()
	elseif(${PROJECT_TYPE} STREQUAL AGGREGATION)
		set(CMAKE_INSTALL_PREFIX "${OUT_ROOT_DIR}/${OUT_INSTALL_DIR}")
	endif()
endif()
# <- install
#...............................................................................
# push up ->
if(THIS_SUB_PROJECT)
	set(CMAKEBIKES_TMP_SUBPROJECT_NAME ${PROJECT_NAME} PARENT_SCOPE)
	push_up_project_variables(${PROJECT_NAME})
endif()
# <- push up
#...............................................................................
message("\n<<<<<<<<<< [ ${PROJECT_NAME} ] <<<<<<<<<< \n")
# <- DEV
endmacro()
#===============================================================================