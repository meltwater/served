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

#ifndef SERVED_CONNECTION_MANAGER_HPP
#define SERVED_CONNECTION_MANAGER_HPP

#include <set>
#include <mutex>

#include <served/net/connection.hpp>

namespace served { namespace net {

/*
 * Oversees a stack of open HTTP connections.
 *
 * The connection manager is used for easily tracking any remaining open HTTP connections, and
 * shutting down those connections in order to gracefully close.
 */
class connection_manager
{
	std::set<connection_ptr> _connections;
	std::mutex               _connections_mutex;

public:
	connection_manager(const connection_manager&) = delete;

	connection_manager& operator=(const connection_manager&) = delete;

	connection_manager();

	/*
	 * Adds a new connection to the stack and prompts it to begin.
	 *
	 * @param c a pointer to a new connection
	 */
	void start(connection_ptr c);

	/*
	 * Stops a connection and removes it from the stack.
	 *
	 * @param c a pointer to an open connection
	 */
	void stop(connection_ptr c);

	/*
	 * Stops all remaining open connections.
	 */
	void stop_all();

    ~connection_manager();
};

} } // net, served

#endif // SERVED_CONNECTION_MANAGER_HPP
