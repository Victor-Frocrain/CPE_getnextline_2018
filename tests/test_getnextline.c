/*
** EPITECH PROJECT, 2018
** test getnextline
** File description:
** test getnextline
*/

#include "get_next_line.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <ctype.h>

void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

void my_putstr(char *str)
{
    for (int i = 0; str[i]; i++)
        write(1, &str[i], 1);
}

Test(getnextline, get_normal_line)
{
    int fd = open("test", O_RDONLY);
    char *str = get_next_line(fd);

    close(fd);
    cr_assert_str_eq(str, "Bonjour, comment allez vous ?");
}

Test(getnextline, display_file, .init = redirect_all_std)
{
    int fd = open("test", O_RDONLY);
    char *str = get_next_line(fd);

    while (str) {
        my_putstr(str);
        write(1, "\n", 1);
        str = get_next_line(fd);
    }
    close(fd);
    cr_assert_stdout_eq_str("Bonjour, comment allez vous ?\nJe vais bien et vous ?\nJ'adore Star Wars.\n");
}

Test(getnextline, empty_line)
{
    int fd = open("empty", O_RDONLY);
    char *str = get_next_line(fd);

    close(fd);
    cr_assert_str_eq(str, "");
}

Test(getnextline, fd_corrupted)
{
    int fd = 5;
    char *str = get_next_line(fd);
    bool empty = false;

    if (str == NULL)
        empty = true;
    cr_assert_eq(empty, true);
}

Test(getnextline, display_long_file, .init = redirect_all_std)
{
    int fd = open("wikiStarWars", O_RDONLY);
    char *str = get_next_line(fd);

    while (str) {
        my_putstr(str);
        str = get_next_line(fd);
    }
    close(fd);
    cr_assert_stdout_eq_str("Star Wars (à l'origine nommée sous son titre français, La Guerre des étoiles) est un univers de fantasy et de science-fiction créé par George Lucas. D'abord conçue comme une trilogie cinématographique sortie entre 1977 et 1983, la saga s'accroît ensuite, entre 1999 et 2005, de trois nouveaux films, qui racontent des événements antérieurs à la première trilogie. Cette dernière (épisodes IV, V et VI) ainsi que la deuxième trilogie dite « Prélogie » (épisodes I, II et III) connaissent un immense succès commercial et un accueil critique généralement positif. Dans un souci de cohérence, et pour atteindre un résultat qu'il n'avait pas pu obtenir dès le départ, le créateur de la saga retravaille également les films de sa première trilogie, ressortis en 1997 et 2004 dans de nouvelles versions. Les droits d'auteur de Star Wars sont achetés en 2012 par la Walt Disney Company pour 4,05 milliards de dollars : la sortie au cinéma du septième épisode de la saga et premier de la troisième trilogie (épisodes VII, VIII et IX) est alors planifiée pour 2015. Le Réveil de la Force devient en l'espace d'un mois le plus important succès commercial de la franchise. Le lancement d'une nouvelle trilogie est annoncé par Disney en novembre 2017, qui ne prendra pas place dans la saga de la famille Skywalker. Par ailleurs, Disney et la société de production Lucasfilm inaugurent en 2016 une série de films dérivés regroupés sous le sigle A Star Wars Story, avec la sortie de Rogue One dont les événements se situent juste avant l'épisode IV.En accord avec les lois du genre space opera, l'action se déroule « il y a bien longtemps, dans une galaxie très lointaine » et se fonde sur la lutte entre les chevaliers Jedi et les Sith. Le personnage central des deux premières trilogies cinématographiques, Anakin Skywalker, cède à la tentation du côté obscur de la Force pour devenir Dark VadorNote 1, puis connaît sa rédemption grâce à l'action de son fils, Luke. La troisième trilogie, à partir de l'épisode VII, se déroule trois décennies plus tard avec une nouvelle génération de héros et d'antagonistes. Les nombreux personnages emblématiques, humains et extraterrestres, ont permis de lancer quelques carrières d'acteurs, notamment Harrison Ford et Natalie Portman. L'univers a été décliné dans divers produits dérivés conçus ou non sous l'égide de Lucas : romans, bandes dessinées, jeux vidéo, séries télévisées, etc. L'histoire de la série est ainsi élargie et approfondie par divers médias.Le monde de Star Wars est inspiré de nombreuses œuvres cinématographiques (serials, western, cinéma japonais), mais aussi littéraires (essentiellement d'après les ouvrages d'Edgar Rice Burroughs, de Frank Herbert, de Joseph Campbell, mais aussi d'Isaac Asimov et de J. R. R. Tolkien) et de faits historiques réels. À son tour, le monde créé par George Lucas a influencé une génération de réalisateurs et contribué à la création de nouvelles techniques dans le domaine du cinéma, notamment en ce qui concerne le montage, les bruitages et les effets spéciaux. L'univers de Star Wars a fait l'objet de nombreuses parodies et hommages et dispose également d'une grande communauté de fans qui s'exprime par le biais de diverses manifestations.");
}

Test(getnextline, file_empty)
{
    int fd = open("nothing", O_RDONLY);
    char *str = get_next_line(fd);
    bool empty = false;

    if (str == NULL)
        empty = true;
    close(fd);
    cr_assert_eq(empty, true);
}
