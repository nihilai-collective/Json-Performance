/*
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2026 Nihilai Collective Corp
 * https://github.com/nihilai-collective/json-performance
 * include/github_events.hpp
 */

#pragma once

#include <common.hpp>

struct github_actor_data {
	std::string gravatar_id;
	std::string login;
	std::string avatar_url;
	std::string url;
	int64_t id;
};

struct github_user_data {
	std::string url;
	std::string gists_url;
	std::string gravatar_id;
	std::string type;
	std::string avatar_url;
	std::string subscriptions_url;
	std::string received_events_url;
	std::string organizations_url;
	std::string repos_url;
	std::string login;
	int64_t id;
	std::string starred_url;
	std::string events_url;
	std::string followers_url;
	std::string following_url;
};

struct github_comment_data {
	github_user_data user;
	std::string url;
	std::string issue_url;
	std::string created_at;
	std::string body;
	std::string updated_at;
	int64_t id;
};

struct github_author_data {
	std::string email;
	std::string name;
};

struct github_commit_data {
	std::string url;
	std::string message;
	bool distinct;
	std::string sha;
	github_author_data author;
};

struct github_forkee_data {
	std::string description;
	bool fork;
	std::string url;
	std::string language;
	std::string stargazers_url;
	std::string clone_url;
	std::string tags_url;
	std::string full_name;
	std::string merges_url;
	int64_t forks;
	bool privateVal;
	std::string git_refs_url;
	std::string archive_url;
	std::string collaborators_url;
	github_user_data owner;
	std::string languages_url;
	std::string trees_url;
	std::string labels_url;
	std::string html_url;
	std::string pushed_at;
	std::string created_at;
	bool has_issues;
	std::string forks_url;
	std::string branches_url;
	std::string commits_url;
	std::string notifications_url;
	int64_t open_issues;
	std::string contents_url;
	std::string blobs_url;
	std::string issues_url;
	std::string compare_url;
	std::string issue_events_url;
	std::string name;
	std::string updated_at;
	std::string statuses_url;
	int64_t forks_count;
	std::string assignees_url;
	std::string ssh_url;
	bool publicVal;
	bool has_wiki;
	std::string subscribers_url;
	std::optional<std::string> mirror_url;
	int64_t watchers_count;
	int64_t id;
	bool has_downloads;
	std::string git_commits_url;
	std::string downloads_url;
	std::string pulls_url;
	std::optional<std::string> homepage;
	std::string issue_comment_url;
	std::string hooks_url;
	std::string subscription_url;
	std::string milestones_url;
	std::string svn_url;
	std::string events_url;
	std::string git_tags_url;
	std::string teams_url;
	std::string comments_url;
	int64_t open_issues_count;
	std::string keys_url;
	std::string git_url;
	std::string contributors_url;
	int64_t size;
	int64_t watchers;
};

struct github_pull_request_data {
	std::optional<std::string> html_url;
	std::optional<std::string> patch_url;
	std::optional<std::string> diff_url;
};

struct github_issue_data {
	github_user_data user;
	std::string url;
	std::vector<std::string> labels;
	std::string html_url;
	std::string labels_url;
	github_pull_request_data pull_request;
	std::string created_at;
	std::optional<std::string> closed_at;
	std::optional<std::string> milestone;
	std::string title;
	std::string body;
	std::string updated_at;
	int64_t number;
	std::string state;
	std::optional<github_user_data> assignee;
	int64_t id;
	std::string events_url;
	std::string comments_url;
	int64_t comments;
};

struct github_page_data {
	std::string page_name;
	std::string html_url;
	std::string title;
	std::string sha;
	std::optional<std::string> summary;
	std::string action;
};

struct github_payload_data {
	std::optional<std::vector<github_commit_data>> commits;
	std::optional<int64_t> distinct_size;
	std::optional<std::string> ref;
	std::optional<int64_t> push_id;
	std::optional<std::string> head;
	std::optional<std::string> before;
	std::optional<int64_t> size;
	std::optional<std::string> description;
	std::optional<std::string> master_branch;
	std::optional<std::string> ref_type;
	std::optional<github_forkee_data> forkee;
	std::optional<std::string> action;
	std::optional<github_issue_data> issue;
	std::optional<github_comment_data> comment;
	std::optional<std::vector<github_page_data>> pages;
};

struct github_repo_data {
	std::string url;
	int64_t id;
	std::string name;
};

struct github_event_data {
	std::string type;
	std::string created_at;
	github_actor_data actor;
	github_repo_data repo;
	bool publicVal;
	github_payload_data payload;
	std::string id;
	std::optional<github_actor_data> org;
};

