
----
### CitmCatalog Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 4166.03 | 0.148079 | 7461.7ms | 1151920 | 160 | 2.43954e+07 | 263694 | 0.141709 | 0.594212 | 1(Win) | true |
| simdjson (ondemand) | 3706.1 | 0.0873312 | 8501.6ms | 1151920 | 640 | 4.28874e+07 | 296419 | 0.100099 | 0.66797 | 2(Loss) | true |
| Jsonifier | 3636.73 | 0.295281 | 8495.71ms | 1151920 | 40 | 3.18239e+07 | 302073 | 0.15553 | 0.680715 | 3(Loss) | true |
| simdjson (reflection) | 3494.4 | 0.152348 | 8802.52ms | 1151920 | 160 | 3.67025e+07 | 314377 | 0.0207119 | 0.708439 | 4(Loss) | true |
| Glaze | 2772.91 | 0.175231 | 5562.25ms | 1151920 | 80 | 3.85553e+07 | 396174 | 0.182883 | 0.892779 | 5(Loss) | true |
