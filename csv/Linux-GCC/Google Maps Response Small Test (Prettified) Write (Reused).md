
----
### Google Maps Response Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 30756.2 | 0.0736946 | 763.778ms | 11521 | 4890 | 338.919 | 357.238 | 0.0187058 | 0.1833 | 0.69178 | 0.0991234 | 8.68513e-05 | 6.05279e-06 | 1.63301e-06 | 1(Win) | true |
| Glaze | 6957.24 | 0.113262 | 885.689ms | 11521 | 2560 | 8190.58 | 1579.26 | 0.150013 | 0.745349 | 3.64795 | 0.607847 | 0.000259953 | 1.51218e-05 | 4.27209e-06 | 2(Loss) | true |
| simdjson (reflection) | 523.315 | 0.115864 | 2855.08ms | 11521 | 4890 | 2.89376e+06 | 20995.5 | 0.182446 | 9.63623 | 37.951 | 6.97405 | 0.0104205 | 0.000110317 | 6.34389e-05 | 3(Loss) | true |
