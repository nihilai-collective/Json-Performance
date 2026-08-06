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

struct emoji_data {
	std::string id;
	std::string name;
	std::vector<std::nullptr_t> roles;
	bool require_colons;
	bool managed;
	bool animated;
	bool available;
};

struct incidents_data_data {
	std::string invites_disabled_until;
	std::string dms_disabled_until;
};

struct tags_data {
	std::optional<std::string> bot_id;
	std::nullptr_t guild_connections;
};

struct role_data {
	std::string id;
	std::string name;
	std::nullptr_t description;
	std::string permissions;
	int64_t position;
	int64_t color;
	bool hoist;
	bool managed;
	bool mentionable;
	std::nullptr_t icon;
	std::nullptr_t unicode_emoji;
	int64_t flags;
	std::optional<tags_data> tags;
};

struct sticker_data {
	std::string id;
	std::string name;
	std::string tags;
	int64_t type;
	int64_t format_type;
	std::string description;
	std::string asset;
	bool available;
	std::string guild_id;
};

struct discord_message {
	std::string id;
	std::string name;
	std::string icon;
	std::string description;
	std::nullptr_t home_header;
	std::nullptr_t splash;
	std::string discovery_splash;
	std::vector<std::string> features;
	std::nullptr_t banner;
	std::string owner_id;
	std::nullptr_t application_id;
	std::string region;
	std::nullptr_t afk_channel_id;
	int64_t afk_timeout;
	std::string system_channel_id;
	int64_t system_channel_flags;
	bool widget_enabled;
	std::string widget_channel_id;
	int64_t verification_level;
	std::vector<role_data> roles;
	int64_t default_message_notifications;
	int64_t mfa_level;
	int64_t explicit_content_filter;
	std::nullptr_t max_presences;
	int64_t max_members;
	int64_t max_stage_video_channel_users;
	int64_t max_video_channel_users;
	std::nullptr_t vanity_url_code;
	int64_t premium_tier;
	int64_t premium_subscription_count;
	std::string preferred_locale;
	std::string rules_channel_id;
	std::string safety_alerts_channel_id;
	std::string public_updates_channel_id;
	std::nullptr_t hub_type;
	bool premium_progress_bar_enabled;
	std::string latest_onboarding_question_id;
	bool nsfw;
	int64_t nsfw_level;
	std::vector<emoji_data> emojis;
	std::vector<sticker_data> stickers;
	incidents_data_data incidents_data;
	std::nullptr_t inventory_settings;
	bool embed_enabled;
	std::string embed_channel_id;
	int64_t approximate_member_count;
	int64_t approximate_presence_count;
};

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, emoji_data& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_field(obj, "id", data_new.id);
	get_field(obj, "name", data_new.name);
	get_field(obj, "roles", data_new.roles);
	get_field(obj, "require_colons", data_new.require_colons);
	get_field(obj, "managed", data_new.managed);
	get_field(obj, "animated", data_new.animated);
	get_field(obj, "available", data_new.available);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, incidents_data_data& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_field(obj, "invites_disabled_until", data_new.invites_disabled_until);
	get_field(obj, "dms_disabled_until", data_new.dms_disabled_until);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, tags_data& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_field(obj, "bot_id", data_new.bot_id);
	get_field(obj, "guild_connections", data_new.guild_connections);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, role_data& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_field(obj, "id", data_new.id);
	get_field(obj, "name", data_new.name);
	get_field(obj, "description", data_new.description);
	get_field(obj, "permissions", data_new.permissions);
	get_field(obj, "position", data_new.position);
	get_field(obj, "color", data_new.color);
	get_field(obj, "hoist", data_new.hoist);
	get_field(obj, "managed", data_new.managed);
	get_field(obj, "mentionable", data_new.mentionable);
	get_field(obj, "icon", data_new.icon);
	get_field(obj, "unicode_emoji", data_new.unicode_emoji);
	get_field(obj, "flags", data_new.flags);
	get_field(obj, "tags", data_new.tags);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, sticker_data& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_field(obj, "id", data_new.id);
	get_field(obj, "name", data_new.name);
	get_field(obj, "tags", data_new.tags);
	get_field(obj, "type", data_new.type);
	get_field(obj, "format_type", data_new.format_type);
	get_field(obj, "description", data_new.description);
	get_field(obj, "asset", data_new.asset);
	get_field(obj, "available", data_new.available);
	get_field(obj, "guild_id", data_new.guild_id);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, discord_message& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_field(obj, "id", data_new.id);
	get_field(obj, "name", data_new.name);
	get_field(obj, "icon", data_new.icon);
	get_field(obj, "description", data_new.description);
	get_field(obj, "home_header", data_new.home_header);
	get_field(obj, "splash", data_new.splash);
	get_field(obj, "discovery_splash", data_new.discovery_splash);
	get_field(obj, "features", data_new.features);
	get_field(obj, "banner", data_new.banner);
	get_field(obj, "owner_id", data_new.owner_id);
	get_field(obj, "application_id", data_new.application_id);
	get_field(obj, "region", data_new.region);
	get_field(obj, "afk_channel_id", data_new.afk_channel_id);
	get_field(obj, "afk_timeout", data_new.afk_timeout);
	get_field(obj, "system_channel_id", data_new.system_channel_id);
	get_field(obj, "system_channel_flags", data_new.system_channel_flags);
	get_field(obj, "widget_enabled", data_new.widget_enabled);
	get_field(obj, "widget_channel_id", data_new.widget_channel_id);
	get_field(obj, "verification_level", data_new.verification_level);
	get_field(obj, "roles", data_new.roles);
	get_field(obj, "default_message_notifications", data_new.default_message_notifications);
	get_field(obj, "mfa_level", data_new.mfa_level);
	get_field(obj, "explicit_content_filter", data_new.explicit_content_filter);
	get_field(obj, "max_presences", data_new.max_presences);
	get_field(obj, "max_members", data_new.max_members);
	get_field(obj, "max_stage_video_channel_users", data_new.max_stage_video_channel_users);
	get_field(obj, "max_video_channel_users", data_new.max_video_channel_users);
	get_field(obj, "vanity_url_code", data_new.vanity_url_code);
	get_field(obj, "premium_tier", data_new.premium_tier);
	get_field(obj, "premium_subscription_count", data_new.premium_subscription_count);
	get_field(obj, "preferred_locale", data_new.preferred_locale);
	get_field(obj, "rules_channel_id", data_new.rules_channel_id);
	get_field(obj, "safety_alerts_channel_id", data_new.safety_alerts_channel_id);
	get_field(obj, "public_updates_channel_id", data_new.public_updates_channel_id);
	get_field(obj, "hub_type", data_new.hub_type);
	get_field(obj, "premium_progress_bar_enabled", data_new.premium_progress_bar_enabled);
	get_field(obj, "latest_onboarding_question_id", data_new.latest_onboarding_question_id);
	get_field(obj, "nsfw", data_new.nsfw);
	get_field(obj, "nsfw_level", data_new.nsfw_level);
	get_field(obj, "emojis", data_new.emojis);
	get_field(obj, "stickers", data_new.stickers);
	get_field(obj, "incidents_data", data_new.incidents_data);
	get_field(obj, "inventory_settings", data_new.inventory_settings);
	get_field(obj, "embed_enabled", data_new.embed_enabled);
	get_field(obj, "embed_channel_id", data_new.embed_channel_id);
	get_field(obj, "approximate_member_count", data_new.approximate_member_count);
	get_field(obj, "approximate_presence_count", data_new.approximate_presence_count);
}

