
----
### Github Events Small Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6069.09 | 0.107302 | 745.319ms | 2158 | 320 | 42.3661 | 339.1 | 0.0165853 | 0.948752 | 3.54495 | 0.491196 | 0.00092244 | 1.15848e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 5220.9 | 0.100888 | 755.524ms | 2158 | 640 | 101.222 | 394.191 | 0.128263 | 1.08943 | 4.01669 | 0.519928 | 0.000898546 | 1.3757e-05 | 4.3443e-06 | 2(Loss) | true |
