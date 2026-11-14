
----
### Apache Builds Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 2124.37 | 0.483349 | 182.833ms | 3370 | 4890 | 261474 | 1512.86 | 0.0701503 | 1(Win) | true |
| Glaze STATISTICAL TIE | 1980.94 | 1.23348 | 196.766ms | 3370 | 640 | 256308 | 1622.4 | 0.245942 | 2(Tie) | true |
| Jsonifier STATISTICAL TIE | 1924.02 | 1.66151 | 194.694ms | 3370 | 320 | 246489 | 1670.4 | 0.384615 | 2(Tie) | true |
| simdjson (reflection) | 1582.14 | 0.22198 | 232.487ms | 3370 | 4890 | 99427.6 | 2031.35 | 0.636718 | 4(Loss) | true |
| simdjson (ondemand) | 1411.11 | 0.29117 | 262.136ms | 3370 | 4890 | 215051 | 2277.56 | 0.146329 | 5(Loss) | true |
