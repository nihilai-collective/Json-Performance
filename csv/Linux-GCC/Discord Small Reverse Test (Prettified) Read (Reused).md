
----
### Discord Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 985.995 | 0.0242112 | 1395.46ms | 6701 | 4890 | 12041.2 | 6481.34 | 0.0542066 | 5.24431 | 21.4672 | 4.29637 | 0.00561168 | 2.64283e-05 | 4.4861e-06 | 1(Win) | true |
| simdjson (ondemand) | 336.725 | 0.0628305 | 2641.04ms | 6701 | 160 | 22750.4 | 18978.6 | 0.0163644 | 15.3249 | 76.3395 | 15.9746 | 0.0355329 | 4.19713e-05 | 8.39427e-06 | 2(Loss) | true |
