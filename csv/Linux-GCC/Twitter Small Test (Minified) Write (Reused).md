
----
### Twitter Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 10849.6 | 0.0544652 | 746.171ms | 2963 | 1280 | 25.7563 | 260.446 | 0.0830216 | 0.548246 | 1.31455 | 0.195748 | 0.000337759 | 2.42575e-05 | 1.08104e-05 | 1(Win) | true |
| simdjson (reflection) | 7440.68 | 0.118847 | 759.937ms | 2963 | 160 | 32.594 | 379.769 | 0.140084 | 0.753736 | 1.75363 | 0.251434 | 0.000337496 | 8.43739e-06 | 0 | 2(Loss) | true |
| Glaze | 6695.59 | 0.12659 | 764.81ms | 2963 | 2560 | 730.679 | 422.029 | 0.0235969 | 0.830407 | 2.53156 | 0.365171 | 0.000337891 | 6.16984e-05 | 2.58395e-05 | 3(Loss) | true |
