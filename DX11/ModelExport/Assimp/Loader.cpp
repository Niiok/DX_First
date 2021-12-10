#include "Framework.h"
#include "Loader.h"
#include "Type.h"
#include "Utilities/Xml.h"
#include "Utilities/BinaryFile.h"


Loader::Loader()
{
	importer = new Assimp::Importer();
}

Loader::~Loader()
{
}

void Loader::ReadFile(wstring file)
{
	this->file = L"../../_Assets/" + file;
	scene = importer->ReadFile(
		String::ToString(this->file),
		aiProcess_ConvertToLeftHanded
		| aiProcess_Triangulate
		| aiProcess_GenUVCoords
		| aiProcess_GenNormals
		| aiProcess_CalcTangentSpace
	);
	assert(scene != NULL);
}

void Loader::ExportMaterial(wstring savePath, bool bOverwrite)
{
	savePath = L"../../_Textures/" + savePath + L".material";
	ReadMaterial();

	WriteMaterial(savePath, bOverwrite);
}

void Loader::ExportMesh(wstring savePath, bool bOverwrite)
{
	savePath = L"../../_Models/" + savePath + L".mesh";
	ReadBoneData(scene->mRootNode, -1, -1);

	WriteMeshData(savePath, bOverwrite);
}

void Loader::ReadMaterial()
{
	for (UINT i = 0; i < scene->mNumMaterials; i++)
	{
		aiMaterial* readMaterial = scene->mMaterials[i];
		AsMaterial* material = new AsMaterial();
		material->Name = readMaterial->GetMame().C_Str();

		float val;
		aiColor3D color;

		readMaterial->Get(AI_MATKEY_COLOR_AMBIENT, color);
		material->Ambient = Color(color.r, color.g, color.b, 1.0f);

		readMaterial->Get(AI_MATKEY_COLOR_DIFFUSE, color);
		material->Diffuse = Color(color.r, color.g, color.b, 1.0f);

		readMaterial->Get(AI_MATKEY_COLOR_SPECULAR, color);
		material->Specular = Color(color.r, color.g, color.b, 1.0f);

		readMaterial->Get(AI_MATKEY_SHINESS, material->Specular.a);

		aiString file;

		ReadMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &file);
		material->DiffuseFile = file.C_Str()		
			
			ReadMaterial->GetTexture(aiTextureType_SPECULAR, 0, &file);
		material->DiffuseFile = file.C_Str()		
			
			ReadMaterial->GetTexture(aiTextureType_NORMAL, 0, &file);
		material->DiffuseFile = file.C_Str()		


		materials.push_back(material);

		//int breakpoint = 999;
	}
}

void Loader::WriteMaterial(wstring savePath, bool bOverrwrite)
{
	if (bOverWrite == false)
	{
		if (Path::ExistFile(savePath) == true)
			return;
	}

	string foler = String::ToString(Path::GetDictionaryName(savePath));
	string file = String::ToString(Path::GetFileName(savePath));

	Path::CreateFolder(foler);

	Xml::XMLDocument* document = new Xml::XMLDocument();
	Xml::XMLDeclaration* decl = document->NewDeclaration();
	doucment->LinkEndChild(decl);

	Xml::XMLElement* root = document->NewElement("Materials");
	root->SetAttribute("xmlns.xsd"), "https:://w3."

		document->LinkEndChild(root);
	for (AsMaterial* meterial : materials)
	{
		Xml::XMLElement* node = document->NewElement("Material");
		root->LinkEndChild(node);

		Xml::XMLElement* element = NULL;
		element = document->NewElement("Name");
		element->SetText(material->Name.c_str());
		node->LinkEndChild(element);

		element = document->NewElement("DiffuseFile");
		element->SetText(WriteTexture(folder, material->DiffuseFile).c_str());
		node->LinkEndChild(element);

		element = document->NewElement("SpecularFile");
		element->SetText(WriteTexture(folder, material->SpecularFile).c_str());
		node->LinkEndChild(element);

		element = document->NewElement("NormalFile");
		element->SetText(WriteTexture(folder, material->NormalFile).c_str());
		node->LinkEndChild(element);

		element = document->NewElement("Ambient");
		element->SetAttribute("R", material->Ambient.r);
		element->SetAttribute("G", material->Ambient.g);
		element->SetAttribute("B", material->Ambient.b);
		element->SetAttribute("A", material->Ambient.a);
		node->LinkEndChild(element);
		
		element = document->NewElement("Diffuse");
		element->SetAttribute("R", material->Diffuse.r);
		element->SetAttribute("G", material->Diffuse.g);
		element->SetAttribute("B", material->Diffuse.b);
		element->SetAttribute("A", material->Diffuse.a);
		node->LinkEndChild(element);
	
		element = document->NewElement("Specular");
		element->SetAttribute("R", material->Specular.r);
		element->SetAttribute("G", material->Specular.g);
		element->SetAttribute("B", material->Specular.b);
		element->SetAttribute("A", material->Specular.a);
		node->LinkEndChild(element);
	
		element = document->NewElement("Normal");
		element->SetAttribute("R", material->Normal.r);
		element->SetAttribute("G", material->Normal.g);
		element->SetAttribute("B", material->Normal.b);
		element->SetAttribute("A", material->Normal.a);
		node->LinkEndChild(element);
	}
}

