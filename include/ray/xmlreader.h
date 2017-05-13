// +----------------------------------------------------------------------
// | Project : ray.
// | All rights reserved.
// +----------------------------------------------------------------------
// | Copyright (c) 2013-2017.
// +----------------------------------------------------------------------
// | * Redistribution and use of this software in source and binary forms,
// |   with or without modification, are permitted provided that the following
// |   conditions are met:
// |
// | * Redistributions of source code must retain the above
// |   copyright notice, this list of conditions and the
// |   following disclaimer.
// |
// | * Redistributions in binary form must reproduce the above
// |   copyright notice, this list of conditions and the
// |   following disclaimer in the documentation and/or other
// |   materials provided with the distribution.
// |
// | * Neither the name of the ray team, nor the names of its
// |   contributors may be used to endorse or promote products
// |   derived from this software without specific prior
// |   written permission of the ray team.
// |
// | THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// | "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// | LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// | A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// | OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// | SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// | LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// | DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// | THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// | (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// | OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// +----------------------------------------------------------------------
#ifndef _H_XMLREADER_H_
#define _H_XMLREADER_H_

#include <ray/ioarchive.h>

class TiXmlNode;
class TiXmlDocument;
class TiXmlElement;
class TiXmlAttribute;

_NAME_BEGIN

class XmlBuf final : public archivebuf
{
public:
	XmlBuf() noexcept;
	~XmlBuf() noexcept;

	virtual bool open() noexcept;
	virtual void close() noexcept;

	virtual bool is_open() const noexcept;

	virtual bool load(StreamReader& stream) noexcept;
	virtual bool save(StreamWrite& stream) noexcept;

	virtual std::string getCurrentNodeName() const noexcept;
	virtual std::string getCurrentNodePath() const noexcept;

	virtual bool addAttribute(const std::string& key, const std::string& value) noexcept;
	virtual void setAttribute(const std::string& key, const std::string& value) noexcept;
	virtual void removeAttribute(const std::string& key) noexcept;

	virtual bool addDeclaration(const std::string& version, const std::string& encoding, const std::string& standalone) noexcept;

	virtual bool insert(const std::string& key) noexcept;
	virtual bool insertToParent(const std::string& key) noexcept;

	virtual bool setToNode(const std::string& path) noexcept;
	virtual bool setToFirstChild() noexcept;
	virtual bool setToFirstChild(const std::string& name) noexcept;
	virtual bool setToNextChild() noexcept;
	virtual bool setToNextChild(const std::string& name) noexcept;
	virtual bool setToParent() noexcept;
	virtual bool setToRoot() noexcept;

	virtual bool hasChild() const noexcept;

	virtual bool hasAttr(const char* name) const noexcept;
	virtual void clearAttrs() noexcept;
	virtual bool addAttrs() noexcept;
	virtual bool addAttrsInChildren() noexcept;
	virtual bool addAttrsInChildren(const std::string& key) noexcept;
	virtual const std::vector<std::string>& getAttrList() const noexcept;

	virtual bool getValue(const std::string& name, bool& result) const noexcept;
	virtual bool getValue(const std::string& name, int1& result) const noexcept;
	virtual bool getValue(const std::string& name, int2& result) const noexcept;
	virtual bool getValue(const std::string& name, int3& result) const noexcept;
	virtual bool getValue(const std::string& name, int4& result) const noexcept;
	virtual bool getValue(const std::string& name, uint1& result) const noexcept;
	virtual bool getValue(const std::string& name, uint2& result) const noexcept;
	virtual bool getValue(const std::string& name, uint3& result) const noexcept;
	virtual bool getValue(const std::string& name, uint4& result) const noexcept;
	virtual bool getValue(const std::string& name, float1& result) const noexcept;
	virtual bool getValue(const std::string& name, float2& result) const noexcept;
	virtual bool getValue(const std::string& name, float3& result) const noexcept;
	virtual bool getValue(const std::string& name, float4& result) const noexcept;
	virtual bool getValue(const std::string& name, std::string& result) const noexcept;

	virtual const char* errorString() const noexcept;

private:
	XmlBuf(const XmlBuf&) noexcept = delete;
	XmlBuf& operator=(const XmlBuf&) noexcept = delete;

private:

	TiXmlNode* _currentNode;
	TiXmlElement* _currentAttrNode;
	std::vector<std::string> _attrNames;
	std::vector<TiXmlAttribute*> _attrLists;
	std::unique_ptr<TiXmlDocument> _document;
};

class EXPORT XMLReader final : public iarchive
{
public:
	XMLReader() noexcept;
	~XMLReader() noexcept;

	XMLReader& open(StreamReader& stream) noexcept;
	XMLReader& close() noexcept;

	bool is_open() const noexcept;

	XMLReader& load(StreamReader& stream) noexcept;

private:
	XMLReader(const XMLReader&) noexcept = delete;
	XMLReader& operator=(const XMLReader&) noexcept = delete;

private:
	XmlBuf _xml;
};

class EXPORT XMLWrite final : public oarchive
{
public:
	XMLWrite() noexcept;
	~XMLWrite() noexcept;

	XMLWrite& open(const std::string& version, const std::string& encoding, const std::string& standalone) noexcept;
	XMLWrite& close() noexcept;

	XMLWrite& save(StreamWrite& ostream) noexcept;

private:
	XMLWrite(const XMLWrite&) noexcept = delete;
	XMLWrite& operator=(const XMLWrite&) noexcept = delete;

private:
	XmlBuf _xml;
};

_NAME_END

#endif