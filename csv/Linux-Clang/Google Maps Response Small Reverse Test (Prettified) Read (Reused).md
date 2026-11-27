
----
### Google Maps Response Small Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1630.43 | 0.107298 | 1308.35ms | 9378 | 40 | 1385.68 | 5485.4 | 0.0437717 | 3.18379 | 13.99 | 2.7315 | 0.00595543 | 1.59949e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 1488.24 | 0.0551271 | 1341.53ms | 9378 | 1280 | 14048 | 6009.49 | 0.00808683 | 3.43688 | 15.1747 | 2.68 | 0.005217 | 1.8744e-05 | 4.33195e-06 | 2(Loss) | true |
