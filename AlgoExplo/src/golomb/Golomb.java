package golomb;

import choco.cp.model.CPModel;
import choco.cp.solver.CPSolver;

public class Golomb {

	private CPModel modele;

	public Golomb() {
		this.modele = new CPModel();
	}

	public static void main(String[] args) {
		Golomb g = new Golomb();

		CPSolver solver = new CPSolver();

		solver.read(g.modele);
		// Solve the model
		solver.solve();

	}

}
