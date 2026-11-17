
----
### Random Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1397.99 | 0.0872016 | 6542.89ms | 676745 | 640 | 1.03722e+08 | 461659 | 0.0239049 | 3.60205 | 16.5733 | 3.28339 | 0.00570284 | 0.0134517 | 1.71339e-05 | 1(Win) | true |
| simdjson (ondemand) | 861.211 | 0.0556091 | 5070.92ms | 676745 | 320 | 5.5574e+07 | 749403 | 0.0331333 | 5.9093 | 26.9902 | 5.30155 | 0.0167038 | 0.0205139 | 3.37415e-05 | 2(Loss) | true |
