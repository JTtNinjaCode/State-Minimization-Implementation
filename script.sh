src_directory="./src"
input_directory="./input"
output_directory="./output"

mkdir -p "$output_directory"
g++ "$src_directory"/B11009054.cpp "$src_directory"/DotFileInfo.cpp "$src_directory"/KissFileInfo.cpp "$src_directory"/ReduceState.cpp "$src_directory"/StateLink.cpp -o "$output_directory"/B11009054

for i in "$input_directory"/*.kiss; do
    file_name=$(basename ${i%.*})
    ./output/B11009054 "$input_directory"/"$file_name".kiss "$output_directory"/"$file_name"_origin.dot "$output_directory"/"$file_name"_minimize.kiss "$output_directory"/"$file_name"_minimize.dot
    dot -T png "$output_directory"/"$file_name"_origin.dot > "$output_directory"/"$file_name"_origin.png
    dot -T png "$output_directory"/"$file_name"_minimize.dot > "$output_directory"/"$file_name"_minimize.png
done