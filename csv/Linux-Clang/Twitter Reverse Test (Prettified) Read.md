
----
### Twitter Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 890.969 | 0.152677 | 5023.23ms | 360584 | 80 | 2.77796e+07 | 385961 | 0.0758115 | 5.74143 | 21.7011 | 4.0771 | 0.0164052 | 0.00634894 | 1.5045e-05 | 1(Win) | true |
| simdjson (ondemand) | 399.53 | 0.14956 | 5504.46ms | 360584 | 160 | 2.65132e+08 | 860710 | 0.0639078 | 12.6936 | 52.8829 | 9.1997 | 0.0529287 | 0.00281436 | 7.85878e-05 | 2(Loss) | true |