using github_events_message = std::vector<github_event_data>;

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, github_actor_data& data_new) {
	auto obj{ get_object(val_new) };
	get_field(obj, "gravatar_id", data_new.gravatar_id);
	get_field(obj, "login", data_new.login);
	get_field(obj, "avatar_url", data_new.avatar_url);
	get_field(obj, "url", data_new.url);
	get_field(obj, "id", data_new.id);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, github_user_data& data_new) {
	auto obj{ get_object(val_new) };
	get_field_unordered(obj, "url", data_new.url);
	get_field_unordered(obj, "gists_url", data_new.gists_url);
	get_field_unordered(obj, "gravatar_id", data_new.gravatar_id);
	get_field_unordered(obj, "type", data_new.type);
	get_field_unordered(obj, "avatar_url", data_new.avatar_url);
	get_field_unordered(obj, "subscriptions_url", data_new.subscriptions_url);
	get_field_unordered(obj, "received_events_url", data_new.received_events_url);
	get_field_unordered(obj, "organizations_url", data_new.organizations_url);
	get_field_unordered(obj, "repos_url", data_new.repos_url);
	get_field_unordered(obj, "login", data_new.login);
	get_field_unordered(obj, "id", data_new.id);
	get_field_unordered(obj, "starred_url", data_new.starred_url);
	get_field_unordered(obj, "events_url", data_new.events_url);
	get_field_unordered(obj, "followers_url", data_new.followers_url);
	get_field_unordered(obj, "following_url", data_new.following_url);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, github_comment_data& data_new) {
	auto obj{ get_object(val_new) };
	get_field(obj, "user", data_new.user);
	get_field(obj, "url", data_new.url);
	get_field(obj, "issue_url", data_new.issue_url);
	get_field(obj, "created_at", data_new.created_at);
	get_field(obj, "body", data_new.body);
	get_field(obj, "updated_at", data_new.updated_at);
	get_field(obj, "id", data_new.id);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, github_author_data& data_new) {
	auto obj{ get_object(val_new) };
	get_field(obj, "email", data_new.email);
	get_field(obj, "name", data_new.name);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, github_commit_data& data_new) {
	auto obj{ get_object(val_new) };
	get_field(obj, "url", data_new.url);
	get_field(obj, "message", data_new.message);
	get_field(obj, "distinct", data_new.distinct);
	get_field(obj, "sha", data_new.sha);
	get_field(obj, "author", data_new.author);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, github_forkee_data& data_new) {
	auto obj{ get_object(val_new) };
	get_field_unordered(obj, "description", data_new.description);
	get_field_unordered(obj, "fork", data_new.fork);
	get_field_unordered(obj, "url", data_new.url);
	get_field_unordered(obj, "language", data_new.language);
	get_field_unordered(obj, "stargazers_url", data_new.stargazers_url);
	get_field_unordered(obj, "clone_url", data_new.clone_url);
	get_field_unordered(obj, "tags_url", data_new.tags_url);
	get_field_unordered(obj, "full_name", data_new.full_name);
	get_field_unordered(obj, "merges_url", data_new.merges_url);
	get_field_unordered(obj, "forks", data_new.forks);
	get_field_unordered(obj, "private", data_new.privateVal);
	get_field_unordered(obj, "git_refs_url", data_new.git_refs_url);
	get_field_unordered(obj, "archive_url", data_new.archive_url);
	get_field_unordered(obj, "collaborators_url", data_new.collaborators_url);
	get_field_unordered(obj, "owner", data_new.owner);
	get_field_unordered(obj, "languages_url", data_new.languages_url);
	get_field_unordered(obj, "trees_url", data_new.trees_url);
	get_field_unordered(obj, "labels_url", data_new.labels_url);
	get_field_unordered(obj, "html_url", data_new.html_url);
	get_field_unordered(obj, "pushed_at", data_new.pushed_at);
	get_field_unordered(obj, "created_at", data_new.created_at);
	get_field_unordered(obj, "has_issues", data_new.has_issues);
	get_field_unordered(obj, "forks_url", data_new.forks_url);
	get_field_unordered(obj, "branches_url", data_new.branches_url);
	get_field_unordered(obj, "commits_url", data_new.commits_url);
	get_field_unordered(obj, "notifications_url", data_new.notifications_url);
	get_field_unordered(obj, "open_issues", data_new.open_issues);
	get_field_unordered(obj, "contents_url", data_new.contents_url);
	get_field_unordered(obj, "blobs_url", data_new.blobs_url);
	get_field_unordered(obj, "issues_url", data_new.issues_url);
	get_field_unordered(obj, "compare_url", data_new.compare_url);
	get_field_unordered(obj, "issue_events_url", data_new.issue_events_url);
	get_field_unordered(obj, "name", data_new.name);
	get_field_unordered(obj, "updated_at", data_new.updated_at);
	get_field_unordered(obj, "statuses_url", data_new.statuses_url);
	get_field_unordered(obj, "forks_count", data_new.forks_count);
	get_field_unordered(obj, "assignees_url", data_new.assignees_url);
	get_field_unordered(obj, "ssh_url", data_new.ssh_url);
	get_field_unordered(obj, "public", data_new.publicVal);
	get_field_unordered(obj, "has_wiki", data_new.has_wiki);
	get_field_unordered(obj, "subscribers_url", data_new.subscribers_url);
	get_field_unordered(obj, "mirror_url", data_new.mirror_url);
	get_field_unordered(obj, "watchers_count", data_new.watchers_count);
	get_field_unordered(obj, "id", data_new.id);
	get_field_unordered(obj, "has_downloads", data_new.has_downloads);
	get_field_unordered(obj, "git_commits_url", data_new.git_commits_url);
	get_field_unordered(obj, "downloads_url", data_new.downloads_url);
	get_field_unordered(obj, "pulls_url", data_new.pulls_url);
	get_field_unordered(obj, "homepage", data_new.homepage);
	get_field_unordered(obj, "issue_comment_url", data_new.issue_comment_url);
	get_field_unordered(obj, "hooks_url", data_new.hooks_url);
	get_field_unordered(obj, "subscription_url", data_new.subscription_url);
	get_field_unordered(obj, "milestones_url", data_new.milestones_url);
	get_field_unordered(obj, "svn_url", data_new.svn_url);
	get_field_unordered(obj, "events_url", data_new.events_url);
	get_field_unordered(obj, "git_tags_url", data_new.git_tags_url);
	get_field_unordered(obj, "teams_url", data_new.teams_url);
	get_field_unordered(obj, "comments_url", data_new.comments_url);
	get_field_unordered(obj, "open_issues_count", data_new.open_issues_count);
	get_field_unordered(obj, "keys_url", data_new.keys_url);
	get_field_unordered(obj, "git_url", data_new.git_url);
	get_field_unordered(obj, "contributors_url", data_new.contributors_url);
	get_field_unordered(obj, "size", data_new.size);
	get_field_unordered(obj, "watchers", data_new.watchers);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, github_pull_request_data& data_new) {
	auto obj{ get_object(val_new) };
	get_field(obj, "html_url", data_new.html_url);
	get_field(obj, "patch_url", data_new.patch_url);
	get_field(obj, "diff_url", data_new.diff_url);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, github_issue_data& data_new) {
	auto obj{ get_object(val_new) };
	get_field_unordered(obj, "user", data_new.user);
	get_field_unordered(obj, "url", data_new.url);
	get_field_unordered(obj, "labels", data_new.labels);
	get_field_unordered(obj, "html_url", data_new.html_url);
	get_field_unordered(obj, "labels_url", data_new.labels_url);
	get_field_unordered(obj, "pull_request", data_new.pull_request);
	get_field_unordered(obj, "created_at", data_new.created_at);
	get_field_unordered(obj, "closed_at", data_new.closed_at);
	get_field_unordered(obj, "milestone", data_new.milestone);
	get_field_unordered(obj, "title", data_new.title);
	get_field_unordered(obj, "body", data_new.body);
	get_field_unordered(obj, "updated_at", data_new.updated_at);
	get_field_unordered(obj, "number", data_new.number);
	get_field_unordered(obj, "state", data_new.state);
	get_field_unordered(obj, "assignee", data_new.assignee);
	get_field_unordered(obj, "id", data_new.id);
	get_field_unordered(obj, "events_url", data_new.events_url);
	get_field_unordered(obj, "comments_url", data_new.comments_url);
	get_field_unordered(obj, "comments", data_new.comments);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, github_page_data& data_new) {
	auto obj{ get_object(val_new) };
	get_field(obj, "page_name", data_new.page_name);
	get_field(obj, "html_url", data_new.html_url);
	get_field(obj, "title", data_new.title);
	get_field(obj, "sha", data_new.sha);
	get_field(obj, "summary", data_new.summary);
	get_field(obj, "action", data_new.action);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, github_payload_data& data_new) {
	auto obj{ get_object(val_new) };
	get_field_unordered(obj, "commits", data_new.commits);
	get_field_unordered(obj, "distinct_size", data_new.distinct_size);
	get_field_unordered(obj, "ref", data_new.ref);
	get_field_unordered(obj, "push_id", data_new.push_id);
	get_field_unordered(obj, "head", data_new.head);
	get_field_unordered(obj, "before", data_new.before);
	get_field_unordered(obj, "size", data_new.size);
	get_field_unordered(obj, "description", data_new.description);
	get_field_unordered(obj, "master_branch", data_new.master_branch);
	get_field_unordered(obj, "ref_type", data_new.ref_type);
	get_field_unordered(obj, "forkee", data_new.forkee);
	get_field_unordered(obj, "action", data_new.action);
	get_field_unordered(obj, "issue", data_new.issue);
	get_field_unordered(obj, "comment", data_new.comment);
	get_field_unordered(obj, "pages", data_new.pages);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, github_repo_data& data_new) {
	auto obj{ get_object(val_new) };
	get_field(obj, "url", data_new.url);
	get_field(obj, "id", data_new.id);
	get_field(obj, "name", data_new.name);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, github_event_data& data_new) {
	auto obj{ get_object(val_new) };
	get_field(obj, "type", data_new.type);
	get_field(obj, "created_at", data_new.created_at);
	get_field(obj, "actor", data_new.actor);
	get_field(obj, "repo", data_new.repo);
	get_field(obj, "public", data_new.publicVal);
	get_field(obj, "payload", data_new.payload);
	get_field(obj, "id", data_new.id);
	get_field(obj, "org", data_new.org);
}

