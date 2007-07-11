/***************************************************************************
 *   Copyright (C) 2007 by Raul Fernandes                                  *
 *   rgbr@yahoo.com.br                                                     *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.          *
 ***************************************************************************/

#include "bgl_stardictbuilder.h"

#include <iostream>

StarDictBuilder::StarDictBuilder( std::string filename )
{
  m_babylonfilename = filename + ".babylon";
  file.open( m_babylonfilename.c_str() );
  m_entriescount = 0;
}


StarDictBuilder::~StarDictBuilder()
{
}

bool StarDictBuilder::addHeadword( std::string word, std::string def, std::vector<std::string> alternates )
{
  if (m_entriescount == 0) {
    std::string line;
    line = "#stripmethod=keep\n#sametypesequence=h\n";
    file.write(line.data(), line.length());
    if (!m_title.empty()) {
      line = "#bookname=";
      line += m_title;
      line += '\n';
      file.write(line.data(), line.length());
    }
    if (!m_author.empty()) {
      line = "#author=";
      line += m_author;
      line += '\n';
      file.write(line.data(), line.length());
    }
    if (!m_email.empty()) {
      line = "#email=";
      line += m_email;
      line += '\n';
      file.write(line.data(), line.length());
    }
    if (!m_website.empty()) {
      line = "#website=";
      line += m_website;
      line += '\n';
      file.write(line.data(), line.length());
    }
    if (!m_description.empty()) {
      line = "#description=";
      line += m_description;
      line += '\n';
      file.write(line.data(), line.length());
    }
  }
  m_entriescount++;
  std::string lines;
  lines = word;
  for (std::vector<std::string>::iterator i = alternates.begin(); i != alternates.end(); ++i) {
    lines += '|';
    lines += *i;
  }
  lines += '\n';
  lines += def;
  lines += "\n\n";
  file.write(lines.data(), lines.length());

  return true;
}

bool StarDictBuilder::finish()
{
  file.close();
  printf("Write file: %s\n\nBookname: %s\nWord count: %d\nAuthor: %s\nEmail: %s\nWebsite: %s\nDescription: %s\n", m_babylonfilename.c_str(), m_title.c_str(), m_entriescount, m_author.c_str(), m_email.c_str(), m_website.c_str(), m_description.c_str());

  return true;
}