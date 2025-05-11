# 🐝 **Project Bee Edition** 🌷

*Un tower defense bourdonnant au cœur d’un univers givré !*

---

## 🎯 **Description du Projet**

**Bee Edition** est un jeu de **tower defense hivernal** où le joueur doit défendre la **tulipe sacrée** contre des **abeilles déchaînées** ! Ces petites créatures volantes suivent un chemin unique généré aléatoirement à travers une carte enneigée.

Le joueur devra **placer stratégiquement ses défenseurs** autour de ce sentier pour stopper la ruée.

**Ennemis** :

* 🐝 Abeille :

  * Dégâts : 1
  * Points de vie : 4
  * Niveau : 0

**Défenseurs** :

* 🌷 Tulipe :

  * Portée : 1
  * Dégâts : 1
  * Niveau : 1

Le joueur commence avec **3 dollars** pour positionner ses tulipes et **0 point**. Chaque ennemi éliminé rapporte **1 point et 1 dollar** pour améliorer sa défense.

---

## 👥 **Équipe de Développement**

* Mathias **CORDERO**
* Clément **SCHEIDER**
* Alexandre **BERNARD**

Étudiants en ingénierie à **CY Tech**, nous avons réalisé ce projet dans le cadre du module de **programmation en C**.

---

## 🚀 **Fonctionnalités principales**

* 🗺️ **Génération aléatoire** de cartes (taille entre 11 et 51)
* 🛤️ **Création procédurale** d’un chemin unique vers la tulipe sacrée
* 🎯 **Placement stratégique** des tulipes
* 🐝 **Déplacement automatique** des abeilles sur le chemin
* 🧠 **Système d’amélioration** des défenseurs
* 💰 **Système de ressources** : chaque ennemi vaincu rapporte des dollars
* ⏸️ **Menu principal** avec options de sauvegarde et reprise
* 🖥️ **Affichage terminal** avec mise à jour dynamique
* 💾 **Fichier de sauvegarde** pour reprendre une partie

---

## 🧪 **Difficultés rencontrées & Solutions**

🧩 **Génération procédurale du chemin**
➡️ Plusieurs essais ont été nécessaires pour que les chemins se terminent correctement sur une case “END”.

🧱 **Affichage et freeze du terminal**
➡️ Résolu en ajustant les conditions de boucle et les `clear` entre les frames.

🐞 **Erreurs de segmentation**
➡️ Survenues lors de la manipulation des tableaux 2D, corrigées avec un meilleur contrôle des indices et utilisation de `calloc`.

🚫 **Problèmes de déplacement**
➡️ Les crabes (anciennes entités ennemies) ne se déplaçaient pas, bugs corrigés progressivement grâce au suivi des coordonnées et à la superposition des entités.

💣 **Double apparition de bombes**
➡️ Anomalie occasionnelle encore en observation, potentiellement due à une erreur de mise à jour de l’état de la carte.

---

## ⏱️ **Phases du Jeu**

1. **Menu principal** : Démarrer / Reprendre / Quitter
2. **Génération de la carte et du chemin**
3. **Placement des tulipes**
4. **Début des vagues d’abeilles**
5. **Déplacement automatique** des ennemis
6. **Phase d’attaque** des défenseurs
7. **Mise à jour de l’affichage** toutes les 0.5 secondes
8. **Fin de partie** : victoire (tulipe protégée) ou défaite (abeilles gagnent)
9. **Sauvegarde** de la partie (optionnel)

---

## 🛠️ **Compilation & Exécution**

Ouvrez votre terminal et entrez les commandes suivantes :

```bash
git clone https://github.com/Alexandre-bat/Projet-Tower-Defense.git
cd Projet-Tower-Defense
make
```

Et c’est parti pour défendre la tulipe sacrée ! 🌷🐝

---

## 💡 **Outils utilisés**

* 👨‍💻 **C** (langage principal)
* 🧰 **GitHub** (versioning collaboratif)
* 💻 **VirtualBox + Debian** (environnement de dev)
* 📹 **Nvidia & Microsoft Clipchamp** (montage vidéo)

---

## 🌸 **Bonne chance**

---
