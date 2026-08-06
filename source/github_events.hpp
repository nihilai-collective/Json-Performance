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

struct actor_data {
	std::string gravatar_id;
	std::string login;
	std::string avatar_url;
	std::string url;
	int64_t id;
};

struct github_user {
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

struct comment_data {
	github_user user;
	std::string url;
	std::string issue_url;
	std::string created_at;
	std::string body;
	std::string updated_at;
	int64_t id;
};

struct author_data {
	std::string email;
	std::string name;
};

struct commit {
	std::string url;
	std::string message;
	bool distinct;
	std::string sha;
	author_data author;
};

struct label_data {
	std::string url;
	std::string name;
	std::string color;
};

struct forkee_data {
	std::optional<std::string> description;
	bool fork;
	std::string url;
	std::optional<std::string> language;
	std::string stargazers_url;
	std::string clone_url;
	std::string tags_url;
	std::string full_name;
	std::string merges_url;
	int64_t forks;
	bool is_private;
	std::string git_refs_url;
	std::string archive_url;
	std::string collaborators_url;
	github_user owner;
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
	bool is_public;
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

struct pull_request_data {
	std::optional<std::string> html_url;
	std::optional<std::string> patch_url;
	std::optional<std::string> diff_url;
};

struct issue_data {
	github_user user;
	std::string url;
	std::vector<label_data> labels;
	std::string html_url;
	std::string labels_url;
	pull_request_data pull_request;
	std::string created_at;
	std::optional<std::string> closed_at;
	std::optional<std::string> milestone;
	std::string title;
	std::string body;
	std::string updated_at;
	int64_t number;
	std::string state;
	std::optional<github_user> assignee;
	int64_t id;
	std::string events_url;
	std::string comments_url;
	int64_t comments;
};

struct page {
	std::string page_name;
	std::string html_url;
	std::string title;
	std::string sha;
	std::optional<std::string> summary;
	std::string action;
};

struct payload_data {
	std::optional<std::vector<commit>> commits;
	std::optional<int64_t> distinct_size;
	std::optional<std::string> ref;
	std::optional<int64_t> push_id;
	std::optional<std::string> head;
	std::optional<std::string> before;
	std::optional<int64_t> size;
	std::optional<std::string> description;
	std::optional<std::string> master_branch;
	std::optional<std::string> ref_type;
	std::optional<forkee_data> forkee;
	std::optional<std::string> action;
	std::optional<issue_data> issue;
	std::optional<comment_data> comment;
	std::optional<std::vector<page>> pages;
};

struct repo_data {
	std::string url;
	int64_t id;
	std::string name;
};

struct github_event {
	std::string type;
	std::string created_at;
	actor_data actor;
	repo_data repo;
	bool is_public;
	payload_data payload;
	std::string id;
	std::optional<actor_data> org;
};

using github_events_message = std::vector<github_event>;

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, actor_data& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_field(obj, "gravatar_id", data_new.gravatar_id);
	get_field(obj, "login", data_new.login);
	get_field(obj, "avatar_url", data_new.avatar_url);
	get_field(obj, "url", data_new.url);
	get_field(obj, "id", data_new.id);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, github_user& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_field(obj, "url", data_new.url);
	get_field(obj, "gists_url", data_new.gists_url);
	get_field(obj, "gravatar_id", data_new.gravatar_id);
	get_field(obj, "type", data_new.type);
	get_field(obj, "avatar_url", data_new.avatar_url);
	get_field(obj, "subscriptions_url", data_new.subscriptions_url);
	get_field(obj, "received_events_url", data_new.received_events_url);
	get_field(obj, "organizations_url", data_new.organizations_url);
	get_field(obj, "repos_url", data_new.repos_url);
	get_field(obj, "login", data_new.login);
	get_field(obj, "id", data_new.id);
	get_field(obj, "starred_url", data_new.starred_url);
	get_field(obj, "events_url", data_new.events_url);
	get_field(obj, "followers_url", data_new.followers_url);
	get_field(obj, "following_url", data_new.following_url);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, comment_data& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_field(obj, "user", data_new.user);
	get_field(obj, "url", data_new.url);
	get_field(obj, "issue_url", data_new.issue_url);
	get_field(obj, "created_at", data_new.created_at);
	get_field(obj, "body", data_new.body);
	get_field(obj, "updated_at", data_new.updated_at);
	get_field(obj, "id", data_new.id);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, author_data& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_field(obj, "email", data_new.email);
	get_field(obj, "name", data_new.name);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, commit& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_field(obj, "url", data_new.url);
	get_field(obj, "message", data_new.message);
	get_field(obj, "distinct", data_new.distinct);
	get_field(obj, "sha", data_new.sha);
	get_field(obj, "author", data_new.author);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, label_data& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_field(obj, "url", data_new.url);
	get_field(obj, "name", data_new.name);
	get_field(obj, "color", data_new.color);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, forkee_data& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_field(obj, "description", data_new.description);
	get_field(obj, "fork", data_new.fork);
	get_field(obj, "url", data_new.url);
	get_field(obj, "language", data_new.language);
	get_field(obj, "stargazers_url", data_new.stargazers_url);
	get_field(obj, "clone_url", data_new.clone_url);
	get_field(obj, "tags_url", data_new.tags_url);
	get_field(obj, "full_name", data_new.full_name);
	get_field(obj, "merges_url", data_new.merges_url);
	get_field(obj, "forks", data_new.forks);
	get_field(obj, "private", data_new.is_private);
	get_field(obj, "git_refs_url", data_new.git_refs_url);
	get_field(obj, "archive_url", data_new.archive_url);
	get_field(obj, "collaborators_url", data_new.collaborators_url);
	get_field(obj, "owner", data_new.owner);
	get_field(obj, "languages_url", data_new.languages_url);
	get_field(obj, "trees_url", data_new.trees_url);
	get_field(obj, "labels_url", data_new.labels_url);
	get_field(obj, "html_url", data_new.html_url);
	get_field(obj, "pushed_at", data_new.pushed_at);
	get_field(obj, "created_at", data_new.created_at);
	get_field(obj, "has_issues", data_new.has_issues);
	get_field(obj, "forks_url", data_new.forks_url);
	get_field(obj, "branches_url", data_new.branches_url);
	get_field(obj, "commits_url", data_new.commits_url);
	get_field(obj, "notifications_url", data_new.notifications_url);
	get_field(obj, "open_issues", data_new.open_issues);
	get_field(obj, "contents_url", data_new.contents_url);
	get_field(obj, "blobs_url", data_new.blobs_url);
	get_field(obj, "issues_url", data_new.issues_url);
	get_field(obj, "compare_url", data_new.compare_url);
	get_field(obj, "issue_events_url", data_new.issue_events_url);
	get_field(obj, "name", data_new.name);
	get_field(obj, "updated_at", data_new.updated_at);
	get_field(obj, "statuses_url", data_new.statuses_url);
	get_field(obj, "forks_count", data_new.forks_count);
	get_field(obj, "assignees_url", data_new.assignees_url);
	get_field(obj, "ssh_url", data_new.ssh_url);
	get_field(obj, "public", data_new.is_public);
	get_field(obj, "has_wiki", data_new.has_wiki);
	get_field(obj, "subscribers_url", data_new.subscribers_url);
	get_field(obj, "mirror_url", data_new.mirror_url);
	get_field(obj, "watchers_count", data_new.watchers_count);
	get_field(obj, "id", data_new.id);
	get_field(obj, "has_downloads", data_new.has_downloads);
	get_field(obj, "git_commits_url", data_new.git_commits_url);
	get_field(obj, "downloads_url", data_new.downloads_url);
	get_field(obj, "pulls_url", data_new.pulls_url);
	get_field(obj, "homepage", data_new.homepage);
	get_field(obj, "issue_comment_url", data_new.issue_comment_url);
	get_field(obj, "hooks_url", data_new.hooks_url);
	get_field(obj, "subscription_url", data_new.subscription_url);
	get_field(obj, "milestones_url", data_new.milestones_url);
	get_field(obj, "svn_url", data_new.svn_url);
	get_field(obj, "events_url", data_new.events_url);
	get_field(obj, "git_tags_url", data_new.git_tags_url);
	get_field(obj, "teams_url", data_new.teams_url);
	get_field(obj, "comments_url", data_new.comments_url);
	get_field(obj, "open_issues_count", data_new.open_issues_count);
	get_field(obj, "keys_url", data_new.keys_url);
	get_field(obj, "git_url", data_new.git_url);
	get_field(obj, "contributors_url", data_new.contributors_url);
	get_field(obj, "size", data_new.size);
	get_field(obj, "watchers", data_new.watchers);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, pull_request_data& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_field(obj, "html_url", data_new.html_url);
	get_field(obj, "patch_url", data_new.patch_url);
	get_field(obj, "diff_url", data_new.diff_url);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, issue_data& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_field(obj, "user", data_new.user);
	get_field(obj, "url", data_new.url);
	get_field(obj, "labels", data_new.labels);
	get_field(obj, "html_url", data_new.html_url);
	get_field(obj, "labels_url", data_new.labels_url);
	get_field(obj, "pull_request", data_new.pull_request);
	get_field(obj, "created_at", data_new.created_at);
	get_field(obj, "closed_at", data_new.closed_at);
	get_field(obj, "milestone", data_new.milestone);
	get_field(obj, "title", data_new.title);
	get_field(obj, "body", data_new.body);
	get_field(obj, "updated_at", data_new.updated_at);
	get_field(obj, "number", data_new.number);
	get_field(obj, "state", data_new.state);
	get_field(obj, "assignee", data_new.assignee);
	get_field(obj, "id", data_new.id);
	get_field(obj, "events_url", data_new.events_url);
	get_field(obj, "comments_url", data_new.comments_url);
	get_field(obj, "comments", data_new.comments);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, page& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_field(obj, "page_name", data_new.page_name);
	get_field(obj, "html_url", data_new.html_url);
	get_field(obj, "title", data_new.title);
	get_field(obj, "sha", data_new.sha);
	get_field(obj, "summary", data_new.summary);
	get_field(obj, "action", data_new.action);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, payload_data& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_field(obj, "commits", data_new.commits);
	get_field(obj, "distinct_size", data_new.distinct_size);
	get_field(obj, "ref", data_new.ref);
	get_field(obj, "push_id", data_new.push_id);
	get_field(obj, "head", data_new.head);
	get_field(obj, "before", data_new.before);
	get_field(obj, "size", data_new.size);
	get_field(obj, "description", data_new.description);
	get_field(obj, "master_branch", data_new.master_branch);
	get_field(obj, "ref_type", data_new.ref_type);
	get_field(obj, "forkee", data_new.forkee);
	get_field(obj, "action", data_new.action);
	get_field(obj, "issue", data_new.issue);
	get_field(obj, "comment", data_new.comment);
	get_field(obj, "pages", data_new.pages);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, repo_data& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_field(obj, "url", data_new.url);
	get_field(obj, "id", data_new.id);
	get_field(obj, "name", data_new.name);
}

template<document_or_value simdjson_type> inline void get_value(simdjson_type val_new, github_event& data_new) {
	simdjson::ondemand::object obj{ get_object(val_new) };
	get_field(obj, "type", data_new.type);
	get_field(obj, "created_at", data_new.created_at);
	get_field(obj, "actor", data_new.actor);
	get_field(obj, "repo", data_new.repo);
	get_field(obj, "public", data_new.is_public);
	get_field(obj, "payload", data_new.payload);
	get_field(obj, "id", data_new.id);
	get_field(obj, "org", data_new.org);
}

template<> struct jsonifier::core<actor_data> {
	using value_type				 = actor_data;
	static constexpr auto parseValue = createValue<&value_type::gravatar_id, &value_type::login, &value_type::avatar_url, &value_type::url, &value_type::id>();
};

template<> struct jsonifier::core<github_user> {
	using value_type				 = github_user;
	static constexpr auto parseValue = createValue<&value_type::url, &value_type::gists_url, &value_type::gravatar_id, &value_type::type, &value_type::avatar_url,
		&value_type::subscriptions_url, &value_type::received_events_url, &value_type::organizations_url, &value_type::repos_url, &value_type::login, &value_type::id,
		&value_type::starred_url, &value_type::events_url, &value_type::followers_url, &value_type::following_url>();
};

template<> struct jsonifier::core<comment_data> {
	using value_type = comment_data;
	static constexpr auto parseValue =
		createValue<&value_type::user, &value_type::url, &value_type::issue_url, &value_type::created_at, &value_type::body, &value_type::updated_at, &value_type::id>();
};

template<> struct jsonifier::core<author_data> {
	using value_type				 = author_data;
	static constexpr auto parseValue = createValue<&value_type::email, &value_type::name>();
};

template<> struct jsonifier::core<commit> {
	using value_type				 = commit;
	static constexpr auto parseValue = createValue<&value_type::url, &value_type::message, &value_type::distinct, &value_type::sha, &value_type::author>();
};

template<> struct jsonifier::core<label_data> {
	using value_type				 = label_data;
	static constexpr auto parseValue = createValue<&value_type::url, &value_type::name, &value_type::color>();
};

template<> struct jsonifier::core<forkee_data> {
	using value_type				 = forkee_data;
	static constexpr auto parseValue = createValue<&value_type::description, &value_type::fork, &value_type::url, &value_type::language, &value_type::stargazers_url,
		&value_type::clone_url, &value_type::tags_url, &value_type::full_name, &value_type::merges_url, &value_type::forks, makeJsonEntity<&value_type::is_private, "private">(),
		&value_type::git_refs_url, &value_type::archive_url, &value_type::collaborators_url, &value_type::owner, &value_type::languages_url, &value_type::trees_url,
		&value_type::labels_url, &value_type::html_url, &value_type::pushed_at, &value_type::created_at, &value_type::has_issues, &value_type::forks_url, &value_type::branches_url,
		&value_type::commits_url, &value_type::notifications_url, &value_type::open_issues, &value_type::contents_url, &value_type::blobs_url, &value_type::issues_url,
		&value_type::compare_url, &value_type::issue_events_url, &value_type::name, &value_type::updated_at, &value_type::statuses_url, &value_type::forks_count,
		&value_type::assignees_url, &value_type::ssh_url, makeJsonEntity<&value_type::is_public, "public">(), &value_type::has_wiki, &value_type::subscribers_url,
		&value_type::mirror_url, &value_type::watchers_count, &value_type::id, &value_type::has_downloads, &value_type::git_commits_url, &value_type::downloads_url,
		&value_type::pulls_url, &value_type::homepage, &value_type::issue_comment_url, &value_type::hooks_url, &value_type::subscription_url, &value_type::milestones_url,
		&value_type::svn_url, &value_type::events_url, &value_type::git_tags_url, &value_type::teams_url, &value_type::comments_url, &value_type::open_issues_count,
		&value_type::keys_url, &value_type::git_url, &value_type::contributors_url, &value_type::size, &value_type::watchers>();
};

template<> struct jsonifier::core<pull_request_data> {
	using value_type				 = pull_request_data;
	static constexpr auto parseValue = createValue<&value_type::html_url, &value_type::patch_url, &value_type::diff_url>();
};

template<> struct jsonifier::core<issue_data> {
	using value_type				 = issue_data;
	static constexpr auto parseValue = createValue<&value_type::user, &value_type::url, &value_type::labels, &value_type::html_url, &value_type::labels_url,
		&value_type::pull_request, &value_type::created_at, &value_type::closed_at, &value_type::milestone, &value_type::title, &value_type::body, &value_type::updated_at,
		&value_type::number, &value_type::state, &value_type::assignee, &value_type::id, &value_type::events_url, &value_type::comments_url, &value_type::comments>();
};

template<> struct jsonifier::core<page> {
	using value_type = page;
	static constexpr auto parseValue =
		createValue<&value_type::page_name, &value_type::html_url, &value_type::title, &value_type::sha, &value_type::summary, &value_type::action>();
};

template<> struct jsonifier::core<payload_data> {
	using value_type				 = payload_data;
	static constexpr auto parseValue = createValue<&value_type::commits, &value_type::distinct_size, &value_type::ref, &value_type::push_id, &value_type::head, &value_type::before,
		&value_type::size, &value_type::description, &value_type::master_branch, &value_type::ref_type, &value_type::forkee, &value_type::action, &value_type::issue,
		&value_type::comment, &value_type::pages>();
};

template<> struct jsonifier::core<repo_data> {
	using value_type				 = repo_data;
	static constexpr auto parseValue = createValue<&value_type::url, &value_type::id, &value_type::name>();
};

template<> struct jsonifier::core<github_event> {
	using value_type				 = github_event;
	static constexpr auto parseValue = createValue<&value_type::type, &value_type::created_at, &value_type::actor, &value_type::repo,
		makeJsonEntity<&value_type::is_public, "public">(), &value_type::payload, &value_type::id, &value_type::org>();
};