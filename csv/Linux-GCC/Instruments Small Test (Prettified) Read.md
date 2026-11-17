
----
### Instruments Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3689.89 | 0.0833692 | 205.513ms | 7932 | 80 | 233.691 | 2050.07 | 0.0609362 | 0.662075 | 1(Win) | true |
| Jsonifier | 2695.2 | 0.0710916 | 291.047ms | 7932 | 80 | 318.501 | 2806.68 | 0.160963 | 0.910562 | 2(Loss) | true |
| simdjson (reflection) | 2333.78 | 0.0865128 | 324.299ms | 7932 | 40 | 314.533 | 3241.32 | 0.0882619 | 1.0521 | 3(Loss) | true |
| Glaze | 2002.08 | 0.0806207 | 375.311ms | 7932 | 40 | 371.156 | 3778.35 | 0.214397 | 1.22715 | 4(Loss) | true |
| simdjson (ondemand) | 1607.02 | 0.201823 | 479.204ms | 7932 | 1280 | 115525 | 4707.2 | 0.109917 | 1.53236 | 5(Loss) | true |
