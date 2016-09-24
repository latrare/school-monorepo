import java.util.concurrent.ThreadLocalRandom;

public enum ApparatusType {
	LEGPRESSMACHINE, BARBELL, HACKSQUATMACHINE, LEGEXTENSIONMACHINE,
	LEGCURLMACHINE, LATPULLDOWNMACHINE, PECDECKMACHINE, CABLECROSSOVERMACHINE;

	// Return a randomly chosen ApparatusType enum value
	public static ApparatusType getRandom() {
		int chosen = ThreadLocalRandom.current().nextInt(
				ApparatusType.class.getEnumConstants().length);
		
		return ApparatusType.class.getEnumConstants()[chosen];
	}
}
