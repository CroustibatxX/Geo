#include <SFML/Graphics.hpp>
#include <fstream>
#include "fonction.h"


#define HAUTEURFENETRE 600
#define LARGEURFENETRE 1000
#define HAUTEURBOUTON 100
#define LARGEURBOUTON 300
#define HAUTEURCREDIT 57
#define LARGEURCREDIT 100
#define POS_X_PERSO 100
#define PAS_PERSO 2
#define HAUTEURPERSO 200
#define LARGEURREGLE 150
#define HAUTEURREGLE 50


#define OPACITE_COIN 70
#define IMG_HEADER "image/background.png"
#define IMG_CIEL "image/new.png"
#define IMG_PERSO "image/pacman.png"
#define IMG_BOUTON_JOUER_FOCUS "image/JouerButton.png"
#define IMG_BOUTON_JOUER "image/JouerButtonClick.png"
#define IMG_BOUTON_CREDIT_FOCUS "image/CreditButton.png"
#define IMG_BOUTON_CREDIT "image/CreditButtonClick.png"
#define IMG_FOND "image/fond.png"
#define IMG_REGLE_FOCUS "image/NormalButton.png"
#define IMG_REGLE "image/NormalButtonClick.png"
#define IMG_QUITTER_FOCUS "image/NormalButton2.png"
#define IMG_QUITTER "image/NormalButtonclick2.png"
#define IMG_REJOUER_FOCUS "image/NormalButton3.png"
#define IMG_REJOUER "image/NormalButtonclick3.png"
#define IMG_BALANCE "image/balance.png"

#define X_MAX_JOUER (LARGEURFENETRE-LARGEURBOUTON)/2+LARGEURBOUTON
#define X_MIN_JOUER (LARGEURFENETRE-LARGEURBOUTON)/2
#define Y_MAX_JOUER 2.4*(HAUTEURFENETRE-HAUTEURBOUTON)/3+HAUTEURBOUTON
#define Y_MIN_JOUER 2.4*(HAUTEURFENETRE-HAUTEURBOUTON)/3

#define X_MAX_CREDIT (LARGEURFENETRE-10)
#define X_MIN_CREDIT (LARGEURFENETRE-10-LARGEURCREDIT)
#define Y_MAX_CREDIT (LARGEURFENETRE-10)
#define Y_MIN_CREDIT (HAUTEURFENETRE-10-HAUTEURCREDIT)

#define X_MAX_REGLE (LARGEURFENETRE-LARGEURREGLE)/2+LARGEURREGLE
#define X_MIN_REGLE (LARGEURFENETRE-LARGEURREGLE)/2
#define Y_MAX_REGLE 2.8*(HAUTEURFENETRE-HAUTEURREGLE)/3+HAUTEURREGLE
#define Y_MIN_REGLE 2.8*(HAUTEURFENETRE-HAUTEURREGLE)/3

using namespace sf;

Font chargeFont(const char nom[ ])
{
    Font font;
    if(!font.loadFromFile(nom))
        printf("Erreur de chargement de la police");
    return font;
}


