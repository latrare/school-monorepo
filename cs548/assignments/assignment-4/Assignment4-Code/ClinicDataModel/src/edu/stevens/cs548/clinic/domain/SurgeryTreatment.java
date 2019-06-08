package edu.stevens.cs548.clinic.domain;

import java.util.Date;

import javax.persistence.*;

// TODO
@Entity
@Table(name = "TREATMENT_SURGERY")
public class SurgeryTreatment extends Treatment {

	/**
	 * 
	 */
	private static final long serialVersionUID = 4173146640306267418L;
	
	// TODO
	@Temporal( TemporalType.DATE )
	private Date surgeryDate;

	public Date getSurgeryDate() {
		return surgeryDate;
	}

	public void setSurgeryDate(Date surgeryDate) {
		this.surgeryDate = surgeryDate;
	}

}
