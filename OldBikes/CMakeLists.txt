# CMakeBikesLists v0.1 (необходимая подпись)
cmake_minimum_required (VERSION 2.8)
#-------------------------------------------------------------------------------
# Включение и инициализация CMakeBikes ->
CMakeBikes_init()
# <- Включение и инициализация CMakeBikes
#-------------------------------------------------------------------------------
# Имя проекта ->
project( OldBikes ) #${THIS_DIR})
# <- Имя проекта 
#-------------------------------------------------------------------------------
# Опции ->

set(PROJECT_TYPE			STATIC_LIB) # AUTO|EXECUTABLE|SHARED_LIB|STATIC_LIB|SHARED_OR_STATIC_LIB|HEADERS_LIB|AGGREGATION

set(REQUIRED_LIBS 			NO) # NO|[AUTO][DEPENDENCIES][PARENT_DEPENDENCIES][<REQUIRED_LIBS_LIST>]

set(REQUIRED_INCLUDE		NO)   # NO|[<REQUIRED_TARGETS_LIST>]

set(ADDITIONAL_INCLUDE_DIRS NO)   # NO|<INCLUDE_DIRS_LIST>

set(PRIVATE_DEFINITIONS 	NO)	  # NO|<DEFINITIONS_LIST>

set(USERS_INCLUDE 			AUTO) # NO|[AUTO][PUBLIC][PRIVATE][DEPENDENCIES][ADDITIONAL][<INCLUDE_DIRS_LIST>]

set(USERS_DEFINITIONS 		AUTO) # NO|[AUTO][STATIC_EXPORT][SHARED_EXPORT][PRIVATE][<DEFINITIONS_LIST>]

set(USE_PRECOMPILED_HEADER 	AUTO) # NO|AUTO|<HEADER_PATH>

set(USE_BOOST				ON)  # ON|OFF

set(USE_QT					OFF)  # ON|OFF|[ON][AUTOMOC][CORE][MAIN][GUI][OPENGL][SVG][XML][SQL][NETWORK][3SUPPORT][WEBKIT][HELP][TEST]

set(USE_INSTALL				OFF)  # ON|OFF|<INSTALL_PATH>

set(HINT_PUBLIC_INCLUDE_PREFIX Bikes)

# <- Опции
#-------------------------------------------------------------------------------
CMakeBikes_run()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

