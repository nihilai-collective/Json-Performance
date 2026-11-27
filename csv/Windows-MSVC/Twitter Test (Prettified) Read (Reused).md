
----
### Twitter Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2175.86 | 0.461529 | 8041.09ms | 631514 | 1280 | 2.08886e+09 | 276791 | 0.173123 | 1.3966 | 1(Win) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 1915.05 | 0.548125 | 9106.91ms | 631514 | 640 | 1.90172e+09 | 314488 | 0.55028 | 1.58674 | 2(Tie) | true |
| Glaze STATISTICAL TIE | 1903.15 | 1.15228 | 9514.36ms | 631514 | 320 | 4.25486e+09 | 316453 | 2.28206 | 1.59684 | 2(Tie) | true |
| simdjson (ondemand) | 1589.52 | 0.290921 | 5315.99ms | 631514 | 640 | 7.77615e+08 | 378893 | 0.936557 | 1.91192 | 4(Loss) | true |
