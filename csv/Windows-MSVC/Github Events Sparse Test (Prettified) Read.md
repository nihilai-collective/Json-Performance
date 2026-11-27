
----
### Github Events Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6212.59 | 0.159778 | 1022.44ms | 65103 | 320 | 81590.9 | 9993.75 | 0.249532 | 0.488082 | 1(Win) | true |
| simdjson (ondemand) | 5334.37 | 0.0883035 | 1184.36ms | 65103 | 2560 | 270416 | 11639.1 | 0.100583 | 0.568601 | 2(Loss) | true |
