#define CATCH_CONFIG_RUNNER
#include "catch/catch.hpp"

#include "game.h"
#include "init.h"
#include "map.h"
#include "morale.h"
#include "path_info.h"
#include "player.h"
#include "worldfactory.h"

void init_global_game_state() {
    PATH_INFO::init_base_path("");
    PATH_INFO::init_user_dir("./");
    PATH_INFO::set_standard_filenames();

    initOptions();
    load_options();
    init_colors();

    g = new game;

    g->load_static_data();
    g->load_core_data();
    DynamicDataLoader::get_instance().finalize_loaded_data();

    world_generator->set_active_world(NULL);
    world_generator->get_all_worlds();
    WORLDPTR test_world = world_generator->make_new_world( false );
    world_generator->set_active_world(test_world);

    g->u = player();
    g->u.create(PLTYPE_NOW);
    g->m.load( g->get_levx(), g->get_levy(), g->get_levz(), false );
}

int main( int argc, char* const argv[] )
{
  // TODO: Only init game if we're running tests that need it.
  init_global_game_state();

  int result = Catch::Session().run( argc, argv );

  return result;
}
