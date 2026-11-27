
----
### Apache Builds Small Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3618.05 | 0.059812 | 807.502ms | 3370 | 4890 | 1380.37 | 888.291 | 0.0171097 | 1.48612 | 6.5819 | 1.12938 | 0.000893242 | 2.16029e-05 | 7.52459e-06 | 1(Win) | true |
| simdjson (ondemand) | 3034.75 | 0.0701582 | 825.101ms | 3370 | 1280 | 706.614 | 1059.03 | 0.153678 | 1.76185 | 7.04629 | 1.16053 | 0.00102304 | 2.22552e-05 | 2.55007e-06 | 2(Loss) | true |
