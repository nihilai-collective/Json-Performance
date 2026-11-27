
----
### Random Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Random%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1333.06 | 0.0672207 | 6236.09ms | 676745 | 640 | 6.77855e+07 | 484144 | 0.105823 | 3.81374 | 17.8472 | 3.53475 | 0.00897212 | 0.031847 | 4.17116e-05 | 1(Win) | true |
| simdjson (ondemand) | 746.963 | 0.108123 | 5506.7ms | 676745 | 80 | 6.982e+07 | 864024 | 0.0832443 | 6.81906 | 28.6715 | 5.6668 | 0.0221303 | 0.0418922 | 4.31292e-05 | 2(Loss) | true |
