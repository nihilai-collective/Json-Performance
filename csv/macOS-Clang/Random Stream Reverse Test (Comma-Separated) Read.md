
----
### Random Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) DID NOT CONVERGE | 611.16 | 0.756468 | 5416.16ms | 4506446 | 40 | 1.13188e+11 | 7.032e+06 | 10.3235 | -(Win) | false |
| simdjson (ondemand) | 264.636 | 0.675281 | 11173.4ms | 4506446 | 30 | 3.60796e+11 | 1.624e+07 | 2.8636 | 2(Loss) | true |
