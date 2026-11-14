
----
### Twitter Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 577.436 | 0.852323 | 5071.07ms | 4219119 | 30 | 1.05819e+11 | 6.96816e+06 | 0.801945 | 1(Win) | true |
| simdjson (ondemand) | 175.753 | 0.688214 | 7130.7ms | 4219119 | 30 | 7.44746e+11 | 2.28939e+07 | 0.866293 | 2(Loss) | true |
