workspace "Embedded Service Framework" {
    model {
        client = person "Client"
        embedded_service = softwareSystem "Embedded Service" {
            embedded_service_framework = container "Embedded Service Framework" {
                description "A collection of components providing tools for simple and fast creation of platform-independent embedded services"
                host = component "Host" {
                    description "Aggregates the references of a Service and IPC Reader/Writer. Facades the IPC communication and service invocation into an event loop embeddable structure: provides a run_once() method performing:\n1. Reading from IPC channel,\n2. Invoking the service,\n3. Writing to IPC channel."
                }
                ipc_data_reader = component "IPC Data Reader" {
                    description "Reads an API request from the IPC channel if received, deserializes it and returns to the caller."
                }
                ipc_data_writer = component "IPC Data Writer" {
                    description "Serializes the API response and writes it to the IPC channel."
                }
                service = component "Service" {
                    description "Processes the API request in an infrastructure-agnostic way, all the low-level dependencies are injected on the instantiation step."
                }
                host -> ipc_data_reader "Uses to read API request"
                host -> service "Uses to process API request"
                host -> ipc_data_writer "Uses to write API response"
            }

            embedded_service_app = container "Embedded Service Application" {
                description "A user application implementing some valuable logic using the Embedded Service Framework"
                app_service = component "Application Service" {
                    description "Implements the business logic of the application in an infrastructure-agnostic way"
                }
                app_ipc_reader = component "App-Specific IPC Reader" {
                    description "Implements or instantiates an existing Framework IPC Reader"
                }
                app_ipc_writer = component "Example IPC Writer" {
                    description "Implements or instantiates an existing Framework IPC Writer"
                }
                app_main = component "Application Entry Point" {
                    description "The entry point of the application, instantiates the Framework Host with the application-specific components and runs the event loop"
                }
                app_main -> app_service "Instantiates"
                app_main -> app_ipc_reader "Instantiates"
                app_main -> app_ipc_writer "Instantiates"
            }
        }
        communication_peripherals = element "Communication Peripherals" {
            description "A hardware peripheral providing IPC communication capabilities (e.g. UART, Ethernet, WiFi, Bluetooth, etc.)"
            tags "mcu_peripheral"
        }
        app_main -> host "Instantiates, runs"
        app_ipc_reader -> communication_peripherals "Reads from"
        app_ipc_writer -> communication_peripherals "Writes to"
        client -> communication_peripherals "Communicates with"
    }

    views {
        systemContext embedded_service "Embedded_Service_Software" {
            include * communication_peripherals client
            autolayout tb
        }

        container embedded_service "Embedded_Service_Containers" {
            include * communication_peripherals client
            autolayout tb
        }

        component embedded_service_framework "Embedded_Service_Framework_Components" {
            include *
            autolayout tb
        }

        component embedded_service_app "Embedded_Service_App_Components" {
            include * client
            autolayout tb
        }

        theme default
    }
}