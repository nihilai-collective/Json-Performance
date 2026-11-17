
----
### Apache Builds Small Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1326.9 | 1.66618 | 200.614ms | 2632 | 80 | 79475.6 | 1891.69 | 0.821165 | 1(Win) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 1025.88 | 0.760604 | 245.5ms | 2632 | 1280 | 443310 | 2446.75 | 1.62016 | 2(Tie) | true |
| Glaze STATISTICAL TIE | 1016.32 | 0.918524 | 283.672ms | 2632 | 640 | 329361 | 2469.77 | 1.02491 | 2(Tie) | true |
| simdjson (ondemand) | 749.057 | 0.413281 | 343.698ms | 2632 | 1280 | 245496 | 3350.97 | 1.60594 | 4(Loss) | true |
