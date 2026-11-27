
----
### Twitter Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 16432.3 | 0.148416 | 4141.3ms | 716365 | 1280 | 4.87358e+06 | 41575.5 | 0.314925 | 0.150547 | 1(Win) | true |
| Glaze | 4984.53 | 0.503006 | 7070.94ms | 716365 | 80 | 3.80238e+07 | 137060 | 0.402773 | 0.496592 | 2(Loss) | true |
| simdjson (reflection) | 564.245 | 0.182887 | 7622.22ms | 716365 | 320 | 1.5691e+09 | 1.21078e+06 | 1.4867 | 4.38766 | 3(Loss) | true |
