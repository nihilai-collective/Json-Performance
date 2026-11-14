
----
### Instruments Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 407.101 | 1.06102 | 1227.01ms | 4669 | 160 | 2.15482e+06 | 10937.6 | 0.117165 | 1(Win) | true |
| simdjson (ondemand) | 143.406 | 0.441521 | 2961.75ms | 4669 | 80 | 1.5035e+06 | 31049.6 | 0.154831 | 2(Loss) | true |
