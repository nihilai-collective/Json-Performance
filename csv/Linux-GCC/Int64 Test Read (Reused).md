
----
### Int64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1917.24 | 0.0891794 | 68.9153ms | 1313 | 80 | 27.1391 | 653.112 | 0.0592961 | 1.23978 | 1(Win) | true |
| simdjson (reflection) | 1066.57 | 0.0723322 | 122.688ms | 1313 | 40 | 28.8455 | 1174.03 | 0.0943155 | 2.26729 | 2(Loss) | true |
| Glaze | 980.922 | 0.0328513 | 131.327ms | 1313 | 640 | 112.55 | 1276.53 | 0.0161545 | 2.46996 | 3(Loss) | true |
| simdjson (ondemand) | 341.363 | 0.305947 | 371.863ms | 1313 | 640 | 80606.1 | 3668.16 | 0.0386071 | 7.19979 | 4(Loss) | true |
