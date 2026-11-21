
----
### Twitter Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Glaze | 1888.58 | 0.114479 | 174.812ms | 2889 | 320 | 892.537 | 1458.86 | 0.161775 | 1(Win) | true |
| Jsonifier (two-stage) | 1735.25 | 0.321909 | 177.215ms | 2889 | 160 | 4179.83 | 1587.76 | 1.44472 | 2(Loss) | true |
| Jsonifier | 1657.31 | 0.733208 | 134.541ms | 2889 | 30 | 4457.22 | 1662.43 | 1.08641 | 3(Loss) | true |
| simdjson (ondemand) | 797.143 | 0.435417 | 382.759ms | 2889 | 40 | 9059.29 | 3456.3 | 1.40932 | 4(Loss) | true |
