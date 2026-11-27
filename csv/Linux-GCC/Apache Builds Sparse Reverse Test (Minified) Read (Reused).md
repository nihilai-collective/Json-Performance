
----
### Apache Builds Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2393.22 | 0.025472 | 5008.07ms | 94653 | 2560 | 236304 | 37718.3 | 0.0899607 | 2.12776 | 10.4805 | 1.99093 | 0.00553168 | 1.55543e-05 | 1.12252e-05 | 1(Win) | true |
| simdjson (ondemand) | 1855.3 | 0.022 | 6089.18ms | 94653 | 2560 | 293310 | 48654.3 | 0.00835143 | 2.75764 | 11.3965 | 2.08434 | 0.00860629 | 5.4434e-06 | 1.95616e-06 | 2(Loss) | true |
