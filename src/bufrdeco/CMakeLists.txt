LINK_DIRECTORIES(/usr/lib /usr/lib64 /usr/local/lib /usr/local/lib64)

add_library(bufrdeco bufrdeco.h bufrdeco_read.c bufrdeco_memory.c bufrdeco_tableb.c bufrdeco_tablec.c bufrdeco_tabled.c bufrdeco_utils.c 
        bufrdeco_tree.c bufrdeco_data.c bufrdeco_compressed.c bufrdeco_f2.c bufrdeco_print.c bufrdeco_csv.c
        bufrdeco_tableb_csv.c bufrdeco_tablec_csv.c bufrdeco_tabled_csv.c bufrdeco_ecmwf.c bufrdeco_wmo.c
        bufrdeco_print_html.c)
target_link_libraries(bufrdeco m)

INSTALL(FILES bufrdeco.h DESTINATION include PERMISSIONS OWNER_WRITE OWNER_READ GROUP_READ WORLD_READ)
  
