var notebookCellList;
var antiPythonCellList = [];
var addCodeCellButton;
var currentPythonCode;
var currentWritingCode;

var codeCellListObserver = new MutationObserver(function(mutations) 
{
    mutations.forEach(function(mutation)
    {
        notebookCellList = mutation.target;
        var currentNotebookCellIdList = [];
        for(var i = 0; i < notebookCellList.children.length; i++)
        {
            currentNotebookCellIdList.push(notebookCellList.children[i].id);
        }
        antiPythonCellList = FindArrayIntersection(currentNotebookCellIdList, antiPythonCellList);
        console.log(antiPythonCellList)
    });
    
});
var codeCellListObserverConfig = { childList: true, subtree:false, characterData: false, attributes: false, attributeOldValue: false, characterDataOldValue: false};


var singleCodeCellObserverConfig = { childList: true, subtree:true, characterData: true, attributes: false, attributeOldValue: false, characterDataOldValue: true};

function GetElementByID(props) {
    new MutationObserver(function(mutations) {
        var element = document.getElementById(props.id);
        if(element)
        {
            this.disconnect();
            props.success(element);
        }
    }).observe(props.parent || document, {
        subtree: !!props.recursive || !props.parent,
        childList: true,
    });
}

function GetElementByClassName(props) {
    new MutationObserver(function(mutations) {
        var element = document.getElementsByClassName(props.className)[0];
        if(element)
        {
            this.disconnect();
            props.success(element);
        }
    }).observe(props.parent || document, {
        subtree: !!props.recursive || !props.parent,
        childList: true,
    });
}

GetElementByID({
    id: 'toolbar-add-code',
    parent: document.querySelector('.notebook-horizontal'),
    recursive: false,
    success: function(element) 
    {
        addCodeCellButton = element;
    }
});

GetElementByID({
    id: 'top-toolbar',
    parent: document.querySelector('.notebook-horizontal'),
    recursive: false,
    success: function(element) 
    {
        AddToToolbar(element);
    }
});

GetElementByID({
    id: 'toolbar-fileforma-custom-cell',
    parent: document.querySelector('.notebook-horizontal'),
    recursive: false,
    success: function(element) 
    {
        element.addEventListener('click', function()
        { 
            AntiPythonButtonClick();
        });
    }
});

GetElementByClassName({
    className: 'notebook-cell-list',
    parent: document.querySelector('.notebook-content'),
    recursive: false,
    success: function(element) 
    {
        notebookCellList = element;
        codeCellListObserver.observe(element, codeCellListObserverConfig);
    }
});


function AddToToolbar(toolbarElement)
{
    //console.log(toolbarElement);
    const myCustomButton = document.createElement('colab-toolbar-button');
    myCustomButton.command = 'Add Fileforma Cell';
    myCustomButton.id = 'toolbar-fileforma-custom-cell';
    myCustomButton.icon = 'icons:add';
    myCustomButton.innerText = '✨ Anti-Python';
    myCustomButton.onclick = AntiPythonButtonClick();
    const textButton = document.getElementById('toolbar-add-text');
    if(textButton)
    {
        textButton.insertAdjacentElement('afterend',myCustomButton);
    }
    else
    {
        console.log("Text not found");
    }
}