template<> struct jsonifier::core<github_actor_data> {
	using value_type				 = github_actor_data;
	static constexpr auto parseValue = createValue<&value_type::gravatar_id, &value_type::login, &value_type::avatar_url, &value_type::url, &value_type::id>();
};

template<> struct jsonifier::core<github_user_data> {
	using value_type				 = github_user_data;
	static constexpr auto parseValue = createValue<&value_type::url, &value_type::gists_url, &value_type::gravatar_id, &value_type::type, &value_type::avatar_url,
		&value_type::subscriptions_url, &value_type::received_events_url, &value_type::organizations_url, &value_type::repos_url, &value_type::login, &value_type::id,
		&value_type::starred_url, &value_type::events_url, &value_type::followers_url, &value_type::following_url>();
};

template<> struct jsonifier::core<github_comment_data> {
	using value_type				 = github_comment_data;
	static constexpr auto parseValue = createValue<&value_type::user, &value_type::url, &value_type::issue_url, &value_type::created_at, &value_type::body,
		&value_type::updated_at, &value_type::id>();
};

template<> struct jsonifier::core<github_author_data> {
	using value_type				 = github_author_data;
	static constexpr auto parseValue = createValue<&value_type::email, &value_type::name>();
};

template<> struct jsonifier::core<github_commit_data> {
	using value_type				 = github_commit_data;
	static constexpr auto parseValue = createValue<&value_type::url, &value_type::message, &value_type::distinct, &value_type::sha, &value_type::author>();
};

