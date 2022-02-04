#!/bin/bash
script_dir=$( dirname "$(readlink -f "$0")" )

export LD_LIBRARY_PATH=$script_dir/lib
export QT_PLUGIN_PATH=$script_dir/lib

echo $LD_LIBRARY_PATH
echo $QT_PLUGIN_PATH

out_file_name=~/.local/share/applications/Lethean.desktop

call_app()
{
  pushd $script_dir
  ./Lethean "$@"
  popd
  exit
}


create_desktop_icon()
{
    target_file_name=$1
    echo "Generating icon file: $target_file_name..."
    rm -f $target_file_name
    echo [Desktop Entry] | tee -a $target_file_name  > /dev/null
    echo Version=1.0 | tee -a $target_file_name  > /dev/null
    echo Name=Lethean | tee -a $target_file_name > /dev/null
    echo GenericName=Lethean | tee -a $target_file_name  > /dev/null
    echo Comment=Privacy blockchain | tee -a $target_file_name > /dev/null
    echo Icon=$script_dir/html/files/desktop_linux_icon.png | tee -a $target_file_name > /dev/null
    echo Exec=$script_dir/Lethean.sh %u | tee -a $target_file_name  > /dev/null
    echo Terminal=true | tee -a $target_file_name  > /dev/null
    echo Type=Application | tee -a $target_file_name  > /dev/null
    echo "Categories=Qt;Utility;" | tee -a $target_file_name  > /dev/null
    echo "MimeType=x-scheme-handler/lthn;" | tee -a $target_file_name  > /dev/null
}


create_desktop_icon $out_file_name

xdg-mime default Lethean.desktop x-scheme-handler/lthn

call_app "$@"