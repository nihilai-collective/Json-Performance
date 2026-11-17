
----
### Google Maps Response Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1583.55 | 0.0952206 | 2266.91ms | 25388 | 320 | 67827.2 | 15289.6 | 0.0408608 | 3.25656 | 14.6661 | 2.89316 | 0.00704676 | 7.26229e-06 | 9.84717e-07 | 1(Win) | true |
| simdjson (ondemand) | 1447.44 | 0.0595167 | 2409.69ms | 25388 | 2560 | 253732 | 16727.4 | 0.00690578 | 3.56178 | 15.387 | 2.90358 | 0.00728303 | 4.35583e-05 | 2.89722e-05 | 2(Loss) | true |
