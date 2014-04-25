#include <QString>

#include "datasets.h"

/*********** VETEMENTS ************/

QString category[] = {
"Sous-vêtement",
"Inter-vêtement",
"Vêtement (1)",
"Vêtement (2)",
"Vêtement (3)",
"Vêtement (4)",
"Sur-Vêtement (1)",
"Sur-Vêtement (2)",
"Sur-Vêtement (3)",
"Ensemble"
};

QString subcategory0[] = {
"Culotte", "Tanga", "String", "Slip", "Tai", "Maillot de bain",
"Caleçon", "Boxer", "Soutien-gorge", "Bustier", "Flanelle", "Justaucorps",
"Chaussettes","Bas", "Collant", "Guêtres", "Socquette"
};

QString subcategory1[] = {"Jupon", "Guêpière", "Gaine"};

QString subcategory2[] = {
"Short", "Bermuda", "Pantalon", "Corsaire", "Jupe", "Kilt", "Jupe-culotte",
"Taille haute", "Taille basse", "Chemise", "T-shirt", "Débardeur", "Bustier",
"Chemisier", "Déshabillé", "Chemise-culotte", "Corsage", "Dos nu",
"Cache coeur", "Robe 1 pièce", "Robe 2 pièces", "Robe 3 pièces", "Kimono",
"Peignoir", "Pyjama 1 pièce", "Pyjama 2 pièces", "Gants", "Mitaines",
"Chaussures", "Mocassin", "Mule", "Babouche", "Sandale", "Spartiate",
"Ballerine", "Espadrille", "Chausson", "Tennis", "Derby", "Bottine", "Botte",
"Galoche", "Sabot", "Pantoufle", "Brodequin", "Chapeau", "Casquette", "Bonnet",
"Châle", "Capuchon", "Cagoule", "Foulard", "Turban", "Bandana", "Bandeau",
"Voile", "Béret", "Couvre-oreilles", "Capuche", "Fichu"
};

QString subcategory3[] = {
"Blouson", "Veste", "Veston", "Vareuse", "Pèlerine", "Surchemise", "Camisole",
"Tricot", "Pull-over", "Molleton", "Sweat-shirt", "Cardigan", "Gilet", "Jaquette",
"Blouse", "Tablier", "Manteau", "Mantelet", "Pelisse", "Pardessus", "Mac Parlane",
"Paletot", "Parka", "Tunique", "Cape", "Combinaison", "Poncho", "Sari", "Toge",
"Salopette", "Robe de chambre", "Surtout", "Ceinture", "Écharpe", "Fraise",
"Cravate", "Col", "Faux-col", "Plastron", "Jabot", "Noeud papillon", "Chandail", "Etole"
};

QString subcategory4[] = {
"Tailleur", "Costume 1 pièce", "Costume 2 pièces", "Costume 3 pièces", "Complet"
};

QString* vetements[] = {subcategory0, subcategory1, subcategory2, subcategory3, subcategory4};

QString color_name[] = {
"Rose", "Orange", "Rouge", "Noir", "Parme", "Vert amande", "Vert", "Beige",
"Gris", "Blanc", "Bleu marine", "Marron", "Jaune", "Blanc cassé", "Marron chocolat",
"Kaki", "Marron caramel", "Lavande", "Bleu", "Violet", "Bleu turquoise",
"Pêche", "Bordeaux", "Bleu ciel", "Vert pomme", "Pourpre", "Noisette"
};


/************ COULEURS ************/

QString color_hexa[] = {
"FD6C9E",
"ED7F10",
"FF0000",
"000000",
"CFA0E9",
"82C46C",
"00FF00",
"C8AD7F",
"606060",
"FFFFFF",
"03224C",
"582900",
"FFFF00",
"FEFEE2",
"5A3A22",
"94812B",
"7E3300",
"9683EC",
"0000FF",
"660099",
"25FDE9",
"FDBFB7",
"6D071A",
"77B5FE",
"34C924",
"9E0E40",
"955628"
};

RGB color_rgb[] = {
{253,108,158},
{237,127,16},
{255,0,0},
{0,0,0},
{207,160,233},
{130,196,108},
{0,255,0},
{200,173,127},
{96,96,96},
{255,255,255},
{3,34,76},
{88,41,1},
{255,255,0},
{254,254,226},
{90,58,34},
{148,129,43},
{126,51,0},
{150,131,236},
{0,0,255},
{136,6,206},
{37,253,233},
{253,191,183},
{109,7,26},
{119,181,254},
{52,201,36},
{158,14,64},
{149,86,40}
};


/************ TAILLES *************/

QString size_name[] = {
"0-3 mois",
"3-6 mois",
"6-9 mois",
"9-12 mois",
"12-18 mois",
"18-24 mois",
"2-3 ans",
"3-4 ans",
"4-5 ans",
"5-6 ans",
"7-8 ans",
"9-10 ans",
"11-12 ans",
"13-14 ans",
"XXS",
"XS",
"S",
"M",
"L",
"XL",
"XXL"
};

int size_num[] = {
0,0,0,0,0,0,
1,1,
2,2,
3,3,
4,4,
5,5,
6,6,
7,7,
8,8,
9,9,
10,10,
11,11,
12,12,
13,13,
14,14,
15,15,
16,16,16,16,
17,17,17,17,
18,18,18,18,
19,19,19,19,
20,20,20,20,
20,20,20,20,
20,20,20,20,
20,20,20,20,
20,20,20,20,
20,20,20,20,
20,20,20,20
};
