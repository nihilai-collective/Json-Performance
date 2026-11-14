
----
### Twitter Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4838.61 | 0.0880202 | 787.62ms | 3770 | 640 | 273.77 | 743.055 | 0.0679668 | 1.12184 | 4.56711 | 0.67878 | 0.000738975 | 2.32095e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 4294.91 | 0.0587394 | 800.957ms | 3770 | 4890 | 1182.34 | 837.119 | 0.0976286 | 1.25317 | 5.05252 | 0.700796 | 0.000648484 | 2.10466e-05 | 3.41736e-06 | 2(Loss) | true |
