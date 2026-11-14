
----
### Marine IK Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 6316.29 | 0.0474116 | 9551.53ms | 9930848 | 30 | 1.51614e+07 | 1.49942e+06 | 0.118671 | 0.799481 | 2.51575 | 0.147539 | 0.000481416 | 0.0249818 | 0.000140794 | 1(Win) | true |
| Glaze | 4076.75 | 0.144576 | 7244.48ms | 9930228 | 80 | 9.02347e+08 | 2.32298e+06 | 0.0899124 | 1.24202 | 4.414 | 0.474254 | 0.000781265 | 0.0224149 | 0.000249594 | 2(Loss) | true |
| simdjson (reflection) | 333.581 | 1.51384 | 8626.27ms | 10018896 | 30 | 5.6405e+12 | 2.8643e+07 | 0.420014 | 13.279 | 38.772 | 5.80014 | 0.0234416 | 0.289026 | 0.143406 | 3(Loss) | true |
