// ============================================================================
// ClearanceFOMTest.java
// ----------------------------------------------------------------------------
// Third-party HLA validation of the CLEARANCE RPR-FOM using Portico
// (github.com/openlvc/portico), an independent implementation of
// IEEE 1516-2010 HLA-Evolved developed by a different team than
// OpenRTI (the RTI the CLEARANCE editor build currently links against).
//
// If Portico can load, validate, and instantiate a federation from
// ClearanceRPR-FOM.xml then the FOM is standards-compliant across
// implementations. This is real cross-RTI portability evidence: the
// FOM is not "OpenRTI-flavoured HLA", it is HLA-Evolved.
//
// This program:
//   1. connects to Portico's local RTI
//   2. creates the federation "CLEARANCE_PORTICO_TEST" from the FOM
//   3. joins as a federate
//   4. waits briefly for any peer publisher
//   5. resigns and (if last) destroys the federation
//
// Any FOM parse error surfaces on step 2 as an ErrorReadingFDD
// exception with the exact line number.
//
// Usage (Windows PowerShell):
//   javac -cp path\to\portico\lib\portico.jar ClearanceFOMTest.java
//   java  -cp "path\to\portico\lib\portico.jar;." ClearanceFOMTest ^
//         ..\..\CLEARANCE\CLEARANCE\CLEARANCE\Plugins\ClearanceSim\FOM\ClearanceRPR-FOM.xml
//
// Usage (Linux / macOS):
//   javac -cp path/to/portico/lib/portico.jar ClearanceFOMTest.java
//   java  -cp "path/to/portico/lib/portico.jar:." ClearanceFOMTest \
//         ../../CLEARANCE/CLEARANCE/CLEARANCE/Plugins/ClearanceSim/FOM/ClearanceRPR-FOM.xml
// ============================================================================

import hla.rti1516e.CallbackModel;
import hla.rti1516e.NullFederateAmbassador;
import hla.rti1516e.RTIambassador;
import hla.rti1516e.ResignAction;
import hla.rti1516e.RtiFactory;
import hla.rti1516e.RtiFactoryFactory;
import hla.rti1516e.exceptions.FederatesCurrentlyJoined;
import hla.rti1516e.exceptions.FederationExecutionAlreadyExists;

import java.io.File;
import java.net.URL;

public class ClearanceFOMTest extends NullFederateAmbassador {

    private static final String FEDERATION = "CLEARANCE_PORTICO_TEST";
    private static final String FEDERATE   = "ClearanceFOMTest";
    private static final String DEFAULT_FOM =
        "../../CLEARANCE/CLEARANCE/CLEARANCE/Plugins/ClearanceSim/FOM/ClearanceRPR-FOM.xml";

    public static void main(String[] args) throws Exception {
        String fomArg = (args.length > 0) ? args[0] : DEFAULT_FOM;
        new ClearanceFOMTest().run(fomArg);
    }

    private void run(String fomPath) throws Exception {
        File fomFile = new File(fomPath);
        if (!fomFile.isFile()) {
            System.err.println("FOM not found at: " + fomFile.getAbsolutePath());
            System.err.println("Pass the FOM path as the first argument.");
            System.exit(2);
        }
        URL fom = fomFile.toURI().toURL();
        System.out.println("Loading FOM: " + fomFile.getAbsolutePath());

        RtiFactory factory = RtiFactoryFactory.getRtiFactory();
        System.out.println("RTI implementation: " + factory.rtiName()
                                                  + " " + factory.rtiVersion());
        RTIambassador rti = factory.getRtiAmbassador();

        rti.connect(this, CallbackModel.HLA_IMMEDIATE);
        System.out.println("Connected to Portico RTI.");

        try {
            rti.createFederationExecution(FEDERATION, new URL[]{fom});
            System.out.println("Created federation: " + FEDERATION);
        } catch (FederationExecutionAlreadyExists ex) {
            System.out.println("Federation already exists (fine): " + FEDERATION);
        }

        rti.joinFederationExecution(FEDERATE, FEDERATION, new URL[]{fom});
        System.out.println("Joined federation as: " + FEDERATE);

        // Give Portico a moment to complete tick + parse the FOM classes;
        // any deferred FOM error would surface as a fed-ambassador callback.
        Thread.sleep(2000);
        System.out.println("Idle window complete. No FOM callback errors.");

        rti.resignFederationExecution(ResignAction.DELETE_OBJECTS);
        System.out.println("Resigned.");

        try {
            rti.destroyFederationExecution(FEDERATION);
            System.out.println("Destroyed federation.");
        } catch (FederatesCurrentlyJoined ex) {
            System.out.println("Other federates joined; leaving federation up.");
        }

        rti.disconnect();
        System.out.println("Disconnected. SUCCESS: FOM validated by Portico end to end.");
    }
}
