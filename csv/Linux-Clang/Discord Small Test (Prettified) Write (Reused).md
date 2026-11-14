
----
### Discord Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 12751.3 | 0.201127 | 790.176ms | 7376 | 4890 | 6019.79 | 551.654 | 0.279501 | 0.426244 | 1.46204 | 0.261659 | 0.000136323 | 2.10709e-05 | 3.90921e-06 | 1(Win) | true |
| Glaze | 2998.07 | 0.150772 | 973.909ms | 7376 | 4890 | 61193.6 | 2346.27 | 0.316138 | 1.71462 | 4.25231 | 0.667029 | 0.000566115 | 2.67545e-05 | 6.65398e-06 | 2(Loss) | true |
