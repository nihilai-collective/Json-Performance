/*
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2026 Nihilai Collective Corp
 * https://github.com/nihilai-collective/json-performance
 * include/twitter.hpp
 */

#pragma once

#include <common.hpp>

struct search_metadata_data {
	double completed_in;
	double max_id;
	std::string max_id_str;
	std::string next_results;
	std::string query;
	std::string refresh_url;
	int64_t count;
	int64_t since_id;
	std::string since_id_str;
};

struct hashtag_data {
	std::string text;
	std::vector<int64_t> indices;
};

struct large_data {
	int64_t w;
	int64_t h;
	std::string resize;
};

struct sizes_data {
	large_data medium;
	large_data small;
	large_data thumb;
	large_data large;
};

struct media_data {
	double id;
	std::string id_str;
	std::vector<int64_t> indices;
	std::string media_url;
	std::string media_url_https;
	std::string url;
	std::string display_url;
	std::string expanded_url;
	std::string type;
	sizes_data sizes;
	std::optional<double> source_status_id;
	std::optional<std::string> source_status_id_str;
};

struct url_data {
	std::string url;
	std::string expanded_url;
	std::string display_url;
	std::vector<int64_t> indices;
};

struct user_mention_data {
	std::string screen_name;
	std::string name;
	int64_t id;
	std::string id_str;
	std::vector<int64_t> indices;
};

struct status_entities {
	std::vector<hashtag_data> hashtags;
	std::vector<std::optional<std::string>> symbols;
	std::vector<url_data> urls;
	std::vector<user_mention_data> user_mentions;
	std::optional<std::vector<media_data>> media;
};

struct metadata_data {
	std::string result_type;
	std::string iso_language_code;
};

struct description_data {
	std::vector<url_data> urls;
};

struct user_entities {
	description_data description;
	std::optional<description_data> url;
};

struct twitter_user_data {
	int64_t id;
	std::string id_str;
	std::string name;
	std::string screen_name;
	std::string location;
	std::string description;
	std::optional<std::string> url;
	user_entities entities;
	JP_SIMDJSON_RENAME("protected") bool protectedVal;
	int64_t followers_count;
	int64_t friends_count;
	int64_t listed_count;
	std::string created_at;
	int64_t favourites_count;
	std::optional<int64_t> utc_offset;
	std::optional<std::string> time_zone;
	bool geo_enabled;
	bool verified;
	int64_t statuses_count;
	std::string lang;
	bool contributors_enabled;
	bool is_translator;
	bool is_translation_enabled;
	std::string profile_background_color;
	std::string profile_background_image_url;
	std::string profile_background_image_url_https;
	bool profile_background_tile;
	std::string profile_image_url;
	std::string profile_image_url_https;
	std::optional<std::string> profile_banner_url;
	std::string profile_link_color;
	std::string profile_sidebar_border_color;
	std::string profile_sidebar_fill_color;
	std::string profile_text_color;
	bool profile_use_background_image;
	bool default_profile;
	bool default_profile_image;
	bool following;
	bool follow_request_sent;
	bool notifications;
};

struct status_data {
	metadata_data metadata;
	std::string created_at;
	double id;
	std::string id_str;
	std::string text;
	std::string source;
	bool truncated;
	std::optional<double> in_reply_to_status_id;
	std::optional<std::string> in_reply_to_status_id_str;
	std::optional<int64_t> in_reply_to_user_id;
	std::optional<std::string> in_reply_to_user_id_str;
	std::optional<std::string> in_reply_to_screen_name;
	twitter_user_data user;
	std::optional<std::string> geo;
	std::optional<std::string> coordinates;
	std::optional<std::string> place;
	std::optional<std::string> contributors;
	int64_t retweet_count;
	int64_t favorite_count;
	status_entities entities;
	bool favorited;
	bool retweeted;
	std::string lang;
	std::optional<bool> possibly_sensitive;
};

