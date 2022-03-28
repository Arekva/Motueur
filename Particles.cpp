using namespace glm;
struct Particle
{
	float Type;
	glm::vec3 Pos;
	glm::vec3 Vel;
	float LifetimeMillis;
};

bool ParticleSystem::InitParticleSystem(const glm::vec3& Pos)
{
	Particle Particles[Max_Particles];
}