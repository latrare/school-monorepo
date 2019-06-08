package edu.stevens.cs548.clinic.domain;

import java.util.Collection;
import java.util.Date;

import javax.persistence.*;

// TODO
@Entity
@Table(name = "TREATMENT_RADIOLOGY")
public class RadiologyTreatment extends Treatment {

	/**
	 * 
	 */
	private static final long serialVersionUID = -3656673416179492428L;

	// TODO JPA annotation
	@ElementCollection
	@CollectionTable(name = "TREATMENT_DATES")
	@Column(name = "TREATMENT_DATE")
	@Temporal( TemporalType.DATE )
	protected Collection<Date> treatmentDates;

	public Collection<Date> getTreatmentDates() {
		return treatmentDates;
	}

	public void setTreatmentDates(Collection<Date> treatmentDates) {
		this.treatmentDates = treatmentDates;
	}
	
}
