
----
### Google Maps Response Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1788.67 | 0.0376902 | 1356.83ms | 11812 | 2560 | 14424 | 6297.88 | 0.0444357 | 2.89545 | 13.6771 | 2.58576 | 0.00727432 | 4.15031e-05 | 2.52325e-05 | 1(Win) | true |
| simdjson (ondemand) | 1656.94 | 0.0423694 | 1400.64ms | 11812 | 1280 | 10620.6 | 6798.55 | 0.151652 | 3.12443 | 13.95 | 2.42889 | 0.00753954 | 3.04246e-05 | 1.04502e-05 | 2(Loss) | true |
