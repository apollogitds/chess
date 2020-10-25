#include <iostream>
#include <string_view>
#include <cstdlib>

void logo()
{
    puts("");
    puts("                              #  #    #");
    puts("                             ### #   # #");
    puts("                              #  ### ###");
    puts("                              #  # # #");
    puts("                              ## # #  ##");
    puts("");
    puts("                  ####  ##  ##  ######  ####   ####");
    puts("                 ##  ## ##  ## ##   ## ##  ## ##  ##");
    puts("                 ##  ## ##  ## ##      ##     ##");
    puts("                 ##     ##  ## ######   ####   ####");
    puts("                 ##  ## ###### ##          ##     ##");
    puts("                 ##  ## ##  ## ##   ## ##  ## ##  ##");
    puts("                  ####  ##  ##  ######  ####   ####");
}
namespace Color
{
    const auto FG_WHITE = "\033[97m";
    const auto FG_BLACK = "\033[30m";
    const auto FG_DEFAULT = "\033[39m";
    const auto BG_LIGHT_BLUE = "\033[104m";
    const auto BG_BLUE = "\033[44m";
    const auto BG_DARK_BLUE = "\033[106m";
    const auto BG_DEFAULT = "\033[49m";
}; // namespace Color

enum class FigureType : uint8_t
{
    king,
    queen,
    rook,
    bishop,
    horse,
    pawn,
    empty
};

enum class FigureColor : uint8_t
{
    black,
    white,
    empty
};

enum class FigureSign : uint8_t
{
    K,
    Q,
    R,
    B,
    H,
    P,
    E
};

class Figure
{
public:
    FigureType type;
    FigureColor color;
    char sign;
    Figure()
    {
        type = FigureType::empty;
        color = FigureColor::empty;
    }
};

class ChessField
{
public:
    Figure field[8][8];
    ChessField()
    {
        for (size_t i = 2; i < 6; i++)
        {
            for (size_t j = 0; j < 8; j++)
            {
                field[i][j].type = FigureType::empty;
                field[i][j].color = FigureColor::empty;
                field[i][j].sign = ' ';
            }
        }

        for (size_t i = 1; i < 7; i += 5)
        {
            auto color = (i == 1 ? FigureColor::black : FigureColor::white);
            for (size_t j = 0; j < 8; j++)
            {
                field[i][j].type = FigureType::pawn;
                field[i][j].color = color;
                field[i][j].sign = 'P';
            }
        }

        for (size_t i = 0; i < 8; i += 7)
        {
            auto color = (i == 0 ? FigureColor::black : FigureColor::white);
            field[i][0].type = FigureType::rook;
            field[i][0].color = color;
            field[i][0].sign = 'R';
            field[i][1].type = FigureType::horse;
            field[i][1].color = color;
            field[i][1].sign = 'H';
            field[i][2].type = FigureType::bishop;
            field[i][2].color = color;
            field[i][2].sign = 'B';
            field[i][3].type = FigureType::queen;
            field[i][3].color = color;
            field[i][3].sign = 'Q';
            field[i][4].type = FigureType::king;
            field[i][4].color = color;
            field[i][4].sign = 'K';
            field[i][5].type = FigureType::bishop;
            field[i][5].color = color;
            field[i][5].sign = 'B';
            field[i][6].type = FigureType::horse;
            field[i][6].color = color;
            field[i][6].sign = 'H';
            field[i][7].type = FigureType::rook;
            field[i][7].color = color;
            field[i][7].sign = 'R';
        }
    }

    void drawpad()
    {
        puts("\n          a      b      c      d      e      f      g      h   \n");
        auto color = Color::BG_BLUE;
        for (size_t row = 0; row < 8; row++)
        {
            for (size_t i = 0; i < 3; i++)
            {
                for (size_t column = 0; column < 10; column++)
                {
                    for (size_t j = 0; j < 7; j++)
                    {
                        if (column == 0 || column == 9)
                        {
                            if (j == 3)
                            {
                                if (i == 1)
                                {
                                    std::cout << row + 1;
                                }
                                else
                                {
                                    std::cout << ' ';
                                }
                            }
                            else
                            {
                                std::cout << ' ';
                            }
                            //color = (Color::BG_BLUE ? Color::BG_LIGHT_BLUE : Color::BG_BLUE); //=

                            continue;
                        }
                        if (i == 1 && j == 3)
                        {
                            if (field[row][column - 1].color == FigureColor::black)
                            {
                                std::cout << color << Color::FG_BLACK << field[row][column - 1].sign << Color::FG_DEFAULT << Color::BG_DEFAULT;
                            }
                            else
                            {
                                std::cout << color << Color::FG_WHITE << field[row][column - 1].sign << Color::FG_DEFAULT << Color::BG_DEFAULT;
                            }
                        }
                        else
                        {
                            std::cout << color << ' ' << Color::BG_DEFAULT;
                        }
                    }
                    color = (color == Color::BG_BLUE ? Color::BG_LIGHT_BLUE : Color::BG_BLUE);
                }
                std::cout << "\n";
            }
            color = (row % 2 == 1 ? Color::BG_BLUE : Color::BG_LIGHT_BLUE);
        }
        puts("\n          a      b      c      d      e      f      g      h   \n");
        return;
    }

    void movement()
    {
    }
};
void turn(Figure field[][8], bool sideturn)
{
    if (!sideturn)
    {
        std::cout << Color::BG_BLUE << Color::FG_WHITE << "  Turn of WHITES  " << Color::FG_DEFAULT << Color::BG_DEFAULT << std::endl;
    }
    else
    {
        std::cout << Color::BG_BLUE << Color::FG_BLACK << "  Turn of BLACKS  " << Color::FG_DEFAULT << Color::BG_DEFAULT << std::endl;
    }
    puts("MOVEMENT");
    printf("from: ");
    char from[2];
    scanf("%c%c", &from[0], &from[1]);
    printf("to: ");
    char to[2];
    scanf("\n%c%c", &to[0], &to[1]);
    printf("from %c%c to %c%c\n", from[0], from[1], to[0], to[1]);
    std::cout << field[from[0] - 96][from[1] - 48].sign << " 123" << std::endl;
}

int main()
{
    logo();
    ChessField one;
    one.drawpad();
    //turn(one.field, 0);
    //one.drawpad();
}