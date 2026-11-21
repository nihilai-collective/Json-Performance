
----
### Prettify Test Write (Reused) Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Prettify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Prettify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4489.4 | 0.571609 | 7806.38ms | 699405 | 30 | 2.16372e+07 | 148573 | 0.147856 | 0.551337 | 1(Win) | true |
| Glaze | 2996.12 | 0.399102 | 5812ms | 699405 | 40 | 3.15767e+07 | 222622 | 0.146576 | 0.826257 | 2(Loss) | true |
| simdjson (ondemand) | 1613.26 | 0.192904 | 5815.97ms | 767297 | 640 | 4.89983e+08 | 453586 | 2.02629 | 1.53414 | 3(Loss) | true |