void afficheMenu(RenderWindow *fenetre, Sprite spFond, Sprite spBack, int *phase)
{


    int posYPacManMenu = -HAUTEURPERSO;
    int focusBouton = 0, focusCredit = 0, texteCredit = 0, focusRegle = 0, texteRegles = 0;
    Texture texBoutonJouer, texPerso, texCredit, texRegles, texHeader, texBalance;
    Sprite spBoutonJouer, spPerso, spCredit, spRegles, spHeader, spBalance;
    Text texteCredits, texteCredits2, texteCredits3, texteCredits4, texteRegle, texteRegle2, texteRegle3, texteRegle4, texteScore;

    Font police = chargeFont("04B_30__.ttf");

    texteCredits.setFont(police);
    texteCredits2.setFont(police);
    texteCredits3.setFont(police);
    texteCredits4.setFont(police);
    texteRegle.setFont(police);
    texteRegle2.setFont(police);
    texteRegle3.setFont(police);
    texteRegle4.setFont(police);
    texteScore.setFont(police);

    texteCredits2.setCharacterSize(28);
    texteCredits4.setCharacterSize(28);
    texteRegle2.setCharacterSize(18);
    texteRegle4.setCharacterSize(18);

    texteCredits.setString("Chef de projet :");
    texteCredits2.setString("Esch Axel");
    texteCredits3.setString("Developpeurs :");
    texteCredits4.setString("Esch Axel \nDeremble Baptiste \nGirardot Lenny");
    texteRegle.setString("But du jeu :");
    texteRegle2.setString("Evitez les obstacles en les cassant, en sautant ou en tirant\ndes fantomespour aller le plus loin possible.\nPlus vous survivez dans rester bloquer, plus votre score\naugmente.Serez vous le meilleur joueur ?");
    texteRegle3.setString("Controles :");
    texteRegle4.setString("\"Space\" : Sauter\n\"Right arrow\" : Tirer des missiles");
    texteScore.setString("0");

    texteCredits.setPosition(50,50);
    texteCredits2.setPosition(100,100);
    texteCredits3.setPosition(50,250);
    texteCredits4.setPosition(100,300);
    texteRegle.setPosition(50,50);
    texteRegle2.setPosition(100,100);
    texteRegle3.setPosition(50,200);
    texteRegle4.setPosition(100,250);
    texteScore.setPosition(LARGEURFENETRE-200,50);

    texteCredits.setStyle(Text::Underlined);
    texteCredits3.setStyle(Text::Underlined);
    texteRegle3.setStyle(Text::Underlined);
    texteRegle.setStyle(Text::Underlined);

    texPerso.loadFromFile(IMG_PERSO);
    texHeader.loadFromFile(IMG_HEADER);
    texBalance.loadFromFile(IMG_BALANCE);

    spHeader.setTexture(texHeader);
    spPerso.setTexture(texPerso);
    spBalance.setTexture(texBalance);

    spBalance.setPosition(LARGEURFENETRE-300, 30);
    spHeader.setPosition(0,0);
    spCredit.setPosition(X_MIN_CREDIT, Y_MIN_CREDIT);
    spBoutonJouer.setPosition(X_MIN_JOUER, Y_MIN_JOUER);
    spRegles.setPosition(X_MIN_REGLE, Y_MIN_REGLE);

    do
    {
        Event evt;
        while (fenetre->pollEvent(evt)) // TOUS LES EVENEMENTS DU MENU
        {
            if (evt.type == Event::Closed)
                fenetre->close();
            else if (evt.type == Event::MouseButtonPressed)
            {
                // Le joueur appuie sur "JOUER"
                if(evt.mouseButton.x >= X_MIN_JOUER && evt.mouseButton.x <= X_MAX_JOUER)
                {
                    if(evt.mouseButton.y >= Y_MIN_JOUER && evt.mouseButton.y <= Y_MAX_JOUER)
                    {
                        *phase = *phase + 1;
                    }
                }
                // Le joueur appuie sur "CREDITS"
                if(evt.mouseButton.x >= X_MIN_CREDIT && evt.mouseButton.x <= X_MAX_CREDIT)
                {
                    if(evt.mouseButton.y >= Y_MIN_CREDIT && evt.mouseButton.y <= Y_MAX_CREDIT)
                    {
                        texteCredit++; // On incremente et divise par deux, suivant le reste on sait si le joueur a cliqué ou non
                    }
                }
                // Le joueur appuie sur "REGLES"
                if(evt.mouseButton.x >= X_MIN_REGLE && evt.mouseButton.x <= X_MAX_REGLE)
                {
                    if(evt.mouseButton.y >= Y_MIN_REGLE && evt.mouseButton.y <= Y_MAX_REGLE)
                    {
                        texteRegles++; // On incremente et divise par deux, suivant le reste on sait si le joueur a cliqué ou non
                    }
                }
            }
            else if (evt.type == Event::MouseMoved)
            {
                // On change l'image (buton focus) si le joueur a la souris dessus BOUTON JOUER
                if(evt.mouseMove.x >= X_MIN_JOUER && evt.mouseMove.x <= X_MAX_JOUER)
                {
                    if(evt.mouseMove.y >= Y_MIN_JOUER && evt.mouseMove.y <= Y_MAX_JOUER)
                    {
                        focusBouton=1;
                    }
                    else
                    {
                        focusBouton=0;
                    }
                }
                else
                {
                    focusBouton=0;
                }

                // On change l'image (buton focus) si le joueur a la souris dessus BOUTON CREDITS
                if(evt.mouseMove.x >= X_MIN_CREDIT && evt.mouseMove.x <= X_MAX_CREDIT)
                {
                    if(evt.mouseMove.y >= Y_MIN_CREDIT && evt.mouseMove.y <= Y_MAX_CREDIT)
                    {
                        focusCredit = 1;
                    }
                    else
                    {
                        focusCredit = 0;
                    }
                }
                else
                {
                    focusCredit = 0;
                }

                // On change l'image (buton regle) si le joueur a la souris dessus BOUTON regle
                if(evt.mouseMove.x >= X_MIN_REGLE && evt.mouseMove.x <= X_MAX_REGLE)
                {
                    if(evt.mouseMove.y >= Y_MIN_REGLE && evt.mouseMove.y <= Y_MAX_REGLE)
                    {
                        focusRegle = 1;
                    }
                    else
                    {
                        focusRegle = 0;
                    }
                }
                else
                {
                    focusRegle = 0;
                }
                // focus balance
                if (evt.mouseMove.x >= LARGEURFENETRE-300 && evt.mouseMove.x <= LARGEURFENETRE)
                {
                    if (evt.mouseMove.y >= 30 && evt.mouseMove.y <= 110) {
                        spBalance.setColor(Color(spBalance.getColor().r,spBalance.getColor().g,spBalance.getColor().b, 255));
                        texteScore.setColor(Color(texteScore.getColor().r,texteScore.getColor().g,texteScore.getColor().b, 255));
                    }
                    else {
                        spBalance.setColor(Color(spBalance.getColor().r,spBalance.getColor().g,spBalance.getColor().b, OPACITE_COIN));
                        texteScore.setColor(Color(texteScore.getColor().r,texteScore.getColor().g,texteScore.getColor().b, OPACITE_COIN));
                    }
                }
                else {
                    spBalance.setColor(Color(spBalance.getColor().r,spBalance.getColor().g,spBalance.getColor().b, OPACITE_COIN));
                    texteScore.setColor(Color(texteScore.getColor().r,texteScore.getColor().g,texteScore.getColor().b, OPACITE_COIN));
                }
            }

        }
        fenetre->clear();
        if(focusBouton == 1)
            texBoutonJouer.loadFromFile(IMG_BOUTON_JOUER);
        else if(focusBouton == 0)
            texBoutonJouer.loadFromFile(IMG_BOUTON_JOUER_FOCUS);

        if(focusCredit == 1)
            texCredit.loadFromFile(IMG_BOUTON_CREDIT);
        else if(focusCredit == 0)
            texCredit.loadFromFile(IMG_BOUTON_CREDIT_FOCUS);

        if(focusRegle == 1)
            texRegles.loadFromFile(IMG_REGLE);
        else if(focusRegle == 0)
            texRegles.loadFromFile(IMG_REGLE_FOCUS);

        spRegles.setTexture(texRegles);
        spBoutonJouer.setTexture(texBoutonJouer);
        spCredit.setTexture(texCredit);

        fenetre->draw(spBack);
        if((texteCredit%2) == 1)  // On clique sur le bouton credits
        {
            fenetre->draw(spFond);
            fenetre->draw(texteCredits);
            fenetre->draw(texteCredits2);
            fenetre->draw(texteCredits3);
            fenetre->draw(texteCredits4);
            fenetre->draw(spCredit);

        }
        else if (texteRegles%2 == 1)
        {
            fenetre->draw(spFond);
            fenetre->draw(texteRegle);
            fenetre->draw(texteRegle2);
            fenetre->draw(texteRegle3);
            fenetre->draw(texteRegle4);
            fenetre->draw(spRegles);
        }
        else  // On ne clique pas sur le bouton credits ni bouton regles: On est dans le menu principal
        {
            fenetre->draw(spHeader);
            if(posYPacManMenu+HAUTEURPERSO+155 < HAUTEURFENETRE)
                posYPacManMenu += PAS_PERSO;
            spPerso.setPosition(POS_X_PERSO, posYPacManMenu);
            fenetre->draw(spRegles);
            fenetre->draw(spPerso);
            fenetre->draw(spBoutonJouer);
            fenetre->draw(spCredit);
            fenetre->draw(spBalance);
            fenetre->draw(texteScore);
        }

        fenetre->display();
    }
    while(*phase == 1);

}


