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
                provider = component "Provider" {
                    description "A collection of interfaces definitions for the Providers which can be used by any Service with no regard to the actual service functionality (e. g. Logger, Display, Storage, etc.)"
                    tags "provider"
                }
                host -> ipc_data_reader "Uses to read API request"
                host -> service "Uses to process API request"
                service -> provider "Uses to access the infrastructure"
                host -> ipc_data_writer "Uses to write API response"
            }

            embedded_service_app = container "Embedded Service Application" {
                description "A user application implementing some valuable logic using the Embedded Service Framework"
                app_service = component "Application Service" {
                    description "A package implementing the service API in a platform-agnostic way. All the low-level deps are represented with abstract interfaces (part of the package API) and are injected on the initialization (construction) step."
                    tags "service"
                }
                app_service_providers = component "Application Service Providers" {
                    description "A collection of interfaces definitions to extend the Framework Providers with application-specific ones (e.g. Sensors, Actuators, etc.)"
                    tags "provider"
                }
                app_service -> app_service_providers "Uses"
                app_service_providers_pl_impl = component "Application Service Providers Platform Implementations" {
                    description "A collection of implementations of the Application Service Providers Interfaces for a specific platform (e.g. STM32, ESP32, Raspberry etc.)"
                    tags "provider"
                }
                app_ipc_reader = component "App-Specific IPC Reader" {
                    description "Implements or instantiates an existing Framework IPC Reader (e.g. UART, Ethernet, etc.)"
                    tags "ipc"
                }
                app_ipc_writer = component "App-Specific IPC Writer" {
                    description "Implements or instantiates an existing Framework IPC Writer (e.g. UART, Ethernet, etc.)"
                    tags "ipc"
                }
                app_service_providers_pl_impl -> app_service_providers "Implements"
                app_main = component "Application Entry Point" {
                    description "The entry point of the application, instantiates the Framework Host with all its dependencies (Service, IPC Reader/Writer) and runs it in a loop"
                    tags "main"
                }
                app_main -> app_service "Instantiates"
                app_main -> app_ipc_reader "Instantiates"
                app_main -> app_ipc_writer "Instantiates"
                app_main -> app_service_providers_pl_impl "Instantiates"
                app_main -> host "Instantiates, runs"
            }
        }
        group "MCU Platform" {
            communication_peripherals = element "Communication Peripherals" {
                description "A hardware peripherals providing IPC communication capabilities (e.g. UART, Ethernet, WiFi, Bluetooth, etc.)"
                tags "mcu_peripheral"
            }
            platform_peripherals = element "Platform Peripherals" {
                description "A hardware peripherals providing all required functionality to carry on the Busyness Logic defined in the Application Service (e.g. GPIOs, Timers, Drivers, etc.)"
                tags "mcu_peripheral"
            }
        }
        app_ipc_reader -> communication_peripherals "Reads from"
        app_ipc_writer -> communication_peripherals "Writes to"
        app_service_providers_pl_impl -> platform_peripherals "Controls"
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
            include * client host
            autolayout tb
        }

        theme default
    }
}