struct twitter_message {
	std::vector<status_data> statuses;
	search_metadata_data search_metadata;
};

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, search_metadata_data& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_fields<"completed_in", "max_id", "max_id_str", "next_results", "query", "refresh_url", "count", "since_id", "since_id_str">(obj, data_new.completed_in, data_new.max_id,
		data_new.max_id_str, data_new.next_results, data_new.query, data_new.refresh_url, data_new.count, data_new.since_id, data_new.since_id_str);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, hashtag_data& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_fields<"text", "indices">(obj, data_new.text, data_new.indices);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, large_data& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_fields<"w", "h", "resize">(obj, data_new.w, data_new.h, data_new.resize);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, sizes_data& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_fields<"medium", "small", "thumb", "large">(obj, data_new.medium, data_new.small, data_new.thumb, data_new.large);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, media_data& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_fields<"id", "id_str", "indices", "media_url", "media_url_https", "url", "display_url", "expanded_url", "type", "sizes", "source_status_id", "source_status_id_str">(obj,
		data_new.id, data_new.id_str, data_new.indices, data_new.media_url, data_new.media_url_https, data_new.url, data_new.display_url, data_new.expanded_url, data_new.type,
		data_new.sizes, data_new.source_status_id, data_new.source_status_id_str);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, url_data& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_fields<"url", "expanded_url", "display_url", "indices">(obj, data_new.url, data_new.expanded_url, data_new.display_url, data_new.indices);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, user_mention_data& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_fields<"screen_name", "name", "id", "id_str", "indices">(obj, data_new.screen_name, data_new.name, data_new.id, data_new.id_str, data_new.indices);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, status_entities& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_fields<"hashtags", "symbols", "urls", "user_mentions", "media">(obj, data_new.hashtags, data_new.symbols, data_new.urls, data_new.user_mentions, data_new.media);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, metadata_data& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_fields<"result_type", "iso_language_code">(obj, data_new.result_type, data_new.iso_language_code);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, description_data& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_fields<"urls">(obj, data_new.urls);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, user_entities& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_fields<"description", "url">(obj, data_new.description, data_new.url);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, twitter_user_data& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_fields<"id", "id_str", "name", "screen_name", "location", "description", "url", "entities", "protected", "followers_count", "friends_count", "listed_count", "created_at",
		"favourites_count", "utc_offset", "time_zone", "geo_enabled", "verified", "statuses_count", "lang", "contributors_enabled", "is_translator", "is_translation_enabled",
		"profile_background_color", "profile_background_image_url", "profile_background_image_url_https", "profile_background_tile", "profile_image_url", "profile_image_url_https",
		"profile_banner_url", "profile_link_color", "profile_sidebar_border_color", "profile_sidebar_fill_color", "profile_text_color", "profile_use_background_image",
		"default_profile", "default_profile_image", "following", "follow_request_sent", "notifications">(obj, data_new.id, data_new.id_str, data_new.name, data_new.screen_name,
		data_new.location, data_new.description, data_new.url, data_new.entities, data_new.protectedVal, data_new.followers_count, data_new.friends_count, data_new.listed_count,
		data_new.created_at, data_new.favourites_count, data_new.utc_offset, data_new.time_zone, data_new.geo_enabled, data_new.verified, data_new.statuses_count, data_new.lang,
		data_new.contributors_enabled, data_new.is_translator, data_new.is_translation_enabled, data_new.profile_background_color, data_new.profile_background_image_url,
		data_new.profile_background_image_url_https, data_new.profile_background_tile, data_new.profile_image_url, data_new.profile_image_url_https, data_new.profile_banner_url,
		data_new.profile_link_color, data_new.profile_sidebar_border_color, data_new.profile_sidebar_fill_color, data_new.profile_text_color, data_new.profile_use_background_image,
		data_new.default_profile, data_new.default_profile_image, data_new.following, data_new.follow_request_sent, data_new.notifications);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, status_data& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_fields<"metadata", "created_at", "id", "id_str", "text", "source", "truncated", "in_reply_to_status_id", "in_reply_to_status_id_str", "in_reply_to_user_id",
		"in_reply_to_user_id_str", "in_reply_to_screen_name", "user", "geo", "coordinates", "place", "contributors", "retweet_count", "favorite_count", "entities", "favorited",
		"retweeted", "lang", "possibly_sensitive">(obj, data_new.metadata, data_new.created_at, data_new.id, data_new.id_str, data_new.text, data_new.source, data_new.truncated,
		data_new.in_reply_to_status_id, data_new.in_reply_to_status_id_str, data_new.in_reply_to_user_id, data_new.in_reply_to_user_id_str, data_new.in_reply_to_screen_name,
		data_new.user, data_new.geo, data_new.coordinates, data_new.place, data_new.contributors, data_new.retweet_count, data_new.favorite_count, data_new.entities,
		data_new.favorited, data_new.retweeted, data_new.lang, data_new.possibly_sensitive);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, twitter_message& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_fields<"statuses", "search_metadata">(obj, data_new.statuses, data_new.search_metadata);
}

