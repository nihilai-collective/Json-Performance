
----
### Github Events Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6771.55 | 0.0563771 | 959.124ms | 65103 | 4890 | 130659 | 9168.81 | 0.333689 | 0.447615 | 1(Win) | true |
| simdjson (ondemand) | 6167.6 | 0.139201 | 1059.54ms | 65103 | 1280 | 251341 | 10066.6 | 0.103112 | 0.491592 | 2(Loss) | true |
