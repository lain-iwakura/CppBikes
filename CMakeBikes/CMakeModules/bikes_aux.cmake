#bikes_aux.cmake
#===============================================================================
function(get_sub_project_flag SUB_PROJECT_FLAG)	
	if(${CMAKE_CURRENT_SOURCE_DIR} STREQUAL ${CMAKE_SOURCE_DIR})
		set(${SUB_PROJECT_FLAG} false PARENT_SCOPE)
	else()
		set(${SUB_PROJECT_FLAG} true PARENT_SCOPE)
	endif()
endfunction()

#===============================================================================
function(get_public_include_dirs _PRIVATE_INCLUDE_DIRS PUBLIC_INCLUDE_PREFIX_LIST OUT_PUBLIC_INCLUDE_DIRS)
	set(DIRS)
	list(REMOVE_DUPLICATES ${PUBLIC_INCLUDE_PREFIX_LIST})
	set(pdirs)
	foreach(pref ${${PUBLIC_INCLUDE_PREFIX_LIST}})
		string(TOLOWER ${pref} pref)
		foreach(d ${${_PRIVATE_INCLUDE_DIRS}})	
			find_files_at_path(${d} ANYFILE HINT_EXT_HEADERS NO fs)			
			if(fs)				
				get_filename_component(dn ${d} NAME)
				string(TOLOWER ${dn} dn)			
				if(${dn} STREQUAL ${pref})
					get_filename_component(p ${d} PATH)
					set(pdirs ${pdirs} ${d})
					set(DIRS ${DIRS} ${p})
				else()
					set(DIRS ${DIRS} ${d})
				endif()		
			else()
				set(DIRS ${DIRS} ${d})
			endif()
		endforeach()
	endforeach()
	
	set(pidirs)
	foreach(d ${DIRS})
		set(inc true)
		foreach(pd ${pdirs})		
			string(FIND ${d} ${pd} f)
			if(NOT (${f} EQUAL -1))	
				set(inc false)
				break()
			endif()			
		endforeach()
		if(inc)
			set(pidirs ${pidirs} ${d})
		endif()
	endforeach()
	
	if(pidirs)
		list(REMOVE_DUPLICATES pidirs)
	else()
		# ?
	endif()		
	
	set(${OUT_PUBLIC_INCLUDE_DIRS} ${pidirs} PARENT_SCOPE)	
endfunction()
#===============================================================================
#===============================================================================
macro(push_up in_var)
set(${in_var} ${${in_var}} PARENT_SCOPE)
endmacro()
#-------------------------------------------------------------------------------
macro(push_up_project_variables in_projectName)	
		get_all_subproject_list(${in_projectName} spl)
		foreach(p ${spl} ${in_projectName})
			push_up(CMAKEBIKES_${p}_EXEC_LIST)
			push_up(CMAKEBIKES_${p}_LIB_LIST)					
			push_up(CMAKEBIKES_${p}_TARGET_LIST)
			push_up(CMAKEBIKES_${p}_SUBPROJECT_LIST)
			push_up(CMAKEBIKES_${p}_USERS_INCLUDE_DIRS)
			push_up(CMAKEBIKES_${p}_USERS_INCLUDE_LIBS)
			push_up(CMAKEBIKES_${p}_USERS_DEFINITIONS)			
			foreach(t ${CMAKEBIKES_${p}_TARGET_LIST})
				push_up(CMAKEBIKES_${t}_REQUIRED_INCLUDE)
				push_up(CMAKEBIKES_${t}_USERS_INCLUDE_DIRS)
				push_up(CMAKEBIKES_${p}_USERS_INCLUDE_LIBS)
				push_up(CMAKEBIKES_${t}_USERS_DEFINITIONS)
			endforeach()
		endforeach()
endmacro()
#===============================================================================
function(get_subvariables_list in_list in_prefix in_postfix out_subvarList)
	set(svl)
	if(NOT in_prefix)
		set(in_prefix)
	endif()
	if(NOT in_postfix)
		set(in_postfix)
	endif()
	foreach(v ${${in_list}})
		set(svl ${svl} ${${in_prefix}${v}${in_postfix}})		
	endforeach()
	set(${out_subvarList} ${svl} PARENT_SCOPE)
