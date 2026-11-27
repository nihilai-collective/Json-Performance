
----
### Random Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2640.6 | 0.055952 | 7930.74ms | 409725 | 160 | 1.09681e+06 | 147975 | 0.00527931 | 1.9141 | 8.99136 | 1.64189 | 0.00640678 | 5.83776e-05 | 6.84911e-06 | 1(Win) | true |
| simdjson (ondemand) | 1981.76 | 0.043969 | 5173.79ms | 409725 | 80 | 601267 | 197170 | 0.151087 | 2.55105 | 10.7131 | 1.82774 | 0.00828095 | 0.00112197 | 5.73861e-05 | 2(Loss) | true |
