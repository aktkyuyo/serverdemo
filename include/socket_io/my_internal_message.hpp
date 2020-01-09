#pragma once

#include <deque>

class my_internal_message
{
	struct header
	{
		std::size_t check_num_ = 0;
		std::size_t total_size_ = 0;
		std::size_t body_length_ = 0;
	};

public:
	enum { header_length = sizeof(header)};
	enum { max_body_length = 4 * 1024};

	my_internal_message() : data_{} {}

	const char* data() const
	{
		return data_;
	}

	char* data()
	{
		return data_;
	}

	std::size_t length() const
	{
		return header_length + header_.body_length_;
	}

	const char* body() const
	{
		return data_ + header_length;
	}

	char* body()
	{
		return data_ + header_length;
	}

	std::size_t total_size() const
	{
		return header_.total_size_;
	}

	std::size_t body_length() const
	{
		return header_.body_length_;
	}

	void body_length(std::size_t new_length)
	{
		header_.body_length_ = new_length;
		if (header_.body_length_ > max_body_length)
			header_.body_length_ = max_body_length;
	}

	std::size_t check_num() const { return header_.check_num_; }

	void check_num(std::size_t check_num_)
	{
		if (header_.check_num_ != check_num_)
		{
			header_.check_num_ = check_num_;
		}
	}

	void total_size(std::size_t size)
	{
		header_.total_size_ = size;
	}

	bool decode_header()
	{
		std::memcpy(&header_, data_, header_length);
		if (header_.body_length_ > max_body_length)
		{
			header_.body_length_ = 0;
			return false;
		}
		return true;
	}

	void encode_header()
	{
		std::memcpy(data_, &header_, header_length);
	}

private:
	char data_[header_length + max_body_length];
	header header_;
};

enum { max_recent_msg_count = 100 * 1024};
typedef std::deque<my_internal_message> my_message_queue;
