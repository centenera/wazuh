#!/bin/bash
# Copyright (C) 2015, Wazuh Inc.
# buenos dias
# validate OS, linux or macos
if [ "X$(uname)" = "XLinux" ] ; then
    # Get Wazuh installation path
    SCRIPT=$(readlink -f "$0")
    WAZUH_HOME=$(dirname $(dirname $(dirname "$SCRIPT")))
    cd "${WAZUH_HOME}"
    (sleep 5 && chmod +x ./var/upgrade/src/init/*.sh && ./var/upgrade/src/init/pkg_installer.sh && find ./var/upgrade/* -not -name upgrade_result -delete) >/dev/null 2>&1 &
else
    (sleep 5 && chmod +x ./var/upgrade/*.sh && ./var/upgrade/pkg_installer_mac.sh && find ./var/upgrade/ -mindepth 1 -not -name upgrade_result -delete) >/dev/null 2>&1 &
fi
