#!/usr/bin/env python
# -*- coding: utf-8 -*-
# Eclipse SUMO, Simulation of Urban MObility; see https://eclipse.org/sumo
# Copyright (C) 2008-2018 German Aerospace Center (DLR) and others.
# This program and the accompanying materials
# are made available under the terms of the Eclipse Public License v2.0
# which accompanies this distribution, and is available at
# http://www.eclipse.org/legal/epl-v20.html
# SPDX-License-Identifier: EPL-2.0

# @file    runner.py
# @author  Michael Behrisch
# @author  Jakob Erdmann
# @author  Daniel Krajzewicz
# @date    2011-03-04
# @version $Id$

import os
import sys
import time

SUMO_HOME = os.path.join(os.path.dirname(__file__), "..", "..", "..", "..", "..")
sys.path.append(os.path.join(os.environ.get("SUMO_HOME", SUMO_HOME), "tools"))
if len(sys.argv) > 1:
    import libsumo as traci  # noqa
    traci.vehicle.addFull = traci.vehicle.add
    traci.vehicle.add = traci.vehicle.addLegacy
else:
    import traci  # noqa
    import traci.constants as tc
    traci._vehicle.VehicleDomain.addFull = traci._vehicle.VehicleDomain.add
    traci._vehicle.VehicleDomain.add = traci._vehicle.VehicleDomain.addLegacy
import sumolib  # noqa

def step():
    s = traci.simulation.getTime()
    traci.simulationStep()
    return s

