
----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5578.95 | 0.275541 | 6529.87ms | 699405 | 160 | 1.73638e+07 | 119557 | 0.000292746 | 0.443655 | 1(Win) | true |
| Glaze | 3819.85 | 0.172695 | 8965.6ms | 699405 | 320 | 2.90988e+07 | 174615 | 0.280175 | 0.648007 | 2(Loss) | true |
| simdjson (ondemand) | 2252.65 | 0.0647201 | 8344.21ms | 767297 | 1280 | 5.65756e+07 | 324841 | 0.272509 | 1.0989 | 3(Loss) | true |
