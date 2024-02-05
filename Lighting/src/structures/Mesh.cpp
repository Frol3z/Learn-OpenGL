#include "Mesh.h"

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"

Mesh::Mesh(const float* vertices, size_t vSize, VertexLayout layout, const unsigned int* indices, size_t iCount)
	: m_VA(nullptr), m_VB(nullptr), m_VBL(nullptr), m_IB(nullptr), m_VertsCount(0)
{
	m_VA = new VertexArray();

	m_VB = new VertexBuffer(vertices, vSize);
	m_VBL = new VertexBufferLayout();
	switch (layout)
	{
		case VF:
		{
			m_VBL->Push<float>(3);
			m_VertsCount = vSize / 3 * sizeof(float);
			break;
		}
		case VFNF:
		{
			m_VBL->Push<float>(3);
			m_VBL->Push<float>(3);
			m_VertsCount = vSize / 6 * sizeof(float);
			break;
		}
	}

	m_VA->AddVertexBuffer(*m_VB, *m_VBL);

	if (indices)
	{
		m_IB = new IndexBuffer(indices, iCount);
		m_VA->AddIndexBuffer(*m_IB);
	}
}

Mesh::~Mesh()
{
	delete m_VA;
	delete m_VBL;
	delete m_IB;
	delete m_VB;
}

void Mesh::Bind() const
{
	m_VA->Bind();
}

void Mesh::Unbind() const
{
	m_VA->Unbind();
}