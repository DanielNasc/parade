# Script para compilar todos os arquivos .c do projeto e linka-los em um único arquivo .o

# Lista com todos os arquivos .c do projeto
Set-Variable -Name "files" -Value (
    Get-ChildItem -Path ".\" -Filter "*.c" -Recurse |
    ForEach-Object { $_.Name }     
)

Set-Variable -Name "filesWithoutExtension" -Value (
    Get-ChildItem -Path ".\" -Filter "*.c" -Recurse |
    ForEach-Object { $_.Name.Replace(".c", "") }     
)

# Compila todos os arquivos .c do projeto

for ($i = 0; $i -lt $files.Count; $i++) {
    $file = $files[$i]
    $fileWithoutExtension = $filesWithoutExtension[$i]

    Write-Output "Compilando $file"
    gcc -c $file -lm -o ($fileWithoutExtension + ".o")
}

Write-Output "`n` `n`Linkando arquivos .o `n` `n` "

# Linka todos os arquivos .o em um único arquivo .o

$compiledFiles = (
    Get-ChildItem -Path ".\" -Filter "*.o" -Recurse |
    ForEach-Object { $_.Name }     
)

gcc -o parade.exe $compiledFiles -lm

# Remove todos os arquivos .o

for ($i = 0; $i -lt $compiledFiles.Count; $i++) {
    $file = $compiledFiles[$i]
    Write-Output "Removendo $file"
    Remove-Item -Path $file -Force
}