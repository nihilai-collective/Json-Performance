
----
### Instruments Small Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2851.69 | 0.164294 | 160.32ms | 4669 | 80 | 526.475 | 1561.42 | 0 | 1(Win) | true |
| Jsonifier (two-stage) | 1763.33 | 0.137475 | 262.663ms | 4669 | 4890 | 58929.7 | 2525.16 | 0.421297 | 2(Loss) | true |
| Glaze | 1402.16 | 0.127214 | 325.867ms | 4669 | 80 | 1305.61 | 3175.6 | 0.0794494 | 3(Loss) | true |
| simdjson (ondemand) | 614.391 | 0.119828 | 729.165ms | 4669 | 4890 | 368793 | 7247.35 | 0.307329 | 4(Loss) | true |
