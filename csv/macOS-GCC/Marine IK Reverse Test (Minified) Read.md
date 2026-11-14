
----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 241.37 | 0.813649 | 10279.5ms | 1834197 | 30 | 1.04309e+11 | 7.24707e+06 | 0.179299 | 1(Win) | true |
| simdjson (ondemand) | 200.12 | 0.459357 | 6107.31ms | 1834197 | 30 | 4.83653e+10 | 8.7409e+06 | 0.657506 | 2(Loss) | true |
