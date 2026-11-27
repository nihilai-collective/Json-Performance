
----
### Google Maps Response Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1957.55 | 0.036858 | 1311.26ms | 11812 | 4890 | 21998.7 | 5754.55 | 0.137018 | 2.62267 | 12.9768 | 2.45386 | 0.00639894 | 2.47746e-05 | 8.39672e-06 | 1(Win) | true |
| simdjson (ondemand) | 1687.02 | 0.0532797 | 1394.2ms | 11812 | 640 | 8100.45 | 6677.32 | 0.0165232 | 3.06993 | 13.7276 | 2.38876 | 0.00682899 | 1.91807e-05 | 4.49754e-06 | 2(Loss) | true |
