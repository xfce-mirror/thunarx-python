#!/bin/sh

THUNAR_INCLUDEDIR=`pkg-config --variable=includedir thunarx-2`/thunarx-2/thunarx
CODEGEN=`pkg-config --variable=codegendir pygtk-2.0`/h2def.py

python $CODEGEN ${THUNAR_INCLUDEDIR}/*.h > thunarx.defs
#python $CODEGEN ${THUNAR_INCLUDEDIR}/thunarx-file-info.h >> thunarx.defs
#python $CODEGEN "${THUNAR_INCLUDEDIR}/thunarx-preferences-provider.h" >> thunarx.defs
#python $CODEGEN "${THUNAR_INCLUDEDIR}/thunarx-property-page.h" >> thunarx.defs
#python $CODEGEN "${THUNAR_INCLUDEDIR}/thunarx-property-page-provider.h" >> thunarx.defs
#python $CODEGEN "${THUNAR_INCLUDEDIR}/thunarx-provider-factory.h" >> thunarx.defs
#python $CODEGEN "${THUNAR_INCLUDEDIR}/thunarx-provider-plugin.h" >> thunarx.defs
#python $CODEGEN "${THUNAR_INCLUDEDIR}/thunarx-renamer.h" >> thunarx.defs
#python $CODEGEN "${THUNAR_INCLUDEDIR}/thunarx-renamer-provider.h" >> thunarx.defs


sed -i 's|define-object|define-interface|g' thunarx.defs
