/*
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2026 Nihilai Collective Corp
 * https://github.com/nihilai-collective/json-performance
 * include/discord.hpp
 */

#pragma once

#include <common.hpp>

struct emoji_data {
	std::string id;
	std::string name;
	std::vector<std::optional<std::string>> roles;
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
	std::optional<std::string> guild_connections;
};

struct role_data {
	std::string id;
	std::string name;
	std::optional<std::string> description;
	std::string permissions;
	int64_t position;
	int64_t color;
	bool hoist;
	bool managed;
	bool mentionable;
	std::optional<std::string> icon;
	std::optional<std::string> unicode_emoji;
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
	std::optional<std::string> home_header;
	std::optional<std::string> splash;
	std::string discovery_splash;
	std::vector<std::string> features;
	std::optional<std::string> banner;
	std::string owner_id;
	std::optional<std::string> application_id;
	std::string region;
	std::optional<std::string> afk_channel_id;
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
	std::optional<std::string> max_presences;
	int64_t max_members;
	int64_t max_stage_video_channel_users;
	int64_t max_video_channel_users;
	std::optional<std::string> vanity_url_code;
	int64_t premium_tier;
	int64_t premium_subscription_count;
	std::string preferred_locale;
	std::string rules_channel_id;
	std::string safety_alerts_channel_id;
	std::string public_updates_channel_id;
	std::optional<std::string> hub_type;
	bool premium_progress_bar_enabled;
	std::string latest_onboarding_question_id;
	bool nsfw;
	int64_t nsfw_level;
	std::vector<emoji_data> emojis;
	std::vector<sticker_data> stickers;
	incidents_data_data incidents_data;
	std::optional<std::string> inventory_settings;
	bool embed_enabled;
	std::string embed_channel_id;
	int64_t approximate_member_count;
	int64_t approximate_presence_count;
};

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, emoji_data& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_fields<"id", "name", "roles", "require_colons", "managed", "animated", "available">(obj, data_new.id, data_new.name, data_new.roles, data_new.require_colons,
		data_new.managed, data_new.animated, data_new.available);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, incidents_data_data& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_fields<"invites_disabled_until", "dms_disabled_until">(obj, data_new.invites_disabled_until, data_new.dms_disabled_until);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, tags_data& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_fields<"bot_id", "guild_connections">(obj, data_new.bot_id, data_new.guild_connections);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, role_data& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_fields<"id", "name", "description", "permissions", "position", "color", "hoist", "managed", "mentionable", "icon", "unicode_emoji", "flags", "tags">(obj, data_new.id,
		data_new.name, data_new.description, data_new.permissions, data_new.position, data_new.color, data_new.hoist, data_new.managed, data_new.mentionable, data_new.icon,
		data_new.unicode_emoji, data_new.flags, data_new.tags);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, sticker_data& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_fields<"id", "name", "tags", "type", "format_type", "description", "asset", "available", "guild_id">(obj, data_new.id, data_new.name, data_new.tags, data_new.type,
		data_new.format_type, data_new.description, data_new.asset, data_new.available, data_new.guild_id);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, discord_message& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_fields<"id", "name", "icon", "description", "home_header", "splash", "discovery_splash", "features", "banner", "owner_id", "application_id", "region", "afk_channel_id",
		"afk_timeout", "system_channel_id", "system_channel_flags", "widget_enabled", "widget_channel_id", "verification_level", "roles", "default_message_notifications",
		"mfa_level", "explicit_content_filter", "max_presences", "max_members", "max_stage_video_channel_users", "max_video_channel_users", "vanity_url_code", "premium_tier",
		"premium_subscription_count", "preferred_locale", "rules_channel_id", "safety_alerts_channel_id", "public_updates_channel_id", "hub_type", "premium_progress_bar_enabled",
		"latest_onboarding_question_id", "nsfw", "nsfw_level", "emojis", "stickers", "incidents_data", "inventory_settings", "embed_enabled", "embed_channel_id",
		"approximate_member_count", "approximate_presence_count">(obj, data_new.id, data_new.name, data_new.icon, data_new.description, data_new.home_header, data_new.splash,
		data_new.discovery_splash, data_new.features, data_new.banner, data_new.owner_id, data_new.application_id, data_new.region, data_new.afk_channel_id, data_new.afk_timeout,
		data_new.system_channel_id, data_new.system_channel_flags, data_new.widget_enabled, data_new.widget_channel_id, data_new.verification_level, data_new.roles,
		data_new.default_message_notifications, data_new.mfa_level, data_new.explicit_content_filter, data_new.max_presences, data_new.max_members,
		data_new.max_stage_video_channel_users, data_new.max_video_channel_users, data_new.vanity_url_code, data_new.premium_tier, data_new.premium_subscription_count,
		data_new.preferred_locale, data_new.rules_channel_id, data_new.safety_alerts_channel_id, data_new.public_updates_channel_id, data_new.hub_type,
		data_new.premium_progress_bar_enabled, data_new.latest_onboarding_question_id, data_new.nsfw, data_new.nsfw_level, data_new.emojis, data_new.stickers,
		data_new.incidents_data, data_new.inventory_settings, data_new.embed_enabled, data_new.embed_channel_id, data_new.approximate_member_count,
		data_new.approximate_presence_count);
}

