#include "../header/shader.h"

char* readFile(string fileName){
    char *texto = NULL;
    ifstream arquivo(fileName);
    string textoArquivo;
    if(arquivo.is_open()){
        ostringstream stream;
        stream << arquivo.rdbuf();
        textoArquivo = stream.str();
        texto = new char[textoArquivo.length() + 1];
        strcpy(texto, textoArquivo.c_str());
    }
    else
        cout << "Arquivo "<< fileName <<" não pode ser aberto" << endl;
    return texto;
}

void initShaders(){
    const char *vertexShader   = readFile("vertexShader.vert");
    const char *fragmentShader = readFile("fragmentShader.frag");

    int  sucesso;
    char mensagemCompilacao[512];

    unsigned int vsId = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vsId, 1, &vertexShader, NULL);
    glCompileShader(vsId);
    glGetShaderiv(vsId, GL_COMPILE_STATUS, &sucesso);
    if(!sucesso){
        glGetShaderInfoLog(vsId, 512, NULL, mensagemCompilacao);
        cout << "Erro de compilacao no vertex shader: \n" << mensagemCompilacao << endl;
    }

    unsigned int fsId = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fsId, 1, &fragmentShader, NULL);
    glCompileShader(fsId);
    glGetShaderiv(fsId, GL_COMPILE_STATUS, &sucesso);
    if(!sucesso){
        glGetShaderInfoLog(fsId, 512, NULL, mensagemCompilacao);
        cout << "Erro de compilacao no fragment shader: \n" << mensagemCompilacao << endl;
    }

    unsigned int shaderId = glCreateProgram();
    glAttachShader(shaderId, vsId);
    glAttachShader(shaderId, fsId);
    glLinkProgram(shaderId);
    glGetProgramiv(shaderId, GL_LINK_STATUS, &sucesso);
    if(!sucesso) {
        glGetProgramInfoLog(shaderId, 512, NULL, mensagemCompilacao);
        cout << "Erro de linkagem dos shaders: \n" << mensagemCompilacao << endl;
    }
}