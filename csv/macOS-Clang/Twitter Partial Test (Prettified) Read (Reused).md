
----
### Twitter Partial Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 5059.24 | 0.444036 | 6406.16ms | 631514 | 160 | 4.47046e+07 | 119041 | 0.445445 | 1(Win) | true |
| Jsonifier | 4863.68 | 0.635006 | 6416.43ms | 631514 | 30 | 1.85487e+07 | 123828 | 0.113147 | 2(Loss) | true |
| simdjson (ondemand) | 4474.2 | 0.242065 | 6953.16ms | 631514 | 640 | 6.79482e+07 | 134607 | 0.586858 | 3(Loss) | true |
| Glaze | 2579.16 | 0.397243 | 6057.92ms | 631514 | 40 | 3.44177e+07 | 233509 | 0.0620397 | 4(Loss) | true |
