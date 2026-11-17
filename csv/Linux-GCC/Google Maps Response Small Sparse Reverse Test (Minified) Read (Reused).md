
----
### Google Maps Response Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1750.05 | 0.160949 | 967.595ms | 4390 | 320 | 4744.12 | 2392.29 | 0.127001 | 2.98907 | 13.508 | 2.52119 | 0.00351865 | 2.06435e-05 | 7.8303e-06 | 1(Win) | true |
| simdjson (ondemand) | 1679.42 | 0.0735993 | 975.227ms | 4390 | 80 | 269.306 | 2492.9 | 0.087324 | 3.11807 | 13.7626 | 2.36515 | 0.004291 | 5.69476e-05 | 2.56264e-05 | 2(Loss) | true |
