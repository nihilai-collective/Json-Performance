
----
### Instruments Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 24152.2 | 0.371776 | 762.785ms | 9249 | 4890 | 9014.66 | 365.206 | 0.209072 | 0.236219 | 0.657152 | 0.1478 | 0.000108695 | 1.0414e-05 | 1.94571e-06 | 1(Win) | true |
| Glaze | 2964.26 | 0.201417 | 1028.61ms | 9249 | 2560 | 91957.7 | 2975.63 | 0.260496 | 1.75739 | 3.52752 | 0.565359 | 0.000339479 | 1.66825e-05 | 8.57356e-06 | 2(Loss) | true |
| simdjson (reflection) | 526.317 | 0.0686576 | 2419.39ms | 9249 | 4890 | 647411 | 16759 | 0.243974 | 9.74524 | 40.8871 | 8.30856 | 0.0134386 | 0.000109999 | 6.15332e-05 | 3(Loss) | true |