endfunction()
#===============================================================================
function(get_all_subvariables_list in_list in_rListPrefix in_rListPostfix out_subvarList)
	set(RLIST ${${out_subvarList}})
	if(NOT in_rListPrefix)
		set(in_rListPrefix)
	endif()
	if(NOT in_rListPostfix)
		set(in_rListPostfix)
	endif()
	foreach(i ${${in_list}})		
		set(RLIST ${RLIST} ${i})
		set(rL ${${in_rListPrefix}${i}${in_rListPostfix}})	
		if(rL)
			list(REMOVE_ITEM rL ${RLIST})
			if(rL)
				set(sl ${RLIST})
				get_all_subvariables_list(rL ${in_rListPrefix} ${in_rListPostfix} sl)
				set(RLIST ${sl})
			endif()
		endif()		
	endforeach()
	if(RLIST)
		list(REMOVE_DUPLICATES RLIST)
	endif()
	set(${out_subvarList} ${RLIST} PARENT_SCOPE)
endfunction()
#===============================================================================
function(get_all_subproject_list in_projectName out_subprojects)
	set(spl)	
	if(CMAKEBIKES_${in_projectName}_SUBPROJECT_LIST)
		get_all_subvariables_list(CMAKEBIKES_${in_projectName}_SUBPROJECT_LIST CMAKEBIKES_ _SUBPROJECT_LIST spl)
	endif()
	set(${out_subprojects} ${spl} PARENT_SCOPE)
endfunction()
#===============================================================================
function(add_some_subdirectory in_dirPath	out_successfully)
	set(CMAKEBIKES_TMP_SUBPROJECT_NAME)
	get_filename_component(in_dirPath ${in_dirPath} ABSOLUTE)
	set(suc)
	if(EXISTS ${in_dirPath}/CMakeLists.txt)
		is_alien_dir(${in_dirPath} alien)
		if(alien)
			add_alien_subdirectory(${in_dirPath} suc)			
		else()
			add_subdirectory(${in_dirPath})
			set(suc YES)
		endif()
	else()
		set(suc NO)
	endif()
	
	if(suc)
		if(CMAKEBIKES_TMP_SUBPROJECT_NAME)
			push_up(CMAKEBIKES_TMP_SUBPROJECT_NAME)			
			push_up_project_variables(${CMAKEBIKES_TMP_SUBPROJECT_NAME})
		else()
			set(suc NO)
		endif()
	endif()
	
	set(${out_successfully} ${suc} PARENT_SCOPE)
endfunction()
#===============================================================================
function(add_subdirs in_pathList in_recurse out_subProjects)
	set(subp)
	foreach(in_path ${${in_pathList}})		
		get_filename_component(in_path ${in_path} ABSOLUTE)
		list_dirs(${in_path} ds)		
		foreach(d ${ds})
			if(EXISTS ${in_path}/${d}/CMakeLists.txt)
				add_some_subdirectory(${in_path}/${d} suc)
				if(suc)
					set(subp ${subp} ${CMAKEBIKES_TMP_SUBPROJECT_NAME})						
				endif()
			elseif(in_recurse)
				add_subdirs(${in_path}/${d} YES subProjects)
				set(subp ${subp} ${subProjects})
			endif()
		endforeach()

		foreach(sp ${subp})
			push_up_project_variables(${sp})
		endforeach()
	endforeach()
	set(${out_subProjects} ${subp} PARENT_SCOPE)
endfunction()
#===============================================================================
function (group_files FILES_LIST GROUPING_PATH ROOT_GROUP DEF_GROUP)
	foreach(f ${${FILES_LIST}})
		get_filename_component(DIR ${f} PATH)
		file(GLOB RPATH RELATIVE ${GROUPING_PATH} ${DIR})
		set(groop)
		if(RPATH)
			string(REGEX REPLACE "/" "\\\\" SUBGROUP ${RPATH})			
			if(ROOT_GROUP)
				if(SUBGROUP)
					set(groop ${ROOT_GROUP}\\${SUBGROUP})
				else()
					set(groop ${ROOT_GROUP})
				endif()
			else()
				set(groop ${SUBGROUP})
			endif()
		endif()
		
		if(groop)			
			source_group(${groop} FILES ${f})
		elseif(DEF_GROUP)
			source_group(${DEF_GROUP} FILES ${f})
		endif()
	endforeach()
