
----
### Google Maps Response Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 26139.2 | 0.107907 | 753.699ms | 11521 | 4890 | 1006.01 | 420.338 | 0.303299 | 0.217829 | 0.774238 | 0.0854961 | 8.69755e-05 | 1.95429e-05 | 1.13423e-05 | 1(Win) | true |
| Glaze | 6749.3 | 0.101106 | 880.255ms | 11521 | 4890 | 13247.3 | 1627.91 | 0.0253966 | 0.781223 | 3.64795 | 0.607847 | 0.000273156 | 3.27667e-05 | 1.63833e-05 | 2(Loss) | true |
| simdjson (reflection) | 522.184 | 0.288904 | 2826.98ms | 11521 | 640 | 2.36495e+06 | 21041 | 0.0152553 | 9.74798 | 38.02 | 7.00109 | 0.0130217 | 5.27569e-05 | 2.41407e-05 | 3(Loss) | true |
