
----
### Random Small Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3135.19 | 0.147167 | 978.066ms | 8150 | 80 | 1064.88 | 2479.1 | 0.0161323 | 1.67139 | 7.45252 | 1.3081 | 0.00277147 | 2.60736e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2567.19 | 0.120326 | 1033.35ms | 8150 | 160 | 2123.42 | 3027.61 | 0.0702366 | 2.02083 | 8.84761 | 1.38994 | 0.00392868 | 2.07055e-05 | 5.3681e-06 | 2(Loss) | true |
