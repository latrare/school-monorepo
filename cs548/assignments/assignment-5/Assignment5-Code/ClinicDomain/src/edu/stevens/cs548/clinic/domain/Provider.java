package edu.stevens.cs548.clinic.domain;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;

import javax.persistence.CascadeType;
import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.Enumerated;
import javax.persistence.GeneratedValue;
import javax.persistence.Id;
import javax.persistence.JoinColumn;
import javax.persistence.ManyToMany;
import javax.persistence.NamedQueries;
import javax.persistence.NamedQuery;
import javax.persistence.OneToMany;
import javax.persistence.Table;
import javax.persistence.Transient;

import org.eclipse.persistence.annotations.CacheType;

import edu.stevens.cs548.clinic.domain.ITreatmentDAO.TreatmentExn;

/**
 * Entity implementation class for Entity: Patient
 *
 */

@NamedQueries({
	@NamedQuery(name = "SearchProviderByNPI", query = "select p from Provider p where p.npi = :npi"),
	@NamedQuery(name = "CountProviderByNPI", query = "select count(p) from Provider p where p.npi = :npi"),
	@NamedQuery(name = "RemoveAllPatients", query = "delete from Patient p") })

@Entity
@Table(name = "provider")
public class Provider implements Serializable {

    private static final long serialVersionUID = 1L;

    public static enum ProviderType {
	INTERNIST, SURGEON, RADIOLOGIST
    };

    // TODO JPA annotations
    @Id
    @GeneratedValue
    @Column(name = "id")
    private long id;

    @Column(name = "npi")
    private long npi;

    // TODO JPA annotationa
    @Enumerated
    @Column(name = "provider_type")
    private ProviderType providerType;

    @Column(name = "name")
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
    @ManyToMany(cascade = CascadeType.ALL, targetEntity = Treatment.class)
    @JoinColumn(referencedColumnName = "id")
    private List<Treatment> treatments;

    protected List<Treatment> getTreatments() {
	return treatments;
    }

    protected void setTreatments(List<Treatment> treatments) {
	this.treatments = treatments;
    }

    // TODO JPA annotation
    @Transient
    private ITreatmentDAO treatmentDAO;

    public void setTreatmentDAO(ITreatmentDAO tdao) {
	this.treatmentDAO = tdao;
    }

    public Provider() {
	super();
	treatments = new ArrayList<Treatment>();
    }

    /*
     * Addition and deletion of treatments should be done here.
     */

    public long addTreatment(Patient p, Treatment t) {
	/*
	 * TODO complete this operation (see patient entity)
	 */
	t.setProvider(p, this);
	return t.getId();
    }

    public void getTreatmentIds(List<Long> treatmentIds) {
	for (Treatment t : this.getTreatments()) {
	    treatmentIds.add(t.getId());
	}
    }

    public <T> T exportTreatment(long tid, ITreatmentExporter<T> visitor)
	    throws TreatmentExn {
	/*
	 * TODO complete this operation (see patient entity)
	 */
	// Export a treatment without violating Aggregate pattern
	// Check that the exported treatment is a treatment for this patient.
	Treatment t = treatmentDAO.getTreatment(tid);
	if (t.getProvider() != this) {
	    throw new TreatmentExn("Inappropriate treatment access: provider = " + id + ", treatment = " + tid);
	}
	return t.export(visitor);
    }

}
