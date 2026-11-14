
----
### Google Maps Response Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1583.46 | 0.0225975 | 2256.38ms | 25388 | 2560 | 30563.4 | 15290.5 | 0.088396 | 3.25614 | 14.636 | 2.88946 | 0.00702037 | 1.25244e-05 | 4.98513e-06 | 1(Win) | true |
| simdjson (ondemand) | 1489.11 | 0.062608 | 2359.09ms | 25388 | 1280 | 132639 | 16259.3 | 0.216508 | 3.45084 | 15.3562 | 2.89401 | 0.00624714 | 1.52016e-05 | 5.16977e-06 | 2(Loss) | true |
