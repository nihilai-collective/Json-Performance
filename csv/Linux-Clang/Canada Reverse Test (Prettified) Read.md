
----
### Canada Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1614.24 | 0.12461 | 9583.6ms | 5212421 | 40 | 5.88988e+08 | 3.07943e+06 | 0.170357 | 3.1521 | 15.0934 | 2.84958 | 0.0102782 | 0.100863 | 0.000733781 | 1(Win) | true |
| simdjson (ondemand) | 1569.62 | 0.129081 | 9842.6ms | 5212421 | 40 | 6.68465e+08 | 3.16698e+06 | 0.163808 | 3.2265 | 15.1882 | 2.6837 | 0.0103242 | 0.121404 | 0.000739877 | 2(Loss) | true |
