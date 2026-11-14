
----
### Canada Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1850.4 | 0.100402 | 9554.85ms | 5212421 | 160 | 1.16401e+09 | 2.68643e+06 | 0.0698385 | 2.73932 | 12.957 | 2.33274 | 0.00980118 | 0.0905794 | 0.000492238 | 1(Win) | true |
| simdjson (ondemand) | 1794.27 | 0.18449 | 9849.98ms | 5212421 | 40 | 1.04498e+09 | 2.77045e+06 | 0.116057 | 2.85404 | 13.0598 | 2.16844 | 0.00995783 | 0.111151 | 0.000711402 | 2(Loss) | true |
