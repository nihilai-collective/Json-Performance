
----
### Twitter Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4214.24 | 0.0953701 | 787.054ms | 2821 | 160 | 59.308 | 638.388 | 0.0528955 | 1.29448 | 5.43283 | 0.868132 | 0.000759926 | 1.32932e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 3608.65 | 0.0663458 | 789.276ms | 2821 | 640 | 156.576 | 745.519 | 0.183514 | 1.48558 | 6.25417 | 0.901453 | 0.000914459 | 1.27393e-05 | 1.10776e-06 | 2(Loss) | true |
