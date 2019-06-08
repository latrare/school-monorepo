package edu.stevens.cs548.clinic.domain;

public class ProviderFactory implements IProviderFactory {

	@Override
	public Provider createProvider(long npi, String name, Provider.ProviderType type) throws IProviderDAO.ProviderExn {
			Provider p = new Provider();
			p.setNpi(npi);
			p.setName(name);
			p.setProviderType(type);
			return p;
	}
	
}
