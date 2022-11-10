#include "Line.h"

_declspec(align(16))
struct constant
{
	float m_angle;
};

Line::Line()
{

}

Line::~Line()
{

}

void Line::init(Vertex::vertex a, Vertex::vertex b)
{
	line[0] = a;
	line[1] = b;

	m_vb = GraphicsEngine::get()->getRenderSystem()->createVertexBuffer();
	UINT size_list = ARRAYSIZE(line);

	void* shader_byte_code = nullptr;

	size_t size_shader = 0;
	GraphicsEngine::get()->getRenderSystem()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	m_vs = GraphicsEngine::get()->getRenderSystem()->createVertexShader(shader_byte_code, size_shader);
	m_vb->load(line, sizeof(Vertex::vertex), size_list, shader_byte_code, size_shader);

	GraphicsEngine::get()->getRenderSystem()->releaseCompiledShader();

	GraphicsEngine::get()->getRenderSystem()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::get()->getRenderSystem()->createPixelShader(shader_byte_code, size_shader);
	GraphicsEngine::get()->getRenderSystem()->releaseCompiledShader();

	constant cc;
	cc.m_angle = 0;

	m_cb = GraphicsEngine::get()->getRenderSystem()->createConstantBuffer();
	m_cb->load(&cc, sizeof(constant));
}

void Line::draw()
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

void Line::onDestroy()
{
	m_vb->release();
	m_vs->release();
	m_ps->release();
}
