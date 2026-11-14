
----
### Github Events Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 18553.7 | 0.0401622 | 1146.25ms | 78778 | 4890 | 12932.7 | 4049.24 | 0.146252 | 0.274511 | 0.823656 | 0.123105 | 2.55487e-05 | 1.20968e-05 | 6.66624e-06 | 1(Win) | true |
| Glaze | 6225.03 | 0.114758 | 1948.6ms | 78778 | 2560 | 491056 | 12068.8 | 0.00945985 | 0.813237 | 2.80596 | 0.434093 | 4.59956e-05 | 2.31366e-05 | 1.26641e-05 | 2(Loss) | true |
| simdjson (reflection) | 639.228 | 0.169841 | 6370.62ms | 78778 | 1280 | 5.1003e+07 | 117530 | 0.258191 | 7.89539 | 29.3753 | 6.6079 | 0.0327612 | 0.000751429 | 0.000162452 | 3(Loss) | true |
