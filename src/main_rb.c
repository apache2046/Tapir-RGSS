#include <ruby.h>
#include "main_rb.h"

#if RGSS == 3
#define RGSS_RESET "RGSSReset"
#define TERMS "Terms"
#define SCRIPT_PATH "\"Data/Scripts.rvdata2\""
#elif RGSS == 2
#define RGSS_RESET "Reset"
#define TERMS "Terms"
#define SCRIPT_PATH "\"Data/Scripts.rvdata\""
#else
#define RGSS_RESET "Reset"
#define TERMS "Words"
#define SCRIPT_PATH "\"Data/Scripts.rxdata\""
#endif

VALUE main_rb(VALUE data) {
  (void) data;
  rb_eval_string(
#if RGSS < 3
      "$KCODE = \"u\"\n"
#endif
      "module Audio\n"
#if RGSS == 3
      "  def self.setup_midi\n"
      "  end\n"
#endif
#if RGSS == 3
      "  def self.bgm_play(path, volume=nil, pitch=nil, pos=nil)\n"
      "  end\n"
#else
      "  def self.bgm_play(path, volume=nil, pitch=nil)\n"
      "  end\n"
#endif
      "  def self.bgm_stop\n"
      "  end\n"
      "  def self.bgm_fade(time)\n"
      "  end\n"
#if RGSS == 3
      "  def self.bgm_pos\n"
      "    0\n"
      "  end\n"
#endif
#if RGSS == 3
      "  def self.bgs_play(path, volume=nil, pitch=nil, pos=nil)\n"
      "  end\n"
#else
      "  def self.bgs_play(path, volume=nil, pitch=nil)\n"
      "  end\n"
#endif
      "  def self.bgs_stop\n"
      "  end\n"
      "  def self.bgs_fade(time)\n"
      "  end\n"
#if RGSS == 3
      "  def self.bgs_pos\n"
      "    0\n"
      "  end\n"
#endif
      "  def self.me_play(path, volume=nil, pitch=nil)\n"
      "  end\n"
      "  def self.me_stop\n"
      "  end\n"
      "  def self.me_fade(time)\n"
      "  end\n"
      "  def self.se_play(path, volume=nil, pitch=nil)\n"
      "  end\n"
      "  def self.se_stop\n"
      "  end\n"
      "end\n"
      "class Bitmap\n"
      "  attr_accessor :font\n"
      "  def font\n"
      "    if !@font\n"
      "      @font = Font.new\n"
      "    end\n"
      "    @font\n"
      "  end\n"
      "  def blur\n"
      "  end\n"
      "  def clear_rect(rect)\n"
      "  end\n"
      "  def draw_text(rect, text, foo=0)\n"
      "  end\n"
      "  def fill_rect(rect, color)\n"
      "  end\n"
      "  def get_pixel(x, y)\n"
      "    Color.new(0.0, 0.0, 0.0, 0.0)\n"
      "  end\n"
      "  def clear\n"
      "  end\n"
      "  def dispose\n"
      "  end\n"
      "end\n"
      "class Font\n"
      "  attr_accessor :color, :size\n"
      "  def initialize\n"
      "    @color = Color.new(0.0, 0.0, 0.0, 0.0)\n"
      "  end\n"
      /* TODO: Font.exist? */
      "  def self.exist?(name)\n"
      "    true\n"
      "  end\n"
      "end\n"
      "module Graphics\n"
      "  def self.frame_reset\n"
      "  end\n"
      "  def self.frame_count=(count)\n"
      "  end\n"
      "  def self.transition(frames = nil)\n"
      "  end\n"
      "  def self.wait(duration)\n"
      "  end\n"
      "  def self.fadeout(duration)\n"
      "  end\n"
      /* TODO: Graphics.freeze */
      "  def self.freeze\n"
      "  end\n"
      "  def self.snap_to_bitmap\n"
      "    Bitmap.new(width, height)\n"
      "  end\n"
      "end\n"
      "class Plane\n"
      "  attr_accessor :z\n"
      "  def initialize(viewport=nil)\n"
      "  end\n"
      "end\n"
      "class Sprite\n"
      "  def update\n"
      "  end\n"
      "end\n"
      "class Tilemap\n"
#if RGSS >= 2
      "  attr_accessor :bitmaps\n"
      "  def initialize(viewport=nil)\n"
      "    @bitmaps = [nil] * 9\n"
      "  end\n"
#else
      "  attr_accessor :autotiles, :map_data, :priorities, :tileset\n"
      "  def initialize(viewport=nil)\n"
      "    @autotiles = [nil, nil, nil, nil, nil, nil]\n"
      "  end\n"
#endif
      "end\n"

      "class Window\n"
      "  attr_accessor :active, :back_opacity, :contents, :contents_opacity, :cursor_rect, :height, :opacity, :openness, :oy, :padding, :padding_bottom, :tone, :visible, :width, :windowskin, :x, :y, :z\n"
      "  def dispose\n"
      "  end\n"
      "  def openness=(newval)\n"
      "    @openness = [[0, newval].max, 255].min\n"
      "  end\n"
      "  def open?\n"
      "    @openness == 255\n"
      "  end\n"
      "  def update\n"
      "  end\n"
      "  def initialize(*args)\n"
      "    @cursor_rect = Rect.new(0, 0, 0, 0)\n"
      "    @contents = Bitmap.new(0, 0)\n"
      "    @oy = 0\n"
      "    @width = 0\n"
      "    @height = 0\n"
      "    @tone = Tone.new(0.0, 0.0, 0.0, 0.0)\n"
      "    @openness = 255\n"
      "  end\n"
      "end\n"
      "\n"
      "module RPG\n"
      "  class Actor\n"
      "    attr_accessor :character_name, :class_id, :initial_level, :name\n"
#if RGSS == 3
      "    attr_accessor :character_index, :equips, :face_index, :face_name, :features, :nickname\n"
#elif RGSS == 2
      "    attr_accessor :armor1_id, :armor2_id, :armor3_id, :armor4_id, :exp_basis, :exp_inflation, :character_index, :face_index, :face_name, :parameters, :weapon_id\n"
#elif RGSS == 1
      "    attr_accessor :armor1_id, :armor2_id, :armor3_id, :armor4_id, :battler_hue, :battler_name, :character_hue, :exp_basis, :exp_inflation, :final_level, :parameters, :weapon_id\n"
#endif
      "  end\n"
      "  class AudioFile\n"
#if RGSS == 1
      "    attr_accessor :name, :pitch, :volume\n"
#endif
      "  end\n"
#if RGSS >= 2
      "  class BGM < AudioFile\n"
      "    def play\n"
      "    end\n"
      "    def self.stop\n"
      "    end\n"
      "    def self.fade(time)\n"
      "    end\n"
      "  end\n"
      "  class BGS < AudioFile\n"
      "    def self.stop\n"
      "    end\n"
      "  end\n"
      "  class ME < AudioFile\n"
      "    def self.stop\n"
      "    end\n"
      "  end\n"
#endif
      "  class Animation\n"
      "    class Frame\n"
      "    end\n"
      "    class Timing\n"
      "    end\n"
      "  end\n"
#if RGSS == 2
      "  class Area\n"
      "  end\n"
#endif
      "  class Armor\n"
#if RGSS == 3
      "    attr_accessor :features\n"
#elif RGSS == 2
#elif RGSS == 1
      "    attr_accessor :auto_state_id\n"
#endif
      "  end\n"
#if RGSS == 3
      "  module BaseItem\n"
      "    class Feature\n"
      "      attr_accessor :code\n"
      "    end\n"
      "  end\n"
#endif
#if RGSS == 1
      "  module Cache\n"
      /* TODO: RPG::Cache.title */
      "    def self.autotile(autotile_name)\n"
      "    end\n"
      "    def self.character(character_name, character_hue)\n"
      "    end\n"
      "    def self.title(title_name)\n"
      "    end\n"
      "    def self.tileset(tileset_name)\n"
      "    end\n"
      "    def self.windowskin(windowskin_name)\n"
      "    end\n"
      "  end\n"
#endif
      "  class Class\n"
      "    attr_accessor :learnings\n"
#if RGSS == 3
      "    attr_accessor :features\n"
      "    def exp_for_level(level)\n"
      // TODO: correct exp_for_level implementation
      "      1\n"
      "    end\n"
#elif RGSS == 2
#elif RGSS == 1
#endif
      "    class Learning\n"
      "      attr_accessor :level\n"
#if RGSS == 3
      "      attr_accessor :skill_id\n"
#elif RGSS == 2
#elif RGSS == 1
      "      attr_accessor :skill_id\n"
#endif
      "    end\n"
      "  end\n"
      "  class CommonEvent\n"
#if RGSS == 3
      "    def autorun?\n"
      "      @trigger == 1\n"
      "    end\n"
      "    def parallel?\n"
      "      @trigger == 2\n"
      "    end\n"
#elif RGSS == 2
      "    attr_accessor :switch_id, :trigger\n"
#elif RGSS == 1
      "    attr_accessor :switch_id, :trigger\n"
#endif
      "  end\n"
      "  class Enemy\n"
      "    class Action\n"
      "    end\n"
#if RGSS >= 2
      "    class DropItem\n"
      "    end\n"
#endif
      "  end\n"
      "  class Event\n"
      "    attr_accessor :pages, :x, :y\n"
#if RGSS == 3
      "    attr_accessor :id\n"
#elif RGSS == 2
#elif RGSS == 1
#endif
      "    class Page\n"
      "      attr_accessor :condition, :direction_fix, :graphic, :list, :move_frequency, :move_route, :move_speed, :move_type, :step_anime, :through, :trigger, :walk_anime\n"
#if RGSS >= 2
      "      attr_accessor :priority_type\n"
#elif RGSS == 1
      "      attr_accessor :always_on_top\n"
#endif
      "      class Condition\n"
      "        attr_accessor :self_switch_valid, :switch1_valid, :switch2_valid, :variable_valid\n"
#if RGSS >= 2
      "        attr_accessor :actor_valid, :item_valid\n"
#elif RGSS == 1
      "        attr_accessor :switch1_id\n"
#endif
      "      end\n"
      "      class Graphic\n"
      "        attr_accessor :character_name, :direction, :pattern, :tile_id\n"
#if RGSS >= 2
      "        attr_accessor :character_index\n"
#elif RGSS == 1
      "        attr_accessor :blend_type, :character_hue, :character_name, :opacity, :tile_id\n"
#endif
      "      end\n"
      "    end\n"
      "  end\n"
      "  class EventCommand\n"
      "  end\n"
      "  class Item\n"
      "  end\n"
      "  class Map\n"
      "    attr_accessor :data, :encounter_step, :height, :width\n"
#if RGSS == 3
      "    attr_accessor :battleback1_name, :battleback2_name, :events, :parallax_loop_x, :parallax_loop_y, :parallax_name, :parallax_sx, :parallax_sy, :scroll_type, :specify_battleback, :tileset_id\n"
#elif RGSS == 2
      "    attr_accessor :autoplay_bgm, :autoplay_bgs, :bgm, :events, :parallax_loop_x, :parallax_loop_y, :parallax_name, :parallax_sx, :parallax_sy, :scroll_type\n"
#elif RGSS == 1
      "    attr_accessor :autoplay_bgm, :autoplay_bgs, :bgm, :events, :tileset_id\n"
#endif
      "  end\n"
      "  class MapInfo\n"
#if RGSS == 1
      "    attr_accessor :name\n"
#endif
      "  end\n"
      "  class MoveCommand\n"
      "  end\n"
      "  class MoveRoute\n"
      "  end\n"
#if RGSS >= 2
      "  class SE\n"
      "    def play\n"
      "    end\n"
      "  end\n"
#endif
      "  class Skill\n"
#if RGSS == 3
      "    attr_accessor :id\n"
#endif
      "  end\n"
#if RGSS == 1
      "  class Sprite < ::Sprite\n"
      "    @@_animations = []\n"
      "  end\n"
#endif
      "  class State\n"
      "  end\n"
      "  class System\n"
      "    attr_accessor :party_members, :start_map_id, :start_x, :start_y, :title_bgm\n"
#if RGSS >= 2
      "    attr_accessor :airship, :boat, :ship\n"
      "    attr_accessor :terms\n"
#endif
#if RGSS == 3
      "    attr_accessor :game_title, :opt_draw_title, :opt_followers, :opt_transparent, :opt_use_midi, :sounds, :title1_name, :title2_name, :window_tone\n"
#elif RGSS == 2
      "    attr_accessor :passages, :sounds\n"
#elif RGSS == 1
      "    attr_accessor :decision_se, :title_name, :windowskin_name\n"
#endif
      "    class "TERMS"\n"
#if RGSS == 3
      "      attr_accessor :commands\n"
#elif RGSS == 2
      "      attr_accessor :continue, :gold, :new_game, :shutdown\n"
#elif RGSS == 1
#endif
      "    end\n"
      "    class TestBattler\n"
      "    end\n"
#if RGSS >= 2
      "    class Vehicle\n"
      "      attr_accessor :character_index, :character_name, :start_map_id, :start_x, :start_y\n"
#if RGSS == 3
#else
      "      attr_accessor :bgm\n"
#endif
      "    end\n"
#endif
      "  end\n"
#if RGSS == 1 || RGSS == 3
      "  class Tileset\n"
#if RGSS == 3
      "    attr_accessor :flags\n"
#elif RGSS == 1
      "    attr_accessor :autotile_names, :battleback_name, :fog_blend_type, :fog_hue, :fog_name, :fog_opacity, :fog_sx, :fog_sy, :fog_zoom, :panorama_hue, :panorama_name, :passages, :priorities, :terrain_tags, :tileset_name\n"
#endif
      "  end\n"
#endif
      "  class Troop\n"
      "    class Member\n"
      "    end\n"
      "    class Page\n"
      "      class Condition\n"
      "      end\n"
      "    end\n"
      "  end\n"
#if RGSS == 3
      "  module UsableItem\n"
      "    class Effect\n"
      "    end\n"
      "    class Damage\n"
      "    end\n"
      "  end\n"
#endif
      "  class Weapon\n"
#if RGSS == 3
      "    attr_accessor :features\n"
#endif
      "  end\n"
      "end\n"
      "\n"
#if RGSS == 3
      "def rgss_main\n"
      "  yield\n"
      "rescue "RGSS_RESET"\n"
      "  GC.start\n"
      "  retry\n"
      "end\n"
      "def rgss_stop\n"
      "  loop { Graphics.update }\n"
      "end\n"
      "def msgbox(*args)\n"
      "  print *args\n"
      "end\n"
      "def msgbox_p(*args)\n"
      "  p *args\n"
      "end\n"
#endif
      /* TODO: read from archive */
      "def load_data(filename)\n"
      "  File.open(filename.gsub(/\\\\/, \"/\"), \"rb\") do|f|\n"
      "    Marshal.load(f)\n"
      "  end\n"
      "end\n"
      "def save_data(obj, filename)\n"
      "  File.open(filename.gsub(/\\\\/, \"/\"), \"wb\") do|f|\n"
      "    Marshal.dump(obj, f)\n"
      "  end\n"
      "end\n"
      "begin\n"
      /* TODO: determine script path from Game.ini */
      "  load_data("SCRIPT_PATH").each do|num,title,script|\n"
      "    s = Zlib::Inflate::inflate(script)\n"
#if RGSS == 3
      "    s.force_encoding(\"utf-8\")\n"
#endif
      "    eval(s, binding, title)\n"
      "  end\n"
      "rescue "RGSS_RESET"\n"
      "  retry\n"
      // "rescue SystemExit\n"
      // "  raise\n"
      "rescue Exception => e\n"
      "  $stderr.print(\"#{e.class}: #{e.message}\\n\")\n"
      "  e.backtrace.each do|frame|\n"
      "    $stderr.print(\"\\tfrom #{frame}\\n\")\n"
      "  end\n"
      "end\n"
  );
  return Qnil;
}
