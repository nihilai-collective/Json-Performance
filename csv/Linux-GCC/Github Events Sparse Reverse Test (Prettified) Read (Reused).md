
----
### Github Events Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6722.36 | 0.0505808 | 1665.82ms | 65103 | 30 | 654.714 | 9235.9 | 0.081139 | 0.755724 | 3.64441 | 0.556533 | 0.00126876 | 1.28002e-05 | 1.07522e-05 | 1(Win) | true |
| simdjson (ondemand) | 4922.07 | 0.0738172 | 2026.35ms | 65103 | 40 | 3468.02 | 12614 | 0.0737157 | 1.05014 | 4.94086 | 0.766263 | 0.0020122 | 1.49763e-05 | 1.22882e-05 | 2(Loss) | true |
