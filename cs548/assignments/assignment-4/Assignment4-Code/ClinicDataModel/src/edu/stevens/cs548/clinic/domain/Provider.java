package edu.stevens.cs548.clinic.domain;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;

import javax.persistence.*;

/**
 * Entity implementation class for Entity: Patient
 *
 */
@NamedQueries({
	@NamedQuery(
		name="SearchProviderByNPI",
		query="select p from Provider p where p.npi = :npi"),
	@NamedQuery(
		name="CountProviderByNPI",
		query="select count(p) from Provider p where p.npi = :npi"),
	@NamedQuery(
		name = "RemoveAllPatients", 
		query = "delete from Patient p")
})

@Entity
@Table(name = "PROVIDER")
public class Provider implements Serializable {
	
	private static final long serialVersionUID = 1L;
	
	public static enum ProviderType {
		INTERNIST,
		SURGEON,
		RADIOLOGIST
	};
	
	// TODO JPA annotations
	@Id @GeneratedValue
	private long id;
	
	private long npi;
	
	@Enumerated
	private ProviderType providerType;

	private String name;
	
	public long getId() {
		return id;
	}

	public void setId(long id) {
		this.id = id;
	}

	public long getNpi() {
		return npi;
	}

	public void setNpi(long npi) {
		this.npi = npi;
	}

	public ProviderType getProviderType() {
		return providerType;
	}

	public void setProviderType(ProviderType providerType) {
		this.providerType = providerType;
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	// TODO JPA annotations (propagate deletion of provider to treatments)
	@OneToMany(cascade = CascadeType.ALL, mappedBy = "provider")
	@JoinColumn(name = "PROVIDER_TREATMENT", nullable = true)
	private List<Treatment> treatments;

	protected List<Treatment> getTreatments() {
		return treatments;
	}

	protected void setTreatments(List<Treatment> treatments) {
		this.treatments = treatments;
	}
	
	/*
	 * Addition and deletion of treatments should be done here.
	 */

	public Provider() {
		super();
		/*
		 * TODO initialize lists
		 */
		this.treatments = new ArrayList<Treatment>();
	}
	
	/*
	 * We will add aggregate methods later.
	 */
   
}
