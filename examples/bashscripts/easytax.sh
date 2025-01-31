#!/bin/sh
# POSIX-shell implementation of the classic "easy tax" program from CpS 110
# (c) 2025, BJU
# demonstrates: echo, read, if/then/else/fi, case/esac, while/do/done, shell functions, use of the `bc` calculator tool

# $1: floating point expression string
# output: bc-calculated result (use with $(...) to capture value)
# status: 0 (succeed-always)
float_calc () {
	local EXPR="$1"
	echo "$EXPR" | bc
}

# $1: floating point comparison expression
# output: none
# status: 0 if bc evaluates the expression to a "1"; non-success otherwise
float_cmp () {
	local CMP="$1"
	local RESULT=$(echo "$CMP" | bc)
	test "$RESULT" = "1"
}

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

AGI=$(float_calc "$TGROSS - $TDEDUCT")
if float_cmp "$AGI < 0"; then
	AGI=0
fi

if float_cmp "$AGI > 20000"; then
	BASE=$(float_calc "($AGI - 20000) * 0.2")
else
	BASE=0
fi

KCRED=$(float_calc "$TKIDS * 1000")

TAXOWED=$(float_calc "$BASE - $KCRED")
REFUND=0

if float_cmp "$TAXOWED < 0"; then
	REFUND=$(float_calc "- $TAXOWED")
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