string Loader::WriteTexture(string savePath, string file)
{
	if (file.length() < 1) return "";

	string fileName = Path::GetFileName(file);

	const aiTexture* texture = scene->GetEmbeddedTexture(file.c_str());
	BinaryWriter w;
	string path = "";
	if (texture != NULL)
	{
		path = savePath + Path::GetFileNameWithoutExtension*(file)+".png";
		if (texture->mHeight < 1)
		{
			w.Open(String::ToWString(path));
			w.Byte(texture->pcData, texture->mWidth);
			w.Close();
		}
		else
		{
			ID3D11Texture2D* dest;
			D3D11_TEXTURE2D_DESC destDesc;
			ZeroMemory(&destDesc, sizeof(D3D11_TEXTURE2D_DESC));
			destDesc.Width = texture->mWidth;
			destDesc.Height = texture->mHeight;
			destDesc.MipLevels = 1;
			destDesc.ArraySize = 1;
			destDesc.ArraySize = 1;
			destDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			destDesc.SampleDesc.Count = 1;
			destDesc.SampleDesc.Quality = 0;
			destDesc.Usage = D3D11_USAGE_IMMUTABLE;

			D3D11_SUBRESOURCE_DATA subResource = {0};
			subResource.pSysMem = texture->pcData;

			HRESULT hr;
			/////
		}
	}
	else
	{
		string directory =
			Path::GetDirectoryName(String::ToString(this->file));
		string origin = directory + file;
		String Replace(&origin, "\\". "/");

		if (Path::ExistFile(origin) == false)
			return "";

		path = savePath + fileName;
		CopyFileA(origin.c_str(), path.c_str(), FALSE);
		String::Replace(&path, "../../_Textures/", "");
	}


	return string();
}

void Loader::ReadBoneData(aiNode * node, int index, int parent)
{
	AsBone* bone = new AsBone();
	bone->Index = index;
	bone->Parent = parent;
	bone->Name = node->mName.C_Str();

	Matrix transform(node->mTransformation[0]);
	D3DXMatrixTranspose(&bone->Transform, &transform);

	Matrix temp;
	if (parent == -1)
		D3DXMatrixIdentity(&temp);
	else
		temp = bones[parent]->Transform;

	bone->Transform = bone->Transform * temp;
	bones.push_back(bone);
	
	ReadMeshData(node, index);

	for (UINT i = 0; i < node->mNumChildren; i++)
		ReadBoneData(node->mChildren[i], bones.size(), index);

}

void Loader::ReadMeshData(aiNode * node, int bone)
{
	if (node->mNumMeshes < 1) return;

	AsMesh* asMesh = new AsMesh();
	asMesh->Name = node->mName.C_Str();
	asMesh->BondIndex = bone;

	for (UINT i = 0; i < node->mNumMeshes; i++)
	{
		UINT index = node->mMeshes[i];
		aiMesh* mesh = scene->mMeshes[index];

		UINT startVertex = asMesh->Vertices.size();
		UINT startIndex = asMesh->Indices.size();

		for (UINT m = 0; m < mesh->mNumVertices; m++)
		{
			Model::ModelVertex vertex;
			memcpy(&vertex.Position, &mesh->mVertices[m], sizeof(Vector3));
			memcpy(&vertex.Uv, &mesh->mTextureCoords[0][m], sizeof(Vector2));
			memcpy(&vertex.Normal, &mesh->mNormals[m], sizeof(Vector3));
			asMesh->Vertices.push_back(vertex);
		}

		for (UINT f = 0; f < mesh->mNumFaces; f++)
		{
			aiFace& face = mesh->mFaces[f];
			for (UINT k = 0; k < face.mNumIndices; k++)
			{
				asMesh->Indices.push_back(face.mIndices[k]);
				asMesh->Indices.back() += startIndex;
			}
		}

		AsMeshPart* meshPart = new AsMeshPart();
		aiMaterial* material = scene->mMaterials[mesh->mMatrialIndex];
		meshPart->Name = mesh->mName.C_Str();
		meshPart->MaterialName = material->GetName().C_Str();
		meshPart->StartVertex = startVertex;
		meshPart->StartIndex = startIndex;
		meshPart->VertexCount = mesh->mNumVertices;
		meshPart->IndexCount = mesh->mNumFaces* mesh->mFaces->mNumIndices;

		asMesh->MeshParts.push_back(meshPart);
	}

	meshes.push_back(asMesh);
}

void Loader::WriteMeshData(wstring savePath, bool bOverwrite)
{
	if (bOverwrite == false)
	{
		if (Path::ExistFile(savePath) == true)
			return;
	}

	Path::CreateFolders(Path::GetDirectoryName(savePath));

	BinaryWriter* w = new BinaryWriter();
	w->Open(savePath);

	w->UInt(bones.size());
	for (AsBone* bone : bones)
	{
		w->Int(bone->Index);
		w->String(bone->Name);
		w->Int(bone->Parent);
		w->Matrix(bone->Transform);
		SafeDelete(bone);
	}

	w->UInt(meshes.size());
	for (AsMesh* meshData : meshes)
	{
		w->String(meshData->Name);
		w->Int(meshData->BondIndex);
		w->UInt(meshData->Vertices.size());

		w->Byte(&meshData->Vertices[0],
			sizeof(Model::ModelVertex) * meshData->Vertices.size());

		w->UInt(meshData->Indices.size());
		w->Byte(&meshData->BondIndex[0],
			sizeof(UINT) * meshData->Indices.size());

		w->UInt(meshData->MeshParts.size());
		for (AsMeshPart* part : meshData->MeshParts)
		{
			w->String(part->Name);
			w->String(part->MaterialName;

			w->UInt(part->StartVertex);
			w->UInt(part->VertexCount);
			
			w->UInt(part->StartIndex);
			w->UInt(part->IndexCount);


		}


	}
}

