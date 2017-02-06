all:
	@cd common_die && $(MAKE)
	@cd secure_rw && $(MAKE)

clean:
	@cd common_die && $(MAKE) clean
	@cd secure_rw && $(MAKE) clean

cross_build:
	@cd common_die && ./make_target.sh
	@cd secure_rw && ./make_target.sh
