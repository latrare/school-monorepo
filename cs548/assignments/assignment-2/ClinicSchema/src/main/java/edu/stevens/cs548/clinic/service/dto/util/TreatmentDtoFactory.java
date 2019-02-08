package edu.stevens.cs548.clinic.service.dto.util;

import edu.stevens.cs548.clinic.service.dto.ObjectFactory;
import edu.stevens.cs548.clinic.service.dto.TreatmentDto;

public class TreatmentDtoFactory {
	
	ObjectFactory factory;
	
	public TreatmentDtoFactory() {
		factory = new ObjectFactory();
	}
	
	public TreatmentDto createDrugTreatmentDto () {
		return this.factory.createTreatmentDto();
	}
	
	public TreatmentDto createSurgeryTreatmentDto() {
		return this.factory.createTreatmentDto();
	}
	
	public TreatmentDto createRadiologyTreatmentDto() {
		return this.factory.createTreatmentDto();
	}
}
