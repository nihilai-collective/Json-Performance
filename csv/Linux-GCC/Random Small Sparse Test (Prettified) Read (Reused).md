
----
### Random Small Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4519.8 | 0.0913908 | 902.384ms | 8150 | 160 | 395.187 | 1719.64 | 0.0498171 | 1.16633 | 5.30049 | 0.854724 | 0.000931748 | 9.96933e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 3661.59 | 0.0518414 | 940.157ms | 8150 | 4890 | 5921.6 | 2122.7 | 0.0464286 | 1.43196 | 6.09951 | 0.906626 | 0.000975222 | 3.84157e-05 | 2.05252e-05 | 2(Loss) | true |
