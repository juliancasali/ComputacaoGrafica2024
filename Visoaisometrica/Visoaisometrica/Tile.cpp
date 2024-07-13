#include "Tile.h"

using namespace glm;

void Tile::inicializar(GLuint texID, int nRows, int nCols, vec3 pos, vec3 escala, float angulo, vec3 cor)
{
	this->pos = pos;
	this->escala.x = escala.x;
	this->escala.y = escala.y;
	this->angulo = angulo;
	this->texID = texID;
	this->nRows = nRows;
	this->nCols = nCols;

	nAnimations = 1;
	nFrames = 1;

	offsetTex.s = 1.0 / (float)nCols;
	offsetTex.t = 1.0 / (float)nRows;
	cor.r = 1.0;
	cor.g = 0.0;
	cor.b = 1.0;

	//Especifica��o da geometria da sprite (quadrado, 2 tri�ngulos)
	float th = 1.0f;
	float tw = 1.0f;

	glm::vec3 A, B, C, D;
	A = glm::vec3(-tw / 2.0, 0.0, 0.0);
	B = glm::vec3(0.0, th / 2.0, 0.0);
	C = glm::vec3(tw / 2.0, 0.0, 0.0);
	D = glm::vec3(0.0, -th / 2.0, 0.0);

	GLfloat vertices[] = {
		//x   y    z    r      g      b      s    t
		A.x, A.y, A.z, cor.r, cor.g, cor.b, 0.0f, offsetTex.t / 2.0f,
		B.x, B.y, B.z, cor.r, cor.g, cor.b, offsetTex.s / 2.0f, offsetTex.t,
		D.x, D.y, D.z, cor.r, cor.g, cor.b, offsetTex.s / 2.0f, 0.0f,
		B.x, B.y, B.z, cor.r, cor.g, cor.b, offsetTex.s / 2.0f, offsetTex.t,
		C.x, C.y, C.z, cor.r, cor.g, cor.b, offsetTex.s, offsetTex.t / 2.0f,
		D.x, D.y, D.z, cor.r, cor.g, cor.b, offsetTex.s / 2.0f, 0.0f
	};

	GLuint VBO;

	//Gera��o do identificador do VBO
	glGenBuffers(1, &VBO);

	//Faz a conex�o (vincula) do buffer como um buffer de array
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	//Envia os dados do array de floats para o buffer da OpenGl
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//Gera��o do identificador do VAO (Vertex Array Object)
	glGenVertexArrays(1, &VAO);

	// Vincula  o VAO primeiro e em seguida conecta e seta o(s) buffer(s) de v�rtices e os ponteiros para os atributos 
	glBindVertexArray(VAO);
	
	//Atributo layout 0 - Posi��o - 3 valores dos 8 que descrevem o v�rtice
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	//Atributo layout 1 - Cor - 3 valores dos 8 que descrevem o v�rtice
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	//Atributo layout 2 - Coordenada de textura - 2 valores dos 8 que descrevem o v�rtice
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Desvincula o VAO 
	glBindVertexArray(0);

	vel = 2.0;

	iTile = 0; //primeiro tile do tileset

	colidiu = false;
}

void Tile::atualizar()
{
	shader->Use();
	//Calculando o quanto teremos que deslocar nas coordenadas de textura
	//Por enquanto considera tilesets com apenas 1 linha
	shader->setVec2("offsetTex", iTile * offsetTex.x, 0.0f * offsetTex.y);

	glm::mat4 model = glm::mat4(1); //matriz identidade
	model = glm::translate(model, pos);
	model = glm::rotate(model, glm::radians(angulo), glm::vec3(0.0, 0.0, 1.0));
	model = glm::scale(model, escala);
	shader->setMat4("model", model);

	shaderDebug->Use();
	shaderDebug->setMat4("model", model);

}

void Tile::desenhar()
{
	this->atualizar();

	shader->Use();
	glBindTexture(GL_TEXTURE_2D, texID); //Conectando com a textura
	glBindVertexArray(VAO); //Conectando ao buffer de geometria

	// Pol�gono Preenchido - GL_TRIANGLES
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindTexture(GL_TEXTURE_2D, 0); //Desconectando buffer de textura
	glBindVertexArray(0);

	shaderDebug->Use();
	glBindVertexArray(VAO);
	glDrawArrays(GL_LINE_LOOP, 0, 6);

	glBindVertexArray(0); //desconectando o buffer de geometria

}

void Tile::desenharNaPos(int i, int j, int iTile, glm::vec2 posIni, int mode)
{
	if (mode == DIAMOND)
	{
		//Encontra a posi��o no mapa para os �ndices ij
		this->pos.x = posIni.x + (j - i) * escala.x / 2.0f;
		this->pos.y = posIni.y + (j + i) * escala.y / 2.0f;
	}

	this->iTile = iTile;

	desenhar();
}