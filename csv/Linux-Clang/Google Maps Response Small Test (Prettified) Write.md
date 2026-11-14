
----
### Google Maps Response Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 15690.1 | 0.145266 | 802.79ms | 11521 | 4890 | 5060.16 | 700.268 | 0.146447 | 0.340711 | 1.50959 | 0.277146 | 0.000113157 | 1.20701e-05 | 2.14776e-06 | 1(Win) | true |
| Glaze | 4790.52 | 0.199114 | 966.211ms | 11521 | 640 | 13347.4 | 2293.55 | 0.0639293 | 1.07938 | 3.86781 | 0.687441 | 0.00118018 | 1.57321e-05 | 2.57682e-06 | 2(Loss) | true |
