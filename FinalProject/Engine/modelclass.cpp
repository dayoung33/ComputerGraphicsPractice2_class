////////////////////////////////////////////////////////////////////////////////
// Filename: modelclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "modelclass.h"


ModelClass::ModelClass()
{
	m_vertexBuffer = 0;
	m_indexBuffer = 0;
	m_Texture = 0;
	m_model = 0;
}


ModelClass::ModelClass(const ModelClass& other)
{
}


ModelClass::~ModelClass()
{
}


bool ModelClass::Initialize(ID3D11Device* device, const wchar_t* modelFilename, const wchar_t* textureFilename)
{
	bool result;

	// Load in the model data,
	result = ReadFileCounts(modelFilename);
	if (!result)
	{
		return false;
	}
	result = LoadModel(modelFilename);
	if (!result)
	{
		return false;
	}

	// Initialize the vertex and index buffers.
	result = InitializeBuffers(device);
	if(!result)
	{
		return false;
	}

	// Load the texture for this model.
	result = LoadTexture(device, textureFilename);
	if(!result)
	{
		return false;
	}

	return true;
}

bool ModelClass::InitializePlane(ID3D11Device* device, const wchar_t* modelFilename ,const wchar_t* textureFilename)
{
	bool result;
	// Load in the model data,
	result = LoadTextModel(modelFilename);
	if (!result)
	{
		return false;
	}

	// Initialize the vertex and index buffers.
	result = InitializeBuffers(device);
	if (!result)
	{
		return false;
	}

	// Load the texture for this model.
	result = LoadTexture(device, textureFilename);
	if (!result)
	{
		return false;
	}
	return true;
}

void ModelClass::Shutdown()
{
	// Release the model texture.
	ReleaseTexture();

	// Shutdown the vertex and index buffers.
	ShutdownBuffers();

	// Release the model data.
	ReleaseModel();

	return;
}


void ModelClass::Render(ID3D11DeviceContext* deviceContext)
{
	// Put the vertex and index buffers on the graphics pipeline to prepare them for drawing.
	RenderBuffers(deviceContext);

	return;
}


int ModelClass::GetIndexCount()
{
	return m_indexCount;
}

int ModelClass::GetVertexCount()
{
	return m_vertexCount;
}


ID3D11ShaderResourceView* ModelClass::GetTexture()
{
	return m_Texture->GetTexture();
}


bool ModelClass::InitializeBuffers(ID3D11Device* device)
{
	VertexType* vertices;
	unsigned long* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
    D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;
	int i;

	m_indexCount = m_vertexCount;

	// Create the vertex array.
	vertices = new VertexType[m_vertexCount];
	if(!vertices)
	{
		return false;
	}

	// Create the index array.
	indices = new unsigned long[m_indexCount];
	if(!indices)
	{
		return false;
	}

	// Load the vertex array and index array with data.
	for (i = 0; i < m_vertexCount; i++)
	{
		vertices[i].position = D3DXVECTOR3(m_model[i].x, m_model[i].y, m_model[i].z);
		vertices[i].texture = D3DXVECTOR2(m_model[i].tu, m_model[i].tv);
		vertices[i].normal = D3DXVECTOR3(m_model[i].nx, m_model[i].ny, m_model[i].nz);

		indices[i] = i;
	}

	// Set up the description of the static vertex buffer.
    vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    vertexBufferDesc.ByteWidth = sizeof(VertexType) * m_vertexCount;
    vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vertexBufferDesc.CPUAccessFlags = 0;
    vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the vertex data.
    vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	// Now create the vertex buffer.
    result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if(FAILED(result))
	{
		return false;
	}

	// Set up the description of the static index buffer.
    indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_indexCount;
    indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    indexBufferDesc.CPUAccessFlags = 0;
    indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the index data.
    indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	// Create the index buffer.
	result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	if(FAILED(result))
	{
		return false;
	}

	// Release the arrays now that the vertex and index buffers have been created and loaded.
	delete [] vertices;
	vertices = 0;

	delete [] indices;
	indices = 0;

	return true;
}


