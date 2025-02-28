/*
 * Copyright (C) 2023 Paranoid Android
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <cstdlib>
#include <fstream>
#include <string.h>
#include <unistd.h>
#include <vector>

#include <android-base/properties.h>
#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include <sys/_system_properties.h>
#include <sys/sysinfo.h>

#include "property_service.h"
#include "vendor_init.h"

using android::base::GetProperty;
using std::string;

std::vector<std::string> ro_props_default_source_order = {
    "",
    "odm.",
    "odm_dlkm.",
    "product.",
    "system.",
    "system_ext.",
    "vendor.",
    "vendor_dlkm.",
};

void property_override(string prop, string value)
{
    auto pi = (prop_info*) __system_property_find(prop.c_str());

    if (pi != nullptr)
        __system_property_update(pi, value.c_str(), value.size());
    else
        __system_property_add(prop.c_str(), prop.size(), value.c_str(), value.size());
}

void load_redmi_fog() {
    property_override("bluetooth.device.default_name", "Redmi 10C");
    property_override("ro.product.brand", "Redmi");
    property_override("ro.product.device", "fog");
    property_override("ro.product.manufacturer", "Xiaomi");
    property_override("ro.product.model", "Redmi 10C");
    property_override("ro.product.mod_device", "fog_global");
    property_override("ro.product.name", "fog_global");
    property_override("vendor.usb.product_string", "Redmi 10C");
}

void load_redmi_fog_in() {
    property_override("bluetooth.device.default_name", "Redmi 10");
    property_override("ro.product.brand", "Redmi");
    property_override("ro.product.device", "fog");
    property_override("ro.product.manufacturer", "Xiaomi");
    property_override("ro.product.model", "Redmi 10");
    property_override("ro.product.mod_device", "fog_in");
    property_override("ro.product.name", "fog_in");
    property_override("vendor.usb.product_string", "Redmi 10");
}

void load_redmi_fog_in2() {
    property_override("bluetooth.device.default_name", "Redmi 10 Power");
    property_override("ro.product.brand", "Redmi");
    property_override("ro.product.device", "fog");
    property_override("ro.product.manufacturer", "Xiaomi");
    property_override("ro.product.model", "Redmi 10 Power");
    property_override("ro.product.mod_device", "fog_in2");
    property_override("ro.product.name", "fog_in2");
    property_override("vendor.usb.product_string", "Redmi 10 Power");
}

void load_redmi_rain() {
    property_override("bluetooth.device.default_name", "Redmi 10C");
    property_override("ro.product.brand", "Redmi");
    property_override("ro.product.device", "rain");
    property_override("ro.product.manufacturer", "Xiaomi");
    property_override("ro.product.model", "Redmi 10C");
    property_override("ro.product.mod_device", "rain_global");
    property_override("ro.product.name", "rain_global");
    property_override("vendor.usb.product_string", "Redmi 10C");
}

void load_redmi_wind() {
    property_override("bluetooth.device.default_name", "Redmi 10C");
    property_override("ro.product.brand", "Redmi");
    property_override("ro.product.device", "wind");
    property_override("ro.product.manufacturer", "Xiaomi");
    property_override("ro.product.model", "Redmi 10C");
    property_override("ro.product.mod_device", "wind_global");
    property_override("ro.product.name", "wind_global");
    property_override("vendor.usb.product_string", "Redmi 10C");
}

void vendor_load_properties() {
    std::string hwname = GetProperty("ro.boot.hwname", "");
    if (access("/system/bin/recovery", F_OK) != 0) {
    if (hwname == "fog_in") {
        load_redmi_fog_in();
    } else if (hwname == "fog") {
        load_redmi_fog();
    } else if (hwname == "rain") {
        load_redmi_rain();
    } else if (hwname == "wind") {
        load_redmi_wind();
    } else {
        load_redmi_fog_in2();
       }
    }

    // Set hardware revision
    property_override("ro.boot.hardware.revision", GetProperty("ro.boot.hwversion", "").c_str());

    // Set dalvik heap configuration
    std::string heapstartsize, heapgrowthlimit, heapsize, heapminfree,
			heapmaxfree, heaptargetutilization;

    struct sysinfo sys;
    sysinfo(&sys);

    property_override("dalvik.vm.heapstartsize", "8m");
    property_override("dalvik.vm.heapgrowthlimit", "128m");
    property_override("dalvik.vm.heapsize", "256m");
    property_override("dalvik.vm.heaptargetutilization", "0.75");
    property_override("dalvik.vm.heapminfree", "512k");
    property_override("dalvik.vm.heapmaxfree", "8m");
    // SafetyNet workaround
    property_override("ro.oem_unlock_supported", "0");
    property_override("ro.boot.verifiedbootstate", "green");
    // ART lowmem
    property_override("ro.config.art_lowmem", "true");
}