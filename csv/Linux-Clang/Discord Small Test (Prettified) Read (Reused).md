
----
### Discord Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2385.4 | 0.060507 | 1015.79ms | 6701 | 320 | 840.851 | 2679.04 | 0.0505989 | 2.19722 | 8.92941 | 1.61066 | 0.00185047 | 4.10387e-05 | 6.99522e-06 | 1(Win) | true |
| simdjson (ondemand) | 2184.84 | 0.0331178 | 1033.72ms | 6701 | 2560 | 2402.16 | 2924.96 | 0.0472185 | 2.38944 | 9.90524 | 1.5438 | 0.00137223 | 2.79226e-05 | 6.23741e-06 | 2(Loss) | true |
