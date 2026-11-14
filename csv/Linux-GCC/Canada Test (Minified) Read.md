
----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 802.065 | 0.0807018 | 7742.21ms | 2090234 | 160 | 6.43662e+08 | 2.48534e+06 | 0.0793309 | 6.31567 | 30.3586 | 5.61964 | 0.0231564 | 0.105401 | 0.00091093 | 1(Win) | true |
| Jsonifier (generic) | 733.265 | 0.0975849 | 8449.76ms | 2090234 | 160 | 1.12604e+09 | 2.71853e+06 | 0.300997 | 6.88274 | 31.1375 | 6.38675 | 0.0217599 | 0.103714 | 0.00125169 | 2(Loss) | true |
