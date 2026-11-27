
----
### Twitter Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 766.853 | 0.0524645 | 9007.89ms | 264040 | 1280 | 3.7989e+07 | 328366 | 0.0897903 | 6.6232 | 26.0929 | 4.74777 | 0.0225413 | 0.000184871 | 3.84441e-05 | 1(Win) | true |
| simdjson (ondemand) | 313.719 | 0.0975171 | 5218.04ms | 264040 | 320 | 1.96052e+08 | 802656 | 0.0876821 | 16.1387 | 62.9066 | 12.7577 | 0.090248 | 0.000309446 | 4.082e-05 | 2(Loss) | true |