template<> struct jsonifier::core<github_forkee_data> {
	using value_type				 = github_forkee_data;
	static constexpr auto parseValue = createValue<&value_type::description, &value_type::fork, &value_type::url, &value_type::language, &value_type::stargazers_url,
		&value_type::clone_url, &value_type::tags_url, &value_type::full_name, &value_type::merges_url, &value_type::forks, makeJsonEntity<&value_type::privateVal, "private">(),
		&value_type::git_refs_url, &value_type::archive_url, &value_type::collaborators_url, &value_type::owner, &value_type::languages_url, &value_type::trees_url,
		&value_type::labels_url, &value_type::html_url, &value_type::pushed_at, &value_type::created_at, &value_type::has_issues, &value_type::forks_url,
		&value_type::branches_url, &value_type::commits_url, &value_type::notifications_url, &value_type::open_issues, &value_type::contents_url, &value_type::blobs_url,
		&value_type::issues_url, &value_type::compare_url, &value_type::issue_events_url, &value_type::name, &value_type::updated_at, &value_type::statuses_url,
		&value_type::forks_count, &value_type::assignees_url, &value_type::ssh_url, makeJsonEntity<&value_type::publicVal, "public">(), &value_type::has_wiki,
		&value_type::subscribers_url, &value_type::mirror_url, &value_type::watchers_count, &value_type::id, &value_type::has_downloads, &value_type::git_commits_url,
		&value_type::downloads_url, &value_type::pulls_url, &value_type::homepage, &value_type::issue_comment_url, &value_type::hooks_url, &value_type::subscription_url,
		&value_type::milestones_url, &value_type::svn_url, &value_type::events_url, &value_type::git_tags_url, &value_type::teams_url, &value_type::comments_url,
		&value_type::open_issues_count, &value_type::keys_url, &value_type::git_url, &value_type::contributors_url, &value_type::size, &value_type::watchers>();
};

template<> struct jsonifier::core<github_pull_request_data> {
	using value_type				 = github_pull_request_data;
	static constexpr auto parseValue = createValue<&value_type::html_url, &value_type::patch_url, &value_type::diff_url>();
};

template<> struct jsonifier::core<github_issue_data> {
	using value_type				 = github_issue_data;
	static constexpr auto parseValue = createValue<&value_type::user, &value_type::url, &value_type::labels, &value_type::html_url, &value_type::labels_url,
		&value_type::pull_request, &value_type::created_at, &value_type::closed_at, &value_type::milestone, &value_type::title, &value_type::body, &value_type::updated_at,
		&value_type::number, &value_type::state, &value_type::assignee, &value_type::id, &value_type::events_url, &value_type::comments_url, &value_type::comments>();
};

template<> struct jsonifier::core<github_page_data> {
	using value_type				 = github_page_data;
	static constexpr auto parseValue = createValue<&value_type::page_name, &value_type::html_url, &value_type::title, &value_type::sha, &value_type::summary, &value_type::action>();
};

template<> struct jsonifier::core<github_payload_data> {
	using value_type				 = github_payload_data;
	static constexpr auto parseValue = createValue<&value_type::commits, &value_type::distinct_size, &value_type::ref, &value_type::push_id, &value_type::head,
		&value_type::before, &value_type::size, &value_type::description, &value_type::master_branch, &value_type::ref_type, &value_type::forkee, &value_type::action,
		&value_type::issue, &value_type::comment, &value_type::pages>();
};

template<> struct jsonifier::core<github_repo_data> {
	using value_type				 = github_repo_data;
	static constexpr auto parseValue = createValue<&value_type::url, &value_type::id, &value_type::name>();
};

template<> struct jsonifier::core<github_event_data> {
	using value_type				 = github_event_data;
	static constexpr auto parseValue = createValue<&value_type::type, &value_type::created_at, &value_type::actor, &value_type::repo,
		makeJsonEntity<&value_type::publicVal, "public">(), &value_type::payload, &value_type::id, &value_type::org>();
};

struct github_actor_data_reverse {
	int64_t id;
	std::string url;
	std::string avatar_url;
	std::string login;
	std::string gravatar_id;
};

struct github_user_data_reverse {
	std::string following_url;
	std::string followers_url;
	std::string events_url;
	std::string starred_url;
	int64_t id;
	std::string login;
	std::string repos_url;
	std::string organizations_url;
	std::string received_events_url;
	std::string subscriptions_url;
	std::string avatar_url;
	std::string type;
	std::string gravatar_id;
	std::string gists_url;
	std::string url;
};

struct github_comment_data_reverse {
	int64_t id;
	std::string updated_at;
	std::string body;
	std::string created_at;
	std::string issue_url;
	std::string url;
	github_user_data_reverse user;
};

struct github_author_data_reverse {
	std::string name;
	std::string email;
};

struct github_commit_data_reverse {
	github_author_data_reverse author;
	std::string sha;
	bool distinct;
	std::string message;
	std::string url;
};

