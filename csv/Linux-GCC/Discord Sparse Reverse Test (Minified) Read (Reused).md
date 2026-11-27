
----
### Discord Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2222.09 | 0.132291 | 3435.08ms | 56369 | 80 | 81941.7 | 24192.3 | 0.0465323 | 2.27585 | 11.2854 | 2.11077 | 0.00309745 | 2.04013e-05 | 1.37487e-05 | 1(Win) | true |
| simdjson (ondemand) | 1515.8 | 0.0172142 | 4568.35ms | 56369 | 4890 | 182256 | 35464.9 | 0.081451 | 3.3769 | 15.0507 | 2.63772 | 0.0103514 | 3.57308e-05 | 2.58231e-05 | 2(Loss) | true |
