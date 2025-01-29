#!/bin/sh

echo "CpS 110 Program 1: Tax Calculator, by Jordan Jueckstock (jpjuecks)"
echo

read -p "Enter Taxpayer Name: " TNAME
read -p "Enter Filing Status (S - Single, M - Married, H - Head of Household): " TFS
while true; do
	case "$TFS" in
		S) 
			TDEDUCT=5000
			TFSNAME="Single"
			break
			;;
		M)
			TDEDUCT=8000
			TFSNAME="Married"
			break
			;;
		H)
			TDEDUCT=8000
			TFSNAME="Head of Household"
			break
			;;
		*)
			read -p "Enter Filing Status (S - Single, M - Married, H - Head of Household): " TFS
			;;
	esac
done
read -p "Enter gross income amount: " TGROSS
read -p "Enter number of children: " TKIDS

AGI=$(echo "$TGROSS - $TDEDUCT" | bc)
if [ "$(echo "$AGI < 0" | bc)" = "1" ]; then
	AGI=0
fi

if [ $(echo "$AGI > 20000" | bc) = "1" ]; then
	BASE=$(echo "($AGI - 20000) * 0.2" | bc)
else
	BASE=0
fi

KCRED=$(echo "$TKIDS * 1000" | bc)

TAXOWED=$(echo "$BASE - $KCRED" | bc)
REFUND=0

if [ $(echo "$TAXOWED < 0" | bc) = "1" ]; then
	REFUND=$(echo "- $TAXOWED" | bc)
	TAXOWED=0
fi

echo "Tax for ${TNAME}"
echo "------------------------------------"
echo "Filing status:           ${TFSNAME}"
echo "Children:                ${TKIDS}"
echo
echo "Gross income:            \$${TGROSS}"
echo "Standard deduction:      \$${TDEDUCT}"
echo "                         -----------"
echo "Adjusted Gross Income:   \$${AGI}"
echo
echo "Base Tax:                \$${BASE}"
echo "Child credit:            \$${KCRED}"
echo "                         -----------"
echo "Refund Amount:           \$${REFUND}"
echo "Amount You Owe:          \$${TAXOWED}"
echo
