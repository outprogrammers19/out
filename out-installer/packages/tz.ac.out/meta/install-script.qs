
function Component()
{
    // default constructor

    // remove old configs and resources if any exists
    component.addOperation("Delete", "@HomeDir@/AppData/Local/OUT/config.ini");
    component.addOperation("Delete", "@HomeDir@/AppData/Local/OUT");
}

Component.prototype.createOperations = function()
{
    component.createOperations();

    // create shortcuts on desktop and in start menu
    if (systemInfo.productType === "windows") {
        component.addOperation("CreateShortcut", "@TargetDir@/OUT.exe", "@StartMenuDir@/OUT.lnk",
            "workingDirectory=@TargetDir@", "description=An aggregator of university links and resources.");

        component.addOperation("CreateShortcut", "@TargetDir@/OUT.exe", "@DesktopDir@/OUT.lnk",
            "workingDirectory=@TargetDir@", "description=An aggregator of university links and resources.");

    }
}
