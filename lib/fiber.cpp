# include <math.h>  //exp

# include "netxpto.h"
# include "fiber.h"


using namespace std;

void Fiber::initialize(void) {

	outputSignals[0]->setSymbolPeriod(inputSignals[0]->getSymbolPeriod());
	outputSignals[0]->setSamplingPeriod(inputSignals[0]->getSamplingPeriod());
	outputSignals[0]->setFirstValueToBeSaved(inputSignals[0]->getFirstValueToBeSaved());

	// initializer

	// reservar espaço em memoria para a função transferencia malloc()
	// reservar espaço em memoria para a resposta impulsional
	// calcular a função H(w)
	// calculas o h(t) ifft(H(w)
	// gravas num ficheiro H(w)
	// gravas noutro ficheiro o h(t)
}

bool Fiber::runBlock(void) {

	int ready = inputSignals[0]->ready();
	
	int space = outputSignals[0]->space();

	int process = min(ready, space);

	if (process == 0) return false;

	t_complex inSig;
	t_complex outSig;
	t_real h = exp(-fiberLength*attenuationCoeficient / 2);
	for (int i = 0; i < process; i++) {

		inputSignals[0]->bufferGet(&inSig);

		outSig = inSig*h;

		outputSignals[0]->bufferPut(outSig);

	}

	return true;
}
