
----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1248.74 | 0.666792 | 6148.13ms | 5373214 | 40 | 2.99477e+10 | 4.10357e+06 | 0.103036 | 2.43383 | 1(Win) | true |
| Jsonifier | 1148.59 | 0.580603 | 6652.99ms | 5373214 | 80 | 5.36766e+10 | 4.46137e+06 | 0.155791 | 2.64607 | 2(Loss) | true |
| simdjson (ondemand) | 861.886 | 0.400206 | 9049.3ms | 5373214 | 30 | 1.69847e+10 | 5.94545e+06 | 1.27915 | 3.52636 | 3(Loss) | true |
| Glaze | 774.151 | 0.502007 | 9973.36ms | 5373214 | 30 | 3.31252e+10 | 6.61924e+06 | 0.284019 | 3.92601 | 4(Loss) | true |
