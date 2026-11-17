
----
### Discord Small Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1486.68 | 0.0884369 | 1031.08ms | 4857 | 640 | 4858.98 | 3115.65 | 0.116963 | 3.50694 | 14.1414 | 2.72782 | 0.00176646 | 2.54144e-05 | 6.43401e-07 | 1(Win) | true |
| simdjson (ondemand) | 1397.47 | 0.156952 | 1051.11ms | 4857 | 30 | 811.909 | 3314.57 | 0.0603761 | 3.73217 | 14.3351 | 2.55487 | 0.0014069 | 6.86295e-05 | 2.74518e-05 | 2(Loss) | true |
