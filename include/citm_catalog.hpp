/*
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2026 Nihilai Collective Corp
 * https://github.com/nihilai-collective/json-performance
 * include/citm_catalog.hpp
 */

#pragma once

#include <common.hpp>

struct audience_sub_category_names {
	std::string the337100890;
};

struct names {};

struct event {
	std::nullptr_t description;
	int64_t id;
	std::optional<std::string> logo;
	std::string name;
	std::vector<int64_t> subTopicIds;
	std::nullptr_t subjectCode;
	std::nullptr_t subtitle;
	std::vector<int64_t> topicIds;
};

struct price {
	int64_t amount;
	int64_t audienceSubCategoryId;
	int64_t seatCategoryId;
};

struct area {
	int64_t areaId;
	std::vector<std::nullptr_t> blockIds;
};

struct seat_category {
	std::vector<area> areas;
	int64_t seatCategoryId;
};

struct venue_names {
	std::string PLEYEL_PLEYEL;
};

struct performance {
	int64_t eventId;
	int64_t id;
	std::optional<std::string> logo;
	std::nullptr_t name;
	std::vector<price> prices;
	std::vector<seat_category> seatCategories;
	std::nullptr_t seatMapImage;
	int64_t start;
	std::string venueCode;
};

struct citm_catalog_message {
	std::unordered_map<std::string, std::string> areaNames;
	audience_sub_category_names audienceSubCategoryNames;
	names blockNames;
	std::unordered_map<std::string, event> events;
	std::vector<performance> performances;
	std::unordered_map<std::string, std::string> seatCategoryNames;
	std::unordered_map<std::string, std::string> subTopicNames;
	names subjectNames;
	std::unordered_map<std::string, std::string> topicNames;
	std::unordered_map<std::string, std::vector<int64_t>> topicSubTopics;
	venue_names venueNames;
};

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, audience_sub_category_names& data_new) {
	auto obj{ get_object(val_new) };
	get_field(obj, "337100890", data_new.the337100890);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, names&) {
	get_object(val_new);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, event& data_new) {
	auto obj{ get_object(val_new) };
	get_field(obj, "description", data_new.description);
	get_field(obj, "id", data_new.id);
	get_field(obj, "logo", data_new.logo);
	get_field(obj, "name", data_new.name);
	get_field(obj, "subTopicIds", data_new.subTopicIds);
	get_field(obj, "subjectCode", data_new.subjectCode);
	get_field(obj, "subtitle", data_new.subtitle);
	get_field(obj, "topicIds", data_new.topicIds);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, price& data_new) {
	auto obj{ get_object(val_new) };
	get_field(obj, "amount", data_new.amount);
	get_field(obj, "audienceSubCategoryId", data_new.audienceSubCategoryId);
	get_field(obj, "seatCategoryId", data_new.seatCategoryId);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, area& data_new) {
	auto obj{ get_object(val_new) };
	get_field(obj, "areaId", data_new.areaId);
	get_field(obj, "blockIds", data_new.blockIds);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, seat_category& data_new) {
	auto obj{ get_object(val_new) };
	get_field(obj, "areas", data_new.areas);
	get_field(obj, "seatCategoryId", data_new.seatCategoryId);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, venue_names& data_new) {
	auto obj{ get_object(val_new) };
	get_field(obj, "PLEYEL_PLEYEL", data_new.PLEYEL_PLEYEL);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, performance& data_new) {
	auto obj{ get_object(val_new) };
	get_field(obj, "eventId", data_new.eventId);
	get_field(obj, "id", data_new.id);
	get_field(obj, "logo", data_new.logo);
	get_field(obj, "name", data_new.name);
	get_field(obj, "prices", data_new.prices);
	get_field(obj, "seatCategories", data_new.seatCategories);
	get_field(obj, "seatMapImage", data_new.seatMapImage);
	get_field(obj, "start", data_new.start);
	get_field(obj, "venueCode", data_new.venueCode);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, citm_catalog_message& data_new) {
	auto obj{ get_object(val_new) };
	get_field(obj, "areaNames", data_new.areaNames);
	get_field(obj, "audienceSubCategoryNames", data_new.audienceSubCategoryNames);
	get_field(obj, "blockNames", data_new.blockNames);
	get_field(obj, "events", data_new.events);
	get_field(obj, "performances", data_new.performances);
	get_field(obj, "seatCategoryNames", data_new.seatCategoryNames);
	get_field(obj, "subTopicNames", data_new.subTopicNames);
	get_field(obj, "subjectNames", data_new.subjectNames);
	get_field(obj, "topicNames", data_new.topicNames);
	get_field(obj, "topicSubTopics", data_new.topicSubTopics);
	get_field(obj, "venueNames", data_new.venueNames);
}

