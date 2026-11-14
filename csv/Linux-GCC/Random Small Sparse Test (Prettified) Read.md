
----
### Random Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3630.7 | 0.0514633 | 930.67ms | 8150 | 2560 | 3107.2 | 2140.76 | 0.00432474 | 1.44738 | 6.26479 | 1.00503 | 0.00136053 | 1.73505e-05 | 4.5533e-06 | 1(Win) | true |
| simdjson (ondemand) | 3264.23 | 0.0472326 | 964.098ms | 8150 | 160 | 202.375 | 2381.09 | 0.163269 | 1.60419 | 6.47571 | 0.991902 | 0.00171472 | 3.06748e-05 | 1.53374e-06 | 2(Loss) | true |
