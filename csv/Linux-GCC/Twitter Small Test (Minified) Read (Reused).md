
----
### Twitter Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2626.36 | 0.0683711 | 832.928ms | 2821 | 160 | 78.4805 | 1024.35 | 0 | 2.03609 | 7.57249 | 1.30946 | 0.000381071 | 2.21553e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2147.2 | 0.0822517 | 850.224ms | 2821 | 2560 | 2718.88 | 1252.94 | 0.0123787 | 2.46768 | 9.04927 | 1.45197 | 0.000361408 | 4.84646e-05 | 9.96987e-06 | 2(Loss) | true |
