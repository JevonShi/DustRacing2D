// This file is part of Dust Racing 2D.
// Copyright (C) 2012 Jussi Lind <jussi.lind@iki.fi>
//
// Dust Racing 2D is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// Dust Racing 2D is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Dust Racing 2D. If not, see <http://www.gnu.org/licenses/>.

#include "shaderprogram.hpp"
#include <MCException>
#include <MCLogger>
#include <MCTrigonom>
#include <cassert>

static const int POSITION = 1;
static const int SIN      = 5;
static const int COS      = 6;
static const int SCALE    = 7;

ShaderProgram::ShaderProgram(const QGLContext * context)
: m_program(context)
, m_fragmentShader(QGLShader::Fragment, context)
, m_vertexShader(QGLShader::Vertex, context)
{
}

void ShaderProgram::bind()
{
    if (!isBound())
    {
        MCGLShaderProgram::bind();
        m_program.bind();
    }
}

void ShaderProgram::release()
{
    if (isBound())
    {
        MCGLShaderProgram::release();
        m_program.release();
    }
}

void ShaderProgram::link()
{
    m_program.link();
    assert(m_program.isLinked());
}

bool ShaderProgram::isLinked() const
{
    return m_program.isLinked();
}

bool ShaderProgram::addVertexShader(const std::string & fileName)
{
    if (!m_vertexShader.compileSourceFile(fileName.c_str()))
    {
        MCLogger().error() << "Cannot compile '" << fileName << "'";
        throw MCException("Compiling a vertex shader failed.");
    }

    m_program.bindAttributeLocation("position", POSITION);
    m_program.bindAttributeLocation("sin1",     SIN);
    m_program.bindAttributeLocation("cos1",     COS);
    m_program.bindAttributeLocation("scale",    SCALE);
    return m_program.addShader(&m_vertexShader);
}

bool ShaderProgram::addFragmentShader(const std::string & fileName)
{
    if (!m_fragmentShader.compileSourceFile(fileName.c_str()))
    {
        MCLogger().error() << "Cannot compile '" << fileName << "'";
        throw MCException("Compiling a fragment shader failed.");
    }

    return m_program.addShader(&m_fragmentShader);
}

void ShaderProgram::rotate(GLfloat angle)
{
    if (!isBound())
    {
        bind();
        m_program.setAttributeValue(SIN, MCTrigonom::sin(angle));
        m_program.setAttributeValue(COS, MCTrigonom::cos(angle));
        release();
    }
    else
    {
        m_program.setAttributeValue(SIN, MCTrigonom::sin(angle));
        m_program.setAttributeValue(COS, MCTrigonom::cos(angle));
    }
}

void ShaderProgram::translate(const MCVector3dF & p)
{
    if (!isBound())
    {
        bind();
        m_program.setAttributeValue(POSITION, p.i(), p.j(), p.k(), 0);
        release();
    }
    else
    {
        m_program.setAttributeValue(POSITION, p.i(), p.j(), p.k(), 0);
    }
}

void ShaderProgram::setColor(GLfloat, GLfloat, GLfloat, GLfloat)
{
    // Not supported. Vertex colors are currently set in VBO's.
}

void ShaderProgram::setScale(GLfloat x, GLfloat y, GLfloat z)
{
    if (!isBound())
    {
        bind();
        m_program.setAttributeValue(SCALE, x, y, z, 1);
        release();
    }
    else
    {
        m_program.setAttributeValue(SCALE, x, y, z, 1);
    }
}

void ShaderProgram::setFadeValue(GLfloat f)
{
    if (!isBound())
    {
        bind();
        m_program.setUniformValue("fade", f);
        release();
    }
    else
    {
        m_program.setUniformValue("fade", f);
    }
}

void ShaderProgram::bindTextureUnit0(GLuint index)
{
    if (!isBound())
    {
        bind();
        m_program.setUniformValue("texture0", index);
        release();
    }
    else
    {
        m_program.setUniformValue("texture0", index);
    }
}

void ShaderProgram::bindTextureUnit1(GLuint index)
{
    if (!isBound())
    {
        bind();
        m_program.setUniformValue("texture1", index);
        release();
    }
    else
    {
        m_program.setUniformValue("texture1", index);
    }
}

ShaderProgram::~ShaderProgram()
{
}

