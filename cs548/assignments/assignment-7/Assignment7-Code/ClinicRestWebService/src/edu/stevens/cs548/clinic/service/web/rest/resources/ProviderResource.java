package edu.stevens.cs548.clinic.service.web.rest.resources;

import java.util.logging.Logger;

import javax.ws.rs.GET;
import javax.ws.rs.Path;
import javax.ws.rs.PathParam;
import javax.ws.rs.Produces;
import javax.ws.rs.QueryParam;
import javax.ws.rs.core.Context;
import javax.ws.rs.core.Response;
import javax.ws.rs.core.UriInfo;

import edu.stevens.cs548.clinic.service.ejb.IProviderServiceLocal;
import edu.stevens.cs548.clinic.service.representations.ProviderRepresentation;
import edu.stevens.cs548.clinic.service.representations.RepresentationFactory;
import edu.stevens.cs548.clinic.service.representations.TreatmentRepresentation;

// TODO
public class ProviderResource {
	
	final static Logger logger = Logger.getLogger(ProviderResource.class.getCanonicalName());
	
    @Context
    private UriInfo uriInfo;
    
    private RepresentationFactory factory = new RepresentationFactory();
    
    /**
     * Default constructor. 
     */
    public ProviderResource() {
    }
    
    // TODO
    private IProviderServiceLocal providerService;
    
    @GET
    @Path("site")
    @Produces("text/plain")
    public String getSiteInfo() {
    	return providerService.siteInfo();
    }

	// TODO complete including annotations
     public Response addProvider(ProviderRepresentation providerRep) {
 		throw new IllegalStateException("Unimplemented addProvider()");
    }
    
	/**
	 * Query methods for provider resources.
	 */
	// TODO complete including annotations
	public ProviderRepresentation getProvider(@PathParam("id") String id) {
		throw new IllegalStateException("Unimplemented getProvider()");
	}
    
	// TODO complete including annotations
	public ProviderRepresentation getProviderByNpi(@QueryParam("npi") String npi) {
		throw new IllegalStateException("Unimplemented getProviderByNPI()");
	}
	
	// TODO complete including annotations
	public Response addTreatment(@PathParam("id") String id, TreatmentRepresentation treatmentRep) {
		throw new IllegalStateException("Unimplemented addTreatment()");
	}
    
	// TODO complete including annotations
    public TreatmentRepresentation getProviderTreatment(@PathParam("id") String id, @PathParam("tid") String tid) {
		throw new IllegalStateException("Unimplemented getProviderTreatment()");
    }

}