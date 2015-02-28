package sudoku;

import java.text.MessageFormat;
import choco.Choco;
import choco.cp.model.CPModel;
import choco.cp.solver.CPSolver;
import choco.kernel.model.constraints.Constraint;
import choco.kernel.model.variables.integer.IntegerVariable;

public class Sudoku {

	private IntegerVariable[][] matrice;
	private CPModel modele;

	public Sudoku() {
		this.matrice = new IntegerVariable[9][9];
		this.modele = new CPModel();
		
		//création des variables et de leurs domaines
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				this.matrice[i][j] = Choco.makeIntVar("var_" + i + "_" + j, 1, 9);
				this.modele.addVariable(this.matrice[i][j]);
			}
		}
	
		//Création des contraites : une ligne ne comporte pas deux fois le même numéro
		for (int i = 0; i < 9; i++) {
			Constraint c = Choco.allDifferent(this.matrice[i]);
			this.modele.addConstraint(c);
		}

		//Création des contraintes : une colonne ne comporte pas deux fois le même numéro
		for (int j = 0; j < 9; j++) {

			IntegerVariable[] l = new IntegerVariable[9];

			for (int i = 0; i < 9; i++) {
				l[i] = this.matrice[i][j];
			}

			Constraint c = Choco.allDifferent(l);
			this.modele.addConstraint(c);
		}

		//Création des contraintes : un carré ne comporte pas dexu fois le même numéro
		for (int k = 0; k < 7; k = k + 3) {
			for (int l = 0; l < 7; l = l + 3) {

				IntegerVariable[] mat = new IntegerVariable[9];
				int d = 0;
				for (int i = 0; i < 3; i++) {
					for (int j = 0; j < 3; j++) {
						mat[d] = this.matrice[i + k][j + l];
						d++;
					}
				}

				Constraint c = Choco.allDifferent(mat);

				this.modele.addConstraint(c);

			}
		}

	}

	public static void main(String[] args) {

		Sudoku s = new Sudoku();
	
		//Création du solver
		CPSolver solver = new CPSolver();

		solver.read(s.modele);
		// Solve the model
		solver.solve();
		// Print the solution
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				if(j==3 || j == 6){
					System.out.print(" " + MessageFormat.format("{0} ",
							solver.getVar(s.matrice[i][j]).getVal()));
				}else{
					System.out.print(MessageFormat.format("{0} ",
							solver.getVar(s.matrice[i][j]).getVal()));
				}

			}
			if(i ==2 || i==5){
				System.out.println();
			}
			System.out.println();
		}

	}

}
