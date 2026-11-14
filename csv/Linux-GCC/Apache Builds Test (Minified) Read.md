
----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1574.8 | 0.079055 | 6435.03ms | 94653 | 160 | 328548 | 57320.5 | 0.140318 | 3.2219 | 14.8731 | 2.85132 | 0.00884045 | 8.1878e-06 | 5.01833e-06 | 1(Win) | true |
| simdjson (ondemand) | 1242.5 | 0.0480665 | 7984.29ms | 94653 | 640 | 780444 | 72650.5 | 0.144364 | 4.11099 | 15.8653 | 3.10282 | 0.0117886 | 4.27549e-06 | 8.74906e-07 | 2(Loss) | true |