void selectionPseudo ( RenderWindow *fenetre, Sprite spFond, Sprite spBack, char pseudo[ ], int *phase)
{

    char pseudoVariable[20] = "_";
    int nbLettre = 0, i=0;

    Text textePseudo, consigne;

    Font font = chargeFont("04B_30__.ttf");

    textePseudo.setFont(font);
    consigne.setFont(font);

    consigne.setPosition(50,150);
    textePseudo.setPosition(100,200);

    consigne.setString("Entrez votre pseudo :");
    do
    {
        Event evt;
        while (fenetre->pollEvent(evt))
        {
            if (evt.type == sf::Event::Closed)
                fenetre->close();
            if (evt.type == Event::TextEntered)
            {
                if(isalpha(evt.text.unicode) && nbLettre < 19)
                {
                    pseudoVariable[i] = evt.text.unicode;
                    i++;
                    pseudoVariable[i] = '_';
                    pseudoVariable[i+1] = '\0';
                    textePseudo.setString(pseudoVariable);
                    nbLettre++;
                }
            }
            if ((evt.type == Event::KeyPressed && evt.key.code == Keyboard::Return) || nbLettre == 19)  // SI ON APPUIE SUR ENTRER OU SI PSEUDO>20 LETTRES
            {
                *phase = *phase + 1;
            }
            if (evt.type == Event::KeyPressed && evt.key.code == Keyboard::BackSpace)   // L'utilisateur veut supprimer le dernier caractere
            {
                char suppr = ' ';
                if (nbLettre >= 1)
                {
                    pseudoVariable[i+1] = suppr;
                    pseudoVariable[i] = '\0';
                    pseudoVariable[i-1] = '_';
                    i--;
                    nbLettre--;
                }
            }
        }
        fenetre->clear();
        fenetre->draw(spBack);
        fenetre->draw(spFond);
        fenetre->draw(textePseudo);
        fenetre->draw(consigne);
        textePseudo.setString(pseudoVariable);
        fenetre->display();
    }
    while (*phase == 2);
    pseudoVariable[nbLettre] = ' '; // On enleve le \0
    pseudoVariable[nbLettre] = '\0'; // On remplace la barre par le caractère de fin de chaine
    printf("Saisie terminee\n");
    for(int i=0; i<sizeof(pseudoVariable); i++)
    {
        pseudo[i] = pseudoVariable[i];
    }

}


