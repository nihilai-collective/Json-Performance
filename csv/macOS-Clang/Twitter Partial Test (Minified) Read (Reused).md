
----
### Twitter Partial Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 5030.25 | 0.226146 | 9103.83ms | 466906 | 160 | 6.41178e+06 | 88519.8 | 0.013544 | 1(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 5014.2 | 0.0534946 | 9112.85ms | 466906 | 4890 | 1.10353e+07 | 88803 | 0.22965 | 1(Tie) | true |
| simdjson (ondemand) | 4188.92 | 0.200049 | 5575.52ms | 466906 | 30 | 1.35659e+06 | 106299 | 0.306151 | 3(Loss) | true |
| Glaze | 2291.37 | 0.102896 | 5001.2ms | 466906 | 1280 | 5.11771e+07 | 194328 | 0.114479 | 4(Loss) | true |
