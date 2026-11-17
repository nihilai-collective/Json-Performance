
----
### Twitter Partial Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 6397.44 | 0.297345 | 46.0447ms | 2889 | 30 | 49.1954 | 430.667 | 0.069611 | 0.361475 | 1(Win) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 6006.73 | 0.35142 | 48.2834ms | 2889 | 4890 | 12705.2 | 458.68 | 0.0362071 | 0.384147 | 2(Tie) | true |
| Jsonifier STATISTICAL TIE | 6005.77 | 0.117149 | 48.5373ms | 2889 | 320 | 92.4248 | 458.753 | 0.00476813 | 0.38448 | 2(Tie) | true |
| Glaze | 3175.71 | 0.21213 | 91.6874ms | 2889 | 40 | 135.481 | 867.575 | 0.651767 | 0.755036 | 4(Loss) | true |
