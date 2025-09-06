workspace "Name" "Description" {

    !identifiers hierarchical

    model {
        client = softwareSystem "Client"
        embedded_service = softwareSystem "Embedded Service" {
            host = container "Host" {
                description "Runs the IPC server and the Service instance"
                ipc_server = component "IPC Server" {
                    description "Maintains the IPC communication channel with the Client."
                }
                service = component "Service" {
                    description "Processes the API request in an infrastructure-agnostic way, all the low-level dependencies are injected on the instantiation step."
                }
                ipc_server -> service "Invokes Service"
            }
        }
        client -> embedded_service.host.ipc_server "Sends API Request"
    }

    views {
        systemContext embedded_service "Embedded_Service" {
            include *
            autolayout lr
        }

        container embedded_service "Embedded_Service_Container" {
            include *
            autolayout lr
        }

        component embedded_service.host "Embedded_Service_Host" {
            include *
            autolayout lr
        }
    }
}