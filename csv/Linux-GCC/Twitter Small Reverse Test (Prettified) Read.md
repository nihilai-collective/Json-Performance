
----
### Twitter Small Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1076.07 | 0.12743 | 1060ms | 3770 | 80 | 1450.22 | 3341.18 | 0.0583287 | 4.84466 | 19.7491 | 3.62255 | 0.00243037 | 9.94695e-05 | 7.29443e-05 | 1(Win) | true |
| simdjson (ondemand) | 529.502 | 0.14969 | 1409.39ms | 3770 | 30 | 3099.24 | 6790.07 | 0.317591 | 9.7752 | 43.7796 | 8.76525 | 0.00768347 | 0 | 0 | 2(Loss) | true |
