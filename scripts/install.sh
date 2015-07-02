#!/bin/sh
set -e
REPO_NAME="cog"
REPO_URL="https://github.com/chutsu/cog.git"

confirm()
{
    read -p "$@ (y/n): " choice
    case "$choice" in
        y|Y ) echo "1";;
        n|N ) echo "0";;
        * ) echo "-1" ;;
    esac
}

confirm_install()
{
    DO_INSTALL=$(confirm "Are you sure you want to install $REPO_NAME?")
    if [ "$DO_INSTALL" == "1" ]; then
        sudo make install
    elif [ "$DO_INSTALL" == "-1" ]; then
        echo "Error invalid option! Please enter y or n!"
    else
        echo "Not installing $REPO_NAME ..."
    fi
}

download_and_make()
{
    # download cog
    git clone $REPO_URL

    # make
    cd $REPO_NAME
    make
}

run()
{
    if [ $# -eq 0 ]; then
        # download_and_make
        # confirm_install
        echo "confirm"
    elif [ "$@" == "--yes" ]; then
        # download_and_make
        # make install
        echo "yes"
    else
        echo "Invalid argument to install.sh!"
    fi
}

# RUN
run $1
