
----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1907.06 | 0.477048 | 6881.09ms | 264040 | 40 | 1.58706e+07 | 132040 | 0.105683 | 1.29792 | 1(Win) | true |
| Jsonifier (generic) | 1724.61 | 0.354205 | 7436.09ms | 264040 | 160 | 4.27944e+07 | 146009 | 0.215545 | 1.43515 | 2(Loss) | true |
