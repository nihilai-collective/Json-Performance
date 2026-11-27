
----
### Discord Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 778.674 | 0.030597 | 7995.02ms | 56369 | 2560 | 1.14227e+06 | 69037.5 | 0.246786 | 6.51102 | 31.8698 | 6.59187 | 0.00978025 | 4.22578e-05 | 2.78577e-05 | 1(Win) | true |
| simdjson (ondemand) | 199.8 | 0.0527752 | 7172.76ms | 56369 | 640 | 1.29042e+07 | 269058 | 0.0452988 | 25.4525 | 130.771 | 27.8026 | 0.033659 | 6.6221e-05 | 4.01096e-05 | 2(Loss) | true |
