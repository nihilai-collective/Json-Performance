
----
### Marine IK Reverse Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 623.41 | 0.146106 | 773.051ms | 4604 | 30 | 3176.75 | 7043.07 | 0.000473276 | 1(Win) | true |
| Jsonifier (two-stage) | 459.877 | 1.33226 | 927.268ms | 4604 | 640 | 1.0355e+07 | 9547.59 | 1.01727 | 2(Loss) | true |
| Glaze | 343.998 | 0.591504 | 1269.23ms | 4604 | 160 | 911999 | 12763.8 | 0.356086 | 3(Loss) | true |
| simdjson (ondemand) | 288.795 | 0.269189 | 1547.73ms | 4604 | 4890 | 8.19057e+06 | 15203.6 | 2.38247 | 4(Loss) | true |
