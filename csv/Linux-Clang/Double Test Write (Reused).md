
----
### Double Test Write (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 644.429 | 0.12178 | 316.568ms | 1997 | 160 | 2072.42 | 2955.31 | 0.0376582 | 3.80444 | 1(Win) | true |
| Glaze | 583.949 | 0.164662 | 303.771ms | 1798 | 30 | 701.352 | 2936.4 | 0.195632 | 4.20362 | 2(Loss) | true |
