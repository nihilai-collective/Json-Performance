
----
### Twitter Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5445.8 | 0.138638 | 762.231ms | 2821 | 4890 | 2293.82 | 494.017 | 0.0360115 | 1.02116 | 3.90961 | 0.502659 | 0.000711288 | 2.50821e-05 | 7.32166e-06 | 1(Win) | true |
| simdjson (ondemand) | 5371.77 | 0.0826803 | 762.139ms | 2821 | 4890 | 838.463 | 500.825 | 0.2811 | 1.03805 | 4.15881 | 0.455158 | 0.000424801 | 2.92141e-05 | 2.6097e-06 | 2(Loss) | true |