template<> struct jsonifier::core<audience_sub_category_names> {
	using value_type				 = audience_sub_category_names;
	static constexpr auto parseValue = createValue<makeJsonEntity<&value_type::the337100890, "337100890">()>();
};

template<> struct jsonifier::core<names> {
	using value_type				 = names;
	static constexpr auto parseValue = createValue();
};

template<> struct jsonifier::core<event> {
	using value_type				 = event;
	static constexpr auto parseValue = createValue<&value_type::description, &value_type::id, &value_type::logo, &value_type::name, &value_type::subTopicIds,
		&value_type::subjectCode, &value_type::subtitle, &value_type::topicIds>();
};

template<> struct jsonifier::core<price> {
	using value_type				 = price;
	static constexpr auto parseValue = createValue<&value_type::amount, &value_type::audienceSubCategoryId, &value_type::seatCategoryId>();
};

template<> struct jsonifier::core<area> {
	using value_type				 = area;
	static constexpr auto parseValue = createValue<&value_type::areaId, &value_type::blockIds>();
};

template<> struct jsonifier::core<seat_category> {
	using value_type				 = seat_category;
	static constexpr auto parseValue = createValue<&value_type::areas, &value_type::seatCategoryId>();
};

template<> struct jsonifier::core<venue_names> {
	using value_type				 = venue_names;
	static constexpr auto parseValue = createValue<&value_type::PLEYEL_PLEYEL>();
};

template<> struct jsonifier::core<performance> {
	using value_type				 = performance;
	static constexpr auto parseValue = createValue<&value_type::eventId, &value_type::id, &value_type::logo, &value_type::name, &value_type::prices, &value_type::seatCategories,
		&value_type::seatMapImage, &value_type::start, &value_type::venueCode>();
};

template<> struct jsonifier::core<citm_catalog_message> {
	using value_type = citm_catalog_message;
	static constexpr auto parseValue =
		createValue<&value_type::areaNames, &value_type::audienceSubCategoryNames, &value_type::blockNames, &value_type::events, &value_type::performances,
			&value_type::seatCategoryNames, &value_type::subTopicNames, &value_type::subjectNames, &value_type::topicNames, &value_type::topicSubTopics, &value_type::venueNames>();
};

struct audience_sub_category_names_reverse {
	std::string the337100890;
};

struct names_reverse {};

struct event_reverse {
	std::vector<int64_t> topicIds;
	std::nullptr_t subtitle;
	std::nullptr_t subjectCode;
	std::vector<int64_t> subTopicIds;
	std::string name;
	std::optional<std::string> logo;
	int64_t id;
	std::nullptr_t description;
};

struct price_reverse {
	int64_t seatCategoryId;
	int64_t audienceSubCategoryId;
	int64_t amount;
};

struct area_reverse {
	std::vector<std::nullptr_t> blockIds;
	int64_t areaId;
};

struct seat_category_reverse {
	int64_t seatCategoryId;
	std::vector<area_reverse> areas;
};

struct venue_names_reverse {
	std::string PLEYEL_PLEYEL;
};

struct performance_reverse {
	std::string venueCode;
	int64_t start;
	std::nullptr_t seatMapImage;
	std::vector<seat_category_reverse> seatCategories;
	std::vector<price_reverse> prices;
	std::nullptr_t name;
	std::optional<std::string> logo;
	int64_t id;
	int64_t eventId;
};

