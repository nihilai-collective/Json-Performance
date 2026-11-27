
----
### Discord Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1768.99 | 0.0276741 | 4128.02ms | 56369 | 2560 | 181058 | 30389 | 0.0398642 | 2.89522 | 13.185 | 2.45502 | 0.00546996 | 1.33953e-05 | 7.99004e-06 | 1(Win) | true |
| simdjson (ondemand) | 1408.8 | 0.0310197 | 4940.93ms | 56369 | 2560 | 358672 | 38158.5 | 0.110789 | 3.61631 | 14.6952 | 2.3474 | 0.0136766 | 1.9438e-05 | 1.17668e-05 | 2(Loss) | true |
