
----
### Google Maps Response Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2605.78 | 0.0349357 | 1062.08ms | 9378 | 4890 | 7030.62 | 3432.2 | 0.0457956 | 1.99897 | 9.11164 | 1.5964 | 0.00104404 | 2.79556e-05 | 6.52007e-06 | 1(Win) | true |
| simdjson (ondemand) | 2144.17 | 0.0448758 | 1134.04ms | 9378 | 640 | 2242.36 | 4171.1 | 0.0869081 | 2.42541 | 9.84304 | 1.71892 | 0.00110581 | 3.03236e-05 | 9.33035e-06 | 2(Loss) | true |
