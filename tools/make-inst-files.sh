#!/bin/bash
#
#
#
BASE_DIR=/opt/tols/ASM24
SRC_DIR=${BASE_DIR}/src
INST_DIR=${BASE_DIR}/src/instructions

INST_HEADER_TEMPLATE=${BASE_DIR}/inst-hdr.template
INST_CPP_TEMPLATE=${BASE_DIR}/inst-cpp.template
INST_SET_FILE=${SRC_DIR}/InstSet.h
TSNI_SET_FILE=${SRC_DIR}/InstSet.temp

INST_LOADER_FILE=${SRC_DIR}/InstLoader.h
TSNI_LOADER_FILE=${SRC_DIR}/InstLoader.temp

HEADER_FILE=""
CPP_FILE=""


DATE=`date +'%Y-%m-%d'`
HOUR=`date +'%H'`
INST=""
OPCODE=""



function CreateHeader()
{
HEADER_FILE=${INST_DIR}/${INST}Inst.h

        INST=${INST} DATE=${DATE} HOUR=${HOUR}  envsubst < ${INST_HEADER_TEMPLATE} > ${HEADER_FILE}
}



function CreateCPP()
{
CPP_FILE=${INST_DIR}/${INST}Inst.cpp

        INST=${INST} DATE=${DATE} HOUR=${HOUR}  envsubst < ${INST_CPP_TEMPLATE} > ${CPP_FILE}
}


function AddToLoaderFile()
{
        sed -i 's/\/\/NEXT_ENTRY/#include "${INST}Inst.h"\n\/\/NEXT_ENTRY/g' ${INST_LOADER_FILE}
        sed -i 's/\/\/NEXT_PUSH_BACK/\tthis->pISet->push_back(new ${INST}Inst);\n\/\/NEXT_PUSH_BACK/g' ${INST_LOADER_FILE}

        mv ${INST_LOADER_FILE} ${TSNI_LOADER_FILE}
        INST=${INST} envsubst < ${TSNI_LOADER_FILE} > ${INST_LOADER_FILE}
        rm -f ${TSNI_LOADER_FILE}
}



function AddToInstSet()
{
        sed -i 's/\/\/NEXT_ENTRY/\t${INST}\t=${OPCODE},\n\/\/NEXT_ENTRY/g' ${INST_SET_FILE}
        mv ${INST_SET_FILE} ${TSNI_SET_FILE}
        INST=${INST} OPCODE=${OPCODE}  envsubst < ${TSNI_SET_FILE} > ${INST_SET_FILE}
        rm -f ${TSNI_SET_FILE}
}


#==================================================
#
#                    M A I N
#
#==================================================

        echo " "
        echo "Enter the Instruction code"
        echo "Examples:"
        echo "NOP, LD, INC"
        echo -n "> "
        read RD_INST
        INST="${RD_INST^^}"
        echo " "
        echo "Enter the Opcode in Hexadecimal"
        echo "This CPU has 2 bits to define Inst. Type"
        echo " "
        echo "00-- ---- Type 0 Instruction - Miscellaneous 00-4f"
        echo "01-- ---- Type 1 Instruction - Moves to/from memory 50-7f"
        echo "10-- ---- Type 2 Instruction - Register operations 80-bf"
        echo "11-- ---- Type 3 Instruction - Jumps/Calls (+halt) c0-ff"
        echo " "
        echo -n "Enter the Opcode FORMAT is 0xFFFF >"
        read RD_OPCODE
        OPCODE="${RD_OPCODE,,}"

        CreateHeader
        CreateCPP
        AddToInstSet
        AddToLoaderFile

        echo "Header file [ ${HEADER_FILE} ]"
        echo "   CPP file [ ${CPP_FILE} ]"
        echo " "
        echo "Added to Instruction Set file [ ${INST_SET_FILE} ]"
        echo "Added to Instruction Loader file [ ${INST_LOADER_FILE} ]"
#
# End of file
