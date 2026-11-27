
----
### Google Maps Response Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1804.2 | 0.040164 | 1364.96ms | 11812 | 2560 | 16098.6 | 6243.64 | 0.0380219 | 2.85452 | 13.5156 | 2.53268 | 0.00728523 | 2.39097e-05 | 7.27544e-06 | 1(Win) | true |
| simdjson (ondemand) | 1644.36 | 0.0419349 | 1418.5ms | 11812 | 2560 | 21127.5 | 6850.59 | 0.189985 | 3.12164 | 14.1921 | 2.33297 | 0.00735319 | 1.43194e-05 | 2.97632e-06 | 2(Loss) | true |
