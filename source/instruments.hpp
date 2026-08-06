/*
	MIT License

	Copyright (c) 2024 RealTimeChris

	Permission is hereby granted, free of charge, to any person obtaining a copy of this
	software and associated documentation files (the "Software"), to deal in the Software
	without restriction, including without limitation the rights to use, copy, modify, merge,
	publish, distribute, sublicense, and/or sell copies of the Software, and to permit
	persons to whom the Software is furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all copies or
	substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
	INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
	PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE
	FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
	OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
	DEALINGS IN THE SOFTWARE.
*/
/// https://github.com/RealTimeChris/Json-Performance
#pragma once

#include "common.hpp"

struct node {
	int64_t tick;
	int64_t value;
};

struct envelope {
	int64_t loop_end;
	int64_t loop_start;
	std::vector<node> nodes;
	int64_t release_node;
	int64_t sustain_end;
	int64_t sustain_start;
};

struct instrument_data {
	int64_t default_filter_cutoff;
	bool default_filter_cutoff_enabled;
	int64_t default_filter_mode;
	int64_t default_filter_resonance;
	bool default_filter_resonance_enabled;
	int64_t default_pan;
	int64_t duplicate_check_type;
	int64_t duplicate_note_action;
	int64_t fadeout;
	int64_t global_volume;
	int64_t graph_insert;
	std::string legacy_filename;
	int64_t midi_bank;
	int64_t midi_channel;
	int64_t midi_drum_set;
	int64_t midi_program;
	std::string name;
	int64_t new_note_action;
	std::optional<std::string> note_map;
	envelope panning_envelope;
	envelope pitch_envelope;
	int64_t pitch_pan_center;
	int64_t pitch_pan_separation;
	int64_t pitch_to_tempo_lock;
	int64_t random_cutoff_weight;
	int64_t random_pan_weight;
	int64_t random_resonance_weight;
	int64_t random_volume_weight;
	std::optional<std::string> sample_map;
	std::optional<std::string> tuning;
	envelope volume_envelope;
	int64_t volume_ramp_down;
	int64_t volume_ramp_up;
};

struct datum {
	int64_t channel;
	int64_t fxcmd;
	int64_t fxparam;
	int64_t instr;
	int64_t note;
	int64_t row;
	int64_t volcmd;
	int64_t volval;
};

struct pattern {
	std::optional<std::vector<datum>> data;
	std::string name;
	int64_t rows;
	int64_t rows_per_beat;
	int64_t rows_per_measure;
};

struct sample_data {
	int64_t c5_samplerate;
	int64_t global_volume;
	std::string legacy_filename;
	int64_t length;
	int64_t loop_end;
	int64_t loop_start;
	std::string name;
	int64_t pan;
	int64_t sustain_end;
	int64_t sustain_start;
	int64_t vibrato_depth;
	int64_t vibrato_rate;
	int64_t vibrato_sweep;
	int64_t vibrato_type;
	int64_t volume;
};

struct instruments_message {
	std::nullptr_t graphstate;
	std::vector<instrument_data> instruments;
	std::optional<std::string> message;
	std::string name;
	std::optional<std::string> orderlist;
	std::vector<pattern> patterns;
	std::optional<std::string> pluginstate;
	std::vector<sample_data> samples;
	int64_t version;
};

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, node& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_field(obj, "tick", data_new.tick);
	get_field(obj, "value", data_new.value);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, envelope& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_field(obj, "loop_end", data_new.loop_end);
	get_field(obj, "loop_start", data_new.loop_start);
	get_field(obj, "nodes", data_new.nodes);
	get_field(obj, "release_node", data_new.release_node);
	get_field(obj, "sustain_end", data_new.sustain_end);
	get_field(obj, "sustain_start", data_new.sustain_start);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, instrument_data& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_field(obj, "default_filter_cutoff", data_new.default_filter_cutoff);
	get_field(obj, "default_filter_cutoff_enabled", data_new.default_filter_cutoff_enabled);
	get_field(obj, "default_filter_mode", data_new.default_filter_mode);
	get_field(obj, "default_filter_resonance", data_new.default_filter_resonance);
	get_field(obj, "default_filter_resonance_enabled", data_new.default_filter_resonance_enabled);
	get_field(obj, "default_pan", data_new.default_pan);
	get_field(obj, "duplicate_check_type", data_new.duplicate_check_type);
	get_field(obj, "duplicate_note_action", data_new.duplicate_note_action);
	get_field(obj, "fadeout", data_new.fadeout);
	get_field(obj, "global_volume", data_new.global_volume);
	get_field(obj, "graph_insert", data_new.graph_insert);
	get_field(obj, "legacy_filename", data_new.legacy_filename);
	get_field(obj, "midi_bank", data_new.midi_bank);
	get_field(obj, "midi_channel", data_new.midi_channel);
	get_field(obj, "midi_drum_set", data_new.midi_drum_set);
	get_field(obj, "midi_program", data_new.midi_program);
	get_field(obj, "name", data_new.name);
	get_field(obj, "new_note_action", data_new.new_note_action);
	get_field(obj, "note_map", data_new.note_map);
	get_field(obj, "panning_envelope", data_new.panning_envelope);
	get_field(obj, "pitch_envelope", data_new.pitch_envelope);
	get_field(obj, "pitch_pan_center", data_new.pitch_pan_center);
	get_field(obj, "pitch_pan_separation", data_new.pitch_pan_separation);
	get_field(obj, "pitch_to_tempo_lock", data_new.pitch_to_tempo_lock);
	get_field(obj, "random_cutoff_weight", data_new.random_cutoff_weight);
	get_field(obj, "random_pan_weight", data_new.random_pan_weight);
	get_field(obj, "random_resonance_weight", data_new.random_resonance_weight);
	get_field(obj, "random_volume_weight", data_new.random_volume_weight);
	get_field(obj, "sample_map", data_new.sample_map);
	get_field(obj, "tuning", data_new.tuning);
	get_field(obj, "volume_envelope", data_new.volume_envelope);
	get_field(obj, "volume_ramp_down", data_new.volume_ramp_down);
	get_field(obj, "volume_ramp_up", data_new.volume_ramp_up);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, datum& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_field(obj, "channel", data_new.channel);
	get_field(obj, "fxcmd", data_new.fxcmd);
	get_field(obj, "fxparam", data_new.fxparam);
	get_field(obj, "instr", data_new.instr);
	get_field(obj, "note", data_new.note);
	get_field(obj, "row", data_new.row);
	get_field(obj, "volcmd", data_new.volcmd);
	get_field(obj, "volval", data_new.volval);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, pattern& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_field(obj, "data", data_new.data);
	get_field(obj, "name", data_new.name);
	get_field(obj, "rows", data_new.rows);
	get_field(obj, "rows_per_beat", data_new.rows_per_beat);
	get_field(obj, "rows_per_measure", data_new.rows_per_measure);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, sample_data& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_field(obj, "c5_samplerate", data_new.c5_samplerate);
	get_field(obj, "global_volume", data_new.global_volume);
	get_field(obj, "legacy_filename", data_new.legacy_filename);
	get_field(obj, "length", data_new.length);
	get_field(obj, "loop_end", data_new.loop_end);
	get_field(obj, "loop_start", data_new.loop_start);
	get_field(obj, "name", data_new.name);
	get_field(obj, "pan", data_new.pan);
	get_field(obj, "sustain_end", data_new.sustain_end);
	get_field(obj, "sustain_start", data_new.sustain_start);
	get_field(obj, "vibrato_depth", data_new.vibrato_depth);
	get_field(obj, "vibrato_rate", data_new.vibrato_rate);
	get_field(obj, "vibrato_sweep", data_new.vibrato_sweep);
	get_field(obj, "vibrato_type", data_new.vibrato_type);
	get_field(obj, "volume", data_new.volume);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, instruments_message& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_field(obj, "graphstate", data_new.graphstate);
	get_field(obj, "instruments", data_new.instruments);
	get_field(obj, "message", data_new.message);
	get_field(obj, "name", data_new.name);
	get_field(obj, "orderlist", data_new.orderlist);
	get_field(obj, "patterns", data_new.patterns);
	get_field(obj, "pluginstate", data_new.pluginstate);
	get_field(obj, "samples", data_new.samples);
	get_field(obj, "version", data_new.version);
}

