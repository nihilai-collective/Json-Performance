
----
### Canada Small Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5738.69 | 0.07681 | 792.586ms | 4630 | 320 | 111.769 | 769.428 | 0.232448 | 0.932235 | 5.02851 | 0.827862 | 0.000649973 | 5.39957e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 5147.36 | 0.0697667 | 802.751ms | 4630 | 4890 | 1751.45 | 857.821 | 0.245451 | 1.04726 | 5.55378 | 0.812959 | 0.000656649 | 1.8374e-05 | 6.31606e-06 | 2(Loss) | true |
