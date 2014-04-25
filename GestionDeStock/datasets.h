#ifndef __DATASETS_H
#define __DATASETS_H

#include <QString>

#define NO_REF 99999999
#define NR -1
#define ALL NR

#define DEF_NAME "?"
#define DEF_SIZE "XXL"

typedef struct str_ref
{
    int c, t, m, s, o;
} Ref;

/*********** VETEMENTS ************/
	/*
	 * On a 4x VETEMENT
	 * et 3x SURVETEMENT
	 * car on a bien plus de vêtements
	 * et survêtement que le reste
	 * (autant utiliser tout le potentiel
	 * de la référence)
	 */
	enum Category {
		SOUSVETEMENT = 0,
		INTERVETEMENT,
		VETEMENT1,
		VETEMENT2,
		VETEMENT3,
		VETEMENT4,
		SURVETEMENT1,
		SURVETEMENT2,
		SURVETEMENT3,
        ENSEMBLE,
        END_CATEGORY
	};
	
	enum SubCategory0 {
		CULOTTE = 0, TANGA, STRING, SLIP, TAI, MAILLOT,
		CALECON, BOXER, SOUTIENGORGE, FLANELLE, JUSTEAUCORPS,
        CHAUSSETTE, BAS, COLLANT, GUETRES, SOCQUETTE,
        END_TYPE0
	};
	
    enum SubCategory1 {JUPON = 0, GUEPIERE, GAINE, END_TYPE1};

	enum SubCategory2 {
		SHORT = 0, BERMUDA, PANTALON, CORSAIRE, JUPE, KILT, JUPECULOTTE,
		TAILLEHAUTE, TAILLEBASSE, CHEMISE, TSHIRT, DEBARDEUR, BUSTIER,
		CHEMISIER, DESHABILLE, CHEMISECULOTTE, CORSAGE, DOSNU, CACHECOEUR,
		ROBE1, ROBE2, ROBE3, KIMONO, PEIGNOIR, PYJAMA1, PYJAMA2, GANT,
		MITAINE, CHAUSSURE, MOCASSIN, MULE, BABOUCHE, SANDALE, SPARTIATE,
		BALLERINE, ESPADRILLE, CHAUSSON, TENNIS, DERBY, BOTTINE, BOTTE,
		GALOCHE, SABOT, PANTOUFLE, BRODEQUIN, CHAPEAU, CASQUETTE, BONNET,
		CHALE, CAPUCHON, CAGOULE, FOULARD, TURBAN, BANDANA, BANDEAU,
        VOILE, BERET, COUVREOREILLES, CAPUCHE, FICHU,
        END_TYPE2
	};

	enum SubCategory3 {
		BLOUSON = 0, VESTE, VESTON, VAREUSE, PELERINE, SURCHEMISE, CAMISOLE,
		TRICOT, PULLOVER, MOLLETON, SWEATSHIRT, CARDIGAN, GILET, JAQUETTE,
		BLOUSE, TABLIER, MANTEAU, MANTELET, PELISSE, PARDESSUS, MACPARLANE,
		PALETOT, PARKA, TUNIQUE, CAPE, COMBINAISON, PONCHO, SARI, TOGE,
		SALOPETTE, ROBEDECHAMBRE, SURTOUT, CEINTURE, ECHARPE, FRAISE, CRAVATE,
        COL, FAUXCOL, PLASTRON, JABOT, NOEUDPAPILLON, CHANDAIL, ETOLE,
        END_TYPE3
	};

	enum SubCategory4 {
        TAILLEUR = 0, COSTUME1, COSTUME2, COSTUME3, COMPLET,
        END_TYPE4
    };
    
	
/************ COULEURS ************/
	enum Color {
		ROSE = 0, ORANGE, ROUGE, NOIR, PARME, VERTAMANDE, VERT, BEIGE,
		GRIS, BLANC, BLEUMARINE, MARRON, JAUNE, BLANCCASSE, MARRONCHOCOLAT,
		KAKI, MARRONCARAMEL, LAVANDE, BLEU, VIOLET, BLEUTURQUOISE,
        PECHE, BORDEAUX, BLEUCIEL, VERTPOMME, POURPRE, NOISETTE,
        END_COLOR
    };

	typedef struct str_RGB {
		unsigned char r, v, b;
	} RGB;


/************ COULEURS ************/
#define END_SIZE_NAME 21
#define END_SIZE_NUM 79

/************************* DECLARATIONS EXTERNES **********************/
extern QString category[];
extern QString subcategory0[];
extern QString subcategory1[];
extern QString subcategory2[];
extern QString subcategory3[];
extern QString subcategory4[];
extern QString* vetements[];
extern QString color_name[];
extern QString color_hexa[];
extern RGB color_rgb[];
extern QString size_name[];
extern int size_num[];


#endif // __DATASETS_H
