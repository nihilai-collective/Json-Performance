
----
### Canada Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7599.91 | 0.044479 | 6918.18ms | 2090234 | 1280 | 1.74218e+07 | 262293 | 0.0581514 | 0.668476 | 3.18846 | 0.436419 | 0.00635833 | 0.0507149 | 5.77649e-06 | 1(Win) | true |
| simdjson (ondemand) | 7228.47 | 0.0615128 | 7257.48ms | 2090234 | 1280 | 3.68331e+07 | 275771 | 0.105561 | 0.703271 | 3.66628 | 0.418407 | 0.00285604 | 0.0508811 | 1.52159e-06 | 2(Loss) | true |
