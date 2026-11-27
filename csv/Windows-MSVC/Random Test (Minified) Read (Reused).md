
----
### Random Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1082.64 | 0.289573 | 6471.58ms | 461466 | 30 | 4.15672e+07 | 406497 | 1.09009 | 2.28657 | 1(Win) | true |
| Jsonifier (two-stage) | 888.927 | 0.0969531 | 7592.41ms | 461466 | 640 | 1.47452e+08 | 495078 | 0.264863 | 2.78498 | 2(Loss) | true |
| Glaze | 769.224 | 0.302577 | 8657.94ms | 461466 | 40 | 1.19869e+08 | 572120 | 0.881828 | 3.21834 | 3(Loss) | true |
| simdjson (ondemand) | 600.728 | 0.183559 | 5320.85ms | 461466 | 80 | 1.44666e+08 | 732591 | 0.290076 | 4.12113 | 4(Loss) | true |
