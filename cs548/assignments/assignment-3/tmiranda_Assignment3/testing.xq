(: Trevor Miranda :)

import schema namespace tns = "http://cs548.stevens.edu/clinic/db" at "Assignment3-Xquery.xsd";

declare function local:getProviderInfo ($database as element(tns:clinic)) {
    for $provider in distinct-values($database/patient/treatment/provider/npi) return
        for $patient in $database/patient[treatment/provider[npi=$provider]] return
            <patient>
                <patient-id>{ $patient/patient-id/text() }</patient-id>
                <name>{ $patient/name/text() }</name>
                {
                    for $treatment in $patient/treatment[provider[npi=$provider]] return
                        <treatment>
                            <drug>
                                { $treatment/drug/text() }
                            </drug>
                            <provider>
                                <npi>
                                    { $treatment/provider/npi/text() }
                                </npi>
                                <name>
                                    { $treatment/provider/name/text() }
                                </name>
                            </provider>
                        </treatment>
                }
            </patient>
};

let $database := doc("instance1.xml")/tns:clinic

return local:getProviderInfo($database)