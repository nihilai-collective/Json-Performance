
----
### Discord Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 15419.3 | 0.101483 | 1086.44ms | 56369 | 4890 | 61213.4 | 3486.4 | 0.00946157 | 0.331895 | 1.40929 | 0.222197 | 0.000208881 | 1.05861e-05 | 5.61956e-06 | 1(Win) | true |
| simdjson (reflection) | 13319.9 | 0.0846234 | 1144.31ms | 56369 | 320 | 3732.6 | 4035.9 | 0.0190514 | 0.383265 | 1.68962 | 0.275222 | 0.000155726 | 4.71225e-06 | 2.43928e-06 | 2(Loss) | true |
| Glaze | 7225.53 | 0.21918 | 1481.12ms | 56369 | 80 | 21273.2 | 7439.96 | 0.221117 | 0.70293 | 2.97538 | 0.448722 | 7.1848e-05 | 1.7075e-05 | 1.24182e-05 | 3(Loss) | true |
