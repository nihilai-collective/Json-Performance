
----
### Canada Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2187.06 | 0.0780813 | 1319.44ms | 11579 | 40 | 621.69 | 5049.05 | 0.0128754 | 2.37451 | 11.6825 | 1.8708 | 0.00138613 | 8.63632e-06 | 0 | 1(Win) | true |
| Jsonifier (generic) | 2086.54 | 0.0284879 | 1346.13ms | 11579 | 4890 | 11115.3 | 5292.31 | 0.0924873 | 2.48531 | 11.8656 | 2.17782 | 0.00181739 | 1.87739e-05 | 6.83488e-06 | 2(Loss) | true |
