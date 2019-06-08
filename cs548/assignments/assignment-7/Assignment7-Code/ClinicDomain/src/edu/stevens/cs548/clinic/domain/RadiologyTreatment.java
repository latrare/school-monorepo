package edu.stevens.cs548.clinic.domain;

import java.util.Date;
import java.util.List;

import javax.persistence.Column;
import javax.persistence.DiscriminatorValue;
import javax.persistence.ElementCollection;
import javax.persistence.Entity;
import javax.persistence.Table;
import javax.persistence.Temporal;
import javax.persistence.TemporalType;

import edu.stevens.cs548.clinic.domain.*;

@Entity
@Table(name = "radiology_treatment")
public class RadiologyTreatment extends Treatment {

    /**
     * 
     */
    private static final long serialVersionUID = -3656673416179492428L;

    // TODO JPA annotation
    @ElementCollection
    @Temporal(TemporalType.DATE)
    @Column(name = "treatment_dates")
    protected List<Date> treatmentDates;

    public List<Date> getTreatmentDates() {
	return treatmentDates;
    }

    public void setTreatmentDates(List<Date> treatmentDates) {
	this.treatmentDates = treatmentDates;
    }

    @Override
    public <T> T export(ITreatmentExporter<T> visitor) {
	return visitor.exportRadiology(this.getId(), this.getPatient().getId(),
		this.getProvider().getId(), this.getDiagnosis(),
		this.getTreatmentDates());
    }

}