template<> struct jsonifier::core<emoji_data> {
	using value_type = emoji_data;
	static constexpr auto parseValue =
		createValue<&value_type::id, &value_type::name, &value_type::roles, &value_type::require_colons, &value_type::managed, &value_type::animated, &value_type::available>();
};

template<> struct jsonifier::core<incidents_data_data> {
	using value_type				 = incidents_data_data;
	static constexpr auto parseValue = createValue<&value_type::invites_disabled_until, &value_type::dms_disabled_until>();
};

template<> struct jsonifier::core<tags_data> {
	using value_type				 = tags_data;
	static constexpr auto parseValue = createValue<&value_type::bot_id, &value_type::guild_connections>();
};

template<> struct jsonifier::core<role_data> {
	using value_type = role_data;
	static constexpr auto parseValue =
		createValue<&value_type::id, &value_type::name, &value_type::description, &value_type::permissions, &value_type::position, &value_type::color, &value_type::hoist,
			&value_type::managed, &value_type::mentionable, &value_type::icon, &value_type::unicode_emoji, &value_type::flags, &value_type::tags>();
};

template<> struct jsonifier::core<sticker_data> {
	using value_type				 = sticker_data;
	static constexpr auto parseValue = createValue<&value_type::id, &value_type::name, &value_type::tags, &value_type::type, &value_type::format_type, &value_type::description,
		&value_type::asset, &value_type::available, &value_type::guild_id>();
};

template<> struct jsonifier::core<discord_message> {
	using value_type = discord_message;
	static constexpr auto parseValue =
		createValue<&value_type::id, &value_type::name, &value_type::icon, &value_type::description, &value_type::home_header, &value_type::splash, &value_type::discovery_splash,
			&value_type::features, &value_type::banner, &value_type::owner_id, &value_type::application_id, &value_type::region, &value_type::afk_channel_id,
			&value_type::afk_timeout, &value_type::system_channel_id, &value_type::system_channel_flags, &value_type::widget_enabled, &value_type::widget_channel_id,
			&value_type::verification_level, &value_type::roles, &value_type::default_message_notifications, &value_type::mfa_level, &value_type::explicit_content_filter,
			&value_type::max_presences, &value_type::max_members, &value_type::max_stage_video_channel_users, &value_type::max_video_channel_users, &value_type::vanity_url_code,
			&value_type::premium_tier, &value_type::premium_subscription_count, &value_type::preferred_locale, &value_type::rules_channel_id, &value_type::safety_alerts_channel_id,
			&value_type::public_updates_channel_id, &value_type::hub_type, &value_type::premium_progress_bar_enabled, &value_type::latest_onboarding_question_id, &value_type::nsfw,
			&value_type::nsfw_level, &value_type::emojis, &value_type::stickers, &value_type::incidents_data, &value_type::inventory_settings, &value_type::embed_enabled,
			&value_type::embed_channel_id, &value_type::approximate_member_count, &value_type::approximate_presence_count>();
};