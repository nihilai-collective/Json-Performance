
----
### Double Test Write (Reused) Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 895.087 | 0.0298625 | 224.511ms | 1997 | 320 | 129.19 | 2127.71 | 0.448289 | 2.73027 | 1(Win) | true |
| Glaze | 576.854 | 0.053901 | 310.461ms | 1798 | 80 | 205.367 | 2972.51 | 0.289734 | 4.25351 | 2(Loss) | true |
