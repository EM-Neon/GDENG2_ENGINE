#include "ImprovedLine.h"

_declspec(align(16))
struct constant
{
	float m_angle;
};

ImprovedLine::ImprovedLine()
{

}

ImprovedLine::~ImprovedLine()
{
}

void ImprovedLine::init(std::vector<Vertex::vertex> vertices)
{

	for (Vertex::vertex i : vertices)
	{
		vertexVect.push_back(i);
	}

	//std::copy(vertices, vertices + _ARRAYSIZE(vertices), vertexVect);

	m_vb = GraphicsEngine::get()->getRenderSystem()->createVertexBuffer();
	UINT size_list = vertexVect.size();

	void* shader_byte_code = nullptr;

	size_t size_shader = 0;
	GraphicsEngine::get()->getRenderSystem()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	m_vs = GraphicsEngine::get()->getRenderSystem()->createVertexShader(shader_byte_code, size_shader);
	m_vb->load(static_cast<void*>(vertices.data()), sizeof(Vertex::vertex), size_list, shader_byte_code, size_shader);

	GraphicsEngine::get()->getRenderSystem()->releaseCompiledShader();

	GraphicsEngine::get()->getRenderSystem()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::get()->getRenderSystem()->createPixelShader(shader_byte_code, size_shader);
	GraphicsEngine::get()->getRenderSystem()->releaseCompiledShader();

	constant cc;
	cc.m_angle = 0;

	m_cb = GraphicsEngine::get()->getRenderSystem()->createConstantBuffer();
	m_cb->load(&cc, sizeof(constant));
}

void ImprovedLine::draw()
{

	m_angle += time * EngineTime::getDeltaTime();
	constant cc;
	cc.m_angle = m_angle;

	m_cb->update(GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext(), &cc);

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setConstantBuffer(m_vs, m_cb);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setConstantBuffer(m_ps, m_cb);

	//SET DEFAULT SHADER IN THE GRAPHICS PIPELINE TO BE ABLE TO DRAW
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setPixelShader(m_ps);

	//SET THE VERTICES OF THE TRIANGLE TO DRAW
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setVertexBuffer(m_vb);

	// FINALLY DRAW THE TRIANGLE
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->drawLineStrip(m_vb->getSizeVertexList(), 0);
}

void ImprovedLine::onDestroy()
{
	if (m_vb != NULL)
		m_vb->release();
	if (m_vs != NULL)
		m_vs->release();
	if (m_ps != NULL)
		m_ps->release();
}