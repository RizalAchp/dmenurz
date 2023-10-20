#define CB_IMPLEMENTATION
#include "cb.h"

#define VERSION  "5.2"
#define CINCLUDE "/usr/X11R6/include", "/usr/include/freetype2"
#define CFLAGS   "-std=c99", "-pedantic", "-Wall", "-Os"
#define CDEFS    "_DEFAULT_SOURCE", "_BSD_SOURCE", "_XOPEN_SOURCE=700", "_POSIX_C_SOURCE=200809L", "VERSION=\"" VERSION "\"", "XINERAMA"
#define LDFLAGS  "-L/usr/X11R6/lib", "-lX11", "-lXinerama", "-lfontconfig", "-lXft", "-lm"

static cb_path_t   PREFIX = {0};

static cb_status_t on_configure_dmenu(cb_t *cb) {
    cb_status_t  result       = CB_OK;
    cb_target_t *dmenu_target = cb_create_exec(cb, "dmenu");
    result &= cb_target_add_includes(dmenu_target, CINCLUDE, NULL);
    result &= cb_target_add_defines(dmenu_target, CDEFS, NULL);
    result &= cb_target_add_flags(dmenu_target, CFLAGS, NULL);
    result &= cb_target_add_ldflags(dmenu_target, LDFLAGS, NULL);

    result &= cb_target_add_sources(dmenu_target, "./drw.c", "./dmenu.c", "./util.c", NULL);

    return result;
}
static cb_status_t on_configure_stests(cb_t *cb) {
    cb_status_t  result        = CB_OK;
    cb_target_t *stests_target = cb_create_exec(cb, "stest");
    result &= cb_target_add_includes(stests_target, CINCLUDE, NULL);
    result &= cb_target_add_defines(stests_target, CDEFS, NULL);
    result &= cb_target_add_flags(stests_target, CFLAGS, NULL);
    result &= cb_target_add_ldflags(stests_target, LDFLAGS, NULL);
    result &= cb_target_add_sources(stests_target, "./stest.c", NULL);

    return result;
}

static cb_status_t on_pre_install(cb_t *cb, cb_config_t *cfg) {
    (void)cb;
    cb_status_t result = CB_OK;
    result &= cb_config_set_install_prefix(cfg, PREFIX);
    if (memcmp(g_cfg.install_prefix.data, "/usr", sizeof("/usr") - 1) == 0) {
        if (getuid() != 0) CB_BAIL_ERROR(return CB_ERR, "Command install requires Admin Privilages!");
    }
    if (result == CB_OK) {
        result &= cb_mkdir_if_not_exists(cb_path_to_cstr(&g_cfg.install_prefix), true);
        result &= cb_mkdir_if_not_exists(cb_path_to_cstr(&g_cfg.bin_install_dir), false);
        result &= cb_mkdir_if_not_exists(cb_path_to_cstr(&g_cfg.lib_install_dir), false);
    }

    return result;
}

static cb_status_t on_post_install(cb_t *cb, cb_config_t *cfg) {
    cb_status_t result = CB_OK;

    result &= cb_chmod("./dmenu_run", 0755);
    result &= cb_chmod("./dmenu_path", 0755);

    cb_path_t dmenu_run = {0};
    cb_path_copy(&dmenu_run, cfg->bin_install_dir);
    result &= cb_path_append_cstr(&dmenu_run, "dmenu_run");

    cb_path_t dmenu_path = {0};
    cb_path_copy(&dmenu_path, cfg->bin_install_dir);
    result &= cb_path_append_cstr(&dmenu_path, "dmenu_path");

    result &= cb_copy_file(cb_path_to_cstr(&dmenu_path), "./dmenu_path");
    result &= cb_copy_file(cb_path_to_cstr(&dmenu_run), "./dmenu_run");

    return result;
}

cb_status_t on_configure(cb_t *cb, cb_config_t *cfg) {
    (void)cfg;
    cb_status_t result = CB_OK;

    result &= on_configure_dmenu(cb);
    result &= on_configure_stests(cb);
    return result;
}

int main(int argc, char *argv[]) {
    CB_REBUILD_SELF(argc, argv, "./cb.h");
    int result = EXIT_SUCCESS;

    PREFIX     = cb_path("/usr/local");
    cb_t *cb   = cb_init(argc, argv);
    // cb_add_on_post_install_callback()
    cb_add_on_pre_install_callback(cb, on_pre_install);
    cb_add_on_post_install_callback(cb, on_post_install);

    if (cb_run(cb) == CB_ERR) cb_return_defer(EXIT_FAILURE);

defer:
    if (cb) cb_deinit(cb);
    return result;
}