template<> struct glz::meta<search_metadata_data> {
	using value_type			= search_metadata_data;
	static constexpr auto value = object(&value_type::completed_in, &value_type::max_id, &value_type::max_id_str, &value_type::next_results, &value_type::query,
		&value_type::refresh_url, &value_type::count, &value_type::since_id, &value_type::since_id_str);
};

template<> struct glz::meta<hashtag_data> {
	using value_type			= hashtag_data;
	static constexpr auto value = object(&value_type::text, &value_type::indices);
};

template<> struct glz::meta<large_data> {
	using value_type			= large_data;
	static constexpr auto value = object(&value_type::w, &value_type::h, &value_type::resize);
};

template<> struct glz::meta<sizes_data> {
	using value_type			= sizes_data;
	static constexpr auto value = object(&value_type::medium, &value_type::small, &value_type::thumb, &value_type::large);
};

template<> struct glz::meta<media_data> {
	using value_type			= media_data;
	static constexpr auto value = object(&value_type::id, &value_type::id_str, &value_type::indices, &value_type::media_url, &value_type::media_url_https, &value_type::url,
		&value_type::display_url, &value_type::expanded_url, &value_type::type, &value_type::sizes, &value_type::source_status_id, &value_type::source_status_id_str);
};

template<> struct glz::meta<url_data> {
	using value_type			= url_data;
	static constexpr auto value = object(&value_type::url, &value_type::expanded_url, &value_type::display_url, &value_type::indices);
};

template<> struct glz::meta<user_mention_data> {
	using value_type			= user_mention_data;
	static constexpr auto value = object(&value_type::screen_name, &value_type::name, &value_type::id, &value_type::id_str, &value_type::indices);
};

template<> struct glz::meta<status_entities> {
	using value_type			= status_entities;
	static constexpr auto value = object(&value_type::hashtags, &value_type::symbols, &value_type::urls, &value_type::user_mentions, &value_type::media);
};

template<> struct glz::meta<metadata_data> {
	using value_type			= metadata_data;
	static constexpr auto value = object(&value_type::result_type, &value_type::iso_language_code);
};

template<> struct glz::meta<description_data> {
	using value_type			= description_data;
	static constexpr auto value = object(&value_type::urls);
};

template<> struct glz::meta<user_entities> {
	using value_type			= user_entities;
	static constexpr auto value = object(&value_type::description, &value_type::url);
};

template<> struct glz::meta<twitter_user_data> {
	using value_type			= twitter_user_data;
	static constexpr auto value = object(&value_type::id, &value_type::id_str, &value_type::name, &value_type::screen_name, &value_type::location, &value_type::description,
		&value_type::url, &value_type::entities, "protected", &value_type::protectedVal, &value_type::followers_count, &value_type::friends_count, &value_type::listed_count,
		&value_type::created_at, &value_type::favourites_count, &value_type::utc_offset, &value_type::time_zone, &value_type::geo_enabled, &value_type::verified,
		&value_type::statuses_count, &value_type::lang, &value_type::contributors_enabled, &value_type::is_translator, &value_type::is_translation_enabled,
		&value_type::profile_background_color, &value_type::profile_background_image_url, &value_type::profile_background_image_url_https, &value_type::profile_background_tile,
		&value_type::profile_image_url, &value_type::profile_image_url_https, &value_type::profile_banner_url, &value_type::profile_link_color,
		&value_type::profile_sidebar_border_color, &value_type::profile_sidebar_fill_color, &value_type::profile_text_color, &value_type::profile_use_background_image,
		&value_type::default_profile, &value_type::default_profile_image, &value_type::following, &value_type::follow_request_sent, &value_type::notifications);
};