void ModelClass::ShutdownBuffers()
{
	// Release the index buffer.
	if(m_indexBuffer)
	{
		m_indexBuffer->Release();
		m_indexBuffer = 0;
	}

	// Release the vertex buffer.
	if(m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = 0;
	}

	return;
}


void ModelClass::RenderBuffers(ID3D11DeviceContext* deviceContext)
{
	unsigned int stride;
	unsigned int offset;


	// Set vertex buffer stride and offset.
	stride = sizeof(VertexType); 
	offset = 0;
    
	// Set the vertex buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

    // Set the index buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

    // Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	return;
}


bool ModelClass::LoadTexture(ID3D11Device* device, const wchar_t* filename)
{
	bool result;


	// Create the texture object.
	m_Texture = new TextureClass;
	if(!m_Texture)
	{
		return false;
	}

	// Initialize the texture object.
	result = m_Texture->Initialize(device, filename);
	if(!result)
	{
		return false;
	}

	return true;
}


void ModelClass::ReleaseTexture()
{
	// Release the texture object.
	if(m_Texture)
	{
		m_Texture->Shutdown();
		delete m_Texture;
		m_Texture = 0;
	}

	return;
}

bool ModelClass::ReadFileCounts(const wchar_t * filename)
{
	ifstream fin;
	char input;

	// Open the file.
	fin.open(filename);

	// Check if it was successful in opening the file.
	if (fin.fail() == true)
	{
		return false;
	}

	// Read from the file and continue to read until the end of the file is reached.
	fin.get(input);
	while (!fin.eof())
	{
		// If the line starts with 'v' then count either the vertex, the texture coordinates, or the normal vector.
		if (input == 'v')
		{
			fin.get(input);
			if (input == ' ') { m_vertexCount++; }
			if (input == 't') { m_textureCount++; }
			if (input == 'n') { m_normalCount++; }
		}

		// If the line starts with 'f' then increment the face count.
		if (input == 'f')
		{
			fin.get(input);
			if (input == ' ') { m_faceCount++; }
		}

		// Otherwise read in the remainder of the line.
		while (input != '\n')
		{
			fin.get(input);
		}

		// Start reading the beginning of the next line.
		fin.get(input);
	}

	// Close the file.
	fin.close();

	return true;
}

