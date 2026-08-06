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
/// Sep 17, 2024
#pragma once

#include "common.hpp"

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
	std::vector<std::nullptr_t> symbols;
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
	bool protectedVal;
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
	std::nullptr_t geo;
	std::nullptr_t coordinates;
	std::nullptr_t place;
	std::nullptr_t contributors;
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
	get_field(obj, "completed_in", data_new.completed_in);
	get_field(obj, "max_id", data_new.max_id);
	get_field(obj, "max_id_str", data_new.max_id_str);
	get_field(obj, "next_results", data_new.next_results);
	get_field(obj, "query", data_new.query);
	get_field(obj, "refresh_url", data_new.refresh_url);
	get_field(obj, "count", data_new.count);
	get_field(obj, "since_id", data_new.since_id);
	get_field(obj, "since_id_str", data_new.since_id_str);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, hashtag_data& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_field(obj, "text", data_new.text);
	get_field(obj, "indices", data_new.indices);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, large_data& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_field(obj, "w", data_new.w);
	get_field(obj, "h", data_new.h);
	get_field(obj, "resize", data_new.resize);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, sizes_data& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_field(obj, "medium", data_new.medium);
	get_field(obj, "small", data_new.small);
	get_field(obj, "thumb", data_new.thumb);
	get_field(obj, "large", data_new.large);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, media_data& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_field(obj, "id", data_new.id);
	get_field(obj, "id_str", data_new.id_str);
	get_field(obj, "indices", data_new.indices);
	get_field(obj, "media_url", data_new.media_url);
	get_field(obj, "media_url_https", data_new.media_url_https);
	get_field(obj, "url", data_new.url);
	get_field(obj, "display_url", data_new.display_url);
	get_field(obj, "expanded_url", data_new.expanded_url);
	get_field(obj, "type", data_new.type);
	get_field(obj, "sizes", data_new.sizes);
	get_field(obj, "source_status_id", data_new.source_status_id);
	get_field(obj, "source_status_id_str", data_new.source_status_id_str);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, url_data& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_field(obj, "url", data_new.url);
	get_field(obj, "expanded_url", data_new.expanded_url);
	get_field(obj, "display_url", data_new.display_url);
	get_field(obj, "indices", data_new.indices);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, user_mention_data& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_field(obj, "screen_name", data_new.screen_name);
	get_field(obj, "name", data_new.name);
	get_field(obj, "id", data_new.id);
	get_field(obj, "id_str", data_new.id_str);
	get_field(obj, "indices", data_new.indices);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, status_entities& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_field(obj, "hashtags", data_new.hashtags);
	get_field(obj, "symbols", data_new.symbols);
	get_field(obj, "urls", data_new.urls);
	get_field(obj, "user_mentions", data_new.user_mentions);
	get_field(obj, "media", data_new.media);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, metadata_data& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_field(obj, "result_type", data_new.result_type);
	get_field(obj, "iso_language_code", data_new.iso_language_code);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, description_data& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_field(obj, "urls", data_new.urls);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, user_entities& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_field(obj, "description", data_new.description);
	get_field(obj, "url", data_new.url);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, twitter_user_data& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_field(obj, "id", data_new.id);
	get_field(obj, "id_str", data_new.id_str);
	get_field(obj, "name", data_new.name);
	get_field(obj, "screen_name", data_new.screen_name);
	get_field(obj, "location", data_new.location);
	get_field(obj, "description", data_new.description);
	get_field(obj, "url", data_new.url);
	get_field(obj, "entities", data_new.entities);
	get_field(obj, "protected", data_new.protectedVal);
	get_field(obj, "followers_count", data_new.followers_count);
	get_field(obj, "friends_count", data_new.friends_count);
	get_field(obj, "listed_count", data_new.listed_count);
	get_field(obj, "created_at", data_new.created_at);
	get_field(obj, "favourites_count", data_new.favourites_count);
	get_field(obj, "utc_offset", data_new.utc_offset);
	get_field(obj, "time_zone", data_new.time_zone);
	get_field(obj, "geo_enabled", data_new.geo_enabled);
	get_field(obj, "verified", data_new.verified);
	get_field(obj, "statuses_count", data_new.statuses_count);
	get_field(obj, "lang", data_new.lang);
	get_field(obj, "contributors_enabled", data_new.contributors_enabled);
	get_field(obj, "is_translator", data_new.is_translator);
	get_field(obj, "is_translation_enabled", data_new.is_translation_enabled);
	get_field(obj, "profile_background_color", data_new.profile_background_color);
	get_field(obj, "profile_background_image_url", data_new.profile_background_image_url);
	get_field(obj, "profile_background_image_url_https", data_new.profile_background_image_url_https);
	get_field(obj, "profile_background_tile", data_new.profile_background_tile);
	get_field(obj, "profile_image_url", data_new.profile_image_url);
	get_field(obj, "profile_image_url_https", data_new.profile_image_url_https);
	get_field(obj, "profile_banner_url", data_new.profile_banner_url);
	get_field(obj, "profile_link_color", data_new.profile_link_color);
	get_field(obj, "profile_sidebar_border_color", data_new.profile_sidebar_border_color);
	get_field(obj, "profile_sidebar_fill_color", data_new.profile_sidebar_fill_color);
	get_field(obj, "profile_text_color", data_new.profile_text_color);
	get_field(obj, "profile_use_background_image", data_new.profile_use_background_image);
	get_field(obj, "default_profile", data_new.default_profile);
	get_field(obj, "default_profile_image", data_new.default_profile_image);
	get_field(obj, "following", data_new.following);
	get_field(obj, "follow_request_sent", data_new.follow_request_sent);
	get_field(obj, "notifications", data_new.notifications);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, status_data& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_field(obj, "metadata", data_new.metadata);
	get_field(obj, "created_at", data_new.created_at);
	get_field(obj, "id", data_new.id);
	get_field(obj, "id_str", data_new.id_str);
	get_field(obj, "text", data_new.text);
	get_field(obj, "source", data_new.source);
	get_field(obj, "truncated", data_new.truncated);
	get_field(obj, "in_reply_to_status_id", data_new.in_reply_to_status_id);
	get_field(obj, "in_reply_to_status_id_str", data_new.in_reply_to_status_id_str);
	get_field(obj, "in_reply_to_user_id", data_new.in_reply_to_user_id);
	get_field(obj, "in_reply_to_user_id_str", data_new.in_reply_to_user_id_str);
	get_field(obj, "in_reply_to_screen_name", data_new.in_reply_to_screen_name);
	get_field(obj, "user", data_new.user);
	get_field(obj, "geo", data_new.geo);
	get_field(obj, "coordinates", data_new.coordinates);
	get_field(obj, "place", data_new.place);
	get_field(obj, "contributors", data_new.contributors);
	get_field(obj, "retweet_count", data_new.retweet_count);
	get_field(obj, "favorite_count", data_new.favorite_count);
	get_field(obj, "entities", data_new.entities);
	get_field(obj, "favorited", data_new.favorited);
	get_field(obj, "retweeted", data_new.retweeted);
	get_field(obj, "lang", data_new.lang);
	get_field(obj, "possibly_sensitive", data_new.possibly_sensitive);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, twitter_message& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_field(obj, "statuses", data_new.statuses);
	get_field(obj, "search_metadata", data_new.search_metadata);
}

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
	get_field(obj, "screen_name", data_new.screen_name);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, status_data_partial& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_field(obj, "text", data_new.text);
	get_field(obj, "user", data_new.user);
	get_field(obj, "retweet_count", data_new.retweet_count);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, twitter_partial_message& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_field(obj, "statuses", data_new.statuses);
}

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