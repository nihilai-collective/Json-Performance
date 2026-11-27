
----
### Twitter Small Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4584.7 | 0.124917 | 782.997ms | 2821 | 640 | 343.88 | 586.803 | 0.100753 | 1.19566 | 5.16164 | 0.832683 | 0.000930521 | 1.10776e-05 | 2.21553e-06 | 1(Win) | true |
| simdjson (ondemand) | 3712.59 | 0.0799625 | 792.891ms | 2821 | 4890 | 1641.85 | 724.647 | 0.147651 | 1.46376 | 6.18681 | 0.898972 | 0.000737385 | 5.1904e-05 | 3.07365e-05 | 2(Loss) | true |
