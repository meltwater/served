/*
 * Copyright (C) 2014 MediaSift Ltd.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "connection.hpp"
// #include "connection_manager.hpp"
// //#include "request_handler.hpp"

// #include <utility>
// #include <vector>

// using namespace served::server;

// connection::connection(boost::asio::ip::tcp::socket socket,
// 		connection_manager& manager, request_handler& handler)
// 	: d_socket(std::move(socket))
// 	, d_connection_manager(manager)
// 	//, d_request_handler(handler)
// {}

// void
// connection::start() {
// 	do_read();
// }

// void
// connection::stop() {
// 	d_socket.close();
// }

// void
// connection::do_read() {
// 	auto self(shared_from_this());
// 	d_socket.async_read_some(boost::asio::buffer(buffer_),
// 		[this, self](boost::system::error_code ec, std::size_t bytes_transferred) {
// 			if (!ec) {
// 				request_parser::result_type result;
// 				std::tie(result, std::ignore) = request_parser_.parse(
// 						request_, buffer_.data(), buffer_.data() + bytes_transferred);

// 				if (result == request_parser::good) {
// 					//d_request_handler.handle_request(request_, reply_);
// 					do_write();
// 				} else if (result == request_parser::bad) {
// 					reply_ = reply::stock_reply(reply::bad_request);
// 					do_write();
// 				} else {
// 					do_read();
// 				}
// 			} else if (ec != boost::asio::error::operation_aborted) {
// 				d_connection_manager.stop(shared_from_this());
// 			}
// 		}
// 	);
// }

// void
// connection::do_write() {
// 	auto self(shared_from_this());
// 	boost::asio::async_write(d_socket, reply_.to_buffers(),
// 		[this, self](boost::system::error_code ec, std::size_t) {
// 			if (!ec) {
// 				// Initiate graceful connection closure.
// 				boost::system::error_code ignored_ec;
// 				d_socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both,
// 					ignored_ec);
// 			}

// 			if (ec != boost::asio::error::operation_aborted) {
// 				d_connection_manager.stop(shared_from_this());
// 			}
// 		}
// 	);
// }
