include ./Makefile.include 

all: bullet-test
	@echo DONE

bullet-test: bullet-test.o
	$(CXX) -o $@ $^ $(OSG_LIBS) -lbulletdynamics -lbulletcollision -lLinearMath -L/usr/local/include/BulletCollision 


