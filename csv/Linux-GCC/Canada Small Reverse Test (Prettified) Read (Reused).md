
----
### Canada Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1995.04 | 0.0384376 | 1364.09ms | 11579 | 4890 | 22134.1 | 5535.03 | 0.0478441 | 2.60314 | 13.2023 | 2.28595 | 0.000862749 | 2.92999e-05 | 1.35638e-05 | 1(Win) | true |
| Jsonifier (generic) | 1810.29 | 0.0812864 | 1427.67ms | 11579 | 40 | 983.426 | 6099.9 | 0.0895387 | 2.86468 | 12.8288 | 2.449 | 0.00336385 | 3.45453e-05 | 1.29545e-05 | 2(Loss) | true |
