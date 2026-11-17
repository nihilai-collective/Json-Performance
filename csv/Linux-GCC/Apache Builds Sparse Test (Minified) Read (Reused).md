
----
### Apache Builds Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3304.5 | 0.0412228 | 3965.77ms | 94653 | 4890 | 620071 | 27316.7 | 0.0180563 | 1.52936 | 7.72976 | 1.27821 | 0.00324509 | 3.21484e-06 | 7.19451e-07 | 1(Win) | true |
| simdjson (ondemand) | 2104.96 | 0.109083 | 5451.52ms | 94653 | 160 | 350116 | 42883.4 | 0.0324531 | 2.40817 | 8.84344 | 1.54555 | 0.0080533 | 3.16947e-06 | 6.60307e-07 | 2(Loss) | true |
