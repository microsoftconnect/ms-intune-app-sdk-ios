// swift-tools-version:5.9
import PackageDescription

let package = Package(
    name: "IntuneMAM",
    platforms: [
        .iOS(.v17)
    ],
    products: [
        .library(name: "IntuneMAMSwift",
                 targets: ["IntuneMAMSwift", "IntuneMAMSwiftStub"]),
        .library(name: "IntuneMAMStatic",
                 targets: ["IntuneMAMStatic", "IntuneMAMSwiftStub"]),
        .library(name: "IntuneMAMTelemetry",
                 targets: ["IntuneMAMTelemetry"]),
        .library(name: "libIntuneMAMSwiftFileProvider",
                 targets: ["libIntuneMAMSwiftFileProvider", "IntuneMAMSwiftStub"])
    ],
    targets: [
        // Local Binary Packages
        .binaryTarget(name: "IntuneMAMSwiftStub",
                      path: "./IntuneMAMSwiftStub.xcframework"
                     ),
        .binaryTarget(name: "IntuneMAMSwift",
                      path: "./IntuneMAMSwift.xcframework"
                     ),
        .binaryTarget(name: "IntuneMAMStatic",
                      path: "./IntuneMAMStatic.xcframework"
                     ),
        .binaryTarget(name: "IntuneMAMTelemetry",
                      path: "./IntuneMAMTelemetry.xcframework"
                     ),
        .binaryTarget(name: "libIntuneMAMSwiftFileProvider",
                      path: "./libIntuneMAMSwiftFileProvider.xcframework"
                     )
    ]
)