template<> struct glz::meta<status_data> {
	using value_type			= status_data;
	static constexpr auto value = object(&value_type::metadata, &value_type::created_at, &value_type::id, &value_type::id_str, &value_type::text, &value_type::source,
		&value_type::truncated, &value_type::in_reply_to_status_id, &value_type::in_reply_to_status_id_str, &value_type::in_reply_to_user_id, &value_type::in_reply_to_user_id_str,
		&value_type::in_reply_to_screen_name, &value_type::user, &value_type::geo, &value_type::coordinates, &value_type::place, &value_type::contributors,
		&value_type::retweet_count, &value_type::favorite_count, &value_type::entities, &value_type::favorited, &value_type::retweeted, &value_type::lang,
		&value_type::possibly_sensitive);
};

template<> struct glz::meta<twitter_message> {
	using value_type			= twitter_message;
	static constexpr auto value = object(&value_type::statuses, &value_type::search_metadata);
};

template<> struct jsonifier::core<search_metadata_data> {
	using value_type				 = search_metadata_data;
	static constexpr auto parseValue = createValue<&value_type::completed_in, &value_type::max_id, &value_type::max_id_str, &value_type::next_results, &value_type::query,
		&value_type::refresh_url, &value_type::count, &value_type::since_id, &value_type::since_id_str>();
};

template<> struct jsonifier::core<hashtag_data> {
	using value_type				 = hashtag_data;
	static constexpr auto parseValue = createValue<&value_type::text, &value_type::indices>();
};

template<> struct jsonifier::core<large_data> {
	using value_type				 = large_data;
	static constexpr auto parseValue = createValue<&value_type::w, &value_type::h, &value_type::resize>();
};

template<> struct jsonifier::core<sizes_data> {
	using value_type				 = sizes_data;
	static constexpr auto parseValue = createValue<&value_type::medium, &value_type::small, &value_type::thumb, &value_type::large>();
};

template<> struct jsonifier::core<media_data> {
	using value_type = media_data;
	static constexpr auto parseValue =
		createValue<&value_type::id, &value_type::id_str, &value_type::indices, &value_type::media_url, &value_type::media_url_https, &value_type::url, &value_type::display_url,
			&value_type::expanded_url, &value_type::type, &value_type::sizes, &value_type::source_status_id, &value_type::source_status_id_str>();
};

template<> struct jsonifier::core<url_data> {
	using value_type				 = url_data;
	static constexpr auto parseValue = createValue<&value_type::url, &value_type::expanded_url, &value_type::display_url, &value_type::indices>();
};

template<> struct jsonifier::core<user_mention_data> {
	using value_type				 = user_mention_data;
	static constexpr auto parseValue = createValue<&value_type::screen_name, &value_type::name, &value_type::id, &value_type::id_str, &value_type::indices>();
};

template<> struct jsonifier::core<status_entities> {
	using value_type				 = status_entities;
	static constexpr auto parseValue = createValue<&value_type::hashtags, &value_type::symbols, &value_type::urls, &value_type::user_mentions, &value_type::media>();
};

template<> struct jsonifier::core<metadata_data> {
	using value_type				 = metadata_data;
	static constexpr auto parseValue = createValue<&value_type::result_type, &value_type::iso_language_code>();
};

template<> struct jsonifier::core<description_data> {
	using value_type				 = description_data;
	static constexpr auto parseValue = createValue<&value_type::urls>();
};

