
----
### Random Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1769.7 | 0.0444659 | 1027.46ms | 4926 | 4890 | 6813.2 | 2654.57 | 0.00787415 | 2.95317 | 12.9586 | 2.44214 | 0.00347868 | 4.08915e-05 | 1.40733e-05 | 1(Win) | true |
| simdjson (ondemand) | 1266.51 | 0.107838 | 1137.66ms | 4926 | 320 | 5119.91 | 3709.25 | 0.0275569 | 4.11086 | 15.9068 | 2.86216 | 0.00532823 | 4.88479e-05 | 1.64941e-05 | 2(Loss) | true |
