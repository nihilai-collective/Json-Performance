
----
### Twitter Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 996.342 | 0.0381026 | 1082.39ms | 3770 | 4890 | 9244.52 | 3608.55 | 0.0487642 | 5.22087 | 20.747 | 3.92016 | 0.00150564 | 5.99936e-05 | 1.83344e-05 | 1(Win) | true |
| simdjson (ondemand) | 538.181 | 0.0283786 | 1387.42ms | 3770 | 4890 | 17575.8 | 6680.56 | 0.112387 | 9.62222 | 43.7403 | 8.74854 | 0.00926565 | 4.23101e-05 | 1.17709e-05 | 2(Loss) | true |
