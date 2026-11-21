
----
### Marine IK Reverse Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 1827.02 | 0.0883455 | 1000.93ms | 18245 | 30 | 2123.7 | 9523.6 | 0.0732052 | 1(Win) | true |
| Jsonifier | 1709.3 | 0.139322 | 1071.76ms | 18245 | 4890 | 983554 | 10179.5 | 0.101406 | 2(Loss) | true |
| simdjson (ondemand) STATISTICAL TIE | 1141.5 | 0.169774 | 1510.68ms | 18245 | 2560 | 1.71443e+06 | 15242.9 | 0.0186732 | 3(Tie) | true |
| Glaze STATISTICAL TIE | 1137.87 | 0.157262 | 1651.82ms | 18245 | 30 | 17348.8 | 15291.5 | 3.40502 | 3(Tie) | true |
