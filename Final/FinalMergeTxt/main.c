#include <stdio.h>
#include <stdlib.h>

#include "merge.h"

int main()
{
    consolidarArchivoCargos("cargosOld.txt", "cargosNew.txt", lineaCargoAEst, cmpCodLegajo, cmpCodCargo);
    return 0;
}
