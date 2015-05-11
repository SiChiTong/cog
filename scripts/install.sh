#!/bin/bash
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

install()
{
    # download cog
    git clone $REPO_URL

    # make
    cd $REPO_NAME
    make

    # install
    if [ $# -eq 0 ]; then
        confirm_install
    elif [ "$@" == "--yes" ]; then
        sudo make install
    else
        echo "Invalid argument to install.sh!"
    fi
}

# RUN
install $1
