
----
### Twitter Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6252.24 | 0.117523 | 6319.54ms | 360584 | 640 | 2.67402e+06 | 55001 | 0.193772 | 0.80533 | 4.18916 | 0.64613 | 0.00135327 | 1.48457e-05 | 1.17734e-05 | 1(Win) | true |
| simdjson (ondemand) | 5056.25 | 0.0386161 | 7624.37ms | 360584 | 1280 | 882879 | 68010.8 | 0.101311 | 0.99934 | 4.97595 | 0.700499 | 0.00191456 | 1.95451e-05 | 1.58164e-05 | 2(Loss) | true |
