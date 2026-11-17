
----
### Instruments Small Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2672.05 | 1.12981 | 176.698ms | 4669 | 640 | 226858 | 1666.4 | 0.287219 | 1(Win) | true |
| Jsonifier (two-stage) | 1566.28 | 0.477216 | 300.577ms | 4669 | 4890 | 900013 | 2842.86 | 0.785494 | 2(Loss) | true |
| Glaze | 1442.13 | 0.480696 | 329.818ms | 4669 | 640 | 140982 | 3087.6 | 0.0129567 | 3(Loss) | true |
| simdjson (reflection) | 1228.44 | 0.249869 | 378.024ms | 4669 | 4890 | 401119 | 3624.68 | 0.119115 | 4(Loss) | true |
| simdjson (ondemand) | 1027.15 | 0.428944 | 435.781ms | 4669 | 1280 | 442578 | 4335 | 0.626741 | 5(Loss) | true |