def check(vehID):
    print("vehicles", traci.vehicle.getIDList())
    print("vehicle count", traci.vehicle.getIDCount())
    print("examining", vehID)
    print("speed", traci.vehicle.getSpeed(vehID))
    print("speed w/o traci", traci.vehicle.getSpeedWithoutTraCI(vehID))
    print("acceleration", traci.vehicle.getAcceleration(vehID))
    print("pos", traci.vehicle.getPosition(vehID))
    print("angle", traci.vehicle.getAngle(vehID))
    print("road", traci.vehicle.getRoadID(vehID))
    print("lane", traci.vehicle.getLaneID(vehID))
    print("laneIndex", traci.vehicle.getLaneIndex(vehID))
    print("type", traci.vehicle.getTypeID(vehID))
    print("routeID", traci.vehicle.getRouteID(vehID))
    print("routeIndex", traci.vehicle.getRouteIndex(vehID))
    print("route", traci.vehicle.getRoute(vehID))
    print("lanePos", traci.vehicle.getLanePosition(vehID))
    print("color", traci.vehicle.getColor(vehID))
    print("bestLanes", traci.vehicle.getBestLanes(vehID))
    print("CO2", traci.vehicle.getCO2Emission(vehID))
    print("CO", traci.vehicle.getCOEmission(vehID))
    print("HC", traci.vehicle.getHCEmission(vehID))
    print("PMx", traci.vehicle.getPMxEmission(vehID))
    print("NOx", traci.vehicle.getNOxEmission(vehID))
    print("fuel", traci.vehicle.getFuelConsumption(vehID))
    print("noise", traci.vehicle.getNoiseEmission(vehID))
    print("Elec", traci.vehicle.getElectricityConsumption(vehID))
    print("traveltime", traci.vehicle.getAdaptedTraveltime(vehID, 0, "1to2"))
    print("effort", traci.vehicle.getEffort(vehID, 0, "1to2"))
    print("route valid", traci.vehicle.isRouteValid(vehID))
    print("signals", traci.vehicle.getSignals(vehID))
    print("routingMode", traci.vehicle.getRoutingMode(vehID))
    print("length", traci.vehicle.getLength(vehID))
    print("maxSpeed", traci.vehicle.getMaxSpeed(vehID))
    print("speedFactor", traci.vehicle.getSpeedFactor(vehID))
    print("allowedSpeed", traci.vehicle.getAllowedSpeed(vehID))
    print("accel", traci.vehicle.getAccel(vehID))
    print("decel", traci.vehicle.getDecel(vehID))
    print("emergencyDecel", traci.vehicle.getEmergencyDecel(vehID))
    print("apparentDecel", traci.vehicle.getApparentDecel(vehID))
    print("actionStepLength", traci.vehicle.getActionStepLength(vehID))
    print("lastActionTime", traci.vehicle.getLastActionTime(vehID))
    print("imperfection", traci.vehicle.getImperfection(vehID))
    print("tau", traci.vehicle.getTau(vehID))
    print("vClass", traci.vehicle.getVehicleClass(vehID))
    print("emissionclass", traci.vehicle.getEmissionClass(vehID))
    print("shape", traci.vehicle.getShapeClass(vehID))
    print("MinGap", traci.vehicle.getMinGap(vehID))
    print("width", traci.vehicle.getWidth(vehID))
    print("height", traci.vehicle.getHeight(vehID))
    print("lcStrategic", traci.vehicle.getParameter(vehID, "laneChangeModel.lcStrategic"))
    print("lcCooperative", traci.vehicle.getParameter(vehID, "laneChangeModel.lcCooperative"))
    print("lcSpeedGain", traci.vehicle.getParameter(vehID, "laneChangeModel.lcSpeedGain"))
    print("maxSpeedLat", traci.vehicle.getMaxSpeedLat(vehID))
    print("minGapLat", traci.vehicle.getMinGapLat(vehID))
    print("lateralAlignment", traci.vehicle.getLateralAlignment(vehID))
    print("lanePosLat", traci.vehicle.getLateralLanePosition(vehID))
    print("person number", traci.vehicle.getPersonNumber(vehID))
    print("waiting time", traci.vehicle.getWaitingTime(vehID))
    print("accumulated waiting time", traci.vehicle.getAccumulatedWaitingTime(vehID))
    print("driving dist", traci.vehicle.getDrivingDistance(vehID, "4fi", 2.))
    print("driving dist 2D", traci.vehicle.getDrivingDistance2D(vehID, 100., 100.))
    print("line", traci.vehicle.getLine(vehID))
    print("via", traci.vehicle.getVia(vehID))
    print("lane change state right", traci.vehicle.getLaneChangeState(vehID, -1))
    print("lane change state left", traci.vehicle.getLaneChangeState(vehID, 1))
    print("lane change able right", traci.vehicle.couldChangeLane(vehID, -1))
    print("lane change able left", traci.vehicle.couldChangeLane(vehID, 1))
    print("lane change wish right", traci.vehicle.wantsAndCouldChangeLane(vehID, -1))
    print("lane change wish left", traci.vehicle.wantsAndCouldChangeLane(vehID, 1))


def checkOffRoad(vehID):
    print(("veh", vehID,
           "speed", traci.vehicle.getSpeed(vehID),
           "pos", traci.vehicle.getPosition(vehID),
           "pos3d", traci.vehicle.getPosition3D(vehID),
           "angle", traci.vehicle.getAngle(vehID),
           "road", traci.vehicle.getRoadID(vehID),
           "lane", traci.vehicle.getLaneID(vehID),
           "lanePos", traci.vehicle.getLanePosition(vehID),
           "CO2", traci.vehicle.getCO2Emission(vehID)
           ))

traci = traci.connect(1337,10)
traci.setOrder(2)
print("\nSleeping temporarily")
time.sleep(5)

vehID = "SmartAlec"

testObject = traci.vehicle.moveToXY(vehID, edgeID="1to2", lane=0, x=0, y=-2, angle=90, keepRoute=2)

print("\n\nTesting moving the vehicle to arbitrary position\n\n")

i = 0
while(traci.simulation.getTime() != 10):
    testObject = traci.vehicle.moveToXY(vehID, edgeID="1to2", lane=0, x=i, y=-2, angle=90, keepRoute=2)
    i += 0.5
    step()

traci.close()