struct citm_catalog_message_reverse {
	venue_names_reverse venueNames;
	std::unordered_map<std::string, std::vector<int64_t>> topicSubTopics;
	std::unordered_map<std::string, std::string> topicNames;
	names_reverse subjectNames;
	std::unordered_map<std::string, std::string> subTopicNames;
	std::unordered_map<std::string, std::string> seatCategoryNames;
	std::vector<performance_reverse> performances;
	std::unordered_map<std::string, event_reverse> events;
	names_reverse blockNames;
	audience_sub_category_names_reverse audienceSubCategoryNames;
	std::unordered_map<std::string, std::string> areaNames;
};

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, audience_sub_category_names_reverse& data_new) {
	auto obj{ get_object(val_new) };
	get_field_unordered(obj, "337100890", data_new.the337100890);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, names_reverse&) {
	get_object(val_new);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, event_reverse& data_new) {
	auto obj{ get_object(val_new) };
	get_field_unordered(obj, "topicIds", data_new.topicIds);
	get_field_unordered(obj, "subtitle", data_new.subtitle);
	get_field_unordered(obj, "subjectCode", data_new.subjectCode);
	get_field_unordered(obj, "subTopicIds", data_new.subTopicIds);
	get_field_unordered(obj, "name", data_new.name);
	get_field_unordered(obj, "logo", data_new.logo);
	get_field_unordered(obj, "id", data_new.id);
	get_field_unordered(obj, "description", data_new.description);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, price_reverse& data_new) {
	auto obj{ get_object(val_new) };
	get_field_unordered(obj, "seatCategoryId", data_new.seatCategoryId);
	get_field_unordered(obj, "audienceSubCategoryId", data_new.audienceSubCategoryId);
	get_field_unordered(obj, "amount", data_new.amount);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, area_reverse& data_new) {
	auto obj{ get_object(val_new) };
	get_field_unordered(obj, "blockIds", data_new.blockIds);
	get_field_unordered(obj, "areaId", data_new.areaId);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, seat_category_reverse& data_new) {
	auto obj{ get_object(val_new) };
	get_field_unordered(obj, "seatCategoryId", data_new.seatCategoryId);
	get_field_unordered(obj, "areas", data_new.areas);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, venue_names_reverse& data_new) {
	auto obj{ get_object(val_new) };
	get_field_unordered(obj, "PLEYEL_PLEYEL", data_new.PLEYEL_PLEYEL);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, performance_reverse& data_new) {
	auto obj{ get_object(val_new) };
	get_field_unordered(obj, "venueCode", data_new.venueCode);
	get_field_unordered(obj, "start", data_new.start);
	get_field_unordered(obj, "seatMapImage", data_new.seatMapImage);
	get_field_unordered(obj, "seatCategories", data_new.seatCategories);
	get_field_unordered(obj, "prices", data_new.prices);
	get_field_unordered(obj, "name", data_new.name);
	get_field_unordered(obj, "logo", data_new.logo);
	get_field_unordered(obj, "id", data_new.id);
	get_field_unordered(obj, "eventId", data_new.eventId);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, citm_catalog_message_reverse& data_new) {
	auto obj{ get_object(val_new) };
	get_field_unordered(obj, "venueNames", data_new.venueNames);
	get_field_unordered(obj, "topicSubTopics", data_new.topicSubTopics);
	get_field_unordered(obj, "topicNames", data_new.topicNames);
	get_field_unordered(obj, "subjectNames", data_new.subjectNames);
	get_field_unordered(obj, "subTopicNames", data_new.subTopicNames);
	get_field_unordered(obj, "seatCategoryNames", data_new.seatCategoryNames);
	get_field_unordered(obj, "performances", data_new.performances);
	get_field_unordered(obj, "events", data_new.events);
	get_field_unordered(obj, "blockNames", data_new.blockNames);
	get_field_unordered(obj, "audienceSubCategoryNames", data_new.audienceSubCategoryNames);
	get_field_unordered(obj, "areaNames", data_new.areaNames);
}

template<> struct jsonifier::core<audience_sub_category_names_reverse> {
	using value_type				 = audience_sub_category_names_reverse;
	static constexpr auto parseValue = createValue<&value_type::the337100890>();
};

template<> struct jsonifier::core<names_reverse> {
	using value_type				 = names_reverse;
	static constexpr auto parseValue = createValue();
};

