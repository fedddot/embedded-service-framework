workspace "Embedded Service Framework" {
    model {
        client = softwareSystem "Client"
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
        }
    }

    views {
        systemContext embedded_service "Embedded_Service" {
            include *
            autolayout lr
        }

        component embedded_service_framework "Embedded_Service_Framework" {
            include *
            autolayout lr
        }
    }
}