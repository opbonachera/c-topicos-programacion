
char* normalizar(const char* cadenaANormalizar, const char* cadenaNormalizada){
    SecuenciaPalabra secLect, sectEscr;

    secPalCrear(&secLect, cadenaANormalizar);
    secPalCrear(&secEscr, cadenaNormalizada);

    Palabra pal;

    secPalLeer(&secLect, &pal);
    while(!secPalFin(&secLect))
    {
        palabraATitulo(&pal);
        secPalEscribir(&secEscr, &pal);
        secPalEscribir(&secEscr, ' ');
        secPalLeer(&secLect, &pal);
    }

    secPalCerrar(&secEscr);

    return cadenaNormalizada;
}

bool secPalLeer(SecuenciaPalabra* sec, Palabra* pal)
{
    while(*sec->cursor != '\0' && !esLetra(*sec->cursor))
    {
        sec->cursor++;
    }

    if(!(*sec->cursor))
    {
        sec->finSec = true;
        return false;
    }

    char* actPal = pal->vectorPalabra;
    while(*sec->cursor && esLetra(*sec->cursor))
    {
        *actPal=*sec->cursor;
        actPal++;
        sec->cursor++;
    }

    *actPal = '\0';
    return true;
}

void secPalCrear(SecuenciaPalabra* sec, const char* cad)
{
    sec->cursor = cad;
    sec->finSec = false;
}

void secPalEscribir(SecuenciaPalabra* sec, const Palabra* pal)
{
    char* actPal = pal->vectorPalabra;
    while(*actPal)
    {
        *sec->cursor = *actPal;
        sec->cursor++;
        actPal++;
    }
}

void secPalEscribirCar(SecuenciaPalabra* sec, char c)
{
    *sec->cursor = c;
    sec->cursor++;
}

void palabraATitulo(Palabra *pal)
{
    char* actPal = pal->vectorPalabra;

    *actPal = aMayuscula(*actPal);
    actPal++;

    while(*actPal)
    {
        *actPal = aMinuscula(&actPal);
        actPal++;
    }
}
