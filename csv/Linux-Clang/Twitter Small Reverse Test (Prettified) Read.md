
----
### Twitter Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1046.46 | 0.0537267 | 1063.15ms | 3770 | 160 | 545.179 | 3435.73 | 0.0263703 | 4.98274 | 20.3992 | 3.79841 | 0.00161804 | 4.64191e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 477.946 | 0.0927506 | 1496.6ms | 3770 | 640 | 31155.7 | 7522.5 | 0.0566313 | 10.823 | 49.7037 | 8.5069 | 0.0105297 | 2.27951e-05 | 0 | 2(Loss) | true |
