
----
### Marine IK Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2221.33 | 0.0794814 | 9818.85ms | 7351818 | 160 | 1.00696e+09 | 3.15632e+06 | 0.0288506 | 2.27279 | 9.2228 | 1.84807 | 0.0112263 | 0.0588003 | 0.00420996 | 1(Win) | true |
| simdjson (ondemand) | 2189.03 | 0.126261 | 9942.85ms | 7351818 | 160 | 2.61663e+09 | 3.20289e+06 | 0.450052 | 2.30972 | 9.55834 | 1.56872 | 0.00934716 | 0.0588531 | 0.00533748 | 2(Loss) | true |
