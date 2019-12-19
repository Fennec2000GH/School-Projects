package edu.ufl.cise.cs1.controllers;

import game.controllers.AttackerController;
import game.models.*;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.stream.Collectors;
import java.util.Collections;
import java.util.stream.Stream;

public final class StudentAttackerController implements AttackerController
{
	public void init(Game game) { }

	public void shutdown(Game game) { }

	public int update(Game game,long timeDue)
	{
		int action = 0;

		//Chooses a random LEGAL action if required.

		//lists of Node objects holding special objects
		Maze currentMaze = game.getCurMaze();
		List<Integer> possibleDirs = game.getAttacker().getPossibleDirs(true);
		List<Defender> defenderList = game.getDefenders();
		List<Defender> vulnerableList = defenderList.stream().parallel().filter(Defender::isVulnerable).collect(Collectors.toList());
		List<Defender> aggressiveList = vulnerableList.size() > 0 ? defenderList.stream().parallel().filter(n -> !vulnerableList.contains(n)).collect(Collectors.toList()) : new ArrayList<>(defenderList);
		List<Node> pillList = currentMaze.getPillNodes();
		List<Node> powerPillList = currentMaze.getPowerPillNodes();

		//important variables to judge direction based on attacker and maze specs
		Attacker attacker = game.getAttacker();
		Node attackerLocation = attacker.getLocation();
		int attackerDir = attacker.getDirection();

		//vulnerable and aggressive defender specs
		Defender nearestVulnerableDefender = vulnerableList.size() > 0 ? (Defender)attacker.getTargetActor(vulnerableList, true) : null;
		Node nearestVulnerableLocation = vulnerableList.size() > 0 ? nearestVulnerableDefender.getLocation() : null;
		int nearestVulnerableDist = vulnerableList.size() > 0 ? attackerLocation.getPathDistance(nearestVulnerableLocation) : -1;
		int nearestVulnerableDir = vulnerableList.size() > 0 ? attacker.getNextDir(nearestVulnerableLocation, true) : -1;
		Defender nearestAggressiveDefender = aggressiveList.size() > 0 ? (Defender)attacker.getTargetActor(aggressiveList, true) : null;
		Node nearestAggressiveLocation = aggressiveList.size() > 0 ? nearestAggressiveDefender.getLocation() : null;
		int nearestAggressiveDist = aggressiveList.size() > 0 ? attackerLocation.getPathDistance(nearestAggressiveLocation) : -1;
		int nearestAggressiveDir = aggressiveList.size() > 0 ? attacker.getNextDir(nearestAggressiveLocation, true) : -1;

		//nearest pill specs
		Node nearestPill = pillList.size() > 0 ?
				pillList
						.stream()
						.parallel()
						.reduce(pillList.get(0), (a, b) -> attackerLocation.getPathDistance(b) < attackerLocation.getPathDistance(a) ? b : a)
				: null;
		int nearestPillDist = pillList.size() > 0 ? attackerLocation.getPathDistance(nearestPill) : -1;
		int nearestPillDir = pillList.size() > 0 ? attacker.getNextDir(nearestPill, true) : -1;

		//safe pill specs
		//list of directions that leads to suicide aka goes to a defender
		List<Integer> dangerDir = defenderList
				.stream()
				.parallel()
				.mapToInt(n -> attacker.getNextDir(n.getLocation(), true))
				.boxed()
				.distinct()
				.collect(Collectors.toList());
		//list of pills that does not get attacker near any defender based on planned directions
		List<Node> safePillList = pillList
				.stream()
				.parallel()
				.filter(n -> !dangerDir.contains(attacker.getNextDir(n, true)))
				.collect(Collectors.toList());
		Node nearestSafePillLocation = safePillList.size() > 0 ?
				safePillList
						.stream()
						.parallel()
						.reduce(safePillList.get(0), (a, b) -> attackerLocation.getPathDistance(b) < attackerLocation.getPathDistance(a) ? b : a)
				: null;
		int nearestSafePillDir = nearestSafePillLocation != null ? attacker.getNextDir(nearestSafePillLocation, true) : -1;

		//power pill specs
		Node nearestPowerPillLocation = powerPillList.size() > 0 ?
				powerPillList
					.stream()
					.parallel()
					.reduce(powerPillList.get(0), (a, b) -> attackerLocation.getPathDistance(b) < attackerLocation.getPathDistance(a) ? b : a)
				: null;
		int nearestPowerPillDist = powerPillList.size() > 0 ? attackerLocation.getPathDistance(nearestPowerPillLocation) : -1;
		int nearestPowerPillDir = nearestPowerPillLocation != null ? attacker.getNextDir(nearestPowerPillLocation, true) : -1;

		if (possibleDirs.size() != 0) { //REDO CODE HERE
			if(powerPillList.size() > 0 && vulnerableList.size() == 0) {
				action = nearestPowerPillDir;
				//if nearest aggressive defender is really close (<= 4), then turn to the safest reachable pill, and continue heading towards a power pill of possible
				if (nearestAggressiveDist <= 4)
					action = safePillList.size() > 0 ? nearestSafePillDir : attacker.getNextDir(nearestAggressiveLocation, false);
			}
			//all defenders are vulnerable - just go for quickest kill
			else if(aggressiveList.size() == 0)
				action = nearestVulnerableDir;
			//if going towards closest vulnerable defender also heads towards the closest aggressive defender, scenario then depends on which is closer to attacker
			else if((nearestVulnerableDir == nearestAggressiveDir && nearestVulnerableDist < nearestAggressiveDist)
					|| (nearestVulnerableDir != nearestAggressiveDir && aggressiveList.stream().parallel().map(Actor::getLocation).noneMatch(attacker.getPathTo(nearestVulnerableLocation)::contains)))
				action = nearestVulnerableDir;
		} else if(game.gameOver())
			this.shutdown(game);
		return action;
	}

}