template<> struct jsonifier::core<user_entities> {
	using value_type				 = user_entities;
	static constexpr auto parseValue = createValue<&value_type::description, &value_type::url>();
};

template<> struct jsonifier::core<twitter_user_data> {
	using value_type = twitter_user_data;
	static constexpr auto parseValue =
		createValue<&value_type::id, &value_type::id_str, &value_type::name, &value_type::screen_name, &value_type::location, &value_type::description, &value_type::url,
			&value_type::entities, makeJsonEntity<&value_type::protectedVal, "protected">(), &value_type::followers_count, &value_type::friends_count, &value_type::listed_count,
			&value_type::created_at, &value_type::favourites_count, &value_type::utc_offset, &value_type::time_zone, &value_type::geo_enabled, &value_type::verified,
			&value_type::statuses_count, &value_type::lang, &value_type::contributors_enabled, &value_type::is_translator, &value_type::is_translation_enabled,
			&value_type::profile_background_color, &value_type::profile_background_image_url, &value_type::profile_background_image_url_https, &value_type::profile_background_tile,
			&value_type::profile_image_url, &value_type::profile_image_url_https, &value_type::profile_banner_url, &value_type::profile_link_color,
			&value_type::profile_sidebar_border_color, &value_type::profile_sidebar_fill_color, &value_type::profile_text_color, &value_type::profile_use_background_image,
			&value_type::default_profile, &value_type::default_profile_image, &value_type::following, &value_type::follow_request_sent, &value_type::notifications>();
};

template<> struct jsonifier::core<status_data> {
	using value_type				 = status_data;
	static constexpr auto parseValue = createValue<&value_type::metadata, &value_type::created_at, &value_type::id, &value_type::id_str, &value_type::text, &value_type::source,
		&value_type::truncated, &value_type::in_reply_to_status_id, &value_type::in_reply_to_status_id_str, &value_type::in_reply_to_user_id, &value_type::in_reply_to_user_id_str,
		&value_type::in_reply_to_screen_name, &value_type::user, &value_type::geo, &value_type::coordinates, &value_type::place, &value_type::contributors,
		&value_type::retweet_count, &value_type::favorite_count, &value_type::entities, &value_type::favorited, &value_type::retweeted, &value_type::lang,
		&value_type::possibly_sensitive>();
};

template<> struct jsonifier::core<twitter_message> {
	using value_type				 = twitter_message;
	static constexpr auto parseValue = createValue<&value_type::statuses, &value_type::search_metadata>();
};

struct user_data_partial {
	std::string screen_name;
};

struct status_data_partial {
	std::string text;
	user_data_partial user;
	int64_t retweet_count;
};

struct twitter_partial_message {
	std::vector<status_data_partial> statuses;
};

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, user_data_partial& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_fields<"screen_name">(obj, data_new.screen_name);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, status_data_partial& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_fields<"text", "user", "retweet_count">(obj, data_new.text, data_new.user, data_new.retweet_count);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, twitter_partial_message& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_fields<"statuses">(obj, data_new.statuses);
}

template<> struct glz::meta<user_data_partial> {
	using value_type			= user_data_partial;
	static constexpr auto value = object(&value_type::screen_name);
};

template<> struct glz::meta<status_data_partial> {
	using value_type			= status_data_partial;
	static constexpr auto value = object(&value_type::text, &value_type::user, &value_type::retweet_count);
};

template<> struct glz::meta<twitter_partial_message> {
	using value_type			= twitter_partial_message;
	static constexpr auto value = object(&value_type::statuses);
};

template<> struct jsonifier::core<user_data_partial> {
	using value_type				 = user_data_partial;
	static constexpr auto parseValue = createValue<&value_type::screen_name>();
};

template<> struct jsonifier::core<status_data_partial> {
	using value_type				 = status_data_partial;
	static constexpr auto parseValue = createValue<&value_type::text, &value_type::user, &value_type::retweet_count>();
};

template<> struct jsonifier::core<twitter_partial_message> {
	using value_type				 = twitter_partial_message;
	static constexpr auto parseValue = createValue<&value_type::statuses>();
};