const backendUrl = "http://localhost:18080";

// Fetch and display all students
function fetchStudents() {
    fetch(`${backendUrl}/students`)
        .then(response => response.json())
        .then(data => {
            const tableBody = document.getElementById("table-body");
            tableBody.innerHTML = "";
            data.forEach(student => {
                const row = document.createElement("tr");
                row.innerHTML = `
                    <td>${student.name}</td>
                    <td>${student.balance}</td>
                `;
                tableBody.appendChild(row);
            });
        });
}

// Add new student
document.getElementById("add-student-form").addEventListener("submit", function (event) {
    event.preventDefault();
    const name = document.getElementById("name").value;
    const initialBalance = document.getElementById("initial-balance").value;
    fetch(`${backendUrl}/add`, {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify({ name, balance: parseFloat(initialBalance) }),
    }).then(() => {
        fetchStudents();
    });
});

// Manage student balance
document.getElementById("manage-balance-form").addEventListener("submit", function (event) {
    event.preventDefault();
    const name = document.getElementById("name-balance").value;
    const amount = parseFloat(document.getElementById("amount").value);
    const action = document.getElementById("action").value;

    fetch(`${backendUrl}/${action}`, {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify({ name, amount }),
    }).then(() => {
        fetchStudents();
    });
});

// Get total balance
document.getElementById("get-total").addEventListener("click", function () {
    fetch(`${backendUrl}/total`)
        .then(response => response.json())
        .then(data => {
            document.getElementById("total-saldo").innerText = `Total Saldo: ${data.total}`;
        });
});

// Withdraw all balance
document.getElementById("withdraw-all").addEventListener("click", function () {
    fetch(`${backendUrl}/withdrawAll`, { method: "POST" }).then(() => {
        fetchStudents();
    });
});

// Initial fetch
fetchStudents();