void affiScore( RenderWindow *fenetre, Sprite spFond, Sprite spBack, char pseudoX[ ], int scoreX, int *phase, int *jouer)
{
    Texture texRejouter, texQuitter;
    Sprite spRejouer, spQuitter;

    int focusRejouer = 0, focusQuitter = 0;
    spQuitter.setPosition(2*(LARGEURFENETRE-LARGEURREGLE)/5, 9*(HAUTEURFENETRE-HAUTEURREGLE)/10);
    spRejouer.setPosition(4*(LARGEURFENETRE-LARGEURREGLE)/5-LARGEURREGLE, 9*(HAUTEURFENETRE-HAUTEURREGLE)/10);

    printf("\ndebut phase %i : SCORES\n", *phase);

    // Chemin du flux de lecture
    std::ifstream entree("score.txt");

    // Lecture du fichier et comparaison des scores
    int resultat, position = 5,trouve = 0, nbreecriture = 0;

    char texteRes[75];
    char reecriture[100] = " "; // On donne une valeure de base pour pas que ca pose de problemes avec le sprintf

    Text texteResultat, texteScore;

    Font font = chargeFont("04B_30__.ttf");

    texteScore.setFont(font);
    texteResultat.setFont(font);

    texteResultat.setPosition(350,300);
    texteScore.setPosition(300,75);
    std::string ligne;

    if(entree) // Fichier ouvert avec succes
    {
        int i;
        for(i=0; i<5; i++) // Tant que la ligne n'est pas vide on lit
        {
            std::string pseudo;
            entree >> pseudo;
            int score;
            entree >> score;
            position--;
            if (scoreX>=score && trouve != 1)
            {
                resultat = (5-position);
                trouve = 1;
                sprintf(reecriture, "%s\n%s\t\t%i", reecriture, pseudoX, scoreX);
                nbreecriture++;
            }

            if (nbreecriture < 5)
            {
                sprintf(reecriture, "%s\n%s\t\t%i", reecriture, pseudo.c_str(), score);
                nbreecriture++;
            }
            else if(trouve == 0 && nbreecriture >= 5)
            {
                resultat = 99; // La valeur n'est pas trouve mais ne se situe pas dans le top 5
            }
        }

    }
    else // Probleme avec le fichier texte
    {
        printf("Probleme avec le fichier score.txt (lecture)");
    }

    // Chemin du flux d'ecriture
    std::ofstream sortie("score.txt");

    if(sortie)
    {
        // Ecriure des nouveaux 5 premiers dans le fichier texte
        sortie << reecriture << std::endl;
        texteScore.setString(reecriture);
        if(resultat <= 5 && resultat > 0)
            sprintf(texteRes,"\nFelicitations,\nvous etes %i\n", resultat);
        else
            sprintf(texteRes,"\nMalheureusement,\nvous n'etes pas dans le top 5... \nRejouez !\n");
        do
        {
            Event evt;
            while (fenetre->pollEvent(evt)) // TOUS LES EVENEMENTS DU MENU
            {
                if (evt.type ==  Event::Closed) {
                    *phase = *phase + 1;
                    fenetre->close();
                }
                else if (evt.type == Event::MouseButtonPressed)
                {
                    // Le joueur appuie sur "JOUER"
                    if(evt.mouseButton.y >= 9*(HAUTEURFENETRE-HAUTEURREGLE)/10 && evt.mouseButton.y <= 9*(HAUTEURFENETRE-HAUTEURREGLE)/10+HAUTEURREGLE)
                    {
                        if(evt.mouseButton.x >= 2*(LARGEURFENETRE-LARGEURREGLE)/5 && evt.mouseButton.x <= 2*(LARGEURFENETRE-LARGEURREGLE)/5+LARGEURREGLE)
                        {
                            *jouer = 0;
                        }
                        if(evt.mouseButton.x >= 4*(LARGEURFENETRE-LARGEURREGLE)/5-LARGEURREGLE && evt.mouseButton.x <= 4*(LARGEURFENETRE-LARGEURREGLE)/5)
                        {
                            *jouer = 1;
                        }
                        *phase = *phase + 1;
                    }
                }
                else if (evt.type == Event::MouseMoved)
                {
                    // Le joueur appuie sur "JOUER"
                    if(evt.mouseMove.y >= 9*(HAUTEURFENETRE-HAUTEURREGLE)/10 && evt.mouseMove.y <= 9*(HAUTEURFENETRE-HAUTEURREGLE)/10+HAUTEURREGLE)
                    {
                        if(evt.mouseMove.x >= 2*(LARGEURFENETRE-LARGEURREGLE)/5 && evt.mouseMove.x <= 2*(LARGEURFENETRE-LARGEURREGLE)/5+LARGEURREGLE)
                        {
                            focusQuitter = 1;
                        }
                        else
                        {
                            focusQuitter = 0;
                        }
                        if(evt.mouseMove.x >= 4*(LARGEURFENETRE-LARGEURREGLE)/5-LARGEURREGLE && evt.mouseMove.x <= 4*(LARGEURFENETRE-LARGEURREGLE)/5)
                        {
                            focusRejouer = 1;
                        }
                        else
                        {
                            focusRejouer = 0;
                        }
                    }
                    else
                    {
                        focusRejouer = 0;
                        focusQuitter = 0;
                    }
                }
            }
            if (focusRejouer == 1)
                texRejouter.loadFromFile(IMG_REJOUER);
            else if (focusRejouer == 0)
                texRejouter.loadFromFile(IMG_REJOUER_FOCUS);

            if (focusQuitter == 1)
                texQuitter.loadFromFile(IMG_QUITTER);
            else if (focusQuitter == 0)
                texQuitter.loadFromFile(IMG_QUITTER_FOCUS);

            spRejouer.setTexture(texRejouter);
            spQuitter.setTexture(texQuitter);

            fenetre->clear();
            texteResultat.setString(texteRes);
            texteResultat.setOrigin(Vector2f(texteResultat.getGlobalBounds().width/2, texteResultat.getGlobalBounds().height/2));
            texteResultat.setPosition(LARGEURFENETRE/2, 6*HAUTEURFENETRE/10);
            texteResultat.setCharacterSize(25);
            fenetre->draw(spBack);
            fenetre->draw(spFond);
            fenetre->draw(spRejouer);
            fenetre->draw(spQuitter);
            fenetre->draw(texteResultat);
            fenetre->draw(texteScore);
            fenetre->display();

        }
        while(*phase == 4);

    }
    else
    {
        printf("Probleme avec le fichier score.txt (ecriture)");
    }

    /* Variables :
    resultat = position du joueur si il est dans le top 5 sinon = 99
    reecriure = texte qui est reecrit dans le fichier texte (modifie si joueur est dans top5)
    */
}

void afficheOr( RenderWindow *fenetre, int *phase, int *score ) {
    Text balance;
    Texture texBalace;
    Sprite spBalance;
    Font font = chargeFont("04B_30__.ttf");
    balance.setFont(font);
    balance.setPosition(LARGEURFENETRE-200,50);
    texBalace.loadFromFile(IMG_BALANCE);
    spBalance.setTexture(texBalace);
    spBalance.setPosition(LARGEURFENETRE-300, 30);
    Event evt;
        while (fenetre->pollEvent(evt)) // TOUS LES EVENEMENTS DU MENU
        {
            if (evt.type == Event::Closed)
                fenetre->close();
            else if (evt.type == Event::KeyPressed && evt.key.code == Keyboard::Return)  // APPUIE SUR ENTRER = 10 POINTS
            {
                *score = *score + 1;
            }
            else if (evt.type == Event::KeyPressed && evt.key.code == Keyboard::BackSpace)  // Suivant
            {
                *phase = *phase + 1;
            }
        }
    char charScore[20] = "";
    sprintf(charScore, "%i", *score);
    balance.setString(charScore);
    fenetre->draw(spBalance);
    fenetre->draw(balance);
}




