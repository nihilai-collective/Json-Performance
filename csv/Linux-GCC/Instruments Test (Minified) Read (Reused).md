
----
### Instruments Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3502.46 | 0.200303 | 3116.66ms | 108313 | 640 | 2.23342e+06 | 29492.2 | 0.204128 | 0.706252 | 1(Win) | true |
| Jsonifier (two-stage) | 2681.82 | 0.501409 | 3923.1ms | 108313 | 40 | 1.49192e+06 | 38516.8 | 0.131869 | 0.922523 | 2(Loss) | true |
| Glaze | 1874.21 | 0.260832 | 5908.48ms | 108313 | 80 | 1.65323e+06 | 55114 | 0.0597947 | 1.32038 | 3(Loss) | true |
| simdjson (reflection) | 1581.66 | 0.0971502 | 6524.47ms | 108313 | 640 | 2.57634e+06 | 65308.2 | 0.13225 | 1.56469 | 4(Loss) | true |
| simdjson (ondemand) | 1169.04 | 0.341813 | 9413.85ms | 108313 | 80 | 7.29744e+06 | 88359.3 | 0.277973 | 2.11725 | 5(Loss) | true |
