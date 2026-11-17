
----
### Apache Builds Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze | 1547 | 0.321861 | 287.606ms | 3370 | 40 | 1788.46 | 2077.5 | 0.120192 | 1.5731 | 1(Win) | true |
| Jsonifier (two-stage) | 1522.27 | 0.125903 | 258.698ms | 3370 | 160 | 1130.5 | 2111.25 | 0.177305 | 1.60402 | 2(Loss) | true |
| Jsonifier | 1372.35 | 0.167069 | 275.449ms | 3370 | 160 | 2449.29 | 2341.88 | 0.133262 | 1.7815 | 3(Loss) | true |
| simdjson (ondemand) | 1348.48 | 0.290369 | 269.288ms | 3370 | 30 | 1436.78 | 2383.33 | 0.140056 | 1.81715 | 4(Loss) | true |
