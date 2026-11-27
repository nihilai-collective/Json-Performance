
----
### Google Maps Response Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2040.08 | 0.0348814 | 1290.38ms | 11812 | 640 | 2374.22 | 5521.74 | 0.0923625 | 2.54451 | 12.795 | 2.40865 | 0.0057644 | 2.19586e-05 | 5.29123e-06 | 1(Win) | true |
| simdjson (ondemand) | 1737.4 | 0.0220269 | 1384.55ms | 11812 | 4890 | 9973.87 | 6483.71 | 0.0491375 | 2.97586 | 13.5196 | 2.33889 | 0.00619387 | 1.87671e-05 | 5.5401e-06 | 2(Loss) | true |
