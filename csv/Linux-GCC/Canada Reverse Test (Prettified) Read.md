
----
### Canada Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1607.51 | 0.44502 | 9639.87ms | 5212421 | 160 | 3.03004e+10 | 3.09232e+06 | 0.384244 | 3.18209 | 14.7144 | 2.67355 | 0.0105404 | 0.120897 | 0.000531766 | 1(Win) | true |
| Jsonifier (generic) | 1548.99 | 0.684486 | 9895.27ms | 5212421 | 80 | 3.86011e+10 | 3.20915e+06 | 0.311078 | 3.27106 | 14.5067 | 2.86064 | 0.0103011 | 0.100387 | 0.000740138 | 2(Loss) | true |
