include ./Makefile.include 

BULLET_LIBS=-lbulletdynamics -lbulletcollision -lLinearMath -L/usr/local/include/bullet/BulletCollision

%.o: %.cpp
	@echo "--------------- compiling $@ ---------------" 
	$(CXX) $(OSG_INCLUDE) $(SPIN_FLAGS) $(SPIN_INCLUDE) $(BOOST_INCLUDE) -c $< -o $@

all: bullet-test
	@echo DONE

bullet-test: bullet-test.o
	$(CXX) -o $@ $^ $(BULLET_LIBS) $(OSG_LIBS) 


bully: bullet-test.o
	$(CXX) -o bully bullet-test.cpp $(BULLET_LIBS) $(OSG_LIBS) 



