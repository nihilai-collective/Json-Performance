
----
### Marine IK Small Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7222.4 | 0.142162 | 253.918ms | 18245 | 1280 | 15014.1 | 2409.14 | 0.0615764 | 0.417134 | 1(Win) | true |
| simdjson (ondemand) | 5815.38 | 0.189372 | 317.453ms | 18245 | 640 | 20546.7 | 2992.03 | 0.0888564 | 0.519334 | 2(Loss) | true |
