package edu.stevens.cs548.clinic.service.dto.util;

import edu.stevens.cs548.clinic.domain.Provider;
import edu.stevens.cs548.clinic.domain.Provider.ProviderType;
import edu.stevens.cs548.clinic.service.dto.ObjectFactory;
import edu.stevens.cs548.clinic.service.dto.ProviderDto;
import edu.stevens.cs548.clinic.service.dto.ProviderSpecType;

public class ProviderDtoFactory {
	
	ObjectFactory factory;
	
	public ProviderDtoFactory() {
		factory = new ObjectFactory();
	}
	
	public ProviderDto createProviderDto () {
		return factory.createProviderDto();
	}
	
	public ProviderDto createProviderDto (Provider p) {
		ProviderDto d = factory.createProviderDto();
		/*
		 * TODO: Initialize the fields of the DTO.
		 */
		throw new IllegalStateException("ProviderDtoFactory");
	}
	
	public static ProviderSpecType getSpecType(ProviderType providerType) {
		switch (providerType) {
		case INTERNIST:
			return ProviderSpecType.INTERNAL;
		case RADIOLOGIST:
			return ProviderSpecType.RADIOLOGY;
		case SURGEON:
			return ProviderSpecType.SURGERY;
		default:
			throw new IllegalStateException("Unrecognized provider type: "+providerType);
		}
	}

}
