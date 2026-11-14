
----
### Twitter Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2343 | 0.121023 | 161.311ms | 3808 | 160 | 562.993 | 1549.97 | 0 | 1(Win) | true |
| Jsonifier (two-stage) | 2237.77 | 0.119892 | 166.109ms | 3808 | 4890 | 18511.9 | 1622.86 | 0.0535169 | 2(Loss) | true |
| Glaze | 2085.05 | 0.298659 | 178.461ms | 3808 | 40 | 1082.36 | 1741.72 | 0.0712387 | 3(Loss) | true |
| simdjson (ondemand) | 1097.25 | 0.206517 | 339.992ms | 3808 | 30 | 1401.58 | 3309.73 | 0 | 4(Loss) | true |