bool ModelClass::LoadModel(const wchar_t* filename)
{
	VertexType *vertices, *texcoords, *normals;
	FaceType *faces;
	ifstream fin;
	int vertexIndex, texcoordIndex, normalIndex, faceIndex, vIndex, tIndex, nIndex;
	char input, input2;
	ofstream fout;


	// Initialize the four data structures.
	vertices = new VertexType[m_vertexCount];
	if (!vertices)
	{
		return false;
	}

	texcoords = new VertexType[m_textureCount];
	if (!texcoords)
	{
		return false;
	}

	normals = new VertexType[m_normalCount];
	if (!normals)
	{
		return false;
	}

	faces = new FaceType[m_faceCount];
	if (!faces)
	{
		return false;
	}

	// Initialize the indexes.
	vertexIndex = 0;
	texcoordIndex = 0;
	normalIndex = 0;
	faceIndex = 0;

	// Open the file.
	fin.open(filename);

	// Check if it was successful in opening the file.
	if (fin.fail() == true)
	{
		return false;
	}

	// Read in the vertices, texture coordinates, and normals into the data structures.
	// Important: Also convert to left hand coordinate system since Maya uses right hand coordinate system.
	fin.get(input);
	while (!fin.eof())
	{
		if (input == 'v')
		{
			fin.get(input);

			// Read in the vertices.
			if (input == ' ')
			{
				fin >> vertices[vertexIndex].position.x >> vertices[vertexIndex].position.y >> vertices[vertexIndex].position.z;

				// Invert the Z vertex to change to left hand system.
				vertices[vertexIndex].position.z = vertices[vertexIndex].position.z * -1.0f;
				vertexIndex++;
			}

			// Read in the texture uv coordinates.
			if (input == 't')
			{
				fin >> texcoords[texcoordIndex].texture.x >> texcoords[texcoordIndex].texture.y;

				// Invert the V texture coordinates to left hand system.
				texcoords[texcoordIndex].texture.y = 1.0f - texcoords[texcoordIndex].texture.y;
				texcoordIndex++;
			}

			// Read in the normals.
			if (input == 'n')
			{
				fin >> normals[normalIndex].normal.x >> normals[normalIndex].normal.y >> normals[normalIndex].normal.z;

				// Invert the Z normal to change to left hand system.
				normals[normalIndex].normal.z = normals[normalIndex].normal.z * -1.0f;
				normalIndex++;
			}
		}

		// Read in the faces.
		if (input == 'f')
		{
			fin.get(input);
			if (input == ' ')
			{
				// Read the face data in backwards to convert it to a left hand system from right hand system.
				fin >> faces[faceIndex].vIndex4 >> input2 >> faces[faceIndex].tIndex4 >> input2 >> faces[faceIndex].nIndex4
					>> faces[faceIndex].vIndex3 >> input2 >> faces[faceIndex].tIndex3 >> input2 >> faces[faceIndex].nIndex3
					>> faces[faceIndex].vIndex2 >> input2 >> faces[faceIndex].tIndex2 >> input2 >> faces[faceIndex].nIndex2
					>> faces[faceIndex].vIndex1 >> input2 >> faces[faceIndex].tIndex1 >> input2 >> faces[faceIndex].nIndex1;
				faceIndex++;
			}
		}

		// Read in the remainder of the line.
		while (input != '\n')
		{
			fin.get(input);
		}

		// Start reading the beginning of the next line.
		fin.get(input);
	}

	// Close the file.
	fin.close();
	// Create the model using the vertex count that was read in.
	m_vertexCount = m_faceCount * 6;
	m_model = new ModelType[m_vertexCount];
	if (!m_model)
	{
		return false;
	}
	m_vertexCount = 0;

	// Now loop through all the faces and output the three vertices for each face.
	for (int i = 0; i < faceIndex; i++)
	{
		vIndex = faces[i].vIndex1 - 1;
		tIndex = faces[i].tIndex1 - 1;
		nIndex = faces[i].nIndex1 - 1;

		m_model[m_vertexCount].x = vertices[vIndex].position.x;
		m_model[m_vertexCount].y = vertices[vIndex].position.y;
		m_model[m_vertexCount].z = vertices[vIndex].position.z;

		m_model[m_vertexCount].tu = texcoords[tIndex].texture.x;
		m_model[m_vertexCount].tv = texcoords[tIndex].texture.y;

		m_model[m_vertexCount].nx = normals[nIndex].normal.x;
		m_model[m_vertexCount].ny = normals[nIndex].normal.y;
		m_model[m_vertexCount].nz = normals[nIndex].normal.z;

		m_vertexCount++;

		vIndex = faces[i].vIndex2 - 1;
		tIndex = faces[i].tIndex2 - 1;
		nIndex = faces[i].nIndex2 - 1;

		m_model[m_vertexCount].x = vertices[vIndex].position.x;
		m_model[m_vertexCount].y = vertices[vIndex].position.y;
		m_model[m_vertexCount].z = vertices[vIndex].position.z;

		m_model[m_vertexCount].tu = texcoords[tIndex].texture.x;
		m_model[m_vertexCount].tv = texcoords[tIndex].texture.y;

		m_model[m_vertexCount].nx = normals[nIndex].normal.x;
		m_model[m_vertexCount].ny = normals[nIndex].normal.y;
		m_model[m_vertexCount].nz = normals[nIndex].normal.z;

		m_vertexCount++;

		vIndex = faces[i].vIndex3 - 1;
		tIndex = faces[i].tIndex3 - 1;
		nIndex = faces[i].nIndex3 - 1;

		m_model[m_vertexCount].x = vertices[vIndex].position.x;
		m_model[m_vertexCount].y = vertices[vIndex].position.y;
		m_model[m_vertexCount].z = vertices[vIndex].position.z;

		m_model[m_vertexCount].tu = texcoords[tIndex].texture.x;
		m_model[m_vertexCount].tv = texcoords[tIndex].texture.y;

		m_model[m_vertexCount].nx = normals[nIndex].normal.x;
		m_model[m_vertexCount].ny = normals[nIndex].normal.y;
		m_model[m_vertexCount].nz = normals[nIndex].normal.z;

		m_vertexCount++;	

		vIndex = faces[i].vIndex1 - 1;
		tIndex = faces[i].tIndex1 - 1;
		nIndex = faces[i].nIndex1 - 1;

		m_model[m_vertexCount].x = vertices[vIndex].position.x;
		m_model[m_vertexCount].y = vertices[vIndex].position.y;
		m_model[m_vertexCount].z = vertices[vIndex].position.z;

		m_model[m_vertexCount].tu = texcoords[tIndex].texture.x;
		m_model[m_vertexCount].tv = texcoords[tIndex].texture.y;

		m_model[m_vertexCount].nx = normals[nIndex].normal.x;
		m_model[m_vertexCount].ny = normals[nIndex].normal.y;
		m_model[m_vertexCount].nz = normals[nIndex].normal.z;

		m_vertexCount++;

		vIndex = faces[i].vIndex3 - 1;
		tIndex = faces[i].tIndex3 - 1;
		nIndex = faces[i].nIndex3 - 1;

		m_model[m_vertexCount].x = vertices[vIndex].position.x;
		m_model[m_vertexCount].y = vertices[vIndex].position.y;
		m_model[m_vertexCount].z = vertices[vIndex].position.z;

		m_model[m_vertexCount].tu = texcoords[tIndex].texture.x;
		m_model[m_vertexCount].tv = texcoords[tIndex].texture.y;

		m_model[m_vertexCount].nx = normals[nIndex].normal.x;
		m_model[m_vertexCount].ny = normals[nIndex].normal.y;
		m_model[m_vertexCount].nz = normals[nIndex].normal.z;

		m_vertexCount++;

		vIndex = faces[i].vIndex4 - 1;
		tIndex = faces[i].tIndex4 - 1;
		nIndex = faces[i].nIndex4 - 1;

		m_model[m_vertexCount].x = vertices[vIndex].position.x;
		m_model[m_vertexCount].y = vertices[vIndex].position.y;
		m_model[m_vertexCount].z = vertices[vIndex].position.z;

		m_model[m_vertexCount].tu = texcoords[tIndex].texture.x;
		m_model[m_vertexCount].tv = texcoords[tIndex].texture.y;

		m_model[m_vertexCount].nx = normals[nIndex].normal.x;
		m_model[m_vertexCount].ny = normals[nIndex].normal.y;
		m_model[m_vertexCount].nz = normals[nIndex].normal.z;

		m_vertexCount++;
	}


	// Release the four data structures.
	if (vertices)
	{
		delete[] vertices;
		vertices = 0;
	}
	if (texcoords)
	{
		delete[] texcoords;
		texcoords = 0;
	}
	if (normals)
	{
		delete[] normals;
		normals = 0;
	}
	if (faces)
	{
		delete[] faces;
		faces = 0;
	}

	return true;
}

