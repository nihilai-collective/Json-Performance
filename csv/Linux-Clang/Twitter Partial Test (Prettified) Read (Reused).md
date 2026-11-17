
----
### Twitter Partial Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 11077.5 | 0.083321 | 5551.8ms | 631514 | 2560 | 5.25329e+06 | 54367.7 | 0.300217 | 0.223359 | 1(Win) | true |
| Jsonifier | 10960 | 0.173742 | 5603.94ms | 631514 | 640 | 5.83361e+06 | 54950.8 | 0.0650472 | 0.225756 | 2(Loss) | true |
| simdjson (ondemand) | 8755.26 | 0.147378 | 7079.04ms | 631514 | 1280 | 1.31554e+07 | 68788.2 | 0.539366 | 0.282605 | 3(Loss) | true |
| Glaze | 3970.37 | 0.111956 | 7794.71ms | 631514 | 640 | 1.84578e+07 | 151688 | 0.585316 | 0.623459 | 4(Loss) | true |