function AddPythonToggleButton(currentCell)
{
    //console.log(currentCell.firstChild.nextSibling.firstChild);
    const cellToolbar = currentCell.firstChild.nextSibling.firstChild;
    const myCustomButton = document.createElement('div');
    myCustomButton.role="button";
    myCustomButton.title="Show/Hide Python State";
    myCustomButton.style.height = 'inherit';
    myCustomButton.style.width = '80px';
    myCustomButton.style.display = 'flex';
    myCustomButton.style.fontWeight = 'bold';
    myCustomButton.style.fontSize = '1.2em';
    myCustomButton.style.alignItems="center";
    myCustomButton.style.textAlign="center";
    myCustomButton.style.cursor="pointer";
    myCustomButton.style.justifyContent="center";
    myCustomButton.style.color = "#f5f5f5";
    myCustomButton.style.borderRadius = "3px";
    myCustomButton.style.transform = "all 0.5s";

    myCustomButton.innerText="Show 🐍";
    myCustomButton.addEventListener('mouseover', function()
    {
        myCustomButton.style.border = "solid 1px #8ab4f8";
    });
    
    myCustomButton.addEventListener('mouseout', function()
    {
        myCustomButton.style.border = "none";
    });

    myCustomButton.addEventListener('mousedown', function(event)
    {
        if(event.button === 0)
        {
            myCustomButton.style.color = "#b3b3b3";
            if(myCustomButton.innerText === "Show 🐍")
            {
                myCustomButton.innerText="Hide 🐍";
            }
            else
            {
                myCustomButton.innerText="Show 🐍";
                if(currentPythonCode)
                {
                    currentWritingCode = currentCell.innerText;
                    currentCell.innerText = currentPythonCode;
                }
            }
        }
    });
    
    myCustomButton.addEventListener('mouseup', function(event)
    {
        if(event.button === 0)
        {
            myCustomButton.style.color = "#f5f5f5";
        }
    });


    const myCustomDropdown = document.createElement('div');
    myCustomDropdown.icon="icons:more-vert";
    myCustomDropdown.role="button";
    myCustomDropdown.title="Current Cell Language";
    myCustomDropdown.style.height = 'inherit';
    myCustomDropdown.style.width = '80px';
    myCustomDropdown.style.fontWeight = '100';
    myCustomDropdown.style.display = 'flex';
    myCustomDropdown.style.fontSize = '0.9em';
    myCustomDropdown.style.alignItems="center";
    myCustomDropdown.style.textAlign="center";
    myCustomDropdown.style.justifyContent="center";
    myCustomDropdown.innerText="Java Server";

    if(cellToolbar)
    {
        cellToolbar.style.width = "400px";
        if(cellToolbar.shadowRoot)
        {
            const cellToolbarFirstChild = cellToolbar.shadowRoot.querySelectorAll('paper-icon-button');
            if(cellToolbarFirstChild)
            {
                console.log(cellToolbarFirstChild[cellToolbarFirstChild.length-1])
                cellToolbarFirstChild[cellToolbarFirstChild.length-1].insertAdjacentElement('afterend',myCustomButton);
                myCustomButton.insertAdjacentElement('afterend',myCustomDropdown);
            }
            else
            {
                console.log("cellToolbarLastChild root not found");
            }
        }
        else
        {
            console.log("Shadow root not found");
        }
    }
    else
    {
        console.log("Toolbar not found");
    }
}

function AntiPythonButtonClick(){
    if(addCodeCellButton)
    {
        addCodeCellButton.click();
        if(notebookCellList)
        {
            currentCellID = notebookCellList.children[notebookCellList.children.length-1].id
            antiPythonCellList.push(currentCellID);
            //Add observer
            GetElementByID({
                id: currentCellID,
                parent: document.querySelector(".notebook-cell-list"),
                recursive: true,
                success: function(element) 
                {
                    console.log("Adding python toggle " + currentCellID);
                    AddPythonToggleButton(element)
                    console.log("Adding observer " + currentCellID);
                    new MutationObserver(function(mutations) 
                    {
                        mutations.forEach(function(mutation)
                        {
                            //console.log(currentCellID);
                            //console.log(mutation.target.innerText);
                            
                            chrome.runtime.sendMessage({message: mutation.target.innerText},(response) =>
                            {
                                //console.log(response);
                            })
                        });
                        
                    }).observe(element, singleCodeCellObserverConfig);
                }
            });
        }
        else
        {
            console.log("notebookCellList not available");
        }
    }
    else
    {
        console.log("addCodeCellButton not available");
    }
}

function FindArrayIntersection(arr1, arr2) {
    const intersection = [];
    for (let i = 0; i < arr1.length; i++) {
      const element = arr1[i];
      if (arr2.indexOf(element) !== -1 && intersection.indexOf(element) === -1) {
        intersection.push(element);
      }
    }
    return intersection;
  }
  chrome.runtime.onMessage.addListener((message, sender, sendResponse)=>{
    var codeString = JSON.parse(message);
    if(codeString && codeString['python'])
    {
        //console.log(codeString['python'])
        currentPythonCode = codeString['python'];
    }
    
    return true;
  })