template<> struct glz::meta<emoji_data> {
	using value_type = emoji_data;
	static constexpr auto value =
		object(&value_type::id, &value_type::name, &value_type::roles, &value_type::require_colons, &value_type::managed, &value_type::animated, &value_type::available);
};

template<> struct glz::meta<incidents_data_data> {
	using value_type			= incidents_data_data;
	static constexpr auto value = object(&value_type::invites_disabled_until, &value_type::dms_disabled_until);
};

template<> struct glz::meta<tags_data> {
	using value_type			= tags_data;
	static constexpr auto value = object(&value_type::bot_id, &value_type::guild_connections);
};

template<> struct glz::meta<role_data> {
	using value_type			= role_data;
	static constexpr auto value = object(&value_type::id, &value_type::name, &value_type::description, &value_type::permissions, &value_type::position, &value_type::color,
		&value_type::hoist, &value_type::managed, &value_type::mentionable, &value_type::icon, &value_type::unicode_emoji, &value_type::flags, &value_type::tags);
};

template<> struct glz::meta<sticker_data> {
	using value_type			= sticker_data;
	static constexpr auto value = object(&value_type::id, &value_type::name, &value_type::tags, &value_type::type, &value_type::format_type, &value_type::description,
		&value_type::asset, &value_type::available, &value_type::guild_id);
};

template<> struct glz::meta<discord_message> {
	using value_type = discord_message;
	static constexpr auto value =
		object(&value_type::id, &value_type::name, &value_type::icon, &value_type::description, &value_type::home_header, &value_type::splash, &value_type::discovery_splash,
			&value_type::features, &value_type::banner, &value_type::owner_id, &value_type::application_id, &value_type::region, &value_type::afk_channel_id,
			&value_type::afk_timeout, &value_type::system_channel_id, &value_type::system_channel_flags, &value_type::widget_enabled, &value_type::widget_channel_id,
			&value_type::verification_level, &value_type::roles, &value_type::default_message_notifications, &value_type::mfa_level, &value_type::explicit_content_filter,
			&value_type::max_presences, &value_type::max_members, &value_type::max_stage_video_channel_users, &value_type::max_video_channel_users, &value_type::vanity_url_code,
			&value_type::premium_tier, &value_type::premium_subscription_count, &value_type::preferred_locale, &value_type::rules_channel_id, &value_type::safety_alerts_channel_id,
			&value_type::public_updates_channel_id, &value_type::hub_type, &value_type::premium_progress_bar_enabled, &value_type::latest_onboarding_question_id, &value_type::nsfw,
			&value_type::nsfw_level, &value_type::emojis, &value_type::stickers, &value_type::incidents_data, &value_type::inventory_settings, &value_type::embed_enabled,
			&value_type::embed_channel_id, &value_type::approximate_member_count, &value_type::approximate_presence_count);
};

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