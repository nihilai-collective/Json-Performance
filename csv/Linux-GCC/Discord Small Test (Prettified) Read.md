
----
### Discord Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2059.86 | 0.0341162 | 1036.48ms | 6701 | 4890 | 5478.15 | 3102.43 | 0.155817 | 2.52579 | 10.3023 | 1.90315 | 0.000534822 | 7.90408e-05 | 3.83607e-05 | 1(Win) | true |
| simdjson (ondemand) | 1904.98 | 0.0251154 | 1066.46ms | 6701 | 4890 | 3471.26 | 3354.67 | 0.0692114 | 2.73238 | 10.9093 | 1.89121 | 0.000308137 | 6.06691e-05 | 2.46583e-05 | 2(Loss) | true |