struct github_forkee_data_reverse {
	int64_t watchers;
	int64_t size;
	std::string contributors_url;
	std::string git_url;
	std::string keys_url;
	int64_t open_issues_count;
	std::string comments_url;
	std::string teams_url;
	std::string git_tags_url;
	std::string events_url;
	std::string svn_url;
	std::string milestones_url;
	std::string subscription_url;
	std::string hooks_url;
	std::string issue_comment_url;
	std::optional<std::string> homepage;
	std::string pulls_url;
	std::string downloads_url;
	std::string git_commits_url;
	bool has_downloads;
	int64_t id;
	int64_t watchers_count;
	std::optional<std::string> mirror_url;
	std::string subscribers_url;
	bool has_wiki;
	bool publicVal;
	std::string ssh_url;
	std::string assignees_url;
	int64_t forks_count;
	std::string statuses_url;
	std::string updated_at;
	std::string name;
	std::string issue_events_url;
	std::string compare_url;
	std::string issues_url;
	std::string blobs_url;
	std::string contents_url;
	int64_t open_issues;
	std::string notifications_url;
	std::string commits_url;
	std::string branches_url;
	std::string forks_url;
	bool has_issues;
	std::string created_at;
	std::string pushed_at;
	std::string html_url;
	std::string labels_url;
	std::string trees_url;
	std::string languages_url;
	github_user_data_reverse owner;
	std::string collaborators_url;
	std::string archive_url;
	std::string git_refs_url;
	bool privateVal;
	int64_t forks;
	std::string merges_url;
	std::string full_name;
	std::string tags_url;
	std::string clone_url;
	std::string stargazers_url;
	std::string language;
	std::string url;
	bool fork;
	std::string description;
};

struct github_pull_request_data_reverse {
	std::optional<std::string> diff_url;
	std::optional<std::string> patch_url;
	std::optional<std::string> html_url;
};

struct github_issue_data_reverse {
	int64_t comments;
	std::string comments_url;
	std::string events_url;
	int64_t id;
	std::optional<github_user_data_reverse> assignee;
	std::string state;
	int64_t number;
	std::string updated_at;
	std::string body;
	std::string title;
	std::optional<std::string> milestone;
	std::optional<std::string> closed_at;
	std::string created_at;
	github_pull_request_data_reverse pull_request;
	std::string labels_url;
	std::string html_url;
	std::vector<std::string> labels;
	std::string url;
	github_user_data_reverse user;
};

struct github_page_data_reverse {
	std::string action;
	std::optional<std::string> summary;
	std::string sha;
	std::string title;
	std::string html_url;
	std::string page_name;
};

struct github_payload_data_reverse {
	std::optional<std::vector<github_page_data_reverse>> pages;
	std::optional<github_comment_data_reverse> comment;
	std::optional<github_issue_data_reverse> issue;
	std::optional<std::string> action;
	std::optional<github_forkee_data_reverse> forkee;
	std::optional<std::string> ref_type;
	std::optional<std::string> master_branch;
	std::optional<std::string> description;
	std::optional<int64_t> size;
	std::optional<std::string> before;
	std::optional<std::string> head;
	std::optional<int64_t> push_id;
	std::optional<std::string> ref;
	std::optional<int64_t> distinct_size;
	std::optional<std::vector<github_commit_data_reverse>> commits;
};

struct github_repo_data_reverse {
	std::string name;
	int64_t id;
	std::string url;
};

struct github_event_data_reverse {
	std::optional<github_actor_data_reverse> org;
	std::string id;
	github_payload_data_reverse payload;
	bool publicVal;
	github_repo_data_reverse repo;
	github_actor_data_reverse actor;
	std::string created_at;
	std::string type;
};

