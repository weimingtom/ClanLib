/*
**  ClanLib SDK
**  Copyright (c) 1997-2012 The ClanLib Team
**
**  This software is provided 'as-is', without any express or implied
**  warranty.  In no event will the authors be held liable for any damages
**  arising from the use of this software.
**
**  Permission is granted to anyone to use this software for any purpose,
**  including commercial applications, and to alter it and redistribute it
**  freely, subject to the following restrictions:
**
**  1. The origin of this software must not be misrepresented; you must not
**     claim that you wrote the original software. If you use this software
**     in a product, an acknowledgment in the product documentation would be
**     appreciated but is not required.
**  2. Altered source versions must be plainly marked as such, and must not be
**     misrepresented as being the original software.
**  3. This notice may not be removed or altered from any source distribution.
**
**  Note: Some of the libraries ClanLib may link to may have additional
**  requirements or restrictions.
**
**  File Author(s):
**
**    Magnus Norddahl
*/

#include "CSSLayout/precomp.h"
#include "css_parser_border_spacing.h"
#include "API/CSSLayout/css_box_properties.h"

namespace clan
{

std::vector<std::string> CSSParserBorderSpacing::get_names()
{
	std::vector<std::string> names;
	names.push_back("border-spacing");
	return names;
}

void CSSParserBorderSpacing::parse(CSSBoxProperties &properties, const std::string &name, const std::vector<CSSToken> &tokens)
{
	CSSLength length1, length2;

	size_t pos = 0;
	CSSToken token = next_token(pos, tokens);
	if (token.type == CSSToken::type_ident && equals(token.value, "inherit") && pos == tokens.size())
	{
		properties.border_spacing.type = CSSValueBorderSpacing::type_inherit;
		return;
	}
	else if (is_length(token))
	{
		if (!parse_length(token, length1))
		{
			debug_parse_error(name, tokens);
			return;
		}
	}
	else
	{
		debug_parse_error(name, tokens);
		return;
	}

	if (pos != tokens.size())
	{
		token = next_token(pos, tokens);
		if (is_length(token) && pos == tokens.size())
		{
			if (parse_length(token, length2))
			{
				properties.border_spacing.type = CSSValueBorderSpacing::type_two_lengths;
				properties.border_spacing.length1 = length1;
				properties.border_spacing.length2 = length2;
			}
		}
	}
	else
	{
		properties.border_spacing.type = CSSValueBorderSpacing::type_one_length;
		properties.border_spacing.length1 = length1;
	}
}

}