template<> struct jsonifier::core<node> {
	using value_type				 = node;
	static constexpr auto parseValue = createValue<&value_type::tick, &value_type::value>();
};

template<> struct jsonifier::core<envelope> {
	using value_type = envelope;
	static constexpr auto parseValue =
		createValue<&value_type::loop_end, &value_type::loop_start, &value_type::nodes, &value_type::release_node, &value_type::sustain_end, &value_type::sustain_start>();
};

template<> struct jsonifier::core<instrument_data> {
	using value_type				 = instrument_data;
	static constexpr auto parseValue = createValue<&value_type::default_filter_cutoff, &value_type::default_filter_cutoff_enabled, &value_type::default_filter_mode,
		&value_type::default_filter_resonance, &value_type::default_filter_resonance_enabled, &value_type::default_pan, &value_type::duplicate_check_type,
		&value_type::duplicate_note_action, &value_type::fadeout, &value_type::global_volume, &value_type::graph_insert, &value_type::legacy_filename, &value_type::midi_bank,
		&value_type::midi_channel, &value_type::midi_drum_set, &value_type::midi_program, &value_type::name, &value_type::new_note_action, &value_type::note_map,
		&value_type::panning_envelope, &value_type::pitch_envelope, &value_type::pitch_pan_center, &value_type::pitch_pan_separation, &value_type::pitch_to_tempo_lock,
		&value_type::random_cutoff_weight, &value_type::random_pan_weight, &value_type::random_resonance_weight, &value_type::random_volume_weight, &value_type::sample_map,
		&value_type::tuning, &value_type::volume_envelope, &value_type::volume_ramp_down, &value_type::volume_ramp_up>();
};

template<> struct jsonifier::core<datum> {
	using value_type				 = datum;
	static constexpr auto parseValue = createValue<&value_type::channel, &value_type::fxcmd, &value_type::fxparam, &value_type::instr, &value_type::note, &value_type::row,
		&value_type::volcmd, &value_type::volval>();
};

template<> struct jsonifier::core<pattern> {
	using value_type				 = pattern;
	static constexpr auto parseValue = createValue<&value_type::data, &value_type::name, &value_type::rows, &value_type::rows_per_beat, &value_type::rows_per_measure>();
};

template<> struct jsonifier::core<sample_data> {
	using value_type				 = sample_data;
	static constexpr auto parseValue = createValue<&value_type::c5_samplerate, &value_type::global_volume, &value_type::legacy_filename, &value_type::length, &value_type::loop_end,
		&value_type::loop_start, &value_type::name, &value_type::pan, &value_type::sustain_end, &value_type::sustain_start, &value_type::vibrato_depth, &value_type::vibrato_rate,
		&value_type::vibrato_sweep, &value_type::vibrato_type, &value_type::volume>();
};

template<> struct jsonifier::core<instruments_message> {
	using value_type				 = instruments_message;
	static constexpr auto parseValue = createValue<&value_type::graphstate, &value_type::instruments, &value_type::message, &value_type::name, &value_type::orderlist,
		&value_type::patterns, &value_type::pluginstate, &value_type::samples, &value_type::version>();
};