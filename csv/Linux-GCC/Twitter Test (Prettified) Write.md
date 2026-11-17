
----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 17676 | 0.195193 | 3952.98ms | 716365 | 1280 | 7.28517e+06 | 38650.1 | 0.0979913 | 0.139947 | 1(Win) | true |
| Glaze | 4175.44 | 0.0732204 | 8448.35ms | 716365 | 1280 | 1.83713e+07 | 163619 | 0.106946 | 0.592815 | 2(Loss) | true |
| simdjson (reflection) | 567.054 | 0.147519 | 7760.17ms | 716365 | 320 | 1.01081e+09 | 1.20479e+06 | 0.907252 | 4.36598 | 3(Loss) | true |
