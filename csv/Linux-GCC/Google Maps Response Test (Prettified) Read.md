
----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3319.03 | 0.0553372 | 1469.35ms | 25388 | 1280 | 20858.3 | 7294.87 | 0.0928729 | 1.52942 | 7.15669 | 1.05042 | 0.00293597 | 1.69248e-05 | 9.2625e-06 | 1(Win) | true |
| Jsonifier | 3281.87 | 0.0266756 | 1475.32ms | 25388 | 4890 | 18938.8 | 7377.47 | 0.212853 | 1.54897 | 7.18631 | 1.38278 | 0.004003 | 1.91949e-05 | 9.76259e-06 | 2(Loss) | true |
| simdjson (reflection) | 2932.28 | 0.0521514 | 1565.83ms | 25388 | 2560 | 47470 | 8257.02 | 0.071387 | 1.72039 | 6.9779 | 1.03116 | 0.00197196 | 1.62478e-05 | 7.38538e-06 | 3(Loss) | true |
| simdjson (ondemand) | 2233.66 | 0.0275268 | 1822.31ms | 25388 | 2560 | 22791.6 | 10839.6 | 0.176771 | 2.27016 | 8.98048 | 1.52061 | 0.00399287 | 1.64479e-05 | 6.56991e-06 | 4(Loss) | true |
| Glaze | 1873.6 | 0.0636183 | 2026.41ms | 25388 | 320 | 21628 | 12922.6 | 0.0369401 | 2.70477 | 9.40986 | 1.80814 | 0.00589144 | 5.78521e-06 | 4.92359e-07 | 5(Loss) | true |