bool ModelClass::LoadTextModel(const wchar_t* filename)
{
	ifstream fin;
	char input;
	int i;


	// Open the model file.  If it could not open the file then exit.
	fin.open(filename);
	if (fin.fail())
	{
		return false;
	}

	// Read up to the value of vertex count.
	fin.get(input);
	while (input != ':')
	{
		fin.get(input);
	}

	// Read in the vertex count.
	fin >> m_vertexCount;

	// Set the number of indices to be the same as the vertex count.
	m_indexCount = m_vertexCount;

	// Create the model using the vertex count that was read in.
	m_model = new ModelType[m_vertexCount];
	if (!m_model)
	{
		return false;
	}

	// Read up to the beginning of the data.
	fin.get(input);
	while (input != ':')
	{
		fin.get(input);
	}
	fin.get(input);
	fin.get(input);

	// Read in the vertex data.
	for (i = 0; i < m_vertexCount; i++)
	{
		fin >> m_model[i].x >> m_model[i].y >> m_model[i].z;
		fin >> m_model[i].tu >> m_model[i].tv;
		fin >> m_model[i].nx >> m_model[i].ny >> m_model[i].nz;
	}

	// Close the model file.
	fin.close();

	return true;
}

void ModelClass::ReleaseModel()
{
	if (m_model)
	{
		delete[] m_model;
		m_model = 0;
	}

	return;
}