using github_events_message_reverse = std::vector<github_event_data_reverse>;

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, github_actor_data_reverse& data_new) {
	auto obj{ get_object(val_new) };
	get_field_unordered(obj, "id", data_new.id);
	get_field_unordered(obj, "url", data_new.url);
	get_field_unordered(obj, "avatar_url", data_new.avatar_url);
	get_field_unordered(obj, "login", data_new.login);
	get_field_unordered(obj, "gravatar_id", data_new.gravatar_id);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, github_user_data_reverse& data_new) {
	auto obj{ get_object(val_new) };
	get_field_unordered(obj, "following_url", data_new.following_url);
	get_field_unordered(obj, "followers_url", data_new.followers_url);
	get_field_unordered(obj, "events_url", data_new.events_url);
	get_field_unordered(obj, "starred_url", data_new.starred_url);
	get_field_unordered(obj, "id", data_new.id);
	get_field_unordered(obj, "login", data_new.login);
	get_field_unordered(obj, "repos_url", data_new.repos_url);
	get_field_unordered(obj, "organizations_url", data_new.organizations_url);
	get_field_unordered(obj, "received_events_url", data_new.received_events_url);
	get_field_unordered(obj, "subscriptions_url", data_new.subscriptions_url);
	get_field_unordered(obj, "avatar_url", data_new.avatar_url);
	get_field_unordered(obj, "type", data_new.type);
	get_field_unordered(obj, "gravatar_id", data_new.gravatar_id);
	get_field_unordered(obj, "gists_url", data_new.gists_url);
	get_field_unordered(obj, "url", data_new.url);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, github_comment_data_reverse& data_new) {
	auto obj{ get_object(val_new) };
	get_field_unordered(obj, "id", data_new.id);
	get_field_unordered(obj, "updated_at", data_new.updated_at);
	get_field_unordered(obj, "body", data_new.body);
	get_field_unordered(obj, "created_at", data_new.created_at);
	get_field_unordered(obj, "issue_url", data_new.issue_url);
	get_field_unordered(obj, "url", data_new.url);
	get_field_unordered(obj, "user", data_new.user);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, github_author_data_reverse& data_new) {
	auto obj{ get_object(val_new) };
	get_field_unordered(obj, "name", data_new.name);
	get_field_unordered(obj, "email", data_new.email);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, github_commit_data_reverse& data_new) {
	auto obj{ get_object(val_new) };
	get_field_unordered(obj, "author", data_new.author);
	get_field_unordered(obj, "sha", data_new.sha);
	get_field_unordered(obj, "distinct", data_new.distinct);
	get_field_unordered(obj, "message", data_new.message);
	get_field_unordered(obj, "url", data_new.url);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, github_forkee_data_reverse& data_new) {
	auto obj{ get_object(val_new) };
	get_field_unordered(obj, "watchers", data_new.watchers);
	get_field_unordered(obj, "size", data_new.size);
	get_field_unordered(obj, "contributors_url", data_new.contributors_url);
	get_field_unordered(obj, "git_url", data_new.git_url);
	get_field_unordered(obj, "keys_url", data_new.keys_url);
	get_field_unordered(obj, "open_issues_count", data_new.open_issues_count);
	get_field_unordered(obj, "comments_url", data_new.comments_url);
	get_field_unordered(obj, "teams_url", data_new.teams_url);
	get_field_unordered(obj, "git_tags_url", data_new.git_tags_url);
	get_field_unordered(obj, "events_url", data_new.events_url);
	get_field_unordered(obj, "svn_url", data_new.svn_url);
	get_field_unordered(obj, "milestones_url", data_new.milestones_url);
	get_field_unordered(obj, "subscription_url", data_new.subscription_url);
	get_field_unordered(obj, "hooks_url", data_new.hooks_url);
	get_field_unordered(obj, "issue_comment_url", data_new.issue_comment_url);
	get_field_unordered(obj, "homepage", data_new.homepage);
	get_field_unordered(obj, "pulls_url", data_new.pulls_url);
	get_field_unordered(obj, "downloads_url", data_new.downloads_url);
	get_field_unordered(obj, "git_commits_url", data_new.git_commits_url);
	get_field_unordered(obj, "has_downloads", data_new.has_downloads);
	get_field_unordered(obj, "id", data_new.id);
	get_field_unordered(obj, "watchers_count", data_new.watchers_count);
	get_field_unordered(obj, "mirror_url", data_new.mirror_url);
	get_field_unordered(obj, "subscribers_url", data_new.subscribers_url);
	get_field_unordered(obj, "has_wiki", data_new.has_wiki);
	get_field_unordered(obj, "public", data_new.publicVal);
	get_field_unordered(obj, "ssh_url", data_new.ssh_url);
	get_field_unordered(obj, "assignees_url", data_new.assignees_url);
	get_field_unordered(obj, "forks_count", data_new.forks_count);
	get_field_unordered(obj, "statuses_url", data_new.statuses_url);
	get_field_unordered(obj, "updated_at", data_new.updated_at);
	get_field_unordered(obj, "name", data_new.name);
	get_field_unordered(obj, "issue_events_url", data_new.issue_events_url);
	get_field_unordered(obj, "compare_url", data_new.compare_url);
	get_field_unordered(obj, "issues_url", data_new.issues_url);
	get_field_unordered(obj, "blobs_url", data_new.blobs_url);
	get_field_unordered(obj, "contents_url", data_new.contents_url);
	get_field_unordered(obj, "open_issues", data_new.open_issues);
	get_field_unordered(obj, "notifications_url", data_new.notifications_url);
	get_field_unordered(obj, "commits_url", data_new.commits_url);
	get_field_unordered(obj, "branches_url", data_new.branches_url);
	get_field_unordered(obj, "forks_url", data_new.forks_url);
	get_field_unordered(obj, "has_issues", data_new.has_issues);
	get_field_unordered(obj, "created_at", data_new.created_at);
	get_field_unordered(obj, "pushed_at", data_new.pushed_at);
	get_field_unordered(obj, "html_url", data_new.html_url);
	get_field_unordered(obj, "labels_url", data_new.labels_url);
	get_field_unordered(obj, "trees_url", data_new.trees_url);
	get_field_unordered(obj, "languages_url", data_new.languages_url);
	get_field_unordered(obj, "owner", data_new.owner);
	get_field_unordered(obj, "collaborators_url", data_new.collaborators_url);
	get_field_unordered(obj, "archive_url", data_new.archive_url);
	get_field_unordered(obj, "git_refs_url", data_new.git_refs_url);
	get_field_unordered(obj, "private", data_new.privateVal);
	get_field_unordered(obj, "forks", data_new.forks);
	get_field_unordered(obj, "merges_url", data_new.merges_url);
	get_field_unordered(obj, "full_name", data_new.full_name);
	get_field_unordered(obj, "tags_url", data_new.tags_url);
	get_field_unordered(obj, "clone_url", data_new.clone_url);
	get_field_unordered(obj, "stargazers_url", data_new.stargazers_url);
	get_field_unordered(obj, "language", data_new.language);
	get_field_unordered(obj, "url", data_new.url);
	get_field_unordered(obj, "fork", data_new.fork);
	get_field_unordered(obj, "description", data_new.description);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, github_pull_request_data_reverse& data_new) {
	auto obj{ get_object(val_new) };
	get_field_unordered(obj, "diff_url", data_new.diff_url);
	get_field_unordered(obj, "patch_url", data_new.patch_url);
	get_field_unordered(obj, "html_url", data_new.html_url);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, github_issue_data_reverse& data_new) {
	auto obj{ get_object(val_new) };
	get_field_unordered(obj, "comments", data_new.comments);
	get_field_unordered(obj, "comments_url", data_new.comments_url);
	get_field_unordered(obj, "events_url", data_new.events_url);
	get_field_unordered(obj, "id", data_new.id);
	get_field_unordered(obj, "assignee", data_new.assignee);
	get_field_unordered(obj, "state", data_new.state);
	get_field_unordered(obj, "number", data_new.number);
	get_field_unordered(obj, "updated_at", data_new.updated_at);
	get_field_unordered(obj, "body", data_new.body);
	get_field_unordered(obj, "title", data_new.title);
	get_field_unordered(obj, "milestone", data_new.milestone);
	get_field_unordered(obj, "closed_at", data_new.closed_at);
	get_field_unordered(obj, "created_at", data_new.created_at);
	get_field_unordered(obj, "pull_request", data_new.pull_request);
	get_field_unordered(obj, "labels_url", data_new.labels_url);
	get_field_unordered(obj, "html_url", data_new.html_url);
	get_field_unordered(obj, "labels", data_new.labels);
	get_field_unordered(obj, "url", data_new.url);
	get_field_unordered(obj, "user", data_new.user);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, github_page_data_reverse& data_new) {
	auto obj{ get_object(val_new) };
	get_field_unordered(obj, "action", data_new.action);
	get_field_unordered(obj, "summary", data_new.summary);
	get_field_unordered(obj, "sha", data_new.sha);
	get_field_unordered(obj, "title", data_new.title);
	get_field_unordered(obj, "html_url", data_new.html_url);
	get_field_unordered(obj, "page_name", data_new.page_name);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, github_payload_data_reverse& data_new) {
	auto obj{ get_object(val_new) };
	get_field_unordered(obj, "pages", data_new.pages);
	get_field_unordered(obj, "comment", data_new.comment);
	get_field_unordered(obj, "issue", data_new.issue);
	get_field_unordered(obj, "action", data_new.action);
	get_field_unordered(obj, "forkee", data_new.forkee);
	get_field_unordered(obj, "ref_type", data_new.ref_type);
	get_field_unordered(obj, "master_branch", data_new.master_branch);
	get_field_unordered(obj, "description", data_new.description);
	get_field_unordered(obj, "size", data_new.size);
	get_field_unordered(obj, "before", data_new.before);
	get_field_unordered(obj, "head", data_new.head);
	get_field_unordered(obj, "push_id", data_new.push_id);
	get_field_unordered(obj, "ref", data_new.ref);
	get_field_unordered(obj, "distinct_size", data_new.distinct_size);
	get_field_unordered(obj, "commits", data_new.commits);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, github_repo_data_reverse& data_new) {
	auto obj{ get_object(val_new) };
	get_field_unordered(obj, "name", data_new.name);
	get_field_unordered(obj, "id", data_new.id);
	get_field_unordered(obj, "url", data_new.url);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, github_event_data_reverse& data_new) {
	auto obj{ get_object(val_new) };
	get_field_unordered(obj, "org", data_new.org);
	get_field_unordered(obj, "id", data_new.id);
	get_field_unordered(obj, "payload", data_new.payload);
	get_field_unordered(obj, "public", data_new.publicVal);
	get_field_unordered(obj, "repo", data_new.repo);
	get_field_unordered(obj, "actor", data_new.actor);
	get_field_unordered(obj, "created_at", data_new.created_at);
	get_field_unordered(obj, "type", data_new.type);
}

