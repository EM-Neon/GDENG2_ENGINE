#include "Quad.h"

_declspec(align(16))
struct constant
{
	float m_angle;
};

Quad::Quad()
{

}

Quad::~Quad()
{

}

void Quad::init(Vertex::vertex a, Vertex::vertex b, Vertex::vertex c, Vertex::vertex d)
{
	quad[0] = a;
	quad[1] = b;
	quad[2] = c;
	quad[3] = d;

	m_vb = GraphicsEngine::get()->createVertexBuffer();
	UINT size_list = ARRAYSIZE(quad);

	void* shader_byte_code = nullptr;

	size_t size_shader = 0;
	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	m_vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);
	m_vb->load(quad, sizeof(Vertex::vertex), size_list, shader_byte_code, size_shader);

	GraphicsEngine::get()->releaseCompiledShader();

	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::get()->createPixelShader(shader_byte_code, size_shader);
	GraphicsEngine::get()->releaseCompiledShader();

	constant cc;
	cc.m_angle = 0;

	m_cb = GraphicsEngine::get()->createConstantBuffer();
	m_cb->load(&cc, sizeof(constant));
}

void Quad::draw()
{
	/*unsigned long new_time = 0;
	if (m_old_time)
		new_time = ::GetTickCount() - m_old_time;
	m_delta_time = new_time / 1000.0f;
	m_old_time = ::GetTickCount();*/

	if (time >= 10.0f) isTimeSlow = true;
	if (time <= 0.0f) isTimeSlow = false;

	if(isTimeSlow)
	{
		time -= 0.01f;
	}
	else
	{
		time += 0.01f;
	}

	m_angle += time * EngineTime::getDeltaTime();
	constant cc;
	cc.m_angle = m_angle;

	m_cb->update(GraphicsEngine::get()->getImmediateDeviceContext(), &cc);

	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_vs, m_cb);
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_ps, m_cb);

	//SET DEFAULT SHADER IN THE GRAPHICS PIPELINE TO BE ABLE TO DRAW
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(m_ps);

	//SET THE VERTICES OF THE TRIANGLE TO DRAW
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vb);

	// FINALLY DRAW THE TRIANGLE
	GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(m_vb->getSizeVertexList(), 0);
}

void Quad::onDestroy()
{
	if(m_vb != NULL)
		m_vb->release();
	if(m_vs != NULL)
		m_vs->release();
	if(m_ps != NULL)
		m_ps->release();
}
