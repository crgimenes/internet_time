#!/bin/bash

# Internet Time Examples and Testing Script
# Demonstrates various features of the Internet Time calculator

# ANSI color codes
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
BLUE='\033[0;34m'
MAGENTA='\033[0;35m'
CYAN='\033[0;36m'
WHITE='\033[0;37m'
BOLD='\033[1m'
NC='\033[0m' # No Color

echo -e "${BOLD}${CYAN}Swatch Internet Time Calculator - Demo Script${NC}"
echo -e "${CYAN}=================================================${NC}"
echo

# Basic usage
echo -e "${BOLD}${GREEN}Basic Usage:${NC}"
echo "Current Internet Time:"
./internet_time
echo

# Timezone examples
echo -e "${BOLD}${BLUE}Timezone Examples:${NC}"
echo -e "${YELLOW}New York (UTC-5):${NC}"
./internet_time -t -5

echo -e "${YELLOW}Tokyo (UTC+9):${NC}"
./internet_time -t 9

echo -e "${YELLOW}London (UTC+0):${NC}"
./internet_time -t 0
echo

# Format examples
echo -e "${BOLD}${MAGENTA}Format Examples:${NC}"
echo -en "${WHITE}Integer beats:${NC}"
./internet_time -f "@%04.0f"

echo -en "\n${WHITE}High precision:${NC}"
./internet_time -f "@%.3f"

echo -en "\n${WHITE}Clean number:${NC}"
./internet_time -f "%.0f"
echo

# Beat conversion
echo -e "${BOLD}${CYAN}Beat Conversion:${NC}"
echo -e "${YELLOW}What time is @500?${NC}"
./internet_time -b 500

echo -e "${YELLOW}What time is @000?${NC}"
./internet_time -b 0

echo -e "${YELLOW}What time is @999?${NC}"
./internet_time -b 999
echo

# Verbose output
echo -e "${BOLD}${GREEN}Verbose Output:${NC}"
./internet_time -v
echo

# Date display
echo -e "${BOLD}${BLUE}Internet Date:${NC}"
./internet_time -d
echo

echo -e "${BOLD}${GREEN}Demo completed!${NC} Try ${CYAN}'./internet_time -h'${NC} for all options."
