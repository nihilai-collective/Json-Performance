
----
### Apache Builds Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1868.2 | 0.0357557 | 8334.23ms | 124597 | 2560 | 1.32404e+06 | 63604.1 | 0.0104585 | 2.71538 | 13.3278 | 2.60816 | 0.00576735 | 1.23774e-05 | 8.10739e-06 | 1(Win) | true |
| simdjson (ondemand) | 1065.44 | 0.0795999 | 6703ms | 124597 | 320 | 2.5219e+06 | 111526 | 0.258641 | 4.77058 | 23.7577 | 4.65681 | 0.00730335 | 5.43251e-05 | 4.8682e-05 | 2(Loss) | true |