template<> struct jsonifier::core<event_reverse> {
	using value_type				 = event_reverse;
	static constexpr auto parseValue = createValue<&value_type::topicIds, &value_type::subtitle, &value_type::subjectCode, &value_type::subTopicIds, &value_type::name, &value_type::logo, &value_type::id, &value_type::description>();
};

template<> struct jsonifier::core<price_reverse> {
	using value_type				 = price_reverse;
	static constexpr auto parseValue = createValue<&value_type::seatCategoryId, &value_type::audienceSubCategoryId, &value_type::amount>();
};

template<> struct jsonifier::core<area_reverse> {
	using value_type				 = area_reverse;
	static constexpr auto parseValue = createValue<&value_type::blockIds, &value_type::areaId>();
};

template<> struct jsonifier::core<seat_category_reverse> {
	using value_type				 = seat_category_reverse;
	static constexpr auto parseValue = createValue<&value_type::seatCategoryId, &value_type::areas>();
};

template<> struct jsonifier::core<venue_names_reverse> {
	using value_type				 = venue_names_reverse;
	static constexpr auto parseValue = createValue<&value_type::PLEYEL_PLEYEL>();
};

template<> struct jsonifier::core<performance_reverse> {
	using value_type				 = performance_reverse;
	static constexpr auto parseValue = createValue<&value_type::venueCode, &value_type::start, &value_type::seatMapImage, &value_type::seatCategories, &value_type::prices, &value_type::name, &value_type::logo, &value_type::id, &value_type::eventId>();
};

template<> struct jsonifier::core<citm_catalog_message_reverse> {
	using value_type				 = citm_catalog_message_reverse;
	static constexpr auto parseValue = createValue<&value_type::venueNames, &value_type::topicSubTopics, &value_type::topicNames, &value_type::subjectNames, &value_type::subTopicNames, &value_type::seatCategoryNames, &value_type::performances, &value_type::events, &value_type::blockNames, &value_type::audienceSubCategoryNames, &value_type::areaNames>();
};

struct citm_performance_sparse {
	int64_t id;
	int64_t start;
	std::string venueCode;
};

struct citm_catalog_sparse_message {
	std::vector<citm_performance_sparse> performances;
};

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, citm_performance_sparse& data_new) {
	auto obj{ get_object(val_new) };
	get_field(obj, "id", data_new.id);
	get_field(obj, "start", data_new.start);
	get_field(obj, "venueCode", data_new.venueCode);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, citm_catalog_sparse_message& data_new) {
	auto obj{ get_object(val_new) };
	get_field(obj, "performances", data_new.performances);
}

template<> struct jsonifier::core<citm_performance_sparse> {
	using value_type				 = citm_performance_sparse;
	static constexpr auto parseValue = createValue<&value_type::id, &value_type::start, &value_type::venueCode>();
};

template<> struct jsonifier::core<citm_catalog_sparse_message> {
	using value_type				 = citm_catalog_sparse_message;
	static constexpr auto parseValue = createValue<&value_type::performances>();
};

struct citm_performance_sparse_reverse {
	std::string venueCode;
	int64_t start;
	int64_t id;
};

struct citm_catalog_sparse_message_reverse {
	std::vector<citm_performance_sparse_reverse> performances;
};

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, citm_performance_sparse_reverse& data_new) {
	auto obj{ get_object(val_new) };
	get_field_unordered(obj, "venueCode", data_new.venueCode);
	get_field_unordered(obj, "start", data_new.start);
	get_field_unordered(obj, "id", data_new.id);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, citm_catalog_sparse_message_reverse& data_new) {
	auto obj{ get_object(val_new) };
	get_field_unordered(obj, "performances", data_new.performances);
}

template<> struct jsonifier::core<citm_performance_sparse_reverse> {
	using value_type				 = citm_performance_sparse_reverse;
	static constexpr auto parseValue = createValue<&value_type::venueCode, &value_type::start, &value_type::id>();
};

template<> struct jsonifier::core<citm_catalog_sparse_message_reverse> {
	using value_type				 = citm_catalog_sparse_message_reverse;
	static constexpr auto parseValue = createValue<&value_type::performances>();
};
