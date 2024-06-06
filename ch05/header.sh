# generate_header.sh
output_file="./all_class_headers.h"
echo "#ifndef ALL_CLASS_HEADERS_H" > $output_file
echo "#define ALL_CLASS_HEADERS_H" >> $output_file

for header in classfile/*.h; do
    echo "#include \"$header\"" >> $output_file
done

echo "#endif // ALL_CLASS_HEADERS_H" >> $output_file
