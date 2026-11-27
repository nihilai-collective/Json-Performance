
----
### CitmCatalog Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2213.89 | 0.0931818 | 895.87ms | 3223 | 4890 | 8184.25 | 1388.37 | 0.234525 | 2.35591 | 9.63668 | 1.76823 | 0.0011454 | 7.18887e-05 | 2.22709e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 1608.32 | 0.305753 | 947.229ms | 3223 | 4890 | 166964 | 1911.11 | 0.0991122 | 3.21336 | 13.3692 | 2.20571 | 0.00111488 | 4.77778e-05 | 7.55054e-06 | 2(Loss) | true |
| Glaze | 1590.2 | 0.134275 | 954.557ms | 3223 | 640 | 4311.11 | 1932.9 | 0.232914 | 3.24931 | 13.4353 | 2.45206 | 0.00112182 | 3.24814e-05 | 3.87837e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1105.23 | 0.179826 | 1034.2ms | 3223 | 1280 | 32013.2 | 2781.04 | 0.249954 | 4.64296 | 17.9231 | 2.7189 | 0.00157923 | 5.69636e-05 | 1.16351e-05 | 4(Loss) | true |
