#Ryan Blankemeier
#Lab 3
#Monte Carlo structure prediction version 3 (starting with native)
import random
import math
from rosetta import *

init()

tz = pose_from_pdb('1le0_m1.pdb')
tz.pdb_info().name('1le0_sim')

le = pose_from_pdb('1le0_m1.pdb')

scorer = create_score_function('score3')
currentScore = scorer(tz)

temp = Pose()
temp.assign(tz)




bestScore = scorer(le)
bestPose = Pose()



kT = 1
count = 0
l = 100000

file1 = open('rmsd_output3', 'w')
file1.write("RMSD between current and native structures\nrmsd \t\tscore\n")

for i in range(l):
    
    num =random.randrange(1, 13)

    temp.set_phi(num,temp.phi(num)+random.randrange(-10,11))
    temp.set_psi(num,temp.psi(num)+random.randrange(-10,11))
    tempScore = scorer(temp)

    if ((tempScore < currentScore) or (random.random() < math.exp(-(tempScore - currentScore)/kT))):
        currentScore = tempScore
        tz.assign(temp)
        kT = kT/1.05
        count += 1

    else:
        temp.assign(tz)
        kT = kT * 1.01

    if (currentScore < bestScore):
        bestScore = currentScore
        bestPose.assign(temp)

    if (count == 100): 
      count = 0
      distance = CA_rmsd(le, tz) 
      file1.write(str(distance))
      file1.write(" ")
      file1.write(str(currentScore))
      file1.write("\n")


print "best score: %f" %scorer(bestPose)
print "Last RMSD: %f" %CA_rmsd(le, bestPose)

distance = CA_rmsd(le, bestPose) 
file1.write(str(distance))
file1.write(" ")
file1.write(str(scorer(bestPose)))
file1.write("\n")


dump_pdb(bestPose, 'output3.pdb')
