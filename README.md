


```
Généralités
```
● Langage:C++avecleframeworkQt
● Fonctionnalité:Jeudecombat en2D
● Classes:
○ GameScene:Gèrelaboucledejeu,lesentréesdujoueur,metàjourles
entitésetaffichelascène.
○ Entity:Classedebasepourtouslesobjetsdujeu(joueur,ennemis,
balles,explosions,etc.).
○ Player:Représentelecombatantdujoueur.
○ Zombieday Représenteunennemidanslejeu.
○ Bullet:Représentelesballestiréesparlejoueur.
○ Helper:Représenteunalliéquifournitdesobjetsaujoueur.
○ Animation:Gèrelesséquencesd'animationdesentités.

### INTRODUCTION

```
○ Lesobjetsincluentdespotionsdeguérison,desarmes,etdesarmures.
○ Lespotionssoignentautomatiquementunpersonnagelorsquesespointsdevie
atteignent0.
○ Lesarmesaugmententlavaleurd'attaque,lesarmuresaugmententlavaleurde
défense.
○ Chaque personnage peut équiper au plus une arme et une armure
simultanément.
○ Lescombatssedéroulentautourpartour,avecdesdégâtscalculésenfonction
desvaleursd'attaqueetdedéfense.
```

```
○ En cas de victoire, lejoueur peut récupérer desobjets dans l'inventairede
l'ennemivaincu.
○ Lesalliésoffrentaujoueurundeleursobjetsauchoix.
○ Lejoueurpeutrencontrerdesobjetsetdéciderdelesramasserounon.
```
# MODÉLISATION

**● Diagrammedeclasse**


```
Structureducode
```
● ClasseGameScene:
○ Constructeur:
■ Chargelesressources(images)
■ Configurelesdimensionsdelascèneetleminuteur
■ Initialiselejoueuretlesennemis
■ Créel'élémentd'arrière-plan
○ Fonctionloop:
■ Metàjourletempsdeltaetletempsdeboucle
■ Gèrelesentréesdujoueur(espace,touchesfléchées)
■ Vérifielescollisionsentrelesentités(joueur-balle-ennemi,
joueur-ennemi,joueur-helper)
■ Metàjourlespositions,animationsetétatsdeviedesentités
■ Supprimelesentitésmortes
■ Effaceetredessinelascèneaveclespositions,animationset
statistiquesdujoueurmisesàjour
○ FonctionpauseGame:


■ Metlejeuenpause
■ Afficheunmessageaujoueurenfonctiondel'inventaired'un
ennemi(peut-êtreenproposantunramassaged'objet)
■ Attendl'entréedel'utilisateur(nombre)etmetpotentiellementà
jourl'inventairedujoueur
○ FonctionloadPixmap:
■ Chargelesressourcesdujeu(images)dansdesvariables
membres
○ FonctionrenderScene(peutnepasêtreutilisée):
■ Captureunecaptured'écrandelascèneetl'enregistreauformat
PNG
○ FonctionskeyPressEventetkeyReleaseEvent:
■ Gèrentlesentréesclavierdujoueur(déplacement,espacepour
tirer)
○ FonctiondrawString:
■ Créeetaffichedesélémentsdetextesurlascène


```
Fonction loop delaclasse GameScene :
Explicationdétaillée:
```
LafonctionloopestlecœurdelaclasseGameScene.Elleestresponsabledelamiseà
jouretdurendudujeuàchaqueitérationdelaboucledejeu.Voiciuneexplication
détailléedechaqueétapedelafonction:
**1.Miseàjourdutempsdeltaetdutempsdeboucle:**

```
● Letempsdelta(m_deltaTime)représenteletempsécoulédepuisladernière
itérationdelaboucle.
● Letempsdeboucle(m_loopTime)représenteletempscumulédepuisledébutde
laboucledejeu.
● Cesdeuxvaleurssontutiliséespourgarantirquelejeufonctionneàunevitesse
constante,quellequesoitlapuissancedel'ordinateurdujoueur.
```
```
2.Gestiondesentréesdujoueur:
● Lafonctionvérifiesilestouchesfléchées,espaceetautrestouchesd'actionsont
```

enfoncées.
● Enfonctiondestouchesenfoncées,ellemetàjourlesvariablesdemouvement
etd'actiondujoueur.
● Parexemple,silatouchefléchéedroiteestenfoncée,lavariablem_angledu
joueurestincrémentéepourlefairetournerversladroite.

```
3.Détectiondescollisions:
```
● Lafonctionutilisedesalgorithmesdecollisionpourdéterminersideuxentitésdu
jeusesontcroisées.
● Ilexistedifférentstypesdecollisionspossibles:
○ Joueur-balle-ennemi
○ Joueur-ennemi
○ Joueur-helper
● Encasdecollision,lafonctionprendlesmesuresappropriéesenfonctiondu
typedecollision.
● Parexemple,siuneballedujoueurtoucheunennemi,l'ennemiestdétruitetle
joueurreçoitdespointsetdesobjets.

```
4.Miseàjourdesentités:
```
● Lafonctionmetàjourlaposition,l'animationetl'étatdeviedechaqueentitédu
jeu.
● Lapositionestmiseàjourenfonctiondelavitesseetdeladirectiondel'entité.
● L'animationestmiseàjourenfonctiondel'étatactueldel'entité(enmouvement,
immobile,attaquant,etc.).


● L'étatdevieestmisàjourenfonctiondescollisionsetdesdégâtssubis.

```
5.Suppressiondesentitésmortes:
```
● Lesentitésdontl'étatdevieestfalsesontsuppriméesdelalistedesentitésdu
jeu.
● Celapermetdelibérerdelamémoireetd'améliorerlesperformancesdujeu.

```
6.Affichagedelascène:
```
● Lafonctioneffacelascèneetlaredessineaveclespositions,animationset
statistiquesdujoueurmisesàjour.
● ElleutilisedesélémentsgraphiquesQGraphicspourafficherlesentités,lefond
d'écranetlesinformationstextuelles.
**7.Ajoutd'effetssonoresetdemusique(optionnel):**

● Lafonctionpeutégalementêtreutiliséepourajouterdeseffetssonoresetdela
musiqueaujeu.

```
Pointsimportantsàretenir:
```
● Lafonctionloopestuneboucleinfiniequis'exécutetantquelejeuestencours.
● Lavitessedujeuestcontrôléeparlavariablem_loopSpeed.
● Lafonctionutiliseplusieursalgorithmesettechniquespourgarantirungameplay
fluideetréactif.

```
Améliorationspossibles:
```
● Lafonctionpeutêtreoptimiséeenutilisantdestechniquesdemiseencacheet


derenduparlots.
● Desévénementsetdesgestionnairesd'événementspeuventêtreutiliséspour
découplerlalogiquedujeudelaboucledejeu.
● Unsystèmed'étatpeutêtreutilisépourgérerlesdifférentsétatsdujeu(jeuen
cours,pause,findepartie,etc.).


# CAPTURES D'ÉCRAN

### MODEDUJEU:

```
● esc:pourquitter
● touchehaut:pourdéplacer
● touchedroite,gauche:pourdiriger
● toucheespace:pourutiliserunearme
```

### AFFICHAGE:

```
● Lesinventairespourlejoueuràgauche
● Fenetrepourchoisirunearme
```
```
NB:onentrelenumerotedel’objetàprendrede 0 à 2
```

