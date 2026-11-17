
----
### Google Maps Response Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 15566.1 | 0.193842 | 803.625ms | 11521 | 2560 | 4792.4 | 705.845 | 0.215367 | 0.343846 | 1.51011 | 0.27732 | 0.000130468 | 4.06527e-05 | 1.94278e-05 | 1(Win) | true |
| Glaze | 4767.56 | 0.0834495 | 969.667ms | 11521 | 4890 | 18086.1 | 2304.59 | 0.354703 | 1.07817 | 3.86946 | 0.688048 | 0.00116723 | 3.17727e-05 | 1.15731e-05 | 2(Loss) | true |
