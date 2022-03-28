class ParticleSystem
{
public:
    ParticleSystem();

    ~ParticleSystem();

    bool InitParticleSystem(const Vector3f& Pos);

    void Render(int DeltaTimeMillis, const Matrix4f& VP, const Vector3f& CameraPos);

private:

    bool m_isFirst;
    unsigned int m_currVB;
    unsigned int m_currTFB;
    GLuint m_particleBuffer[2];
    GLuint m_transformFeedback[2];
    PSUpdateTechnique m_updateTechnique;
    BillboardTechnique m_billboardTechnique;
    RandomTexture m_randomTexture;
    Texture* m_pTexture;
    int m_time;
};