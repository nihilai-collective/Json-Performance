
----
### Discord Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3385.99 | 0.0410378 | 3470.47ms | 83958 | 4890 | 460500 | 23647 | 0.0562307 | 1.49519 | 7.33266 | 1.22247 | 0.00166989 | 1.13359e-05 | 5.10285e-06 | 1(Win) | true |
| Glaze | 2966.56 | 0.0361998 | 3810.58ms | 83958 | 4890 | 466807 | 26990.3 | 0.0896667 | 1.70601 | 8.94217 | 1.79286 | 0.00351461 | 1.54498e-05 | 8.12316e-06 | 2(Loss) | true |
| Jsonifier | 2082.12 | 0.0419121 | 4951.97ms | 83958 | 4890 | 1.27028e+06 | 38455.2 | 0.0335938 | 2.42935 | 8.37882 | 1.84644 | 0.00514519 | 2.27789e-05 | 1.38837e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1618.66 | 0.0650973 | 6102.84ms | 83958 | 4890 | 5.07047e+06 | 49466 | 0.0507767 | 3.10169 | 13.5606 | 2.09705 | 0.00627483 | 2.06793e-05 | 1.175e-05 | 4(Loss) | true |
