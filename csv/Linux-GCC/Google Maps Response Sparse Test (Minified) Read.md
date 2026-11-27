
----
### Google Maps Response Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2770.17 | 0.0765061 | 1153.44ms | 11812 | 4890 | 47330 | 4066.47 | 0.167261 | 1.86197 | 9.12834 | 1.62657 | 0.00181347 | 2.94837e-05 | 1.29846e-05 | 1(Win) | true |
| simdjson (ondemand) | 2058.03 | 0.159681 | 1299.18ms | 11812 | 160 | 12222.7 | 5473.58 | 0.0707304 | 2.48244 | 11.0704 | 1.86624 | 0.00334194 | 2.64561e-05 | 3.17474e-06 | 2(Loss) | true |