template<> struct jsonifier::core<github_actor_data_reverse> {
	using value_type				 = github_actor_data_reverse;
	static constexpr auto parseValue = createValue<&value_type::id, &value_type::url, &value_type::avatar_url, &value_type::login, &value_type::gravatar_id>();
};

template<> struct jsonifier::core<github_user_data_reverse> {
	using value_type				 = github_user_data_reverse;
	static constexpr auto parseValue = createValue<&value_type::following_url, &value_type::followers_url, &value_type::events_url, &value_type::starred_url, &value_type::id,
		&value_type::login, &value_type::repos_url, &value_type::organizations_url, &value_type::received_events_url, &value_type::subscriptions_url, &value_type::avatar_url,
		&value_type::type, &value_type::gravatar_id, &value_type::gists_url, &value_type::url>();
};

template<> struct jsonifier::core<github_comment_data_reverse> {
	using value_type				 = github_comment_data_reverse;
	static constexpr auto parseValue = createValue<&value_type::id, &value_type::updated_at, &value_type::body, &value_type::created_at, &value_type::issue_url, &value_type::url,
		&value_type::user>();
};

template<> struct jsonifier::core<github_author_data_reverse> {
	using value_type				 = github_author_data_reverse;
	static constexpr auto parseValue = createValue<&value_type::name, &value_type::email>();
};

template<> struct jsonifier::core<github_commit_data_reverse> {
	using value_type				 = github_commit_data_reverse;
	static constexpr auto parseValue = createValue<&value_type::author, &value_type::sha, &value_type::distinct, &value_type::message, &value_type::url>();
};

