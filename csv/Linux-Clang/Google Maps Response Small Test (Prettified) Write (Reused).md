
----
### Google Maps Response Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 17601.7 | 0.0843856 | 793.644ms | 11521 | 4890 | 1356.81 | 624.219 | 0.0217296 | 0.305945 | 1.46012 | 0.265255 | 8.74193e-05 | 7.8278e-06 | 1.54426e-06 | 1(Win) | true |
| Glaze | 5361.55 | 0.0719497 | 937.614ms | 11521 | 4890 | 10630.8 | 2049.27 | 0.0645148 | 0.963302 | 3.62026 | 0.633279 | 0.00115823 | 1.84424e-05 | 4.70378e-06 | 2(Loss) | true |
