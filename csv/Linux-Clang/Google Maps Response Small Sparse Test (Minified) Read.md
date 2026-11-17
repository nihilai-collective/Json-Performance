
----
### Google Maps Response Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2095.77 | 0.113135 | 915.624ms | 4390 | 160 | 817.246 | 1997.66 | 0.067846 | 2.46905 | 10.7417 | 1.97585 | 0.00227648 | 4.98292e-05 | 2.98975e-05 | 1(Win) | true |
| simdjson (ondemand) | 1976.3 | 0.104355 | 928.2ms | 4390 | 640 | 3127.74 | 2118.42 | 0.0382212 | 2.65142 | 11.8565 | 1.89932 | 0.00134325 | 3.59482e-05 | 8.54214e-06 | 2(Loss) | true |