template<> struct jsonifier::core<github_forkee_data_reverse> {
	using value_type				 = github_forkee_data_reverse;
	static constexpr auto parseValue = createValue<&value_type::watchers, &value_type::size, &value_type::contributors_url, &value_type::git_url, &value_type::keys_url,
		&value_type::open_issues_count, &value_type::comments_url, &value_type::teams_url, &value_type::git_tags_url, &value_type::events_url, &value_type::svn_url,
		&value_type::milestones_url, &value_type::subscription_url, &value_type::hooks_url, &value_type::issue_comment_url, &value_type::homepage, &value_type::pulls_url,
		&value_type::downloads_url, &value_type::git_commits_url, &value_type::has_downloads, &value_type::id, &value_type::watchers_count, &value_type::mirror_url,
		&value_type::subscribers_url, &value_type::has_wiki, makeJsonEntity<&value_type::publicVal, "public">(), &value_type::ssh_url, &value_type::assignees_url,
		&value_type::forks_count, &value_type::statuses_url, &value_type::updated_at, &value_type::name, &value_type::issue_events_url, &value_type::compare_url,
		&value_type::issues_url, &value_type::blobs_url, &value_type::contents_url, &value_type::open_issues, &value_type::notifications_url, &value_type::commits_url,
		&value_type::branches_url, &value_type::forks_url, &value_type::has_issues, &value_type::created_at, &value_type::pushed_at, &value_type::html_url,
		&value_type::labels_url, &value_type::trees_url, &value_type::languages_url, &value_type::owner, &value_type::collaborators_url, &value_type::archive_url,
		&value_type::git_refs_url, makeJsonEntity<&value_type::privateVal, "private">(), &value_type::forks, &value_type::merges_url, &value_type::full_name,
		&value_type::tags_url, &value_type::clone_url, &value_type::stargazers_url, &value_type::language, &value_type::url, &value_type::fork, &value_type::description>();
};

template<> struct jsonifier::core<github_pull_request_data_reverse> {
	using value_type				 = github_pull_request_data_reverse;
	static constexpr auto parseValue = createValue<&value_type::diff_url, &value_type::patch_url, &value_type::html_url>();
};

template<> struct jsonifier::core<github_issue_data_reverse> {
	using value_type				 = github_issue_data_reverse;
	static constexpr auto parseValue = createValue<&value_type::comments, &value_type::comments_url, &value_type::events_url, &value_type::id, &value_type::assignee,
		&value_type::state, &value_type::number, &value_type::updated_at, &value_type::body, &value_type::title, &value_type::milestone, &value_type::closed_at,
		&value_type::created_at, &value_type::pull_request, &value_type::labels_url, &value_type::html_url, &value_type::labels, &value_type::url, &value_type::user>();
};

template<> struct jsonifier::core<github_page_data_reverse> {
	using value_type				 = github_page_data_reverse;
	static constexpr auto parseValue = createValue<&value_type::action, &value_type::summary, &value_type::sha, &value_type::title, &value_type::html_url, &value_type::page_name>();
};

template<> struct jsonifier::core<github_payload_data_reverse> {
	using value_type				 = github_payload_data_reverse;
	static constexpr auto parseValue = createValue<&value_type::pages, &value_type::comment, &value_type::issue, &value_type::action, &value_type::forkee, &value_type::ref_type,
		&value_type::master_branch, &value_type::description, &value_type::size, &value_type::before, &value_type::head, &value_type::push_id, &value_type::ref,
		&value_type::distinct_size, &value_type::commits>();
};

template<> struct jsonifier::core<github_repo_data_reverse> {
	using value_type				 = github_repo_data_reverse;
	static constexpr auto parseValue = createValue<&value_type::name, &value_type::id, &value_type::url>();
};

template<> struct jsonifier::core<github_event_data_reverse> {
	using value_type				 = github_event_data_reverse;
	static constexpr auto parseValue = createValue<&value_type::org, &value_type::id, &value_type::payload, makeJsonEntity<&value_type::publicVal, "public">(), &value_type::repo,
		&value_type::actor, &value_type::created_at, &value_type::type>();
};

struct github_actor_sparse {
	std::string login;
};

struct github_repo_sparse {
	std::string name;
};

struct github_event_sparse {
	std::string type;
	github_actor_sparse actor;
	github_repo_sparse repo;
	std::string id;
};

using github_events_sparse_message = std::vector<github_event_sparse>;

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, github_actor_sparse& data_new) {
	auto obj{ get_object(val_new) };
	get_field(obj, "login", data_new.login);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, github_repo_sparse& data_new) {
	auto obj{ get_object(val_new) };
	get_field(obj, "name", data_new.name);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, github_event_sparse& data_new) {
	auto obj{ get_object(val_new) };
	get_field(obj, "type", data_new.type);
	get_field(obj, "actor", data_new.actor);
	get_field(obj, "repo", data_new.repo);
	get_field(obj, "id", data_new.id);
}

template<> struct jsonifier::core<github_actor_sparse> {
	using value_type				 = github_actor_sparse;
	static constexpr auto parseValue = createValue<&value_type::login>();
};

template<> struct jsonifier::core<github_repo_sparse> {
	using value_type				 = github_repo_sparse;
	static constexpr auto parseValue = createValue<&value_type::name>();
};

template<> struct jsonifier::core<github_event_sparse> {
	using value_type				 = github_event_sparse;
	static constexpr auto parseValue = createValue<&value_type::type, &value_type::actor, &value_type::repo, &value_type::id>();
};

struct github_event_sparse_reverse {
	std::string id;
	github_repo_sparse repo;
	github_actor_sparse actor;
	std::string type;
};

using github_events_sparse_message_reverse = std::vector<github_event_sparse_reverse>;

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, github_event_sparse_reverse& data_new) {
	auto obj{ get_object(val_new) };
	get_field_unordered(obj, "id", data_new.id);
	get_field_unordered(obj, "repo", data_new.repo);
	get_field_unordered(obj, "actor", data_new.actor);
	get_field_unordered(obj, "type", data_new.type);
}

template<> struct jsonifier::core<github_event_sparse_reverse> {
	using value_type				 = github_event_sparse_reverse;
	static constexpr auto parseValue = createValue<&value_type::id, &value_type::repo, &value_type::actor, &value_type::type>();
};
