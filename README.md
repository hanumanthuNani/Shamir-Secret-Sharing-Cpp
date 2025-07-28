# 🔐 Secret Share JSON Validator

A simple utility to **validate and visualize** Shamir's Secret Sharing (SSS) data in JSON format.

This tool allows users to:
- Upload a JSON file containing secret shares.
- See a live preview of the parsed shares.
- Download the validated, clean JSON back.

---

## 📜 Example JSON Format

```json
{
  "n": 4,
  "k": 3,
  "shares": [
    { "x": "1", "y": "4", "base": 10 },
    { "x": "2", "y": "111", "base": 2 },
    { "x": "3", "y": "12", "base": 10 },
    { "x": "6", "y": "213", "base": 4 }
  ]
}

⚠️ All x and y fields must be strings. base is optional (defaults to base-10 if omitted).
