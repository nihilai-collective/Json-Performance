
----
### Canada Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 733.679 | 0.22841 | 8555ms | 2090234 | 30 | 1.15539e+09 | 2.71699e+06 | 0.581436 | 6.95844 | 34.6585 | 6.57569 | 0.0232366 | 0.180947 | 0.000986572 | 1(Win) | true |
| Jsonifier (generic) | 696.097 | 0.34763 | 8900ms | 2090234 | 160 | 1.58564e+10 | 2.86369e+06 | 0.680584 | 7.35256 | 34.0008 | 7.02411 | 0.0218087 | 0.155829 | 0.000368918 | 2(Loss) | true |
