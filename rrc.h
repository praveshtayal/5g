enum rrc_scs {
    scs15khz,
    scs30khz,
    scs60khz,
    scs120khz,
    scs240khz,
    scs480khz
};

enum rrc_sl {
    rrc_sl5,
    rrc_sl10,
    rrc_sl20,
    rrc_sl40,
    rrc_sl80,
    rrc_sl160,
    rrc_sl320,
    rrc_sl640,
    rrc_sl1280,
};

enum rrc_rf {
    rrc_rf8,
    rrc_rf16,
    rrc_rf32,
    rrc_rf64,
    rrc_rf128,
    rrc_rf256,
    rrc_rf512,
};

int slot(enum rrc_sl sl);
int radioframe(enum rrc_rf rf);
rrc_sl slots_in_frame(rrc_scs scs);
