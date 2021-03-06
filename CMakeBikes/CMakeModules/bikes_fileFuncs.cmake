#bikes_fileFuncs.cmake
#===============================================================================
function (get_curent_dir_name _CUR_DIR_NAME)
	get_filename_component(THIS_DIR ${CMAKE_CURRENT_SOURCE_DIR} NAME)
	set(${_CUR_DIR_NAME} ${THIS_DIR} PARENT_SCOPE)	
endfunction (get_curent_dir_name)
#===============================================================================
function (list_dirs LISTING_PATH OUT_DIR_LIST)
	set(DIRS)
	file(GLOB DIRFILES RELATIVE ${LISTING_PATH} ${LISTING_PATH}/*)
	foreach(df ${DIRFILES})
		if(IS_DIRECTORY ${LISTING_PATH}/${df})
			is_ignor_dir(${df} ignor)
			if(NOT ignor)
				set(DIRS ${DIRS} ${df})	
			endif()
		endif()		
	endforeach()
	set(${OUT_DIR_LIST} ${DIRS} PARENT_SCOPE)	
endfunction (list_dirs)
#===============================================================================
function(list_dirs_without_cmakelists in_listingPath out_dirList)
	set(DIRS)
	file(GLOB DIRFILES RELATIVE ${in_listingPath} ${in_listingPath}/*)
	foreach(df ${DIRFILES})
		if(IS_DIRECTORY ${in_listingPath}/${df})			
			is_ignor_dir(${df} ignor)
			if(NOT ignor)
				if(NOT (EXISTS ${in_listingPath}/${df}/CMakeLists.txt))
					set(DIRS ${DIRS} ${df})	
				endif()
			endif()
		endif()		
	endforeach()
	set(${out_dirList} ${DIRS} PARENT_SCOPE)	
endfunction()
#===============================================================================
function (find_dir _DIR_PATH _EXPECTED_DIR_NAMES _OUT_DIR_NAME)
	foreach(_dn ${${_EXPECTED_DIR_NAMES}})
		file(GLOB _DIRFILES RELATIVE ${_DIR_PATH} ${_DIR_PATH}/${_dn})		
	 	foreach(_df ${_DIRFILES})				
			if(IS_DIRECTORY ${_DIR_PATH}/${_df})					
				set(${_OUT_DIR_NAME} ${_df} PARENT_SCOPE)
				return()
			endif()
		endforeach()		
	endforeach()
	#set(${_OUT_DIR_NAME} NO PARENT_SCOPE)
endfunction (find_dir)
#===============================================================================
function (find_dirs _DIR_PATH _EXPECTED_DIR_NAMES _OUT_DIR_NAMES)
	set(_DIRS)
	foreach(_dn ${${_EXPECTED_DIR_NAMES}})
		file(GLOB _DIRFILES RELATIVE ${_DIR_PATH} ${_DIR_PATH}/${_dn})
	 	foreach(_df ${_DIRFILES})
			if(IS_DIRECTORY ${_DIR_PATH}/${_df})
				set(_DIRS ${_DIRS} ${_df})				
			endif()
		endforeach()
	endforeach()
	set(${_OUT_DIR_NAMES} ${_DIRS} PARENT_SCOPE)
endfunction (find_dirs)
#===============================================================================
function (find_files_at_path FILES_PATH FILES_NAME_LIST FILES_EXT_LIST RECURSE OUT_FILES_LIST)
	set(fs)
	if(RECURSE)
		set(R GLOB_RECURSE)
	else()
		set(R GLOB)
	endif()
	foreach(fn ${${FILES_NAME_LIST}})
		foreach(ext ${${FILES_EXT_LIST}})		
			if((${ext} STREQUAL *) AND (${fn} STREQUAL *))
				file(${R} DIRFILES "${FILES_PATH}/*")		
			else()
				file(${R} DIRFILES "${FILES_PATH}/${fn}.${ext}")
			endif()
			foreach(df ${DIRFILES})
				if(IS_DIRECTORY ${df})
				else()				
					set(fs ${fs} ${df})
				endif()			
			endforeach()
		endforeach()
	endforeach()
	set(${OUT_FILES_LIST} ${fs} PARENT_SCOPE)
endfunction()
#===============================================================================
function (is_ignor_dir DIR_NAME OUT_IGNOR)
	foreach(id ${HINT_IGNOR_DIRS})
		if(${id} STREQUAL ${DIR_NAME})
			set(${OUT_IGNOR} true PARENT_SCOPE) 
			return()
		endif()
	endforeach()
	set(${OUT_IGNOR} false PARENT_SCOPE) 
endfunction()
#===============================================================================
function (find_project_files FILES_PATH FILES_NAME_LIST FILES_EXT_LIST OUT_FILES)	
	set(FILES_LIST)
	find_files_at_path(${FILES_PATH} ${FILES_NAME_LIST} ${FILES_EXT_LIST} false FILES_LIST)
	#message(***)
	#message_list(FILES_LIST)
	#message(***)
	list_dirs(${FILES_PATH} DIRS)	
	foreach(d ${DIRS})		
		if(EXISTS ${FILES_PATH}/${d}/CMakeLists.txt)
		else()
			is_ignor_dir(${d} IGNOR)
			if(NOT IGNOR)				
				find_project_files("${FILES_PATH}/${d}" ${FILES_NAME_LIST} ${FILES_EXT_LIST} SUBDIR_FILES)
				set(FILES_LIST ${FILES_LIST} ${SUBDIR_FILES})
			endif()
		endif()
	endforeach()
	set(${OUT_FILES} ${FILES_LIST} PARENT_SCOPE)
endfunction()
#===============================================================================
function (get_files_dir_list  FILES_LIST  OUT_DIR_LIST)
	set(DIRS)
	foreach(f ${${FILES_LIST}})
		get_filename_component(p ${f} PATH)
		set(add true)
		foreach(d ${DIRS})
			if(${d} STREQUAL ${p})
				set(add false)
				break()
			endif()
		endforeach()
		if(add)
			set(DIRS ${DIRS} ${p})
		endif()
	endforeach()
	set(${OUT_DIR_LIST} ${DIRS} PARENT_SCOPE)
endfunction()
#===============================================================================
function(find_files_with_words FILES_LIST WORDS OUT_FILES_LIST)
set(fs)
foreach(f ${${FILES_LIST}})
	foreach(w ${${WORDS}})
		file(STRINGS ${f} str REGEX ${w})
		if(str)
			set(fs ${fs} ${f})
		endif()
	endforeach()
endforeach()
set(${OUT_FILES_LIST} ${fs} PARENT_SCOPE)
endfunction()
#===============================================================================
