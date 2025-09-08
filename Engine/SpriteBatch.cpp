#include "SpriteBatch.h"

namespace Engine
{
	SpriteBatch::SpriteBatch() : m_vbo(0), m_vao(0)
	{}

	SpriteBatch::~SpriteBatch()
	{}

	void SpriteBatch::init()
	{
		createVertexArray();
	}

	void SpriteBatch::begin(GlyphSortType sortType /* = GlyphSortType::TEXTURE*/)
	{
		m_sortType = sortType;
		m_renderBatches.clear();

		m_glyphs.clear();
	}

	void SpriteBatch::end()
	{
		m_glyphPointers.resize(m_glyphs.size());
		for (int i = 0; i < m_glyphs.size(); i++)
		{
			m_glyphPointers[i] = &m_glyphs[i];
		}
		sortGlyphs();
		createRenderBatches();
	}

	void SpriteBatch::draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, ColorRGBA8& color)
	{
		m_glyphs.emplace_back(destRect, uvRect, texture, depth, color);
	}

	void SpriteBatch::renderBatch()
	{
		glBindVertexArray(m_vao);

		for (int i = 0; i < m_renderBatches.size(); i++)
		{
			glBindTexture(GL_TEXTURE_2D, m_renderBatches[i].texture);

			glDrawArrays(GL_TRIANGLES, m_renderBatches[i].offset, m_renderBatches[i].numVertices);
		}

		glBindVertexArray(0);
	}

	void SpriteBatch::createRenderBatches()
	{
		std::vector<Vertex> vertices;
		vertices.resize(m_glyphPointers.size() * 6);

		if(m_glyphPointers.empty())
		{
			return;
		}

		int offset = 0;
		int currentVertex = 0;
		m_renderBatches.emplace_back(0, 6, m_glyphPointers[0]->texture);
		vertices[currentVertex++] = m_glyphPointers[0]->topLeft;
		vertices[currentVertex++] = m_glyphPointers[0]->bottomLeft;
		vertices[currentVertex++] = m_glyphPointers[0]->bottomRight;
		vertices[currentVertex++] = m_glyphPointers[0]->bottomRight;
		vertices[currentVertex++] = m_glyphPointers[0]->topRight;
		vertices[currentVertex++] = m_glyphPointers[0]->topLeft;
		offset += 6;

		for (int currentGlyph = 1; currentGlyph < m_glyphs.size(); currentGlyph++)
		{
			if (m_glyphPointers[currentGlyph]->texture != m_glyphPointers[currentGlyph - 1]->texture)
			{
				m_renderBatches.emplace_back(offset, 6, m_glyphPointers[currentGlyph]->texture);
			}
			else
			{
				m_renderBatches.back().numVertices += 6;
			}

			vertices[currentVertex++] = m_glyphPointers[currentGlyph]->topLeft;
			vertices[currentVertex++] = m_glyphPointers[currentGlyph]->bottomLeft;
			vertices[currentVertex++] = m_glyphPointers[currentGlyph]->bottomRight;
			vertices[currentVertex++] = m_glyphPointers[currentGlyph]->bottomRight;
			vertices[currentVertex++] = m_glyphPointers[currentGlyph]->topRight;
			vertices[currentVertex++] = m_glyphPointers[currentGlyph]->topLeft;
			offset += 6;
		}

		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		//Orphan the buffer
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
		//Uplaod the data
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());

		glBindBuffer(GL_ARRAY_BUFFER, 0);


	}

	void SpriteBatch::createVertexArray()
	{
		if (m_vao == 0)
		{
			glGenVertexArrays(1, &m_vao);
		}
		glBindVertexArray(m_vao);
		
		if (m_vbo == 0)
		{
			glGenBuffers(1, &m_vbo);
		}
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		//Position attribute pointer
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
		//Color attribute pointer
		glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
		//Vertex attribute pointer
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

		glBindVertexArray(0);
	}

	void SpriteBatch::sortGlyphs()
	{
		switch (m_sortType)
		{
		case GlyphSortType::BACK_TO_FRONT:
			std::stable_sort(m_glyphPointers.begin(), m_glyphPointers.end(), compareBackToFront);
			break;

		case GlyphSortType::FRONT_TO_BACK:
			std::stable_sort(m_glyphPointers.begin(), m_glyphPointers.end(), compareFrontToBack);
			break;

		case GlyphSortType::TEXTURE:
			std::stable_sort(m_glyphPointers.begin(), m_glyphPointers.end(), compareTexture);
			break;
		}
		
	}

	bool SpriteBatch::compareFrontToBack(Glyph* a, Glyph* b)
	{
		return (a->depth < b->depth);
	}

	bool SpriteBatch::compareBackToFront(Glyph* a, Glyph* b)
	{
		return (a->depth > b->depth);
	}

	bool SpriteBatch::compareTexture(Glyph* a, Glyph* b)
	{
		return (a->texture < b->texture);
	}

}