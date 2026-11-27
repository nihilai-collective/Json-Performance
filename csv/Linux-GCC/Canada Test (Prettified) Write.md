
----
### Canada Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5617.99 | 0.133315 | 7179.88ms | 6661989 | 80 | 1.81842e+08 | 1.1309e+06 | 0.0157466 | 0.440677 | 1(Win) | true |
| Glaze | 3009.26 | 0.60845 | 6444.84ms | 6661897 | 30 | 4.95048e+09 | 2.11124e+06 | 0.550612 | 0.822637 | 2(Loss) | true |
| simdjson (reflection) | 435.272 | 0.269807 | 10293.7ms | 6661989 | 30 | 4.65279e+10 | 1.45963e+07 | 0.659403 | 5.68773 | 3(Loss) | true |
