
----
### Random Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 977.101 | 0.41401 | 8887.03ms | 676745 | 320 | 2.393e+09 | 660520 | 0.584332 | 1(Win) | true |
| simdjson (ondemand) | 551.92 | 0.354016 | 7470.06ms | 676745 | 30 | 5.1412e+08 | 1.16936e+06 | 0.17086 | 2(Loss) | true |
