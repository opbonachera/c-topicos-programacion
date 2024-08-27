
char* normalizar(){
    SecuenciaPalabra secLect, sectEscrt;

    secPalCrear(&secLect, cadANormalizar);
    secPalCrear(&secEscrt, cadANormalizar);

    Palabra pal;
    secPalLeer(&secLect, &pal);
    while(!secPalFin(&secLect))
    {
        palabraATitulo(&pal);
        secPalEscribir(&secEscrt, &pal);
        secPalEscribir();
    }
}

bool secPalLeer(SecPal* sec, Palabra* pal)
{
    while(*sec->cursor !='\0' && !esLetra(*sec->cursor))
    {
        sec->cursor;
    }
}

void secPalCrear(SecPal* sec, const char* cad)
{
    sec->cursor = cad;
    sec->finSec = false;
}



