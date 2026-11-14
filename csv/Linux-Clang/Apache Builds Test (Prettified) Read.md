
----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1899.28 | 0.0603998 | 7033.39ms | 124597 | 160 | 228469 | 62563.2 | 0.227819 | 2.71171 | 11.8484 | 2.26045 | 0.00713385 | 6.35549e-05 | 5.93413e-05 | 1(Win) | true |
| simdjson (ondemand) | 1630.8 | 0.0324445 | 8020.39ms | 124597 | 1280 | 715324 | 72862.8 | 0.0842048 | 3.13007 | 12.9142 | 2.3706 | 0.00879225 | 4.82807e-06 | 1.19761e-06 | 2(Loss) | true |
