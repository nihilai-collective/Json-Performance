
----
### Discord Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2711.03 | 0.0431535 | 3122.85ms | 83958 | 80 | 12995 | 29534.4 | 0.0174766 | 1(Win) | true |
| Jsonifier (two-stage) | 2283.06 | 0.0567498 | 4260.59ms | 83958 | 30 | 11883.4 | 35070.7 | 0.0199557 | 2(Loss) | true |
| Glaze | 2170.73 | 0.0710314 | 3896.52ms | 83958 | 2560 | 1.75733e+06 | 36885.6 | 0.13598 | 3(Loss) | true |
| simdjson (ondemand) | 1214.12 | 0.0584738 | 6936.31ms | 83958 | 2560 | 3.80685e+06 | 65948 | 0.00800105 | 4(Loss) | true |
