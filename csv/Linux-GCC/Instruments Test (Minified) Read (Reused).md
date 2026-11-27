
----
### Instruments Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3366.46 | 0.459 | 3288.2ms | 108313 | 40 | 793415 | 30683.7 | 0.631074 | 0.734812 | 1(Win) | true |
| Jsonifier (two-stage) | 2739.45 | 0.17723 | 4020.08ms | 108313 | 1280 | 5.71635e+06 | 37706.6 | 0.362892 | 0.903105 | 2(Loss) | true |
| Glaze | 1741.69 | 0.0452424 | 6098.06ms | 108313 | 4890 | 3.52062e+06 | 59307.5 | 0.0375789 | 1.42085 | 3(Loss) | true |
| simdjson (reflection) | 1665.48 | 0.119629 | 6395.21ms | 108313 | 320 | 1.76158e+06 | 62021.3 | 0.200114 | 1.48589 | 4(Loss) | true |
| simdjson (ondemand) | 1331.01 | 0.129205 | 7922.17ms | 108313 | 640 | 6.43487e+06 | 77606.6 | 0.0946408 | 1.85944 | 5(Loss) | true |
