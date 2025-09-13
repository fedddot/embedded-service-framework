workspace "Embedded Service Framework" {
    model {
        client = person "Client"
        embedded_service = softwareSystem "Embedded Service" {
            embedded_service_framework = container "Embedded Service Framework" {
                description "A collection of components providing tools for simple and fast creation of platform-independent embedded services"
                host = component "Host" {
                    description "Aggregates the references of a Service and IPC Reader/Writer. Facades the IPC communication and service invocation into an event loop embeddable structure: provides a run_once() method performing: 1. Reading from IPC channel, 2. Invoking the service, 3. Writing into the IPC channel."
                    tags "host"
                }
                ipc_data_reader = component "IPC Data Reader" {
                    description "Reads an API request from the IPC channel if received, deserializes it and returns to the caller."
                    tags "ipc"
                }
                ipc_data_writer = component "IPC Data Writer" {
                    description "Serializes the API response and writes it to the IPC channel."
                    tags "ipc"
                }
                service = component "Service" {
                    description "Processes the API request in an infrastructure-agnostic way, all the low-level dependencies are injected on the instantiation step."
                    tags "service"
                }
                host -> ipc_data_reader "Uses to read API request"
                host -> service "Uses to process API request"
                host -> ipc_data_writer "Uses to write API response"
            }


            embedded_service_app = container "Embedded Service Application" {
                description "A user application implementing some valuable logic using the Embedded Service Framework"
                group "Service" {
                    app_service = component "Application Service" {
                        description "A package implementing the service API in a platform-agnostic way. All the low-level deps are represented with abstract interfaces (part of the package API) and are injected on the initialization (construction) step."
                        tags "service"
                    }
                    app_service_providers_interfaces = component "Application Service Providers Interfaces" {
                        description "A collection of interfaces definitions to abstract-out all the low-level infrastructures required by the Application Service (e.g. TempController, MotorDriver, etc.)"
                        tags "providers"
                    }
                }
                group "App Infrastructure" {
                    app_service_providers = component "Application Service Providers" {
                        description "A collection of interfaces injected into the Application Service on the instantiation step, providing all the required low-level functionality abstractions (e.g. GPIOs, Timers, Drivers, etc.)"
                        tags "providers"
                    }
                    app_ipc_reader = component "App-Specific IPC Reader" {
                        description "Implements or instantiates an existing Framework IPC Reader"
                        tags "ipc"
                    }
                    app_ipc_writer = component "Example IPC Writer" {
                        description "Implements or instantiates an existing Framework IPC Writer"
                        tags "ipc"
                    }
                }
                app_main = component "Application Entry Point" {
                    description "The entry point of the application, instantiates the Framework Host with the application-specific components and runs the event loop"
                }
                app_main -> app_service "Instantiates"
                app_service -> app_service_providers "Uses"
                app_main -> app_ipc_reader "Instantiates"
                app_main -> app_ipc_writer "Instantiates"
            }
        }
        communication_peripherals = element "Communication Peripherals" {
            description "A hardware peripherals providing IPC communication capabilities (e.g. UART, Ethernet, WiFi, Bluetooth, etc.)"
            tags "mcu_peripheral"
        }
        platform_peripherals = element "Platform Peripherals" {
            description "A hardware peripherals providing all required functionality to carry on the Busyness Logic defined in the Application Service (e.g. GPIOs, Timers, Drivers, etc.)"
            tags "mcu_peripheral"
        }
        app_main -> host "Instantiates, runs"
        app_ipc_reader -> communication_peripherals "Reads from"
        app_ipc_writer -> communication_peripherals "Writes to"
        app_service_providers -> platform_peripherals "Abstracts"
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