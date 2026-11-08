# CO2 Calculator

## Features

### Transport Emissions
Estimate CO₂ emissions from travel by car, bus, train, or flight.

### Electricity Emissions
Estimate CO₂ emissions from household or grid electricity usage.

### Book Printing Estimate
Estimate the approximate CO₂ impact of printing a book based on its number of pages.

This feature can also be used alongside the Book Manager project.

## Emission Factors Used

| Activity | Factor | Notes |
|---|---|---|
| Car (petrol) | 0.20 kg CO₂e / km | Average passenger car |
| Bus | 0.10 kg CO₂e / km | Shared public transport |
| Train | 0.04 kg CO₂e / km | Electric/rail average |
| Flight | 0.25 kg CO₂e / km | Short-to-medium haul average |
| Electricity | 0.40 kg CO₂e / kWh | Varies significantly by country |
| Book printing | ~0.0007 kg / page | Rough paper + printing estimate |

## How to Run the Program

1. Open the project folder in Visual Studio Code.
2. Open the terminal.
3. Run the following command:

`python .\CO2_Calculator.py`

4. Select an option from the menu.
5. Enter the requested information.
6. View the estimated CO₂ emissions.

## Important Note

All emission factors are approximate and intended for educational and demonstration purposes only.Contains the CO2 calculator challenge
