
function Component()
{
    // default constructor
}

Component.prototype.createOperations = function()
{
    component.createOperations();

    if (systemInfo.productType === "windows") {
        component.addOperation("CreateShortcut", "@TargetDir@/OUT.exe", "@StartMenuDir@/OUT.lnk",
            "workingDirectory=@TargetDir@", "description=An aggregator of university links and resources.");

        component.addOperation("CreateShortcut", "@TargetDir@/OUT.exe", "@DesktopDir@/OUT.lnk",
            "workingDirectory=@TargetDir@", "description=An aggregator of university links and resources.");
    }
}
