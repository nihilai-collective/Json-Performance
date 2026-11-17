
----
### Apache Builds Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1672.89 | 0.237998 | 199.19ms | 3370 | 4890 | 102230 | 1921.15 | 0.504856 | 1(Win) | true |
| Glaze | 1407.97 | 0.355073 | 255.597ms | 3370 | 4890 | 321232 | 2282.64 | 0.612161 | 2(Loss) | true |
| Jsonifier (two-stage) | 1365.69 | 0.551346 | 209.215ms | 3370 | 2560 | 430967 | 2353.3 | 1.01734 | 3(Loss) | true |
| simdjson (reflection) | 1151.85 | 0.996966 | 264.804ms | 3370 | 1280 | 990470 | 2790.2 | 0.0644699 | 4(Loss) | true |
| simdjson (ondemand) | 1050.12 | 0.150954 | 321.57ms | 3370 | 4890 | 104371 | 3060.48 | 0.22226 | 5(Loss) | true |