endfunction()
#===============================================================================
function(group_projects in_projects in_rootFolder)
	foreach(rp ${${in_projects}})
		get_all_subproject_list(${rp} spl)	
		set(rpspl ${rp} ${spl})		
		get_subvariables_list(rpspl CMAKEBIKES_ _TARGET_LIST allTargets)		
		if(allTargets)
			list(REMOVE_DUPLICATES allTargets)
			list(LENGTH allTargets tcount)
		else()
			set(tcount 0)
		endif()
		
		if(${tcount} GREATER 1)
			set(f ${${rp}_SOURCE_DIR})			
		else()			
			get_filename_component(f "${${rp}_SOURCE_DIR}/.." ABSOLUTE)			
		endif()
		
		if(${in_rootFolder} STREQUAL AUTO)
			if(f)
				file(RELATIVE_PATH rf ${CMAKE_CURRENT_SOURCE_DIR} ${f})
				if((NOT rf) AND (NOT THIS_SUB_PROJECT))
					set(rf root)
				else()
					get_filename_component(f "${${rp}_SOURCE_DIR}/.." ABSOLUTE)	
					file(RELATIVE_PATH rf_ ${CMAKE_CURRENT_SOURCE_DIR} ${f})
					if((NOT rf_) AND (NOT THIS_SUB_PROJECT))
						set(rf root/${rf})
					endif()
				endif()
			else()
				set(rf)
			endif()
			#string(REGEX REPLACE "/" "\\\\" rf ${rf})
		else()
			set(rf ${in_rootFolder})
		endif()		
		
		if(rf)
			foreach(t ${allTargets})
				if(TARGET ${t})
					get_property(sf TARGET ${t} PROPERTY FOLDER)
					if(sf)						
						set_property(TARGET ${t} PROPERTY FOLDER ${rf}/${sf})
					else()
						set_property(TARGET ${t} PROPERTY FOLDER ${rf})
					endif()
				endif()
			endforeach()		
		endif()	
		
	endforeach()	
endfunction()
#===============================================================================
macro(get_required_include_dirs in_linkList out_requiredIncludeDirs out_libsWithoutIncludeDirs)
set(RLIST)
get_required_include_dirs_(${in_linkList} ${out_requiredIncludeDirs} ${out_libsWithoutIncludeDirs})
endmacro()
#-------------------------------------------------------------------------------
function(get_required_include_dirs_ in_linkList out_requiredIncludeDirs out_libsWithoutIncludeDirs)
	set(includeDirs)
	set(badLibs)	
	foreach(lib ${${in_linkList}})
		set(RLIST ${RLIST} ${lib})
		if(CMAKEBIKES_${lib}_USERS_INCLUDE_DIRS OR CMAKEBIKES_${lib}_USERS_INCLUDE_LIBS)
			set(includeDirs ${includeDirs} ${CMAKEBIKES_${lib}_USERS_INCLUDE_DIRS})			
			set(uil ${CMAKEBIKES_${lib}_USERS_INCLUDE_LIBS})
			if(uil)
				list(REMOVE_ITEM uil ${RLIST})
				if(uil)
					get_required_include_dirs(uil rdirs rlibs)
					set(includeDirs ${includeDirs} ${rdirs})
					set(badLibs ${badLibs} ${rlibs})
				endif()
			endif()
		else()
			set(badLibs ${badLibs} ${lib})
		endif()
	endforeach()
	if(includeDirs)
		list(REMOVE_DUPLICATES includeDirs)
		set(${out_requiredIncludeDirs} ${includeDirs} PARENT_SCOPE)
	else()
		set(${out_requiredIncludeDirs} PARENT_SCOPE)
	endif()
	set(${out_libsWithoutIncludeDirs} ${badLibs} PARENT_SCOPE)
	if(RLIST)
		list(REMOVE_DUPLICATES RLIST)
	endif()
	push_up(RLIST)
endfunction()
#===============================================================================
function(get_required_definitions in_linkList out_requiredDefinitions)	
	set(rDef)
	set(all_libs)		
	get_all_subvariables_list(${in_linkList} CMAKEBIKES_ _USERS_INCLUDE_LIBS all_libs)		
	get_subvariables_list(all_libs CMAKEBIKES_ _USERS_DEFINITIONS rDef)	
	set(${out_requiredDefinitions} ${rDef} PARENT_SCOPE)
endfunction()
#===============================================================================
macro(ifndef_set var)	
	if(NOT ${var})
		set(${var} ${ARGN})
	endif()
endmacro()
#===============================================================================
macro(ifnodef_set var)
	if(NOT (DEFINED ${var}))
		set(${var} ${ARGN})
	endif()
endmacro()
#===============================================================================














