#include "Halide.h"
#include "halide_image_io.h" // Para carregar/salvar imagens

int main(int argc, char **argv) {
    Halide::Var x("x"), y("y"), c("c");

    Halide::Buffer<uint8_t> input = Halide::Tools::load_image("imagem_entrada.png");

    Halide::Func input_float("input_float");
    input_float(x, y, c) = Halide::cast<float>(input(x, y, c));

    Halide::Func sepia("sepia");

    Halide::Expr r = input_float(x, y, 0);
    Halide::Expr g = input_float(x, y, 1);
    Halide::Expr b = input_float(x, y, 2);

    Halide::Expr new_r = (r * 0.393f) + (g * 0.769f) + (b * 0.189f);
    Halide::Expr new_g = (r * 0.349f) + (g * 0.686f) + (b * 0.168f);
    Halide::Expr new_b = (r * 0.272f) + (g * 0.534f) + (b * 0.131f);

    new_r = Halide::min(new_r, 255.0f);
    new_g = Halide::min(new_g, 255.0f);
    new_b = Halide::min(new_b, 255.0f);

    sepia(x, y, c) = Halide::select(c == 0, Halide::cast<uint8_t>(new_r),
                                    c == 1, Halide::cast<uint8_t>(new_g),
                                            Halide::cast<uint8_t>(new_b));

    sepia.parallel(y);
    sepia.vectorize(x, 16);

    Halide::Buffer<uint8_t> output =
        sepia.realize({input.width(), input.height(), input.channels()});

    Halide::Tools::save_image(output, "imagem_saida_sepia.png");

    printf("Filtro sépia aplicado com sucesso!\n");
    return 0;
}
