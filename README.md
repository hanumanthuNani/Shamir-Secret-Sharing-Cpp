

# 🔐 Secret Share JSON Validator

A simple utility to **validate and visualize** Shamir's Secret Sharing (SSS) data in JSON format.

This tool allows users to:

* ✅ Upload a JSON file containing secret shares.
* 🔍 See a live preview of the parsed shares.
* 📥 Download the validated, clean JSON back.

---

## 📜 Example JSON Format

Your JSON should contain:

* `"n"`: total number of shares.
* `"k"`: minimum shares needed to reconstruct the secret.
* `"shares"`: an array of shares, where each share has:

  * `"x"`: string representing the x-coordinate (must be a string).
  * `"y"`: string representing the y-coordinate (must be a string).
  * `"base"`: optional, integer base of the value (defaults to base-10).

### ✅ Input Example 1 (Correct Format)

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
```

### ❌ Input Example 2 (Incorrect Format – Will Throw Validation Error)

```json
{
  "keys": {
    "n": 4,
    "k": 3
  },
  "1": {
    "base": "10",
    "value": "4"
  },
  "2": {
    "base": "2",
    "value": "111"
  }
}
```

⚠️ In **Input 2**, the format is invalid because:

* `n`, `k`, and `shares` are not at the top level.
* Share fields do not have `x`, `y` as strings.
* `value` is not a valid key for share data.

---

## 🛠 How to Use

1. Clone the repository:

```bash
git clone https://github.com/<your-username>/secret-share-json-validator.git
cd secret-share-json-validator
```

2. Install dependencies:

```bash
npm install
```

3. Start the development server:

```bash
npm run dev
```

4. Open your browser and go to:

```
http://localhost:3000
```

5. Upload your `.json` file and validate it instantly.

---

## 🚀 Future Improvements (Coming Soon or Contribute!)

* [ ] Dark mode UI toggle 🌙
* [ ] Auto-formatting on file upload ✨
* [ ] Share QR code generation 📱
* [ ] JSON schema validator integration 🧠
* [ ] Drag-and-drop JSON file support 🖱️

Want to contribute? Fork the repo, open a pull request, and let's build magic together!

---

## 🙏 Acknowledgements

* Based on the powerful concept of **Shamir's Secret Sharing**.
* Inspired by traditional cryptographic techniques, now modernized for developers like you.

